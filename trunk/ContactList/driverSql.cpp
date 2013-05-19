#include "driverSql.h"
#include <QtSql>

namespace {
const QString QSQLITE("QSQLITE");
const QString QUERY_CREATE_TABLE_CONTACTS("CREATE TABLE Contacts ("
                                                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                                  "alias VARCHAR(255) NOT NULL, "
                                                  "name VARCHAR(255), "
                                                  "surName VARCHAR(255), "
                                                  "birthday VARCHAR(255));");
const QString QUERY_CREATE_TABLE_COMPANIES("CREATE TABLE Companies ("
                                                   "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                                   "name VARCHAR(255) NOT NULL, "
                                                   "department VARCHAR(255), "
                                                   "post VARCHAR(255), "
                                                   "dateIn VARCHAR(255), "
                                                   "dateOut VARCHAR(255));");
const QString QUERY_CREATE_TABLE_ADDRESSES("CREATE TABLE Addresses ("
                                                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                                  "country VARCHAR(255) NOT NULL, "
                                                  "city VARCHAR(255), "
                                                  "street VARCHAR(255), "
                                                  "home VARCHAR(255), "
                                                  "apartment VARCHAR(255), "
                                                  "type VARCHAR(255), "
                                                  "ownerId INTEGER);");
const QString QUERY_CREATE_TABLE_CHANNELS("CREATE TABLE Channels ("
                                                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                                  "format VARCHAR(255) NOT NULL, "
                                                  "title VARCHAR(255), "
                                                  "value VARCHAR(255), "
                                                  "type VARCHAR(255), "
                                                  "ownerId INTEGER);");

const QString QUERY_INSERT_TO_CONTACTS("INSERT INTO Contacts(alias, name, surName, birthday) "
                                        "VALUES ('%1', '%2', '%3', '%4');");
const QString QUERY_INSERT_TO_COMPANIES("INSERT INTO Companies(name, department, post, dateIn, dateOut) "
                                        "VALUES ('%1', '%2', '%3', '%4', '%5');");
const QString QUERY_INSERT_TO_ADDRESSES("INSERT INTO Addresses(country, city, street, home, apartment, type, ownerId) "
                                        "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7');");
const QString QUERY_INSERT_TO_CHANNELS("INSERT INTO Channels(format, title, value, type, ownerId) "
                                        "VALUES ('%1', '%2', '%3', '%4', '%5');");
const QString QUERY_SELECT("SELECT * FROM Contacts");
}

DriverSql::DriverSql()
{
}

DriverSql::~DriverSql()
{
}

bool DriverSql::saveData(const Data::Contacts &data, const QString &path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(path);
    db.open();

    QSqlQuery query;
    query.exec(QUERY_CREATE_TABLE_CONTACTS);
    query.exec(QUERY_CREATE_TABLE_COMPANIES);
    query.exec(QUERY_CREATE_TABLE_CHANNELS);
    query.exec(QUERY_CREATE_TABLE_ADDRESSES);

    for(int i=0; i < data.size(); ++i) {
        Data::ContactData *contact = data.at(i);
        QString strInsertToContacts = QUERY_INSERT_TO_CONTACTS.arg(
                                contact->alias(),
                                contact->name(),
                                contact->surName(),
                                contact->birthdayAsString());
        QString strInsertToCompanies = QUERY_INSERT_TO_COMPANIES.arg(
                                contact->companyName(),
                                contact->department(),
                                contact->post(),
                                contact->dateInAsString(),
                                contact->dateOutAsString());
        QString strInsertToAddresses = QUERY_INSERT_TO_ADDRESSES.arg(
                                contact->country(),
                                contact->city(),
                                contact->street(),
                                contact->home(),
                                contact->apartment(),
                                QString("user"),
                                QString::number(i+1));

        QString strInsertPhone = QUERY_INSERT_TO_CHANNELS.arg(
                    Value::Phone,
                    QString(),
                    contact->phones().at(0),
                    QString("user"),
                    QString::number(i+1));
        QString strInsertEmail = QUERY_INSERT_TO_CHANNELS.arg(
                    Value::Email,
                    QString(),
                    contact->emails().at(0),
                    QString("user"),
                    QString::number(i+1));
        QString strInsertSkype = QUERY_INSERT_TO_CHANNELS.arg(
                    Value::Skype,
                    QString(),
                    contact->skypes().at(0),
                    QString("user"),
                    QString::number(i+1));
        QString strInsertSite = QUERY_INSERT_TO_CHANNELS.arg(
                    Value::Site,
                    QString(),
                    contact->sites().at(0),
                    QString("user"),
                    QString::number(i+1));

        query.exec(strInsertToContacts);
        query.exec(strInsertToCompanies);
        query.exec(strInsertToAddresses);
        query.exec(strInsertPhone);
        query.exec(strInsertEmail);
        query.exec(strInsertSkype);
        query.exec(strInsertSite);
    }
    return true;
}

Data::Contacts *DriverSql::loadData(const QString &path)
{
    //FIXME add code
    QSqlDatabase db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(path);
    db.open();

    QSqlQuery query;
    query.exec(QUERY_SELECT);

    Data::Contacts *data = new Data::Contacts();

    QSqlRecord record = query.record();
    while (query.next()) {
        Data::ContactData *contact = new Data::ContactData();
        contact->setAlias(query.value(record.indexOf(Attribute::Alias)).toString());
        contact->setName(query.value(record.indexOf(Attribute::Name)).toString());
        contact->setSurName(query.value(record.indexOf(Attribute::SurName)).toString());
        contact->setBirthday(query.value(record.indexOf(Attribute::Birthday)).toString());
        //...
        data->append(contact);
    }
    return data;
}

bool DriverSql::saveContact(const Data::ContactData &data, const QString &path)
{
    //FIXME add code
    return false;
}

Data::ContactData *DriverSql::loadContact(const QString &path)
{
    //FIXME add code
    return 0;
}
