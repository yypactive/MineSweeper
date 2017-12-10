#include "stopwatch.h"
#include <QDebug>
StopWatch::StopWatch(QObject *parent) : QObject(parent)
{
    initTimer();
    initLCD();
    connect(m_QtTimer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

QLCDNumber *StopWatch::getLCD()
{
    return m_LCD;
}

void StopWatch::start()
{
    m_StartTime = QTime::currentTime();
    m_QtTimer->start();
}

void StopWatch::stop()
{
    m_QtTimer->stop();
}

void StopWatch::reset()
{
    m_QtTimer->stop();
    m_StartTime = QTime::currentTime();
    m_LCD->display("00:00:00");
}

void StopWatch::onTimerOut()
{
    QTime currentTime = QTime::currentTime();
    QTime deltaTime = QTime(0, 0, 0, 0).addMSecs(m_StartTime.msecsTo(currentTime));
    m_LCD->display(deltaTime.toString("hh:mm:ss"));
}

StopWatch::initTimer()
{
    m_QtTimer = new QTimer();
    m_QtTimer->setInterval(ms_intervalTime);
}

StopWatch::initLCD()
{
    m_LCD = new QLCDNumber();
    m_LCD->setDigitCount(8);
    m_LCD->setMode(QLCDNumber::Dec);
    m_LCD->setSegmentStyle(QLCDNumber::Flat);

    QPalette palette = m_LCD->palette();
    palette.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
    m_LCD->setPalette(palette);
    m_LCD->setStyleSheet("background-color: black");
    m_LCD->display("00:00:00");
}
