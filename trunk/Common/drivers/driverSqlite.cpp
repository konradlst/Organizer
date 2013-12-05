﻿#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include "cgMetaschemeConst.h"
#include "logger.h"
#include "driverSqlite.h"

namespace
{
const QString Insert = "INSERT INTO %1 (%2) VALUES %3;";
const QString SelectFull = "SELECT %1 FROM %2 WHERE %3;";
const QString Select = "SELECT %1 FROM %2;";
const QString AndSeparator = " AND ";
const QString CommaSeparator = ", ";
const QString AllFields = "*";

const QString Contacts = "CONTACTS";
const QString Accounts = "ACCOUNTS";
const QString Transactions = "TRANSACTIONS";
const QString Times = "TIMES";
const QString Books = "BOOKS";
const QString Deals = "DEALS";

const QString ConnectionName = "SqliteDriverConnection";
const QString QSqlite = "QSQLITE";
}

DriverSqlite::DriverSqlite(QObject *parent)
    : QObject(parent)
{
}

Data::Table *DriverSqlite::contacts()
{
    openDb();
    QSqlQuery q = QSqlQuery(Select.arg(AllFields, Contacts));
    if (!q.exec())
        return 0;

    Data::Table *table = new Data::Table;
    while (q.next())
    {
        Data::Record *record = new Data::Record;
        for (int counter = 0; counter < q.record().count(); ++counter)
            record->append(q.value(counter));
        table->append(record);
    }
    return table;
}

Data::Record *DriverSqlite::contact(const QString &alias)
{
    openDb();
    QSqlQuery q = QSqlQuery(SelectFull.arg(AllFields, Contacts, "alias = " + alias));
    if (!q.exec())
        return 0;

    Data::Record *record = new Data::Record;
    if (q.first())
    {
        for (int counter = 0; counter < q.record().count(); ++counter)
            record->append(q.value(counter));
        return record;
    }
    return 0;
}

Data::Table *DriverSqlite::accounts()
{
    openDb();
    QSqlQuery q = QSqlQuery(Select.arg(AllFields, Accounts));
    if (!q.exec())
        return 0;

    Data::Table *table = new Data::Table;
    while (q.next())
    {
        Data::Record *record = new Data::Record;
        for (int counter = 0; counter < q.record().count(); ++counter)
            record->append(q.value(counter));
        table->append(record);
    }
    return table;
}

Data::Table *DriverSqlite::transactions(const QDate &date)
{
    openDb();
    QSqlQuery q = QSqlQuery(SelectFull.arg(AllFields, Transactions,
                                           QString("timestamp = %1").arg(date.toString("dd.MM.yyyy"))));
    if (!q.exec())
        return 0;

    Data::Table *table = new Data::Table;
    while (q.next())
    {
        Data::Record *record = new Data::Record;
        for (int counter = 0; counter < q.record().count(); ++counter)
            record->append(q.value(counter));
        table->append(record);
    }
    return table;
}

Data::Table *DriverSqlite::timeLine(const QDate &date)
{
    openDb();
    QSqlQuery q = QSqlQuery(Select.arg(AllFields, Times));
    if (!q.exec())
        return 0;

    Data::Table *table = new Data::Table;
    while (q.next())
    {
        Data::Record *record = new Data::Record;
        for (int counter = 0; counter < q.record().count(); ++counter)
            record->append(q.value(counter));
        table->append(record);
    }
    return table;
}

Data::Table *DriverSqlite::deals(const QDate &date, const QStringList params)
{
    openDb();
    QSqlQuery q = QSqlQuery(SelectFull.arg(AllFields, Deals,
                                           QString("created = %1").arg(date.toString("dd.MM.yyyy"))));
    if (!q.exec())
        return 0;

    Data::Table *table = new Data::Table;
    while (q.next())
    {
        Data::Record *record = new Data::Record;
        for (int counter = 0; counter < q.record().count(); ++counter)
            record->append(q.value(counter));
        table->append(record);
    }
    return table;
}

void DriverSqlite::addAccount(const Data::Record &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    for (int i = 0; i < record.count(); ++i)
        values << record.at(i).toString();

    QString query = Insert.arg(Accounts, fields.join(SQL::Comma), values.join(SQL::Comma));
    QSqlQuery q(query);
    if (!q.exec())
    {
        Log::error("cannot add transaction in Db" + QString::number(q.lastError().number())
                   + " " + q.lastError().text());
        return;
    }
    Log::error("new transaction success added in Db");
    return;
}

void DriverSqlite::addTransaction(const Data::Record &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    for (int i = 0; i < record.count(); ++i)
        values << record.at(i).toString();

    QString query = Insert.arg(Transactions, fields.join(SQL::Comma), values.join(SQL::Comma));
    QSqlQuery q(query);
    if (!q.exec())
    {
        Log::error("cannot add transaction in Db" + QString::number(q.lastError().number())
                   + " " + q.lastError().text());
        return;
    }
    Log::error("new transaction success added in Db");
    return;
}

void DriverSqlite::addTimeRecord(const Data::Record &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    for (int i = 0; i < record.count(); ++i)
        values << record.at(i).toString();

    QString query = Insert.arg(Times, fields.join(SQL::Comma), values.join(SQL::Comma));
    QSqlQuery q(query);
    if (!q.exec())
    {
        Log::error("cannot add times in Db" + QString::number(q.lastError().number())
                   + " " + q.lastError().text());
        return;
    }
    Log::error("new times success added in Db");
    return;
}

void DriverSqlite::addDeal(const Data::Record &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    for (int i = 0; i < record.count(); ++i)
        values << record.at(i).toString();

    QString query = Insert.arg(Deals, fields.join(SQL::Comma), values.join(SQL::Comma));
    QSqlQuery q(query);
    if (!q.exec())
    {
        Log::error("cannot add deal in Db" + QString::number(q.lastError().number())
                   + " " + q.lastError().text());
        return;
    }
    Log::error("new deal success added in Db");
    return;
}

void DriverSqlite::addContact(const Data::Record &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    for (int i = 0; i < record.count(); ++i)
        values << record.at(i).toString();

    QString query = Insert.arg(Contacts, fields.join(SQL::Comma), values.join(SQL::Comma));
    QSqlQuery q(query);
    if (!q.exec())
    {
        Log::error("cannot add contact in Db" + QString::number(q.lastError().number())
                   + " " + q.lastError().text());
        return;
    }
    Log::error("new contact success added in Db");
    return;
}

bool DriverSqlite::openDb()
{
    if (m_db.isOpen())
        return true;

    if (QSqlDatabase::connectionNames().contains(ConnectionName))
        m_db = QSqlDatabase::database(ConnectionName);
    else
        m_db = QSqlDatabase::addDatabase(QSqlite, ConnectionName);
    m_db.setDatabaseName(m_pathToDb);

    if (!m_db.open())
        return false;
    return true;
}
