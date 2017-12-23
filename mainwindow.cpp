#include "mainwindow.h"

const qreal MainWindow::ms_spaceW = 15.;
const qreal MainWindow::ms_spaceH = 15.;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_isFirstTime(true), m_btnStyle(State::wait),
      m_row(OptionsWidget::ms_easyRow), m_col(OptionsWidget::ms_easyCol), m_amount(OptionsWidget::ms_easyMine)
{   
    initWindow();
    initMenu();
    initOptionsWidget();
    initConnect();
    newGame();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initWindow()
{
    m_mainWidget = new QWidget(this);
    setCentralWidget(m_mainWidget);

    m_mainLayout = new QVBoxLayout(m_mainWidget);

    m_topLayout = new QHBoxLayout();
    // TODO: mineBoard
    m_mineBoard = new MineBoard();
    QLCDNumber * mlcd = m_mineBoard->getLCD();
    mlcd->setFixedSize(70, 50);
    m_topLayout->addWidget(mlcd);
    m_topLayout->addItem(new QSpacerItem(100, 50));
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

    setWindowTitle("MineSweeper yyp");

}

void MainWindow::initOptionsWidget()
{
    m_optionsWidget = new OptionsWidget();
    m_optionsWidget->hide();
}

void MainWindow::initMenu()
{

    m_gameMenu = new QMenu(tr("Game"), this);
    m_helpMenu = new QMenu(tr("Help"), this);
    initAction();

    menuBar()->addMenu(m_gameMenu);
    menuBar()->addMenu(m_helpMenu);
}

void MainWindow::initAction()
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

void MainWindow::initConnect()
{
    connect(m_newGameAct, SIGNAL(triggered()), this, SLOT(onBtnClickedHandle()));
    connect(m_optionsAct, SIGNAL(triggered()), this, SLOT(showOptions()));
    connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(m_helpAct, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(m_moreGameAct, SIGNAL(triggered()), this, SLOT(showMoreGame()));

    connect(m_ctrlBtn, SIGNAL(clicked()), this, SLOT(onBtnClickedHandle()));
    connect(m_ViewWidget, SIGNAL(startStopWatch()), this, SLOT(startStopWatch()));
    connect(m_ViewWidget, SIGNAL(sendSucc()), this, SLOT(succ()));
    connect(m_ViewWidget, SIGNAL(sendFail()), this, SLOT(fail()));
    connect(m_ViewWidget, SIGNAL(setFlagCount(unsigned)), m_mineBoard, SLOT(setMineNumber(unsigned)));
    connect(m_optionsWidget, SIGNAL(sendOptions(unsigned, unsigned, unsigned)), this, SLOT(onOptionsHandle(unsigned, unsigned, unsigned)));
}

void MainWindow::newGame()
{
    m_ViewWidget->newGame(m_row, m_col, m_amount);
    m_mineBoard->setMineNumber(m_amount);
    update();
    setFixedSize(m_ViewWidget->width() + 2 * ms_spaceW,
                 m_ViewWidget->height() + m_mineBoard->getLCD()->height() + 5 * ms_spaceH);
}

void MainWindow::setNormalStyle(QPushButton *_btn)
{
    _btn->setText("^_^");
    m_ctrlBtn->setFont(QFont("Consolas", 14, 70));
    _btn->setStyleSheet("background-color: rgb(150, 150, 150);");
}

void MainWindow::setSuccessStyle(QPushButton *_btn)
{
    _btn->setText("^v^");
    m_ctrlBtn->setFont(QFont("Consolas", 14, 70));
    _btn->setStyleSheet("background-color: rgb(170, 120, 50);");
}

void MainWindow::setFailStyle(QPushButton *_btn)
{
    _btn->setText("*_*");
    m_ctrlBtn->setFont(QFont("Consolas", 14, 70));
    _btn->setStyleSheet("background-color: rgb(50, 170, 170);");
}

void MainWindow::onBtnClickedHandle()
{
    m_stopWatch->stop();
    m_stopWatch->reset();
    setNormalStyle(m_ctrlBtn);
    newGame();
    // clean all
    // new Game
}

void MainWindow::startStopWatch()
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

void MainWindow::showOptions()
{
    m_optionsWidget->show();
}

void MainWindow::showHelp()
{
    QMessageBox::about(this, tr("Help"),
                       tr("<h3>User Manual</h3>"
                          "<p>F2: newGame\n"
                          "<p>F4: options\n"
                          ));
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About"),
                       tr("<h3>MineSweeper</h3>"
                          "<p>Copyright &copy; 2017 yyp\n"
                          "<p>Version 0.3\n"
                          ));
}

void MainWindow::showMoreGame()
{
    QMessageBox::about(this, tr("More Game"),
        tr("<h3>For More Game</h3>"
        "<a href = https://github.com/yypactive>https://github.com/yypactive<\a>"
           ));
}

void MainWindow::onOptionsHandle(unsigned _row, unsigned _col, unsigned _mine)
{
    m_row = _row;
    m_col = _col;
    m_amount = _mine;
    onBtnClickedHandle();
}

