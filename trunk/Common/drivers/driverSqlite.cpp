#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include "cgMetaschemeConst.h"
#include "transactionData.h"
#include "contactData.h"
#include "addressData.h"
#include "channelData.h"
#include "companyData.h"
#include "accountData.h"
#include "dealData.h"
#include "timeData.h"
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

QList<ContactData *> *DriverSqlite::contacts()
{
    openDb();
    QSqlQuery q = QSqlQuery(Select.arg(AllFields, Contacts));
    if (!q.exec())
        return 0;

    QList<ContactData *> *data = new QList<ContactData *>();
    while (q.next())
    {
        ContactData *contact = new ContactData;
        contact->nickName = q.value("nickName").toString();
        contact->name = q.value("name").toString();
        contact->surName = q.value("surName").toString();
        contact->otherName = q.value("otherName").toString();
        contact->birthday = q.value("birthday").toString();
        contact->userPic = q.value("userPic").toString();
        data->append(contact);
    }
    return data;
}

ContactData *DriverSqlite::contact(const QString &alias)
{
    openDb();
    QSqlQuery q = QSqlQuery(SelectFull.arg(AllFields, Contacts, "alias = " + alias));
    if (!q.exec())
        return 0;

    ContactData *contact = new ContactData;
    if (q.first())
    {
        contact->nickName = q.value("nickName").toString();
        contact->name = q.value("name").toString();
        contact->surName = q.value("surName").toString();
        contact->otherName = q.value("otherName").toString();
        contact->birthday = q.value("birthday").toString();
        contact->userPic = q.value("userPic").toString();
        return contact;
    }
    return 0;
}

QList<AccountData *> *DriverSqlite::accounts()
{
    openDb();
    QSqlQuery q = QSqlQuery(Select.arg(AllFields, Accounts));
    if (!q.exec())
        return 0;

    QList<AccountData *> *data = new QList<AccountData *>();
    while (q.next())
    {
        AccountData *account = new AccountData;
        account->created = QDate::fromString(q.value("created").toString(), "dd.MM.yyyy");
        account->type = q.value("type").toInt();
        account->name = q.value("name").toString();
        account->value = q.value("value").toLongLong();
        account->total = q.value("total").toLongLong();
        account->description = q.value("description").toString();
        data->append(account);
    }
    return data;
}

QList<TransactionData *> *DriverSqlite::transactions(const QDate &date)
{
    openDb();
    QSqlQuery q = QSqlQuery(SelectFull.arg(AllFields, Transactions,
                                           QString("timestamp = %1").arg(date.toString("dd.MM.yyyy"))));
    if (!q.exec())
        return 0;

    QList<TransactionData *> *data = new QList<TransactionData *>();
    while (q.next())
    {
        TransactionData *transaction = new TransactionData;
        transaction->created = QDate::fromString(q.value("created").toString(), "dd.MM.yyyy");
        transaction->type = q.value("type").toInt();
        transaction->name = q.value("name").toString();
        transaction->value = q.value("value").toLongLong();
        transaction->description = q.value("description").toString();
        data->append(transaction);
    }
    return data;
}

QList<TimeData *> *DriverSqlite::timeLine(const QDate &date)
{
    openDb();
    QSqlQuery q = QSqlQuery(SelectFull.arg(AllFields, Times,
                                           QString("created = %1").arg(date.toString("dd.MM.yyyy"))));
    if (!q.exec())
        return 0;

    QList<TimeData *> *data = new QList<TimeData *>();
    while (q.next())
    {
        TimeData *time = new TimeData;
        time->started = QTime::fromString(q.value("created").toString(), "hh:mm:ss");
        time->stoped = QTime::fromString(q.value("stoped").toString(), "hh:mm:ss");
        time->duration = QTime::fromString(q.value("duration").toString(), "hh:mm:ss");
        time->type = q.value("type").toInt();
        time->description = q.value("description").toString();
        data->append(time);
    }
    return data;
}

QList<DealData *> *DriverSqlite::deals(const QDate &date)
{
    openDb();
    QSqlQuery q = QSqlQuery(SelectFull.arg(AllFields, Deals,
                                           QString("created = %1").arg(date.toString("dd.MM.yyyy"))));
    if (!q.exec())
        return 0;

    QList<DealData *> *data = new QList<DealData *>();
    while (q.next())
    {
        DealData *deal = new DealData;
        deal->date = QDate::fromString(q.value("date").toString(), "dd.MM.yyyy");
        deal->deadLine = QDate::fromString(q.value("deadLine").toString(), "dd.MM.yyyy");
        deal->duration = QTime::fromString(q.value("duration").toString(), "hh:mm:ss");
        deal->type = q.value("type").toInt();
        deal->humans = q.value("humans").toString();
        deal->money = q.value("money").toLongLong();
        deal->description = q.value("description").toString();
        data->append(deal);
    }
    return data;
}

void DriverSqlite::addAccount(const AccountData &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    values << record.created.toString("dd.MM.yyyy")
           << record.name
           << QString::number(record.type)
           << QString::number(record.value)
           << QString::number(record.total)
           << record.description;

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

void DriverSqlite::addTransaction(const TransactionData &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    values << record.created.toString("dd.MM.yyyy")
           << record.name
           << QString::number(record.type)
           << QString::number(record.value)
           << record.description;

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

void DriverSqlite::addTimeRecord(const TimeData &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    values << QString::number(record.type)
           << record.started.toString("hh:mm:ss")
           << record.stoped.toString("hh:mm:ss")
           << record.duration.toString("hh:mm:ss")
           << record.description;

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

void DriverSqlite::addDeal(const DealData &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    values << record.date.toString("dd.MM.yyyy")
           << QString::number(record.type)
           << record.duration.toString("hh:mm:ss")
           << record.humans
           << QString::number(record.money)
           << record.deadLine.toString("dd.MM.yyyy")
           << record.description;

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

void DriverSqlite::addContact(const ContactData &record)
{
    openDb();
    QStringList fields;
    QStringList values;
    values << record.nickName
           << record.name
           << record.surName
           << record.otherName
           << record.birthday;

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

    if (!m_db.isOpen() &&!m_db.open())
        return false;
    return true;
}
