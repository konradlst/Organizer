#include "cgFinance.h"
#include <QtGui>
#include <QtSql>
#include <QtWidgets>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QComboBox>
#include "dbGenerator.h"
#include "cgAccountList.h"
#include "cgTransactionList.h"
#include "cgDelegateManager.h"
#include "cgComboBoxDelegate.h"

namespace {
const QString INSERT_DEFAULT = QString("INSERT INTO %1 DEFAULT VALUES");
const QString DELETE = QString("DELETE FROM %1 WHERE id=%2");

enum { TAB_LOG = 0, TAB_ACCOUNT, TAB_TIME, TAB_BOOK, TAB_SPORT, TAB_DEAL };

const QString metascheme("./metascheme.xml");
const QString DEFAULT_DB("concierge.sqlite");

const QString CG_FINANCEACCOUNTS("CG_FINANCEACCOUNTS");
const QString CG_FINANCELOG("CG_FINANCELOG");
const QString CG_TIME("CG_TIME");
const QString CG_BOOK("CG_BOOK");
const QString CG_SPORT("CG_SPORT");
const QString CG_DEAL("CG_DEAL");

#define SAVE_TITLE QObject::trUtf8("Path from SQL database")
#define DEFAULT_PATH QDir::currentPath()
#define FILE_TYPES QObject::trUtf8("All Files (*.*);;SQLite files (*.sqlite)")
}

cgFinance::cgFinance(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      m_tabWidget(new QTabWidget(centralWidget)),
      m_view(new QTableView),
      m_models(new QHash<QString, QSqlTableModel *>),
      m_tableComboBox(new QComboBox(this)),
      m_btnOpenDb(new QPushButton(tr("Open Db"))),
      m_btnAdd(new QPushButton(tr("Add"))),
      m_btnSubmit(new QPushButton(tr("Submit"))),
      m_btnRevert(new QPushButton(tr("&Revert All"))),
      m_btnRemove(new QPushButton(tr("Remove"))),
      m_accountTab(new QWidget(this))
{
    createAccountTab();
    dbGenerate();
    initModel();
    createInterface();

    connect(m_tableComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(currentTableChanged(int)));
    connect(m_btnOpenDb, SIGNAL(clicked()), this, SLOT(dbGenerate()));
    connect(m_btnAdd,    SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(m_btnSubmit, SIGNAL(clicked()), this, SLOT(submit()));
    connect(m_btnRevert, SIGNAL(clicked()), this, SLOT(revertAll()));
    connect(m_btnRemove, SIGNAL(clicked()), this, SLOT(removeRecord()));
}

cgFinance::~cgFinance()
{
}

void cgFinance::currentTableChanged(const int &index)
{
    m_currentTable = m_tables.at(index);
    m_view->setModel(m_models->value(m_currentTable));
}

void cgFinance::submit()
{
    m_models->value(m_currentTable)->database().transaction();
    if (m_models->value(m_currentTable)->submitAll())
        m_models->value(m_currentTable)->database().commit();
    else
        m_models->value(m_currentTable)->database().rollback();
    m_models->value(m_currentTable)->select();
}

void cgFinance::addRecord()
{
    QSqlQuery query;
    query.exec(INSERT_DEFAULT.arg(m_currentTable));
    m_models->value(m_currentTable)->select();
}

void cgFinance::removeRecord()
{
    QSqlQuery query;
    int id = m_view->model()->index(m_view->currentIndex().row() ,0).data().toInt();

    query.exec(DELETE.arg(m_currentTable)
                     .arg(id));
    m_models->value(m_currentTable)->select();
}

void cgFinance::revertAll()
{
    m_models->value(m_currentTable)->database().rollback();
    m_models->value(m_currentTable)->revertAll();
}

void cgFinance::initModel()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(Db::SQLITE);
    db.setDatabaseName(m_currentPathToDb);
    db.open();
    m_tables =  db.tables();

    m_currentTable = m_tables.at(0);
    m_tableComboBox->addItems(m_tables);
    foreach (QString table, m_tables)
    {
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable(table);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        m_models->insert(table, model);
    }
}

void cgFinance::createInterface()
{
    m_tabWidget->addTab(m_view, QString("Tables"));
    m_tabWidget->addTab(m_accountTab, QString("Accounts"));

    m_view->setModel(m_models->value(m_currentTable));
    m_view->verticalHeader()->hide();
    setDelegates();

    m_btnOpenDb->setDefault(true);

    QHBoxLayout *hlay = new QHBoxLayout(this);
    hlay->addWidget(m_tableComboBox);
    hlay->addWidget(m_btnOpenDb);
    hlay->addWidget(m_btnAdd);
    hlay->addWidget(m_btnSubmit);
    hlay->addWidget(m_btnRevert);
    hlay->addWidget(m_btnRemove);

    QVBoxLayout *vlay = new QVBoxLayout(centralWidget);
    vlay->addLayout(hlay);
    vlay->addWidget(m_tabWidget);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Сoncierge: Finance"));
    resize(760,230);
}

void cgFinance::createAccountTab()
{
    cgAccountList *accounts = new cgAccountList;
    cgTransactionList *transactions = new cgTransactionList;

    m_accountTab->setLayout(new QHBoxLayout);
    m_accountTab->layout()->addWidget(accounts->view());
    m_accountTab->layout()->addWidget(transactions->view());

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

QString cgFinance::openDb()
{
    QString path = QFileDialog::getSaveFileName(this, SAVE_TITLE, DEFAULT_PATH,FILE_TYPES);
    m_currentPathToDb = path.isEmpty() ? DEFAULT_DB : path;
    return m_currentPathToDb;
}

void cgFinance::setDelegates()
{
//    QList<QAbstractItemDelegate *> *list =  cgDelegateManager::getDelegateList(m_currentTable);

//    int i=0;
//    foreach (QAbstractItemDelegate d, list)
//    {
//        m_view->setItemDelegateForColumn(i, d);
//        ++i;
//    }
}

void cgFinance::dbGenerate()
{
    QString path = openDb();
    dbGenerator gen = dbGenerator(metascheme, path);
    gen.generate(true);
}
