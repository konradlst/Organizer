#include <QtGui>
#include <QtSql>
#include <QtWidgets>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "cgFinance.h"
#include "dbGenerator.h"

namespace {
const QString INSERT = QString("INSERT INTO %1(%2) VALUES(%3)");
const QString DELETE = QString("DELETE FROM %1 WHERE id=%2");

const int TAB_LOG = 0;
const int TAB_ACCOUNT = 1;

QString metascheme = QString("./metascheme.xml");
QString path = QString("concierge.sqlite");

const QString CG_FINANCEACCOUNTS = QString("CG_FINANCEACCOUNTS");
const QString CG_FINANCELOG = QString("CG_FINANCELOG");

#define SAVE_TITLE QObject::trUtf8("Path from SQL database")
#define DEFAULT_PATH QDir::currentPath()
#define FILE_TYPES QObject::trUtf8("All Files (*.*);;SQLite files (*.sqlite)")
}

cgFinance::cgFinance(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      tabWidget(new QTabWidget(centralWidget)),
      tabLog(new QWidget()),
      m_tabMain(new QWidget()),
      logView(new QTableView),
      m_mainView(new QTableView),
      addButton(new QPushButton(tr("Add"))),
      submitButton(new QPushButton(tr("Submit"))),
      revertButton(new QPushButton(tr("&Revert All"))),
      m_btnRemove(new QPushButton(tr("Remove"))),
      buttonBox(new QDialogButtonBox(Qt::Horizontal))
{
    show();
    dbGenerate();
    initModel();
    createInterface();

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(revertButton, SIGNAL(clicked()), logModel, SLOT(revertAll()));
    connect(revertButton, SIGNAL(clicked()), m_accountModel, SLOT(revertAll()));
    connect(m_btnRemove, SIGNAL(clicked()), this, SLOT(removeRecord()));
}

cgFinance::~cgFinance()
{
}

void cgFinance::submit()
{
    if(tabWidget->currentIndex() == TAB_LOG)
    {
        logModel->database().transaction();
        if (logModel->submitAll())
            logModel->database().commit();
        else
            logModel->database().rollback();

        logModel->select();
    }
    else if(tabWidget->currentIndex() == TAB_ACCOUNT)
    {
        m_accountModel->database().transaction();
        if (m_accountModel->submitAll())
            m_accountModel->database().commit();
        else
            m_accountModel->database().rollback();

        m_accountModel->select();
    }
}

void cgFinance::addRecord()
{
    QSqlQuery query;

    if(tabWidget->currentIndex() == TAB_LOG)
    {
        query.exec(INSERT.arg(CG_FINANCELOG)
                   .arg("timestamp,operation,value,sendfrom,sendto,comment")
                   .arg("'2013.07.25 15:05',' ',' ',' ',' ',' '"));
        logModel->select();
    }
    else if(tabWidget->currentIndex() == TAB_ACCOUNT)
    {
        query.exec(INSERT.arg(CG_FINANCEACCOUNTS)
                   .arg("number,status,type,name,value")
                   .arg("' ',' ',' ',' ',' '"));
        m_accountModel->select();
    }
}

void cgFinance::removeRecord()
{
    QSqlQuery query;

    if(tabWidget->currentIndex() == TAB_LOG)
    {
        query.exec(DELETE.arg(CG_FINANCELOG)
                   .arg(logView->model()->index(logView->currentIndex().row(),0).data().toInt()));
        logModel->select();
    }
    else if(tabWidget->currentIndex() == TAB_ACCOUNT)
    {
        query.exec(DELETE.arg(CG_FINANCEACCOUNTS)
                   .arg(logView->model()->index(logView->currentIndex().row(),0).data().toInt()));
        m_accountModel->select();
    }
}


void cgFinance::initModel()
{
    logModel = new QSqlTableModel(this);
    logModel->setTable(CG_FINANCELOG);
    logModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    logModel->select();
//    logModel->setHeaderData(1, Qt::Horizontal, QObject::tr("number"));

    m_accountModel = new QSqlTableModel(this);
    m_accountModel->setTable(CG_FINANCEACCOUNTS);
    m_accountModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_accountModel->select();
}

void cgFinance::createInterface()
{
    centralWidget->setLayout(new QVBoxLayout(centralWidget));

    tabLog->setLayout(new QVBoxLayout(tabLog));
    tabLog->layout()->addWidget(logView);

    m_tabMain->setLayout(new QVBoxLayout(m_tabMain));
    m_tabMain->layout()->addWidget(m_mainView);

    tabWidget->addTab(tabLog, QString("Log"));
    tabWidget->addTab(m_tabMain, QString("Account"));

    logView->setModel(logModel);
    m_mainView->setModel(m_accountModel);

    submitButton->setDefault(true);

    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(m_btnRemove, QDialogButtonBox::ActionRole);

    centralWidget->layout()->addWidget(buttonBox);
    centralWidget->layout()->addWidget(tabWidget);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Сoncierge: Finance"));
    resize(760,230);
}

bool cgFinance::dbGenerate()
{
//    QString path = QFileDialog::getSaveFileName(this, SAVE_TITLE, DEFAULT_PATH,FILE_TYPES);
    dbGenerator gen = dbGenerator(metascheme,path);
    gen.generate();

    return true;
}
