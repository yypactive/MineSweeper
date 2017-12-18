#include "view.h"

View::View(QGraphicsScene * _scene, QWidget *parent)
    : QGraphicsView(_scene, parent)
{

}

void View::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->pos());
    if (dynamic_cast<MineTile *>(item))
    {
        dynamic_cast<MineTile *>(item)->onMousePressEventHandle(event);
    }
    QGraphicsView::mousePressEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->pos());
    if (dynamic_cast<MineTile *>(item))
    {
        dynamic_cast<MineTile *>(item)->onMouseReleaseEventHandle(event);
    }
    QGraphicsView::mouseReleaseEvent(event);
}
