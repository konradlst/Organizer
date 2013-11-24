#include <QSqlTableModel>
#include <QPushButton>
#include <QHeaderView>
#include <QFileDialog>
#include <QTableView>
#include <QBoxLayout>
#include <QComboBox>
#include <QSqlQuery>
#include <QDir>
#include "cgComboBoxDelegate.h"
#include "cgDelegateManager.h"
#include "cgMetaschemeConst.h"
#include "dbGenerator.h"
#include "cgDBManager.h"

namespace
{
const QString DefaultDb = "concierge.sqlite";
const QString Title = QObject::trUtf8("Organizer: DBManager");
const QString OpenTitle = QObject::trUtf8("Path to SQL database");
const QString FileTypes = QObject::trUtf8("All Files (*.*);;SQLite files (*.sqlite)");

const QString OpenDb = QObject::trUtf8("Open Db");
const QString AddRecord = QObject::trUtf8("Add");
const QString RemoveRecord = QObject::trUtf8("Remove");
const QString Submit = QObject::trUtf8("Submit");
const QString RevertAll = QObject::trUtf8("&Revert All");
}

cgDBManager::cgDBManager(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      m_view(new QTableView),
      m_models(new QHash<QString, QSqlTableModel*>),
      m_tableComboBox(new QComboBox(this)),
      m_btnOpenDb(new QPushButton(OpenDb)),
      m_btnAdd(new QPushButton(AddRecord)),
      m_btnSubmit(new QPushButton(Submit)),
      m_btnRevert(new QPushButton(RevertAll)),
      m_btnRemove(new QPushButton(RemoveRecord))
{
    dbGenerate();
    createInterface();

    connect(m_tableComboBox, SIGNAL(currentIndexChanged(int)),
            SLOT(currentTableChanged(int)));
    connect(m_btnOpenDb, SIGNAL(clicked()), SLOT(dbGenerate()));
    connect(m_btnAdd,    SIGNAL(clicked()), SLOT(addRecord()));
    connect(m_btnSubmit, SIGNAL(clicked()), SLOT(submit()));
    connect(m_btnRevert, SIGNAL(clicked()), SLOT(revertAll()));
    connect(m_btnRemove, SIGNAL(clicked()), SLOT(removeRecord()));
}

void cgDBManager::currentTableChanged(const int index)
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
    int id = m_view->model()->index(m_view->currentIndex().row(), 0).data().toInt();
    query.exec(SQL::DELETE_WHERE.arg(m_currentTable, QString::number(id)));
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
    if (m_tables.isEmpty())
        return;

    m_currentTable = m_tables.at(0);
    m_tableComboBox->addItems(m_tables);
    foreach (const QString &table, m_tables)
    {
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable(table);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        m_models->insert(table, model);
    }
    currentTableChanged(0);
}

void cgDBManager::createInterface()
{
    m_view->setModel(m_models->value(m_currentTable));
    m_view->setSortingEnabled(true);
    m_view->setColumnHidden(0, true);
    if (!m_currentTable.isNull())
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
    setWindowTitle(Title);
    resize(550, 550);
}

void cgDBManager::setDelegates()
{
    for (int i = 0; i < m_view->model()->columnCount(); ++i)
        m_view->setItemDelegateForColumn(i, 0);

    QList<QAbstractItemDelegate*> *list =  cgDelegateManager::getDelegateList(m_currentTable);

    int i=0;
    foreach (QAbstractItemDelegate *d, *list)
    {
        if (d)
            m_view->setItemDelegateForColumn(i, d);
        ++i;
    }
}

QString cgDBManager::openDb()
{
    QString path = QFileDialog::getSaveFileName(this, OpenTitle,
                                                QDir::currentPath(), FileTypes);
    m_currentPathToDb = path.isEmpty() ? DefaultDb : path;
    return m_currentPathToDb;
}

void cgDBManager::dbGenerate()
{
    dbGenerator gen = dbGenerator(openDb());
    gen.generate(true);
    initModel();
}
