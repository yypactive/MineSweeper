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
    initAction();
    m_GameMenu = new QMenu(tr("Game"), this);
    m_HelpMenu = new QMenu(tr("Help"), this);

    menuBar()->addMenu(m_GameMenu);
    menuBar()->addMenu(m_HelpMenu);
}

MainWindow::initAction()
{

}

MainWindow::initConnect()
{
    connect(m_ctrlBtn, SIGNAL(clicked()), this, SLOT(onBtnClickedHandle()));
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
    m_stopWatch->start();
    // run
    m_btnStyle == State::run;
}

