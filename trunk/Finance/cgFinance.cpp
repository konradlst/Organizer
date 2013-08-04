#include <QtGui>
#include <QtSql>
#include <QtWidgets>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QComboBox>
#include "cgFinance.h"
#include "dbGenerator.h"
#include "cgFinanceView.h"

namespace {
const QString INSERT_DEFAULT = QString("INSERT INTO %1 DEFAULT VALUES");
const QString DELETE = QString("DELETE FROM %1 WHERE id=%2");

enum { TAB_LOG = 0, TAB_ACCOUNT, TAB_TIME, TAB_BOOK, TAB_SPORT, TAB_DEAL };

QString metascheme = QString("./metascheme.xml");
QString DEFAULT_DB = QString("concierge.sqlite");

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
    connect(m_btnAdd, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(m_btnSubmit, SIGNAL(clicked()), this, SLOT(submit()));
    connect(m_btnRevert, SIGNAL(clicked()), m_models->value(m_currentTable), SLOT(revertAll()));
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
    int id = m_view->model()->index(m_view->currentIndex().row(),0).data().toInt();

    query.exec(DELETE.arg(m_currentTable)
                     .arg(id));
    m_models->value(m_currentTable)->select();
}

void cgFinance::initModel()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","initModel");
    db.setDatabaseName(m_currentPathToDb);
    db.open();
    m_tables =  db.tables();
    db.close();

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

    centralWidget->setLayout(vlay);
    setCentralWidget(centralWidget);
    setWindowTitle(tr("Сoncierge: Finance"));
    resize(760,230);
}

void cgFinance::createAccountTab()
{
    //FIXME simple
    cgFinanceView view;

    QFrame *lineAccount       = view.getLine();
    QFrame *lineToday         = view.getLine();
    QDateEdit *date           = view.getDateWidget();
    QProgressBar *cashBar     = view.getProgressBar();
    QProgressBar *depositBar  = view.getProgressBar();
    QDoubleSpinBox *resumeBox = view.getDoubleSpinBox();
    QDoubleSpinBox *dsbTravel = view.getDoubleSpinBox();
    QDoubleSpinBox *dsbZp     = view.getDoubleSpinBox();
    cashBar->setMaximum(100);
    cashBar->setValue(24);
    depositBar->setMaximum(100);
    depositBar->setValue(70);
    resumeBox->setValue(500);
    dsbTravel->setValue(-20);
    dsbZp->setValue(15000);

    QFormLayout *lay = new QFormLayout;
    lay->addRow("Cash", cashBar);
    lay->addRow("Deposit", depositBar);
    lay->addRow(lineAccount);
    lay->addRow("Total :", resumeBox);

    QGroupBox *account = new QGroupBox("Accounts");
    account->setLayout(lay);

    QFormLayout *layToday = new QFormLayout;
    layToday->addRow("travel", dsbTravel);
    layToday->addRow("ZP", dsbZp);

    QGroupBox *gbToday = new QGroupBox("Today");
    gbToday->setLayout(layToday);

    QVBoxLayout *vlay = new QVBoxLayout(m_accountTab);
    vlay->addWidget(date);
    vlay->addWidget(new QPushButton("Add Transaction"));
    vlay->addWidget(lineToday);
    vlay->addWidget(gbToday);

    QWidget *wdt = new QWidget();
    wdt->setLayout(vlay);

    m_accountTab->setLayout(new QHBoxLayout);
    m_accountTab->layout()->addWidget(account);
    m_accountTab->layout()->addWidget(wdt);
}

QString cgFinance::openDb()
{
    QString path = QFileDialog::getSaveFileName(this, SAVE_TITLE, DEFAULT_PATH,FILE_TYPES);
    m_currentPathToDb = path.isEmpty() ? DEFAULT_DB : path;
    return m_currentPathToDb;
}

void cgFinance::dbGenerate()
{
    QString path = openDb();
    dbGenerator gen = dbGenerator(metascheme, path);
    gen.generate();
}
