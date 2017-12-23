#include "viewwidget.h"

const qreal ViewWidget::ms_frameW = 10;

ViewWidget::ViewWidget(QWidget *parent) : QWidget(parent)
{
    m_scene = new QGraphicsScene(this);
    m_view = new View(m_scene, this);
    m_scene->setBackgroundBrush(QBrush(QColor(220,220,220,255)));
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_view->setWindowFlags(Qt::FramelessWindowHint);
}

void ViewWidget::newGame(unsigned _row, unsigned _col, unsigned _amount)
{
    clearAll();
    initMatrix(_row, _col, _amount);
    m_scene->setSceneRect(0, 0, m_mineMatrix->getWidth(), m_mineMatrix->getHeight());
    // m_view->scale(.95, .95);
    m_view->setFixedSize(m_mineMatrix->getWidth() + 2 * ms_frameW, m_mineMatrix->getHeight() + 2 * ms_frameW);
    setFixedSize(m_mineMatrix->getWidth() + 2 * ms_frameW, m_mineMatrix->getHeight() + 2 * ms_frameW);
    update();
}

void ViewWidget::initMatrix(unsigned _row, unsigned _col, unsigned _amount)
{
    m_mineMatrix.reset(new MineTileMatrix(m_scene));
    m_mineMatrix->init(_row, _col, _amount);
    m_mineMatrix->addToScene();
    initConnect();
}

void ViewWidget::initConnect()
{
    connect(m_mineMatrix.get(),
            SIGNAL(startStopWatch()),
            this,
            SIGNAL(startStopWatch())
                   );
    connect(m_mineMatrix.get(),
            SIGNAL(sendSucc()),
            this,
            SIGNAL(sendSucc())
                   );
    connect(m_mineMatrix.get(),
            SIGNAL(sendFail()),
            this,
            SIGNAL(sendFail())
                   );
    connect(m_mineMatrix.get(),
            SIGNAL(setFlagCount(unsigned)),
            this,
            SIGNAL(setFlagCount(unsigned))
            );
}

void ViewWidget::clearAll()
{
    // sth to do
}
