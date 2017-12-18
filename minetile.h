#ifndef MINETILE_H
#define MINETILE_H

#include <QObject>
#include <QtGui>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QHoverEvent>
#include <QGraphicsRectItem>
#include <memory>
#include "minedata.h"

class MineTile : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    using MineDataPtr = std::shared_ptr<MineData>;
    static const qreal ms_width;
    static const qreal ms_height;
    static const qreal ms_fontSize;
    static const qreal ms_shadowDepth;
    static const unsigned ms_hoverColor;
    static const unsigned ms_backColor;
    static const unsigned ms_frontColor;
    static const unsigned ms_hlColor;
    static const unsigned ms_shColor;
    static QPoint ms_clickedTile;

public:
    MineTile();
    virtual	~MineTile();

    void setData(MineDataPtr _data);
    void setPhyPos(QPointF _p);

    void setChecked(bool _check = true);

    char getDisplayVal();
    char getVal();
    QPointF getPos();
    bool getCovered();
    QPoint getLogicPos();
    bool getMine();
    unsigned getIndexX();
    unsigned getIndexY();

public:
    void setDisplayState(bool _isCovered = false); // left click
    void setFlag(char _flag); //right click

    virtual void onMousePressEventHandle(QMouseEvent *event);
    virtual void onMouseReleaseEventHandle(QMouseEvent *event);

signals:
    void tileClicked(QPoint, bool);
    void tileFlagChange(bool);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void paintShadow(QPainter *painter, qreal _depth = 0);
    void paintHover(QPainter *painter);
    void paintMine(QPainter *painter);
    void paintFlag(QPainter *painter);
    void paintCross(QPainter *painter);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    char m_displayVal; //'1'-'9','^','?','0'=None
    bool m_isCovered;

    qreal m_phx;
    qreal m_phy;
    MineDataPtr m_data;
    bool m_isHovered;
    bool m_isPressed;
    bool m_isChecked;

};

#endif // MINETILE_H
