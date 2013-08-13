#include "cgFinanceView.h"
#include "ui_cgFinanceView.h"
#include <QHBoxLayout>
#include "cgAccountList.h"
#include "cgTransactionList.h"

cgFinanceView::cgFinanceView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cgFinanceView)
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

void cgFinanceView::createAccountTab()
{
    cgAccountList *accounts = new cgAccountList;
    cgTransactionList *transactions = new cgTransactionList;

    ui->tabMain->setLayout(new QHBoxLayout);
    ui->tabMain->layout()->addWidget(accounts->view());
    ui->tabMain->layout()->addWidget(transactions->view());

    //test Data
    cgAccount acc = cgAccount(QString("Deposit"), 70);
    accounts->addAccount(acc);
    acc.m_name = QString("Cash");
    acc.m_value = 24;
    accounts->addAccount(acc);

    cgTransaction trans;
    trans.m_comment = "Travel";
    trans.m_value = -20;
    transactions->addTransaction(trans);
    trans.m_comment = "ZP";
    trans.m_value = 15000;
    transactions->addTransaction(trans);
}
