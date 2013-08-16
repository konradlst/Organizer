#include "cgDBManager.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QComboBox>
#include "dbGenerator.h"
#include "cgDelegateManager.h"
#include "cgComboBoxDelegate.h"
#include "cgMetaschemeConst.h"

namespace
{
enum { TAB_LOG = 0, TAB_ACCOUNT, TAB_TIME, TAB_BOOK, TAB_SPORT, TAB_DEAL };

const QString TITLE = QObject::trUtf8("Сoncierge: DBManager");

const QString DEFAULT_DB("concierge.sqlite");
const QString CG_FINANCEACCOUNTS("CG_FINANCEACCOUNTS");
const QString CG_FINANCELOG("CG_FINANCELOG");
const QString CG_TIME("CG_TIME");
const QString CG_BOOK("CG_BOOK");
const QString CG_SPORT("CG_SPORT");
const QString CG_DEAL("CG_DEAL");

#define OPEN_TITLE QObject::trUtf8("Path to SQL database")
#define DEFAULT_PATH QDir::currentPath()
#define FILE_TYPES QObject::trUtf8("All Files (*.*);;SQLite files (*.sqlite)")
}

cgDBManager::cgDBManager(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      m_view(new QTableView),
      m_models(new QHash<QString, QSqlTableModel *>),
      m_tableComboBox(new QComboBox(this)),
      m_btnOpenDb(new QPushButton(tr("Open Db"))),
      m_btnAdd(new QPushButton(tr("Add"))),
      m_btnSubmit(new QPushButton(tr("Submit"))),
      m_btnRevert(new QPushButton(tr("&Revert All"))),
      m_btnRemove(new QPushButton(tr("Remove")))
{
    dbGenerate();
    createInterface();

    connect(m_tableComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(currentTableChanged(int)));
    connect(m_btnOpenDb, SIGNAL(clicked()), this, SLOT(dbGenerate()));
    connect(m_btnAdd,    SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(m_btnSubmit, SIGNAL(clicked()), this, SLOT(submit()));
    connect(m_btnRevert, SIGNAL(clicked()), this, SLOT(revertAll()));
    connect(m_btnRemove, SIGNAL(clicked()), this, SLOT(removeRecord()));
}

cgDBManager::~cgDBManager()
{
}

void cgDBManager::currentTableChanged(const int &index)
{
    m_currentTable = m_tables.at(index);
    m_view->setModel(m_models->value(m_currentTable));
    setDelegates();
}

void cgDBManager::submit()
{
    m_models->value(m_currentTable)->database().transaction();
    if (m_models->value(m_currentTable)->submitAll())
        m_models->value(m_currentTable)->database().commit();
    else
        m_models->value(m_currentTable)->database().rollback();
    m_models->value(m_currentTable)->select();
}

void cgDBManager::addRecord()
{
    QSqlQuery query;
    query.exec(SQL::INSERT_DEFAULT.arg(m_currentTable));
    m_models->value(m_currentTable)->select();
}

void cgDBManager::removeRecord()
{
    QSqlQuery query;
    int id = m_view->model()->index(m_view->currentIndex().row() ,0).data().toInt();

    query.exec(SQL::DELETE.arg(m_currentTable)
                     .arg(id));
    m_models->value(m_currentTable)->select();
}

void cgDBManager::revertAll()
{
    m_models->value(m_currentTable)->database().rollback();
    m_models->value(m_currentTable)->revertAll();
}

void cgDBManager::initModel()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(SQL::SQLITE);
    db.setDatabaseName(m_currentPathToDb);
    db.open();
    m_tables =  db.tables();

    if(!m_tables.isEmpty())
    {
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
        currentTableChanged(0);
    }
}

void cgDBManager::createInterface()
{
    m_view->setModel(m_models->value(m_currentTable));
    m_view->verticalHeader()->hide();
    if(!m_currentTable.isNull())
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
    vlay->addWidget(m_view);

    setCentralWidget(centralWidget);
    setWindowTitle(TITLE);
    resize(760,230);
}

QString cgDBManager::openDb()
{
    QString path = QFileDialog::getOpenFileName(this, OPEN_TITLE,
                                                DEFAULT_PATH,FILE_TYPES);
    m_currentPathToDb = path.isEmpty() ? DEFAULT_DB : path;
    return m_currentPathToDb;
}

void cgDBManager::setDelegates()
{
    for(int i=0; i<m_view->model()->columnCount(); ++i)
        m_view->setItemDelegateForColumn(i, 0);

    QList<QAbstractItemDelegate *> *list =  cgDelegateManager::getDelegateList(m_currentTable);

    int i=0;
    foreach (QAbstractItemDelegate *d, *list)
    {
        if(d)
            m_view->setItemDelegateForColumn(i, d);
        ++i;
    }
}

void cgDBManager::dbGenerate()
{
    dbGenerator gen = dbGenerator(openDb());
    gen.generate(true);
    initModel();
}
