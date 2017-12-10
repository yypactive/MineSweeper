#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>

#include <memory>

#include "view.h"
#include "minetilematrix.h"

class ViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWidget(QWidget *parent = 0);

    void initMatrix();

public:
    using MineTileMatrixPtr = std::unique_ptr<MineTileMatrix>;

public slots:

private:
    View * m_view;
    QGraphicsScene * m_scene;

    MineTileMatrixPtr m_mineMatrix;
};

#endif // VIEWWIDGET_H
