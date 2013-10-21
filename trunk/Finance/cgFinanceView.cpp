#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHBoxLayout>
#include <QFileDialog>
#include "cgTransactionList.h"
#include "cgAccountList.h"
#include "cgFinanceView.h"
#include "ui_cgFinanceView.h"

namespace
{
    const QString Qsqlite = "QSQLITE";
    const QString ConnectionName = "ChooseFinanceDataConnection";
    const QString TitleChooseDb = QObject::trUtf8("Choose Db");
    const QString FileTypes = QObject::trUtf8("All Files (*.*);;SQLite files (*.sqlite)");
}

cgFinanceView::cgFinanceView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::cgFinanceView),
      m_accounts(new cgAccountList),
      m_transactions(new cgTransactionList)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->vLayout);
    ui->tabStatistic->setLayout(ui->staticticLayout);
    createAccountTab();

    connect(ui->pbChooseDb, SIGNAL(clicked()), this, SLOT(chooseDb()));
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

void cgFinanceView::chooseDb()
{
    QString path = QFileDialog::getOpenFileName(this, TitleChooseDb, QDir::currentPath(), FileTypes);
    QSqlDatabase db = QSqlDatabase::addDatabase(Qsqlite, ConnectionName);
    db.setDatabaseName(path);
    db.open();
//    QString queryCurrentIn = "SELECT SUM(VALUE) FROM CG_FINANCELOG WHERE timestamp=CURRENT_TIMESTAMP AND SENDFROM='IN'";
//    QString queryCurrentOut = "SELECT SUM(VALUE) FROM CG_FINANCELOG WHERE timestamp=CURRENT_TIMESTAMP AND SENDTO='OUT'"
//    QSqlQuery(query, db);
    db.close();
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
