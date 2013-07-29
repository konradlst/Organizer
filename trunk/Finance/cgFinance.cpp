#include <QtGui>
#include <QtSql>
#include <QtWidgets>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "cgFinance.h"
#include "dbGenerator.h"

namespace {
const QString INSERT_DEFAULT = QString("INSERT INTO %1 DEFAULT VALUES");
const QString DELETE = QString("DELETE FROM %1 WHERE id=%2");

enum { TAB_LOG = 0, TAB_ACCOUNT, TAB_TIME };

QString metascheme = QString("./metascheme.xml");
QString DEFAULT_DB = QString("concierge.sqlite");

const QString CG_FINANCEACCOUNTS = QString("CG_FINANCEACCOUNTS");
const QString CG_FINANCELOG = QString("CG_FINANCELOG");
const QString CG_TIME = QString("CG_TIME");

#define SAVE_TITLE QObject::trUtf8("Path from SQL database")
#define DEFAULT_PATH QDir::currentPath()
#define FILE_TYPES QObject::trUtf8("All Files (*.*);;SQLite files (*.sqlite)")
}

cgFinance::cgFinance(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      m_tabWidget(new QTabWidget(centralWidget)),
      m_logView(new QTableView),
      m_accountView(new QTableView),
      m_timeView(new QTableView),
      m_models(new QHash<QString, QSqlTableModel *>),
      m_btnOpenDb(new QPushButton(tr("Open Db"))),
      m_btnAdd(new QPushButton(tr("Add"))),
      m_btnSubmit(new QPushButton(tr("Submit"))),
      m_btnRevert(new QPushButton(tr("&Revert All"))),
      m_btnRemove(new QPushButton(tr("Remove"))),
      m_btnBox(new QDialogButtonBox(Qt::Horizontal)),
      m_accountTab(new QWidget(this))
{
    createAccountTab();
    dbGenerate();
    initModel();
    createInterface();

    connect(m_btnOpenDb, SIGNAL(clicked()), this, SLOT(dbGenerate()));
    connect(m_btnAdd, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(m_btnSubmit, SIGNAL(clicked()), this, SLOT(submit()));
    connect(m_btnRevert, SIGNAL(clicked()), m_models->value(CG_FINANCELOG), SLOT(revertAll()));
    connect(m_btnRevert, SIGNAL(clicked()), m_models->value(CG_FINANCEACCOUNTS), SLOT(revertAll()));
    connect(m_btnRevert, SIGNAL(clicked()), m_models->value(CG_TIME), SLOT(revertAll()));
    connect(m_btnRemove, SIGNAL(clicked()), this, SLOT(removeRecord()));
}

cgFinance::~cgFinance()
{
}

void cgFinance::submit()
{
    QString tableName;
    int index = m_tabWidget->currentIndex();

    switch (index)
    {
    case TAB_LOG:
        tableName = CG_FINANCELOG;
        break;
    case TAB_ACCOUNT:
        tableName = CG_FINANCEACCOUNTS;
        break;
    case TAB_TIME:
        tableName = CG_TIME;
    default:
        break;
    }

    if(!tableName.isEmpty())
    {
        m_models->value(tableName)->database().transaction();
        if (m_models->value(tableName)->submitAll())
            m_models->value(tableName)->database().commit();
        else
            m_models->value(tableName)->database().rollback();
        m_models->value(tableName)->select();
    }
}

void cgFinance::addRecord()
{
    QSqlQuery query;
    QString tableName;
    int index = m_tabWidget->currentIndex();

    switch (index)
    {
    case TAB_LOG:
        tableName = CG_FINANCELOG;
        query.exec(INSERT_DEFAULT.arg(CG_FINANCELOG));
        break;
    case TAB_ACCOUNT:
        tableName = CG_FINANCEACCOUNTS;
        query.exec(INSERT_DEFAULT.arg(CG_FINANCEACCOUNTS));
        break;
    case TAB_TIME:
        tableName = CG_TIME;
        query.exec(INSERT_DEFAULT.arg(CG_TIME));
    default:
        break;
    }
    m_models->value(tableName)->select();
}

void cgFinance::removeRecord()
{
    QSqlQuery query;
    QString tableName;
    int id;
    int index = m_tabWidget->currentIndex();

    switch (index)
    {
    case TAB_LOG:
        tableName = CG_FINANCELOG;
        id = m_logView->model()->index(m_logView->currentIndex().row(),0).data().toInt();
        break;
    case TAB_ACCOUNT:
        tableName = CG_FINANCEACCOUNTS;
        id = m_accountView->model()->index(m_accountView->currentIndex().row(),0).data().toInt();
        break;
    case TAB_TIME:
        tableName = CG_TIME;
        id = m_timeView->model()->index(m_timeView->currentIndex().row(),0).data().toInt();
    default:
        break;
    }

    if(!tableName.isEmpty())
    {
        query.exec(DELETE.arg(tableName)
                         .arg(id));
        m_models->value(tableName)->select();
    }
}

void cgFinance::initModel()
{
    QStringList tables;
    tables << CG_FINANCELOG
           << CG_FINANCEACCOUNTS
           << CG_TIME;

    foreach (QString table, tables)
    {
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable(table);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        m_models->insert(table, model);
    }
//    QSqlTableModel::setHeaderData(1, Qt::Horizontal, QObject::tr("TEXT"));
}

void cgFinance::createInterface()
{
    centralWidget->setLayout(new QVBoxLayout(centralWidget));

    m_tabWidget->addTab(m_logView, QString("Log"));
    m_tabWidget->addTab(m_accountView, QString("Account"));
    m_tabWidget->addTab(m_timeView, QString("Time"));
    m_tabWidget->addTab(m_accountTab, QString("MainAccount"));

    m_logView->setModel(m_models->value(CG_FINANCELOG));
    m_accountView->setModel(m_models->value(CG_FINANCEACCOUNTS));
    m_timeView->setModel(m_models->value(CG_TIME));

    m_logView->verticalHeader()->hide();
    m_accountView->verticalHeader()->hide();
    m_timeView->verticalHeader()->hide();

    m_btnSubmit->setDefault(true);

    m_btnBox->addButton(m_btnOpenDb, QDialogButtonBox::AcceptRole);
    m_btnBox->addButton(m_btnAdd,    QDialogButtonBox::ActionRole);
    m_btnBox->addButton(m_btnSubmit, QDialogButtonBox::ActionRole);
    m_btnBox->addButton(m_btnRevert, QDialogButtonBox::ActionRole);
    m_btnBox->addButton(m_btnRemove, QDialogButtonBox::ActionRole);

    centralWidget->layout()->addWidget(m_btnBox);
    centralWidget->layout()->addWidget(m_tabWidget);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Сoncierge: Finance"));
    resize(760,230);
}

QString cgFinance::openDb()
{
    return QFileDialog::getSaveFileName(this, SAVE_TITLE, DEFAULT_PATH,FILE_TYPES);
}

void cgFinance::createAccountTab()
{
    //FIXME simple
    QGroupBox *account = new QGroupBox("Accounts");

    m_accountTab->setLayout(new QHBoxLayout);

    QFormLayout *lay = new QFormLayout;
    QProgressBar *cashBar = new QProgressBar();
    cashBar->setMaximum(100);
    cashBar->setValue(24);
    cashBar->setTextVisible(true);
    cashBar->setFormat("%v p.");

    QProgressBar *depositBar = new QProgressBar();
    depositBar->setMaximum(100);
    depositBar->setValue(70);
    depositBar->setTextVisible(true);
    depositBar->setFormat("%v p.");

    QFrame *lineAccount = new QFrame(m_accountTab);
    lineAccount->setFrameShape(QFrame::HLine);
    lineAccount->setFrameShadow(QFrame::Sunken);

    QSpinBox *resumeBox = new QSpinBox();
    resumeBox->setReadOnly(true);
    resumeBox->setButtonSymbols(QSpinBox::NoButtons);
    resumeBox->setSuffix(" p.");
    resumeBox->setMinimum(-100000);
    resumeBox->setMaximum(100000);
    resumeBox->setValue(500);

    lay->addRow("Cash", cashBar);
    lay->addRow("Deposit", depositBar);
    lay->addWidget(lineAccount);
    lay->addRow("Total", resumeBox);

    account->setLayout(lay);

    QVBoxLayout *vlay = new QVBoxLayout(m_accountTab);
    QDateEdit *date = new QDateEdit(QDate::currentDate());
    date->setFrame(false);
    date->setReadOnly(true);
    date->setButtonSymbols(QDateEdit::NoButtons);
    date->setAlignment(Qt::AlignCenter);
    date->setDisplayFormat("ddd, dd MMMM yyyy года");

    QFrame *lineToday = new QFrame(m_accountTab);
    lineToday->setFrameShape(QFrame::HLine);
    lineToday->setFrameShadow(QFrame::Sunken);

    QGroupBox *gbToday = new QGroupBox("Today");

    QDoubleSpinBox *dsbTravel = new QDoubleSpinBox();
    dsbTravel->setReadOnly(true);
    dsbTravel->setButtonSymbols(QDoubleSpinBox::NoButtons);
    dsbTravel->setSuffix(" p.");
    dsbTravel->setMinimum(-100000);
    dsbTravel->setMaximum(100000);
    dsbTravel->setValue(-20);

    QDoubleSpinBox *dsbZp = new QDoubleSpinBox();
    dsbZp->setReadOnly(true);
    dsbZp->setButtonSymbols(QDoubleSpinBox::NoButtons);
    dsbZp->setSuffix(" p.");
    dsbZp->setMinimum(-100000);
    dsbZp->setMaximum(100000);
    dsbZp->setValue(15000);

    QFormLayout *layToday = new QFormLayout;
    layToday->addRow("travel", dsbTravel);
    layToday->addRow("ZP", dsbZp);

    gbToday->setLayout(layToday);

    vlay->addWidget(date);
    vlay->addWidget(new QPushButton("Add Transaction"));
    vlay->addWidget(lineToday);
    vlay->addWidget(gbToday);

    QWidget *wdt = new QWidget();
    wdt->setLayout(vlay);

    m_accountTab->layout()->addWidget(account);
    m_accountTab->layout()->addWidget(wdt);
}

bool cgFinance::dbGenerate()
{
    QString path = openDb();
    dbGenerator gen = dbGenerator(metascheme, path.isEmpty() ? DEFAULT_DB : path);

    return gen.generate();
}
