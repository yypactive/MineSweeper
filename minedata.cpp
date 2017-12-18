#include "minedata.h"

MineData::MineData()
    : m_y(-1), m_x(-1),
      m_val('0'), m_mine(false)
{

}

void MineData::setX(unsigned _x)
{
    m_x = _x;
}

void MineData::setY(unsigned _y)
{
    m_y = _y;
}

void MineData::setVal(unsigned _val)
{
    m_val = _val;
}

void MineData::setMine(bool _mine)
{
    m_mine = _mine;
}

unsigned MineData::getX() const
{
    return m_x;
}

unsigned MineData::getY() const
{
    return m_y;
}

unsigned MineData::getVal() const
{
    return m_val;
}

bool MineData::getMine() const
{
    return m_mine;
}
