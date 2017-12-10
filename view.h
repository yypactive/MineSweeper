#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>

class View : public QGraphicsView
{
public:
    View(QGraphicsScene * _scene, QWidget *parent = Q_NULLPTR);
};

#endif // VIEW_H
