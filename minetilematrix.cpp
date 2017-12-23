#include "minetilematrix.h"

const qreal MineTileMatrix::ms_space = 3.;

MineTileMatrix::MineTileMatrix(QGraphicsScene * _scene)
    : m_scene(_scene),
      m_mineTileMatrix(0),
      m_mineMgr(),
      m_width(0), m_height(0),
      m_firstStep(true), m_mineAmount(0)
{

}

void MineTileMatrix::init(unsigned _row, unsigned _col, unsigned _amount)
{
    clear();
    m_mineMgr.init(_row, _col, _amount);
    m_mineMgr.initMine();

    m_mineAmount = _amount;

    m_mineTileMatrix.reserve(_row);
    for (unsigned i = 0; i < _row; ++i)
    {
        std::vector <MineTilePtr> tileVec;
        tileVec.reserve(_col);
        for (unsigned j = 0; j < _col; ++j)
        {
            tileVec.emplace_back(std::make_unique<MineTile>());
        }
        m_mineTileMatrix.push_back(std::move(tileVec));
    }
    for (unsigned i = 0; i < _row; ++i)
    {
        for (unsigned j = 0; j < _col; ++j)
        {
            m_mineTileMatrix[i][j]->setData(m_mineMgr.getMineData(i, j));
            m_mineTileMatrix[i][j]->setPos(
                        QPointF(j * (MineTile::ms_width + MineTileMatrix::ms_space) + 1 * MineTileMatrix::ms_space,
                                i * (MineTile::ms_height + MineTileMatrix::ms_space) + 1 * MineTileMatrix::ms_space)
                        );
        }
    }
    initConnect();

    m_width = _col * (MineTile::ms_width + MineTileMatrix::ms_space) + 1 * MineTileMatrix::ms_space;
    m_height = _row * (MineTile::ms_height + MineTileMatrix::ms_space) + 1 * MineTileMatrix::ms_space;

    CountFlag();
}

void MineTileMatrix::clear()
{
    m_mineTileMatrix.clear();
}

void MineTileMatrix::addToScene()
{
    for (unsigned i = 0; i < m_mineTileMatrix.size(); ++i)
    {
        for (unsigned j = 0; j < m_mineTileMatrix[0].size(); ++j)
        {
            m_scene->addItem(m_mineTileMatrix[i][j].get());
        }
    }
}

qreal MineTileMatrix::getWidth()
{
    return m_width;
}

qreal MineTileMatrix::getHeight()
{
    return m_height;
}

void MineTileMatrix::onTileClickedHandle(QPoint _cp, bool _isShift)
{
    if (m_firstStep)
    {
        m_firstStep = false;
        emit startStopWatch();
        m_mineMgr.assignMine(_cp.y(), _cp.x());
        m_mineMgr.calVal();
        m_mineTileMatrix[_cp.y()][_cp.x()]->update();
    }
    if (m_mineTileMatrix[_cp.y()][_cp.x()]->getMine())
    {
        failure();
    }
    else if (m_mineTileMatrix[_cp.y()][_cp.x()]->getVal() == '0')
    {
        // when '0'
        std::vector<QPoint> vec = std::move(getNeighborVec(_cp));
        while (!vec.empty())
        {
            QPoint point = vec.back();
            vec.pop_back();
            if (!m_mineTileMatrix[point.y()][point.x()]->getCovered())
                continue;
            m_mineTileMatrix[point.y()][point.x()]->setDisplayState(false);
            if (m_mineTileMatrix[point.y()][point.x()]->getVal() == '0')
            {
                std::vector<QPoint> newVec = std::move(getNeighborVec(point));
                vec.insert(vec.begin(), newVec.begin(), newVec.end());
            }
        }
    }
    if (_isShift)
    {
        // auto clicked error
        std::vector<QPoint> vec = std::move(getNeighborVec(_cp));
        unsigned flagCount = getNeighborFlag(_cp);
        // unsigned questCount = getNeighborQuest(_cp);
        if (flagCount == (m_mineTileMatrix[_cp.y()][_cp.x()]->getDisplayVal() - '0')
                )// && questCount == 0)
        {
            std::for_each(vec.begin(), vec.end(),
                          [&](QPoint & p)
            {
                m_mineTileMatrix[p.y()][p.x()]->setDisplayState(false);
                onTileClickedHandle(p, false);
            });
        }
    }
    if (countCovered() == m_mineAmount)
    {
        success();
    }
}

