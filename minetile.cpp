#include "minetile.h"

const qreal MineTile::ms_width = 10.;
const qreal MineTile::ms_height = 10.;

MineTile::MineTile()
    : m_displayVal('0'), m_isCovered(true),
      m_phx(-1), m_phy(-1),
      m_data()
{
    setRect(0, 0, ms_width, ms_height);
    QPen pen;
    pen.setWidthF(0.);
    setPen(pen);
}

MineTile::~MineTile()
{

}

void MineTile::setData(MineDataPtr _data)
{
    m_data = _data;
}

void MineTile::setPhyPos(QPointF _p)
{
    m_phx = _p.x();
    m_phy = _p.y();
}

char MineTile::getDisplayVal()
{
    return m_displayVal;
}

char MineTile::getVal()
{
    return m_data->getVal();
}

QPointF MineTile::getPos()
{
    return QPointF(m_phx, m_phy);
}

QPoint MineTile::getLogicPos()
{
    return QPoint(m_data->getX(), m_data->getY());
}

void MineTile::setDisplayState(bool _isCovered)
{
    m_isCovered = _isCovered;
    if (!_isCovered)
    {
        m_displayVal = m_data->getVal();
    }
}

void MineTile::setFlag(char _flag)
{
    if (m_isCovered)
    {
        m_displayVal = _flag;
    }
}

void MineTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    if (m_displayVal >= '0' && m_displayVal <= '9')
    {
        painter->drawText(boundingRect(), QString(m_displayVal));
        setBrush(QBrush(QColor(200, 200, 200, 255)));
    }
    else if (m_displayVal == '?')
    {
        painter->drawText(boundingRect(), QString(m_displayVal));
        setBrush(QBrush(QColor(50, 50, 50, 255)));
    }
    else if (m_displayVal == '^')
    {
        painter->drawText(boundingRect(), QString(m_displayVal));;
        setBrush(QBrush(QColor(50, 50, 50, 255)));
    }

    painter->restore();
    QGraphicsRectItem::paint(painter, option, widget);
}
