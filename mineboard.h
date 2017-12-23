#ifndef MINEBOARD_H
#define MINEBOARD_H

#include <QObject>
#include <QLCDNumber>

class MineBoard : public QObject
{
    Q_OBJECT
public:
    explicit MineBoard(QObject *parent = 0);

    QLCDNumber * getLCD();

public slots:
    setMineNumber(unsigned _num);

private:
    void initLCD();

private:
    QLCDNumber * m_LCD;
    unsigned m_mineNumber;
};

#endif // MINEBOARD_H
