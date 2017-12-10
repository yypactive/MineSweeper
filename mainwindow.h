#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include "mineboard.h"
#include <QPushButton>
#include "stopwatch.h"
#include "viewwidget.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum State {
        wait,
        run,
        end
    };

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    initWindow();
    initMenu();
    initAction();
    initStateBar();
    initConnect();

private:
    void setInit();
    void setSuccess();
    void setFailure();

    void setNormalStyle(QPushButton * _btn);
    void setSuccessStyle(QPushButton * _btn);
    void setFailStyle(QPushButton * _btn);

private slots:
    void onBtnClickedHandle();

private:
    QWidget * m_mainWidget;
    ViewWidget * m_ViewWidget;

    QVBoxLayout * m_mainLayout;
    QHBoxLayout * m_topLayout;

    QMenu * m_GameMenu;
    QMenu * m_HelpMenu;

    MineBoard * m_mineBoard;
    QPushButton * m_ctrlBtn;
    StopWatch * m_stopWatch;

    bool m_isFirstTime;
    State m_btnStyle;
};

#endif // MAINWINDOW_H
