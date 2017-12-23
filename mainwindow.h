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
#include "optionswidget.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSpacerItem>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum State {
        wait,
        run,
        end
    };
    static const qreal ms_spaceW;
    static const qreal ms_spaceH;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initWindow();
    void initOptionsWidget();
    void initMenu();
    void initAction();
    void initStateBar();
    void initConnect();

    void newGame();

private:
    void setNormalStyle(QPushButton * _btn);
    void setSuccessStyle(QPushButton * _btn);
    void setFailStyle(QPushButton * _btn);

private slots:
    void onBtnClickedHandle();
    void startStopWatch();
    void succ();
    void fail();
    void showOptions();
    void showHelp();
    void showAbout();
    void showMoreGame();
    void onOptionsHandle(unsigned _row, unsigned _col, unsigned _mine);

private:
    QWidget * m_mainWidget;
    ViewWidget * m_ViewWidget;
    OptionsWidget * m_optionsWidget;

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
    //option
    unsigned m_row;
    unsigned m_col;
    unsigned m_amount;


};

#endif // MAINWINDOW_H
