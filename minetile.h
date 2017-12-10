#ifndef MINETILE_H
#define MINETILE_H

#include <QObject>
#include <QGraphicsRectItem>

#include "minedata.h"

class MineTile : public QGraphicsRectItem
{
public:
    MineTile();
    virtual	~MineTile();

    char getDisplayVal();
    QPoint getPos();

public slots:
    void setDisplayState(bool _isCovered = false); // left click
    void setFlag(char _flag); //right click

protected:
    void virtual paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


private:
    char m_displayVal; //'1'-'9','^','?','0'=None

    unsigned m_locx;
    unsigned m_locy;
    MineData m_data;

};

#endif // MINETILE_H
