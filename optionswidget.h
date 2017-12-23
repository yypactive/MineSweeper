#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <qDebug>

class OptionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsWidget(QWidget *parent = 0);

public:
    static const unsigned ms_easyRow = 9;
    static const unsigned ms_easyCol = 9;
    static const unsigned ms_easyMine = 10;

    static const unsigned ms_normalRow = 16;
    static const unsigned ms_normalCol = 16;
    static const unsigned ms_normalMine = 40;

    static const unsigned ms_hardRow = 16;
    static const unsigned ms_hardCol = 30;
    static const unsigned ms_hardMine = 99;

    static const unsigned ms_comMinRow = 9;
    static const unsigned ms_comMinCol = 9;
    static const unsigned ms_comMinMine = 10;

    static const unsigned ms_comMaxRow = 24;
    static const unsigned ms_comMaxCol = 30;
    static const unsigned ms_comMaxMine = 668;

signals:
    sendOptions(unsigned, unsigned, unsigned);

private slots:
    void onConfirmHandle();
    void onCancelHandle();
    void onCustomTextChangedHandle();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    void init();
    void initBtn();
    void initLabel();
    void initLine();
    void initWindiow();
    void initConnnect();

private:
    unsigned m_row;
    unsigned m_col;
    unsigned m_mine;
    QVBoxLayout * m_mainlayout;
    QHBoxLayout * m_botlayout;

    QRadioButton* m_lastBtn;

    QRadioButton* m_easyBtn;
    QRadioButton* m_normalBtn;
    QRadioButton* m_hardBtn;
    QRadioButton* m_customBtn;

    QLabel * m_easyDiffLab;
    QLabel * m_easyMinelab;
    QLabel * m_easySizelab;

    QLabel * m_normalDiffLab;
    QLabel * m_normalMinelab;
    QLabel * m_normalSizelab;

    QLabel * m_hardDiffLab;
    QLabel * m_hardMinelab;
    QLabel * m_hardSizelab;

    QLabel * m_customDLab;
    QLabel * m_customHLab;
    QLabel * m_customWlab;
    QLabel * m_custonMlab;

    QGroupBox* m_group;
    QGridLayout* m_grouplayout;

    QButtonGroup*  m_BtnGroup;

    QLineEdit* m_rowLine;
    QLineEdit* m_colLine;
    QLineEdit* m_mineLine;

    QIntValidator * m_rowVal;
    QIntValidator * m_colVal;
    QIntValidator * m_mineVal;

    QPushButton* m_confirmBtn;
    QPushButton* m_cancelBtn;
};

#endif // OPTIONSWIDGET_H
