#include "driverSqlite.h"
#include <QtSql>

namespace {
const QString QSQLITE("QSQLITE");
const QString USER("user");
const QString MAIN("main");
const QString FORMAT("format");
const QString VALUE("value");
const QString ID("id");

namespace Table {
const QString Contacts("Contacts");
const QString Addresses("Addresses");
const QString Companies("Companies");
const QString Channels("Channels");
}

const QString QUERY_CREATE_TABLE_CONTACTS("CREATE TABLE Contacts ("
                                                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                                  "alias VARCHAR(255) NOT NULL, "
                                                  "name VARCHAR(255), "
                                                  "surName VARCHAR(255), "
                                                  "otherName VARCHAR(255), "
                                                  "birthday VARCHAR(255));");
const QString QUERY_CREATE_TABLE_COMPANIES("CREATE TABLE Companies ("
                                                   "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                                   "name VARCHAR(255) NOT NULL, "
                                                   "phone VARCHAR(255), "
                                                   "department VARCHAR(255), "
                                                   "post VARCHAR(255), "
                                                   "address VARCHAR(255), "
                                                   "dateIn VARCHAR(255), "
                                                   "dateOut VARCHAR(255), "
                                                   "ownerId INTEGER);");
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

const QString QUERY_INSERT_TO_CONTACTS("INSERT INTO Contacts(alias, name, surName, otherName, birthday) "
                                        "VALUES ('%1', '%2', '%3', '%4', '%5');");
const QString QUERY_INSERT_TO_COMPANIES("INSERT INTO Companies(name, phone, department, post, address, dateIn, dateOut, ownerId) "
                                        "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');");
const QString QUERY_INSERT_TO_ADDRESSES("INSERT INTO Addresses(country, city, street, home, apartment, type, ownerId) "
                                        "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7');");
const QString QUERY_INSERT_TO_CHANNELS("INSERT INTO Channels(format, title, value, type, ownerId) "
                                        "VALUES ('%1', '%2', '%3', '%4', '%5');");
const QString QUERY_SELECT_SHORT("SELECT * FROM %1");
const QString QUERY_SELECT_FULL("SELECT * FROM %1 WHERE ownerId = '%2'");
const QString QUERY_SELECT_FULL_2("SELECT * FROM %1 WHERE type = '%2' AND ownerId = '%3'");
}

DriverSqlite::DriverSqlite()
{
}

DriverSqlite::~DriverSqlite()
{
}

bool DriverSqlite::saveData(const Data::Contacts &data, const QString &path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(path);
    db.open();

    QSqlQuery query;
    query.exec(QUERY_CREATE_TABLE_CONTACTS);
    query.exec(QUERY_CREATE_TABLE_COMPANIES);
    query.exec(QUERY_CREATE_TABLE_CHANNELS);
    query.exec(QUERY_CREATE_TABLE_ADDRESSES);

    for(int i=0; i < data.size(); ++i)
        contactDataToSql(query, data.at(i), i);
    return true;
}

Data::Contacts *DriverSqlite::loadData(const QString &path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(path);
    db.open();

    QSqlQuery query;
    query.exec(QUERY_SELECT_SHORT.arg(Table::Contacts));
    QSqlRecord record = query.record();

    Data::Contacts *data = new Data::Contacts();

    while (query.next()) {
        Data::ContactData *contact = new Data::ContactData();
        sqlToContactData(query, record, contact);
        data->append(contact);
    }
    return data;
}

bool DriverSqlite::saveContact(const Data::ContactData &, const QString &)
{
    //not used
    return false;
}

Data::ContactData *DriverSqlite::loadContact(const QString &)
{
    //not used
    return 0;
}

