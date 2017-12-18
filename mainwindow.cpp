#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_isFirstTime(true), m_btnStyle(State::wait)
{   
    initWindow();
    initMenu();
    initConnect();
}

MainWindow::~MainWindow()
{
}

MainWindow::initWindow()
{
    m_mainWidget = new QWidget(this);
    setCentralWidget(m_mainWidget);

    m_mainLayout = new QVBoxLayout(this);

    m_topLayout = new QHBoxLayout(this);
    // TODO: mineBoard
    m_mineBoard = new MineBoard();
    QLCDNumber * mlcd = m_mineBoard->getLCD();
    mlcd->setFixedSize(70, 50);
    m_topLayout->addWidget(mlcd);
    m_topLayout->addStretch();

    m_ctrlBtn = new QPushButton("^_^", this);
    setNormalStyle(m_ctrlBtn);
    m_ctrlBtn->setFixedSize(50, 50);
    m_topLayout->addWidget(m_ctrlBtn);

    m_stopWatch = new StopWatch();
    QLCDNumber * lcd = m_stopWatch->getLCD();
    lcd->setFixedSize(170, 50);
    m_topLayout->addStretch();
    m_topLayout->addWidget(lcd);

    m_mainLayout->addLayout(m_topLayout);

    m_ViewWidget = new ViewWidget(this);
    m_mainLayout->addWidget(m_ViewWidget);

    m_mainWidget->setLayout(m_mainLayout);

}

MainWindow::initMenu()
{

    m_gameMenu = new QMenu(tr("Game"), this);
    m_helpMenu = new QMenu(tr("Help"), this);
    initAction();

    menuBar()->addMenu(m_gameMenu);
    menuBar()->addMenu(m_helpMenu);
}

MainWindow::initAction()
{
    // Game
    m_newGameAct = new QAction(QIcon(""), tr("New Game"), this);
    m_optionsAct = new QAction(QIcon(""), tr("Options"), this);
    m_exitAct = new QAction(QIcon(""), tr("Exit"), this);
    m_newGameAct->setShortcut(QKeySequence(tr("F2")));
    m_optionsAct->setShortcut(QKeySequence(tr("F4")));
    m_gameMenu->addAction(m_newGameAct);
    m_gameMenu->addSeparator();
    m_gameMenu->addAction(m_optionsAct);
    m_gameMenu->addSeparator();
    m_gameMenu->addAction(m_exitAct);
    // Help
    m_helpAct = new QAction(QIcon(""), tr("View Help"), this);
    m_aboutAct = new QAction(QIcon(""), tr("About"), this);
    m_moreGameAct = new QAction(QIcon(""), tr("More Game"), this);
    m_helpAct->setShortcut(QKeySequence(tr("F1")));
    m_helpMenu->addAction(m_helpAct);
    m_helpMenu->addSeparator();
    m_helpMenu->addAction(m_aboutAct);
    m_helpMenu->addSeparator();
    m_helpMenu->addAction(m_moreGameAct);
}

MainWindow::initConnect()
{
    connect(m_ctrlBtn, SIGNAL(clicked()), this, SLOT(onBtnClickedHandle()));
    connect(m_ViewWidget, SIGNAL(startStopWatch()), this, SLOT(startGame()));
    connect(m_ViewWidget, SIGNAL(sendSucc()), this, SLOT(succ()));
    connect(m_ViewWidget, SIGNAL(sendFail()), this, SLOT(fail()));
    connect(m_ViewWidget, SIGNAL(setFlagCount(unsigned)), m_mineBoard, SLOT(setMineNumber(unsigned)));
}

void MainWindow::setNormalStyle(QPushButton *_btn)
{
    _btn->setText("^_^");
    m_ctrlBtn->setFont(QFont("msyh", 12, 10));
    _btn->setStyleSheet("background-color: grey;");
}

void MainWindow::setSuccessStyle(QPushButton *_btn)
{
    _btn->setText("^v^");
    m_ctrlBtn->setFont(QFont("msyh", 12, 10));
    _btn->setStyleSheet("background-color: rgb(170, 0, 255);");
}

void MainWindow::setFailStyle(QPushButton *_btn)
{
    _btn->setText("x_x");
    m_ctrlBtn->setFont(QFont("msyh", 12, 10));
    _btn->setStyleSheet("background-color: blue;");
}

void MainWindow::onBtnClickedHandle()
{
    m_stopWatch->reset();
    // clean all
    // new Game
}

void MainWindow::startGame()
{
    m_stopWatch->start();
}

void MainWindow::succ()
{
    m_stopWatch->stop();
    setSuccessStyle(m_ctrlBtn);
}

void MainWindow::fail()
{
    m_stopWatch->stop();
    setFailStyle(m_ctrlBtn);
}

