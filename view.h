#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "minetile.h"

class View : public QGraphicsView
{
public:
    View(QGraphicsScene * _scene, QWidget *parent = Q_NULLPTR);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // VIEW_H
