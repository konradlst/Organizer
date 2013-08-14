#include "cgFinanceView.h"
#include "ui_cgFinanceView.h"
#include <QHBoxLayout>
#include "cgAccountList.h"
#include "cgTransactionList.h"

cgFinanceView::cgFinanceView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cgFinanceView),
    m_accounts(new cgAccountList),
    m_transactions(new cgTransactionList)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->vLayout);
    ui->tabStatistic->setLayout(ui->staticticLayout);
    createAccountTab();
}

cgFinanceView::~cgFinanceView()
{
    delete ui;
}

bool cgFinanceView::addTransaction()
{
    cgTransaction transaction;
    m_transactions->addTransaction(transaction);
    return true;
}

void cgFinanceView::createAccountTab()
{
    ui->tabMain->setLayout(new QHBoxLayout);
    ui->tabMain->layout()->addWidget(m_accounts->view());
    ui->tabMain->layout()->addWidget(m_transactions->view());

    //test Data
    cgAccount acc = cgAccount(QString("Deposit"), 70);
    m_accounts->addAccount(acc);
    acc.m_name = QString("Cash");
    acc.m_value = 24;
    m_accounts->addAccount(acc);

    cgTransaction trans;
    trans.m_comment = "Travel";
    trans.m_value = -20;
    m_transactions->addTransaction(trans);
    trans.m_comment = "ZP";
    trans.m_value = 15000;
    m_transactions->addTransaction(trans);
}
