#include <QSqlQuery>
#include <QStringList>
#include "driverSqlite.h"

namespace
{
const QString Insert = "INSERT INTO %1 (%2) VALUES %3;";
const QString SelectFull = "SELECT %1 FROM %2 WHERE %3;";
const QString Select = "SELECT %1 FROM %2;";
const QString AndSeparator = " AND ";
const QString CommaSeparator = ", ";
const QString AllFields = "*";

const QString Contacts = "CG_CONTACTS";
const QString Accounts = "CG_FINANCEACCOUNTS";
const QString Transactions = "CG_FINANCELOG";
const QString TimeLine = "CG_TIME";
const QString Books = "CG_BOOK";
const QString Dealss = "CG_DEAL";

const QString ConnectionName = "SqliteDriverConnection";
const QString QSqlite = "QSQLITE";
}

DriverSqlite::DriverSqlite(QObject *parent)
    : QObject(parent)
{
}

Data::Table *DriverSqlite::contacts() const
{
    //FIXME :
//    QSqlQuery(Select.arg(AllFields, Contacts));
    return new Data::Table;
}

Data::Record *DriverSqlite::contact(const QString &alias) const
{
    //FIXME :
//    QSqlQuery(SelectFull.arg(AllFields, Contacts, "alias = " + alias));
    return new Data::Record;
}

Data::Table *DriverSqlite::financeAccounts() const
{
    //FIXME :
//    QSqlQuery(Select.arg(AllFields, Accounts));
    return new Data::Table;
}

Data::Table *DriverSqlite::financeTransaction(const QDate &date) const
{
    //FIXME :
//    QSqlQuery(Select.arg(AllFields, Transactions));
    return new Data::Table;
}

Data::Table *DriverSqlite::timeLine(const QDate &date) const
{
    //FIXME :
//    QSqlQuery(Select.arg(AllFields, TimeLine));
    return new Data::Table;
}

Data::Table *DriverSqlite::deals(const QDate &date) const
{
    //FIXME :
//    QSqlQuery(Select.arg(AllFields, Deals));
    return new Data::Table;
}

Data::Table *DriverSqlite::notes(const QStringList &params) const
{
    //FIXME :
//    QSqlQuery(Select.arg(AllFields, Deals));
    return new Data::Table;
}

void DriverSqlite::addAccount(const Data::Record &record)
{
    openDb();
    //FIXME :
}

void DriverSqlite::addTransaction(const Data::Record &record)
{
    openDb();
    //FIXME :
}

void DriverSqlite::addTimeRecord(const Data::Record &record)
{
    //FIXME :
}

void DriverSqlite::addDeal(const Data::Record &record)
{
    openDb();
    //FIXME :
}

void DriverSqlite::addContact(const Data::Record &record)
{
    openDb();
    //FIXME :
}

void DriverSqlite::addNote(const Data::Record &record)
{
    openDb();
    //FIXME :
}

bool DriverSqlite::openDb()
{
    if (QSqlDatabase::connectionNames().contains(ConnectionName))
        m_db = QSqlDatabase::database(ConnectionName);
    else
        m_db = QSqlDatabase::addDatabase(QSqlite, ConnectionName);
    m_db.setDatabaseName(m_pathToDb);
    if (!m_db.open())
        return false;
}
