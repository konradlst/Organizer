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
QString path = QString("concierge.sqlite");

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
      m_btnAdd(new QPushButton(tr("Add"))),
      m_btnSubmit(new QPushButton(tr("Submit"))),
      m_btnRevert(new QPushButton(tr("&Revert All"))),
      m_btnRemove(new QPushButton(tr("Remove"))),
      m_btnBox(new QDialogButtonBox(Qt::Horizontal))
{
    dbGenerate();
    initModel();
    createInterface();

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

    m_logView->setModel(m_models->value(CG_FINANCELOG));
    m_accountView->setModel(m_models->value(CG_FINANCEACCOUNTS));
    m_timeView->setModel(m_models->value(CG_TIME));

    m_logView->verticalHeader()->hide();
    m_accountView->verticalHeader()->hide();
    m_timeView->verticalHeader()->hide();

    m_btnSubmit->setDefault(true);

    m_btnBox->addButton(m_btnAdd, QDialogButtonBox::ActionRole);
    m_btnBox->addButton(m_btnSubmit, QDialogButtonBox::ActionRole);
    m_btnBox->addButton(m_btnRevert, QDialogButtonBox::ActionRole);
    m_btnBox->addButton(m_btnRemove, QDialogButtonBox::ActionRole);

    centralWidget->layout()->addWidget(m_btnBox);
    centralWidget->layout()->addWidget(m_tabWidget);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Сoncierge: Finance"));
    resize(760,230);
}

bool cgFinance::dbGenerate()
{
//    QString path = QFileDialog::getSaveFileName(this, SAVE_TITLE, DEFAULT_PATH,FILE_TYPES);
    dbGenerator gen = dbGenerator(metascheme, path);
    gen.generate();

    return true;
}
