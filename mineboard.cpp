#include "mineboard.h"

MineBoard::MineBoard(QObject *parent) : QObject(parent)
{
    initLCD();
}

QLCDNumber *MineBoard::getLCD()
{
    return m_LCD;
}

MineBoard::setMineNumber(unsigned _num)
{
    m_mineNumber = _num;
    m_LCD->display(QString::number(static_cast<int>(m_mineNumber), 10));
    m_LCD->update();
}

void MineBoard::initLCD()
{
    m_LCD = new QLCDNumber();
    m_LCD->setDigitCount(3);
    m_LCD->setMode(QLCDNumber::Dec);
    m_LCD->setSegmentStyle(QLCDNumber::Flat);

    QPalette palette = m_LCD->palette();
    palette.setColor(QPalette::Normal, QPalette::WindowText, QColor(250, 50, 50, 255));
    m_LCD->setPalette(palette);
    m_LCD->setStyleSheet("background-color: rgb(50, 50, 50);");
    m_LCD->display("000");
    m_LCD->update();
}
