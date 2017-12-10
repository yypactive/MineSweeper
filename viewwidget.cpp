#include "viewwidget.h"

ViewWidget::ViewWidget(QWidget *parent) : QWidget(parent)
{
    m_scene = new QGraphicsScene(this);
    m_view = new View(m_scene, this);
    m_mineMatrix.reset(new MineTileMatrix(m_scene));

    initMatrix();
}

void ViewWidget::initMatrix()
{
  m_mineMatrix->init(MineTileMatrix::ms_col,
                     MineTileMatrix::ms_col,
                     MineTileMatrix::ms_amount);
}
