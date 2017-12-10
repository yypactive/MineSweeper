#ifndef MINEDATA_H
#define MINEDATA_H


class MineData
{
public:
    MineData();

    void setX(unsigned _x);
    void setY(unsigned _y);
    void setVal(unsigned _val);

    unsigned getX();
    unsigned getY();
    unsigned getVal();

private:
    unsigned m_y;
    unsigned m_x;
    unsigned m_val;
};

#endif // MINEDATA_H
