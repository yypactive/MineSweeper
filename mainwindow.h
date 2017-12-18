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
    void setNormalStyle(QPushButton * _btn);
    void setSuccessStyle(QPushButton * _btn);
    void setFailStyle(QPushButton * _btn);

private slots:
    void onBtnClickedHandle();
    void startGame();
    void succ();
    void fail();

private:
    QWidget * m_mainWidget;
    ViewWidget * m_ViewWidget;

    QVBoxLayout * m_mainLayout;
    QHBoxLayout * m_topLayout;

    MineBoard * m_mineBoard;
    QPushButton * m_ctrlBtn;
    StopWatch * m_stopWatch;

    bool m_isFirstTime;
    State m_btnStyle;

    QMenu * m_gameMenu;
    QMenu * m_helpMenu;
    // Game
    QAction* m_newGameAct;
    QAction* m_optionsAct;
    QAction* m_exitAct;
    // Help
    QAction* m_helpAct;
    QAction* m_aboutAct;
    QAction* m_moreGameAct;


};

#endif // MAINWINDOW_H
