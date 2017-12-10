#ifndef MINETILE_H
#define MINETILE_H

#include <QObject>
#include <QtGui>
#include <QGraphicsRectItem>
#include <memory>
#include "minedata.h"

class MineTile : public QGraphicsRectItem
{
public:
    using MineDataPtr = std::shared_ptr<MineData>;
    static const qreal ms_width;
    static const qreal ms_height;

public:
    MineTile();
    virtual	~MineTile();

    void setData(MineDataPtr _data);
    void setPhyPos(QPointF _p);

    char getDisplayVal();
    char getVal();
    QPointF getPos();
    QPoint getLogicPos();
    unsigned getIndexX();
    unsigned getIndexY();

public slots:
    void setDisplayState(bool _isCovered = false); // left click
    void setFlag(char _flag); //right click

protected:
    void virtual paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


private:
    char m_displayVal; //'1'-'9','^','?','0'=None
    bool m_isCovered;

    qreal m_phx;
    qreal m_phy;
    MineDataPtr m_data;

};

#endif // MINETILE_H
