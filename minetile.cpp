#include "minetile.h"

const qreal MineTile::ms_width = 40.;
const qreal MineTile::ms_height = 40.;
const qreal MineTile::ms_fontSize = 12;
const qreal MineTile::ms_shadowDepth = 3.;
const unsigned MineTile::ms_hoverColor = 240;
const unsigned MineTile::ms_backColor = 230;
const unsigned MineTile::ms_frontColor = 180;
const unsigned MineTile::ms_hlColor = 240;
const unsigned MineTile::ms_shColor = 90;
QPoint MineTile::ms_clickedTile = QPoint(-1, -1);

MineTile::MineTile()
    : m_displayVal('0'), m_isCovered(true),
      m_phx(-1), m_phy(-1),
      m_data(),
      m_isHovered(false), m_isPressed(false), m_isChecked(false)
{
    setRect(0, 0, ms_width, ms_height);
    QPen pen = this->pen();
    pen.setWidthF(0.);
    setPen(Qt::NoPen);
    setAcceptHoverEvents(true);
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

void MineTile::setChecked(bool _check)
{
    m_isChecked = _check;
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

bool MineTile::getCovered()
{
    return m_isCovered;
}

QPoint MineTile::getLogicPos()
{
    return QPoint(m_data->getX(), m_data->getY());
}

bool MineTile::getMine()
{
    return m_data->getMine();
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
    if (!m_isCovered && getMine())
        this->setBrush(QBrush(Qt::red));
    else if (m_isCovered && !m_isPressed)
        this->setBrush(QBrush(QColor(ms_frontColor, ms_frontColor, ms_frontColor, 255)));
    else
        this->setBrush(QBrush(QColor(ms_backColor, ms_backColor, ms_backColor, 255)));

    QGraphicsRectItem::paint(painter, option, widget);

    painter->save();

    if (getMine() &&
            (!m_isCovered || m_isChecked && m_displayVal != '^'))
    {
        //draw mine
        paintMine(painter);

    }

    QFont font = painter->font();
    font.setFamily("yahei");
    font.setPointSizeF(ms_fontSize);
    font.setBold(true);
    painter->setFont(font);
    QFontMetrics fm = painter->fontMetrics();

    if (m_displayVal >= '1' && m_displayVal <= '9' && !getMine())
    {
        painter->setPen(QPen(QColor(100, 100, 100, 255)));
        int fw = fm.width(QChar(m_displayVal));
        int fh = fm.ascent() + fm.descent();
        QRectF rect(boundingRect().width() / 2. - fw / 2., boundingRect().height() / 2. - fh / 2., fw, fh);
        painter->drawText(rect, QString(m_displayVal));

    }
    else if (m_displayVal == '?')
    {
        painter->setPen(QPen(QColor(100, 100, 100, 255)));
        int fw = fm.width(QChar(m_displayVal));
        int fh = fm.ascent() + fm.descent();
        QRectF rect(boundingRect().width() / 2. - fw / 2., boundingRect().height() / 2. - fh / 2., fw, fh);
        painter->drawText(rect, QString(m_displayVal));
    }
    else if (m_displayVal == '^')
    {
        if (m_isChecked && !m_data->getMine())
        {
            paintMine(painter);
            paintCross(painter);
        }
        else
        {
            // draw flag;
            paintFlag(painter);
        }

    }

    painter->restore();

    if (m_isCovered)
    {
        paintShadow(painter, ms_shadowDepth);
        if (m_isHovered && !m_isPressed)
        {
            paintHover(painter);
        }
    }

}

void MineTile::paintShadow(QPainter *painter, qreal _depth)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    qreal width = boundingRect().width();
    qreal height = boundingRect().height();
    // hightlight
    if (!m_isPressed)
        painter->setBrush(QBrush(QColor(ms_hlColor, ms_hlColor, ms_hlColor, 255)));
    else
        painter->setBrush(QBrush(QColor(ms_shColor, ms_shColor, ms_shColor, 255)));
    QPointF hlp[6] = {
        QPointF(0., 0.),
        QPointF(0., height),
        QPointF(_depth, height-_depth),
        QPointF(_depth, _depth),
        QPointF(width-_depth, _depth),
        QPointF(width, 0)
    };
    painter->drawPolygon(hlp, 6);
    // shadow
    if (!m_isPressed)
        painter->setBrush(QBrush(QColor(ms_shColor, ms_shColor, ms_shColor, 255)));
    else
        painter->setBrush(QBrush(QColor(ms_hlColor, ms_hlColor, ms_hlColor, 255)));
    QPointF shp[6] = {
        QPointF(width, height),
        QPointF(0., height),
        QPointF(_depth, height-_depth),
        QPointF(width-_depth, height-_depth),
        QPointF(width-_depth, _depth),
        QPointF(width, 0)
    };
    painter->drawPolygon(shp, 6);
    painter->restore();
}

void MineTile::paintHover(QPainter *painter)
{
    painter->save();

    qreal width = boundingRect().width();
    qreal height = boundingRect().height();

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(ms_hoverColor, ms_hoverColor, ms_hoverColor, 150)));
    painter->drawRect(boundingRect());

    painter->restore();
}