void DriverSqlite::contactDataToSql(QSqlQuery &query, const Data::ContactData *contact,
                                 const int i) const
{
    QString strInsertToContacts = QUERY_INSERT_TO_CONTACTS.arg(
                            contact->alias(),
                            contact->name(),
                            contact->surName(),
                            contact->otherName(),
                            contact->birthdayAsString());
    QString strInsertToCompanies = QUERY_INSERT_TO_COMPANIES.arg(
                            contact->companyName(),
                            contact->companyPhone(),
                            contact->department(),
                            contact->post(),
                            contact->companyAddress(),
                            contact->dateInAsString(),
                            contact->dateOutAsString(),
                            QString::number(i+1));
    QString strInsertToAddresses = QUERY_INSERT_TO_ADDRESSES.arg(
                            contact->country(),
                            contact->city(),
                            contact->street(),
                            contact->home(),
                            contact->apartment(),
                            USER,
                            QString::number(i+1));

    QString strInsertPhone = QUERY_INSERT_TO_CHANNELS.arg(
                                    Value::Phone, MAIN,
                                    contact->phones().at(0), USER,
                                    QString::number(i+1));
    QString strInsertEmail = QUERY_INSERT_TO_CHANNELS.arg(
                                    Value::Email, MAIN,
                                    contact->emails().at(0), USER,
                                    QString::number(i+1));
    QString strInsertSkype = QUERY_INSERT_TO_CHANNELS.arg(
                                    Value::Skype, MAIN,
                                    contact->skypes().at(0), USER,
                                    QString::number(i+1));
    QString strInsertSite = QUERY_INSERT_TO_CHANNELS.arg(
                                    Value::Site, MAIN,
                                    contact->sites().at(0), USER,
                                    QString::number(i+1));

    query.exec(strInsertToContacts);
    query.exec(strInsertToCompanies);
    query.exec(strInsertToAddresses);
    query.exec(strInsertPhone);
    query.exec(strInsertEmail);
    query.exec(strInsertSkype);
    query.exec(strInsertSite);
}

void DriverSqlite::sqlToContactData(const QSqlQuery &query, const QSqlRecord &record, Data::ContactData *contact) const
{
    contact->setAlias(query.value(record.indexOf(Attribute::Alias)).toString());
    contact->setName(query.value(record.indexOf(Attribute::Name)).toString());
    contact->setSurName(query.value(record.indexOf(Attribute::SurName)).toString());
    contact->setOtherName(query.value(record.indexOf(Attribute::OtherName)).toString());
    contact->setBirthday(query.value(record.indexOf(Attribute::Birthday)).toString());

    int index = query.value(record.indexOf(ID)).toInt();

    QSqlQuery tempQuery;
    QSqlRecord tempRecord;
    tempQuery.exec(QUERY_SELECT_FULL_2.arg(Table::Addresses, USER, QString::number(index)));
    tempRecord = tempQuery.record();
    while (tempQuery.next()) {
        contact->setCountry(0, tempQuery.value(tempRecord.indexOf(Attribute::Country)).toString());
        contact->setCity(0, tempQuery.value(tempRecord.indexOf(Attribute::City)).toString());
        contact->setStreet(0, tempQuery.value(tempRecord.indexOf(Attribute::Street)).toString());
        contact->setHome(0, tempQuery.value(tempRecord.indexOf(Attribute::Home)).toString());
        contact->setApartment(0, tempQuery.value(tempRecord.indexOf(Attribute::Apartment)).toString());
    }

    tempQuery.clear();
    tempQuery.exec(QUERY_SELECT_FULL.arg(Table::Companies, QString::number(index)));
    tempRecord = tempQuery.record();
    while (tempQuery.next()) {
        contact->setCompanyName(0, tempQuery.value(tempRecord.indexOf(Attribute::Name)).toString());
        contact->setCompanyPhone(0, tempQuery.value(tempRecord.indexOf(Attribute::Phone)).toString());
        contact->setDepartment(0, tempQuery.value(tempRecord.indexOf(Attribute::Department)).toString());
        contact->setPost(0, tempQuery.value(tempRecord.indexOf(Attribute::Post)).toString());
        contact->setCompanyAddress(0, tempQuery.value(tempRecord.indexOf(Attribute::Address)).toString());
        contact->setDateIn(0, tempQuery.value(tempRecord.indexOf(Attribute::DateIn)).toString());
        contact->setDateOut(0, tempQuery.value(tempRecord.indexOf(Attribute::DateOut)).toString());
    }

    tempQuery.clear();
    tempQuery.exec(QUERY_SELECT_FULL_2.arg(Table::Channels, USER, QString::number(index)));
    tempRecord = tempQuery.record();
    while (tempQuery.next()) {
        QString format = tempQuery.value(tempRecord.indexOf(FORMAT)).toString();
        QString value = tempQuery.value(tempRecord.indexOf(VALUE)).toString();
        if(format == Value::Phone)
            contact->setPhone(MAIN, value);
        else if(format == Value::Email)
            contact->setEmail(MAIN, value);
        else if(format == Value::Skype)
            contact->setSkype(MAIN, value);
        else if(format == Value::Site)
            contact->setSite(MAIN, value);
    }
}
