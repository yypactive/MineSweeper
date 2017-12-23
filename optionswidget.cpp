#include "optionswidget.h"

OptionsWidget::OptionsWidget(QWidget *parent)
    : QWidget(parent),
      m_row(ms_easyRow), m_col(ms_easyCol), m_mine(ms_easyMine)
{
    init();
}

void OptionsWidget::onConfirmHandle()
{
    if (m_easyBtn->isChecked())
    {
        m_lastBtn = m_easyBtn;
        m_row = ms_easyRow;
        m_col = ms_easyCol;
        m_mine = ms_easyMine;
    }
    else if (m_normalBtn->isChecked())
    {
        m_lastBtn = m_normalBtn;
        m_row = ms_normalRow;
        m_col = ms_normalCol;
        m_mine = ms_normalMine;
    }
    else if (m_hardBtn->isChecked())
    {
        m_lastBtn = m_hardBtn;
        m_row = ms_hardRow;
        m_col = ms_hardCol;
        m_mine = ms_hardMine;
    }
    else if (m_customBtn->isChecked())
    {
        m_lastBtn = m_customBtn;
        m_row = m_rowLine->text().toInt();
        m_col = m_colLine->text().toInt();
        m_mine = m_mineLine->text().toInt();
    }
    else
    {
        return;
    }
    emit sendOptions(m_row, m_col, m_mine);
    hide();
}

void OptionsWidget::onCancelHandle()
{
    if (m_lastBtn == m_customBtn)
    {
        m_rowLine->setText(QString::number(m_row));
        m_colLine->setText(QString::number(m_col));
        m_mineLine->setText(QString::number(m_mine));
    }
    m_group->setChecked(false);
    m_lastBtn->setChecked(true);
    hide();
}

void OptionsWidget::onCustomTextChangedHandle()
{
    int mine = m_mineLine->text().toInt();
    int row = m_rowLine->text().toInt();
    int col = m_colLine->text().toInt();
    int mineMax = std::min(row * col - 10, static_cast<int>(ms_comMaxMine));
    m_mineVal->setTop(mineMax);
    if (mine > mineMax)
        m_mineLine->setText(QString::number(mineMax));
}

void OptionsWidget::closeEvent(QCloseEvent *event)
{
    onCancelHandle();
    QWidget::closeEvent(event);
}

void OptionsWidget::init()
{
    setFont(QFont("Arial", 11, 1));
    initBtn();
    initLine();
    initLabel();
    initWindiow();
    initConnnect();
    //emit sendOptions(m_row, m_col, m_amount);
}

void OptionsWidget::initBtn()
{
    m_BtnGroup = new QButtonGroup(this);
    m_easyBtn = new QRadioButton("",this);
    m_normalBtn = new QRadioButton("",this);
    m_hardBtn = new QRadioButton("",this);
    m_customBtn = new QRadioButton("",this);
    m_BtnGroup->addButton(m_easyBtn);
    m_BtnGroup->addButton(m_normalBtn);
    m_BtnGroup->addButton(m_hardBtn);
    m_BtnGroup->addButton(m_customBtn);
    m_lastBtn = m_easyBtn;
    m_easyBtn->setChecked(true);

    m_confirmBtn = new QPushButton("Confirm",this);
    QFont font = m_confirmBtn->font();
    font.setWeight(70);
    m_confirmBtn->setFont(font);
    m_cancelBtn = new QPushButton("Cancel",this);
    font = m_cancelBtn->font();
    font.setWeight(70);
    m_cancelBtn->setFont(font);
}

void OptionsWidget::initLabel()
{
    m_easyDiffLab = new QLabel("Easy", this);
    m_easyMinelab = new QLabel(QString::number(ms_easyMine) + QString(" Mines"), this);
    m_easySizelab = new QLabel("( " + QString::number(ms_easyRow) + " X " + QString::number(ms_easyCol) + " )", this);

    m_normalDiffLab = new QLabel("Normal", this);
    m_normalMinelab = new QLabel(QString::number(ms_normalMine) + " Mines", this);
    m_normalSizelab = new QLabel("( " + QString::number(ms_normalRow) + " X " + QString::number(ms_normalCol) + " )", this);

    m_hardDiffLab = new QLabel("Hard", this);
    m_hardMinelab = new QLabel(QString::number(ms_hardMine) + " Mines", this);;
    m_hardSizelab = new QLabel("( " + QString::number(ms_hardRow) + " X " + QString::number(ms_hardCol) + " )", this);

    m_customDLab = new QLabel("Custom", this);
    m_customHLab = new QLabel("  Height: ( " + QString::number(ms_comMinRow) + " - " + QString::number(ms_comMaxRow) + " )", this);
    m_customWlab = new QLabel("  Width:  ( " + QString::number(ms_comMinCol) + " - " + QString::number(ms_comMaxCol) + " )", this);
    m_custonMlab = new QLabel("  Mines:  ( " + QString::number(ms_comMinMine) + " - " + QString::number(ms_comMaxMine) + " )", this);
}

