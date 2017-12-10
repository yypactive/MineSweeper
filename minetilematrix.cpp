#include "minetilematrix.h"

const qreal MineTileMatrix::ms_space = 10.;

MineTileMatrix::MineTileMatrix(QGraphicsScene * _scene)
    : m_scene(_scene),
      m_mineTileMatrix(0)
{

}

void MineTileMatrix::init(unsigned _row, unsigned _col, unsigned _amount)
{
    clear();
    m_mineMgr.init(_row, _col, _amount);
    m_mineMgr.initMine();

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
                        QPointF(j * (MineTile::ms_width + MineTileMatrix::ms_space),
                                i * (MineTile::ms_height + MineTileMatrix::ms_space))
                        );
        }
    }
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
