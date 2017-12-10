#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTimer>
#include <QLCDNumber>
#include <QTime>
#include <QObject>

class StopWatch : public QObject
{
    Q_OBJECT
public:
    explicit StopWatch(QObject *parent = 0);

    QLCDNumber * getLCD();

public:
    static const unsigned ms_intervalTime = 100;

public slots:
    void start();
    void stop();
    void reset();

private slots:
    void onTimerOut();

private:
    initTimer();
    initLCD();

private:
    QTimer * m_QtTimer;
    QLCDNumber * m_LCD;
    QTime m_StartTime;
    bool m_isRun;
};

#endif // STOPWATCH_H