void MineTileMatrix::CountFlag()
{
    unsigned sum = 0;
    for (unsigned i = 0; i < m_mineTileMatrix.size(); ++i)
    {
        for (unsigned j = 0; j < m_mineTileMatrix[i].size(); ++j)
        {
            auto & tilePtr = m_mineTileMatrix[i][j];
            if (tilePtr->getCovered() && tilePtr->getDisplayVal() == '^')
                sum++;
        }
    }
    emit setFlagCount(m_mineAmount - sum);
}

void MineTileMatrix::initConnect()
{
    // init connect
    for (unsigned i = 0; i < m_mineTileMatrix.size(); ++i)
    {
        for (unsigned j = 0; j < m_mineTileMatrix[i].size(); ++j)
        {
            connect(m_mineTileMatrix[i][j].get(),
                    SIGNAL(tileClicked(QPoint, bool)),
                    this,
                    SLOT(onTileClickedHandle(QPoint, bool))
                           );
            connect(m_mineTileMatrix[i][j].get(),
                    SIGNAL(tileFlagChange(bool)),
                    this,
                    SLOT(CountFlag())
                           );
        }
    }

}

std::vector<QPoint> MineTileMatrix::getNeighborVec(QPoint _p)
{
    std::vector<QPoint> pvec;
    int x = _p.x();
    int y = _p.y();
    int row = m_mineTileMatrix.size();
    int col = 0;
    if (row)
        col = m_mineTileMatrix[0].size();
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (y + i >= 0 && y + i < row && x +j >= 0 && x + j < col && (i | j))
            {
                auto & tilePtr = m_mineTileMatrix[y+i][x+j];
                if (tilePtr->getCovered() && tilePtr->getDisplayVal() == '0')
                    pvec.push_back(std::move(QPoint(x+j, y+i)));
            }
        }
    }
    return pvec;
}

unsigned MineTileMatrix::getNeighborFlag(QPoint _p)
{
    int x = _p.x();
    int y = _p.y();
    int row = m_mineTileMatrix.size();
    int col = 0;
    if (row)
        col = m_mineTileMatrix[0].size();
    unsigned sum = 0;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (y + i >= 0 && y + i < row && x +j >= 0 && x + j < col && (i | j))
            {
                auto & tilePtr = m_mineTileMatrix[y+i][x+j];
                if (tilePtr->getCovered() && tilePtr->getDisplayVal() == '^')
                    sum ++;
            }
        }
    }
    return sum;
}

unsigned MineTileMatrix::getNeighborQuest(QPoint _p)
{
    int x = _p.x();
    int y = _p.y();
    int row = m_mineTileMatrix.size();
    int col = 0;
    if (row)
        col = m_mineTileMatrix[0].size();
    unsigned sum = 0;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (y + i >= 0 && y + i < row && x +j >= 0 && x + j < col && (i | j))
            {
                auto & tilePtr = m_mineTileMatrix[y+i][x+j];
                if (tilePtr->getCovered() && tilePtr->getDisplayVal() == '?')
                    sum ++;
            }
        }
    }
    return sum;
}


unsigned MineTileMatrix::countCovered()
{
    unsigned sum = 0;
    for (unsigned i = 0; i < m_mineTileMatrix.size(); ++i)
    {
        for (unsigned j = 0; j < m_mineTileMatrix[i].size(); ++j)
        {
            if (m_mineTileMatrix[i][j]->getCovered())
                ++ sum;
        }
    }
    return sum;
}

void MineTileMatrix::success()
{
    // success
    // qDebug() << "Success!!";
    checkMine();
    emit sendSucc();
}

void MineTileMatrix::failure()
{
    // boom!!
    // qDebug() << "Failure!!";
    checkMine();
    emit sendFail();
}

void MineTileMatrix::checkMine()
{
    for (unsigned i = 0; i < m_mineTileMatrix.size(); ++i)
    {
        for (unsigned j = 0; j < m_mineTileMatrix[i].size(); ++j)
        {
            m_mineTileMatrix[i][j]->setChecked(true);
            m_mineTileMatrix[i][j]->update();
        }
    }
}
