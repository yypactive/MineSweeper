#include "minedata.h"

MineData::mineData()
    : m_y(-1), m_x(-1),
      m_val(0)
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

unsigned MineData::getX()
{
    return m_x;
}

unsigned MineData::getY()
{
    return m_y;
}

unsigned MineData::getVal()
{
    return m_val;
}
