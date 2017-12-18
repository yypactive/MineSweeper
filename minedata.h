#ifndef MINEDATA_H
#define MINEDATA_H


class MineData
{
public:
    MineData();

    void setX(unsigned _x);
    void setY(unsigned _y);
    void setVal(unsigned _val);
    void setMine(bool _mine);

    unsigned getX() const;
    unsigned getY() const;
    unsigned getVal() const;
    bool getMine() const;
private:
    unsigned m_y;
    unsigned m_x;
    unsigned m_val;
    bool m_mine;
};

#endif // MINEDATA_H
