#include "viewwidget.h"

ViewWidget::ViewWidget(QWidget *parent) : QWidget(parent)
{
    m_scene = new QGraphicsScene(this);
    m_view = new View(m_scene, this);
    m_mineMatrix.reset(new MineTileMatrix(m_scene));
    initMatrix();
    m_scene->setBackgroundBrush(QBrush(QColor(230,230,230,255)));
    m_scene->setSceneRect(0, 0, m_mineMatrix->getWidth(), m_mineMatrix->getHeight());
    m_view->scale(.95, .95);
    m_view->setFixedSize(m_mineMatrix->getWidth(), m_mineMatrix->getHeight());
    setFixedSize(m_mineMatrix->getWidth(), m_mineMatrix->getHeight());
    update();
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_view->setWindowFlags(Qt::FramelessWindowHint);
}

void ViewWidget::newGame()
{
    clearAll();
    initMatrix();
}

void ViewWidget::initMatrix()
{
  m_mineMatrix->init(MineTileMatrix::ms_col,
                     MineTileMatrix::ms_col,
                     MineTileMatrix::ms_amount);
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