void OptionsWidget::initLine()
{
    m_rowLine = new QLineEdit("", this);
    m_colLine = new QLineEdit("", this);
    m_mineLine = new QLineEdit("", this);

    m_rowLine->setText(QString::number(ms_easyRow));
    m_rowLine->setFont(QFont("Arial"));
    m_colLine->setText(QString::number(ms_easyCol));
    m_colLine->setFont(QFont("Arial"));
    m_mineLine->setText(QString::number(ms_easyMine));
    m_mineLine->setFont(QFont("Arial"));

    m_rowVal = new QIntValidator(ms_comMinRow, ms_comMaxRow, this);
    m_colVal = new QIntValidator(ms_comMinCol, ms_comMaxCol, this);
    m_mineVal = new QIntValidator(ms_comMinMine, ms_comMaxMine, this);

    m_rowLine->setValidator(m_rowVal);
    m_colLine->setValidator(m_colVal);
    m_mineLine->setValidator(m_mineVal);

    m_rowLine->setEnabled(false);
    m_colLine->setEnabled(false);
    m_mineLine->setEnabled(false);
}

void OptionsWidget::initWindiow()
{
    m_mainlayout = new QVBoxLayout(this);
    m_botlayout = new QHBoxLayout();

    m_group = new QGroupBox("Difficulty", this);
    m_grouplayout = new QGridLayout(m_group);

    m_group->setLayout(m_grouplayout);
    m_grouplayout->addWidget(m_easyBtn, 0, 0, 1, 1);
    m_grouplayout->addWidget(m_normalBtn, 4, 0, 1, 1);
    m_grouplayout->addWidget(m_hardBtn, 8, 0, 1, 1);
    m_grouplayout->addWidget(m_customBtn, 0, 2, 1, 1);
    m_grouplayout->addItem(new QSpacerItem(25, 25), 3, 0,1,1);
    m_grouplayout->addItem(new QSpacerItem(25, 25), 7, 0,1,1);

    m_grouplayout->addWidget(m_easyDiffLab, 0, 1, 1, 1);
    m_grouplayout->addWidget(m_easyMinelab, 1, 1, 1, 1);
    m_grouplayout->addWidget(m_easySizelab, 2, 1, 1, 1);

    m_grouplayout->addWidget(m_normalDiffLab, 4, 1, 1, 1);
    m_grouplayout->addWidget(m_normalMinelab, 5, 1, 1, 1);
    m_grouplayout->addWidget(m_normalSizelab, 6, 1, 1, 1);

    m_grouplayout->addWidget(m_hardDiffLab, 8, 1, 1, 1);
    m_grouplayout->addWidget(m_hardMinelab, 9, 1, 1, 1);
    m_grouplayout->addWidget(m_hardSizelab, 10, 1, 1, 1);

    m_grouplayout->addWidget(m_customDLab, 0, 3, 1, 1);
    m_grouplayout->addWidget(m_customHLab, 1, 3, 1, 1);
    m_grouplayout->addWidget(m_customWlab, 2, 3, 1, 1);
    m_grouplayout->addWidget(m_custonMlab, 3, 3, 1, 1);

    m_grouplayout->addWidget(m_rowLine, 1, 4, 1, 1);
    m_grouplayout->addWidget(m_colLine, 2, 4, 1, 1);
    m_grouplayout->addWidget(m_mineLine, 3, 4, 1, 1);

    m_grouplayout->setVerticalSpacing(2);

    m_botlayout->addWidget(m_confirmBtn);
    m_botlayout->addWidget(m_cancelBtn);

    m_mainlayout->addWidget(m_group);
    m_mainlayout->addLayout(m_botlayout);

    this->setLayout(m_mainlayout);

    setWindowTitle("Options");
}

void OptionsWidget::initConnnect()
{
    connect(m_confirmBtn, SIGNAL(clicked()), this, SLOT(onConfirmHandle()));
    connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelHandle()));
    connect(m_customBtn, SIGNAL(toggled(bool)), m_rowLine, SLOT(setEnabled(bool)));
    connect(m_customBtn, SIGNAL(toggled(bool)), m_colLine, SLOT(setEnabled(bool)));
    connect(m_customBtn, SIGNAL(toggled(bool)), m_mineLine, SLOT(setEnabled(bool)));
    connect(m_group, SIGNAL(toggled(bool)), m_confirmBtn, SLOT(setEnabled(bool)));
    connect(m_rowLine, SIGNAL(editingFinished()), this, SLOT(onCustomTextChangedHandle()));
    connect(m_colLine, SIGNAL(editingFinished()), this, SLOT(onCustomTextChangedHandle()));
}