void MineTile::paintMine(QPainter *painter)
{
    painter->save();

    qreal width = boundingRect().width();
    qreal height = boundingRect().height();
    qreal sqt = 1.732;
    qreal trilen = 1 / 2.5;
    painter->setBrush(QColor(50, 50, 50, 255));
    painter->drawEllipse(QPointF(width / 2., height / 2.),
                         width / 3.7, height / 3.7);
    QPointF tri[3] = {
        QPointF(width / 2., height * (1/2.-trilen)),
        QPointF(width * (1/2. - sqt/2.*trilen), height * (1/2.+trilen/2.)),
        QPointF(width * (1/2. + sqt/2.*trilen), height * (1/2.+trilen/2.)),
    };
    painter->drawPolygon(tri, 3);

    QPointF tri2[3] = {
        QPointF(width / 2., height * (1/2.+trilen)),
        QPointF(width * (1/2. - sqt/2.*trilen), height * (1/2.-trilen/2.)),
        QPointF(width * (1/2. + sqt/2.*trilen), height * (1/2.-trilen/2.)),
    };
    painter->drawPolygon(tri2, 3);

    painter->restore();
}

void MineTile::paintFlag(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setColor(QColor(50, 50, 50, 255));
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(0);
    painter->setPen(pen);
    painter->setBrush(QBrush(QColor(Qt::red)));

    qreal width = boundingRect().width();
    qreal height = boundingRect().height();
    qreal flaglen = 1/3.;
    qreal baselen = 1/6.;
    QPointF tri[3] = {
        QPointF(width / 2., height * (1/2.-flaglen)),
        QPointF(width * (1/2. + flaglen), height * 1/2.),
        QPointF(width / 2, height * 1/2.)
    };
    painter->drawPolygon(tri, 3);

    QPen pen2 = painter->pen();
    pen2.setWidthF(width / 20.);
    painter->setPen(pen2);
    painter->drawLine(QPointF(width/2., height * (1/2.-flaglen)), QPointF(width/2., height * (1-flaglen)));

    QPen pen3 = painter->pen();
    pen3.setWidth(0);
    painter->setPen(pen3);
    painter->setBrush(QBrush(QColor(50, 50, 50, 255)));
    QPointF base[4] = {
        QPointF(width * (1/2. + flaglen), height * (1-baselen)),
        QPointF(width * (1/2. + flaglen - baselen), height * (1-flaglen)),
        QPointF(width * (1/2. - flaglen + baselen), height * (1-flaglen)),
        QPointF(width * (1/2. - flaglen), height * (1-baselen))
    };
    painter->drawPolygon(base, 4);

    painter->restore();
}

void MineTile::paintCross(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidthF(boundingRect().width() / 8.);
    painter->setPen(pen);

    qreal width = boundingRect().width();
    qreal height = boundingRect().height();
    qreal len = 1/8.;
    painter->drawLine(QPointF(width * len, height * (1-len)), QPointF(width * (1-len), height * len));
    painter->drawLine(QPointF(width * len, height * len), QPointF(width * (1-len), height * (1-len)));

    painter->restore();
}

void MineTile::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // qDebug() << "hover Enter: " << getLogicPos();
    if (!m_isCovered || m_isChecked)
        return;
    m_isHovered = true;
    update();
}

void MineTile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // qDebug() << "hover Leave: " << getLogicPos();
    m_isHovered = false;
    update();
}

void MineTile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_isCovered || m_isChecked)
        return;
//    if (!m_isCovered && QApplication::keyboardModifiers() != Qt::ShiftModifier)
//        return;
    m_isPressed = true;
    update();
}

void MineTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_isPressed = false;
    update();
}

void MineTile::onMousePressEventHandle(QMouseEvent *event)
{
    // qDebug() << "mouse press: " << getLogicPos();
    if (m_isChecked)
        return;
    if (event->button() == Qt::RightButton)
    {
        if (m_isPressed)
            return;
        if (m_displayVal == '0')
        {
            setFlag('^');
            emit tileFlagChange(true);
        }
        else if (m_displayVal == '^')
        {
            setFlag('?');
            emit tileFlagChange(false);
        }
        else if (m_displayVal == '?')
        {
            setFlag('0');
        }
    }
    else if (event->button() == Qt::LeftButton)
    {
        ms_clickedTile = getLogicPos();
    }
    update();
}

void MineTile::onMouseReleaseEventHandle(QMouseEvent *event)
{
    // qDebug() << "mouse release: " << getLogicPos();
    if (m_isChecked)
        return;
    if (event->button() == Qt::RightButton)
    {
        if (m_isPressed)
            return;
    }
    else if (event->button() == Qt::LeftButton)
    {
        QPoint myLogicPos = getLogicPos(); // pro
        if (myLogicPos != ms_clickedTile)
            return;
        if (m_isCovered)
        {
            setDisplayState(false);
            emit tileClicked(getLogicPos(), false);
            setDisplayState(false);
        }
        else if (QApplication::keyboardModifiers() == Qt::ShiftModifier)
        {
            emit tileClicked(getLogicPos(), true);
        }
    }
    update();
}
