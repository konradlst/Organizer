#include "driverSql.h"
#include <QtSql>

namespace {
const QString QSQLITE("QSQLITE");
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

const QString USER("user");
const QString MAIN("main");
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

    for(int i=0; i < data.size(); ++i)
        contactDataToSql(query, data.at(i), i);
    return true;
}

Data::Contacts *DriverSql::loadData(const QString &path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(path);
    db.open();

    QSqlQuery query;
    query.exec(QUERY_SELECT_SHORT.arg("Contacts"));
    QSqlRecord record = query.record();

    Data::Contacts *data = new Data::Contacts();

    while (query.next()) {
        Data::ContactData *contact = new Data::ContactData();
        sqlToContactData(query, record, contact);
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

void DriverSql::contactDataToSql(QSqlQuery &query, const Data::ContactData *contact, const int i) const
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

void DriverSql::sqlToContactData(const QSqlQuery &query, const QSqlRecord &record, Data::ContactData *contact) const
{
    contact->setAlias(query.value(record.indexOf(Attribute::Alias)).toString());
    contact->setName(query.value(record.indexOf(Attribute::Name)).toString());
    contact->setSurName(query.value(record.indexOf(Attribute::SurName)).toString());
    contact->setOtherName(query.value(record.indexOf(Attribute::OtherName)).toString());
    contact->setBirthday(query.value(record.indexOf(Attribute::Birthday)).toString());

    int index = query.value(record.indexOf("id")).toInt();

    QSqlQuery addressesQuery;
    addressesQuery.exec(QUERY_SELECT_FULL_2.arg(QString("Addresses"), USER, QString::number(index)));
    QSqlRecord addressesRecord = addressesQuery.record();
    while (addressesQuery.next()) {
        contact->setCountry(0, addressesQuery.value(addressesRecord.indexOf(Attribute::Country)).toString());
        contact->setCity(0, addressesQuery.value(addressesRecord.indexOf(Attribute::City)).toString());
        contact->setStreet(0, addressesQuery.value(addressesRecord.indexOf(Attribute::Street)).toString());
        contact->setHome(0, addressesQuery.value(addressesRecord.indexOf(Attribute::Home)).toString());
        contact->setApartment(0, addressesQuery.value(addressesRecord.indexOf(Attribute::Apartment)).toString());
    }

    QSqlQuery companiesQuery;
    companiesQuery.exec(QUERY_SELECT_FULL.arg(QString("Companies"), QString::number(index)));
    QSqlRecord companiesRecord = companiesQuery.record();
    while (companiesQuery.next()) {
        contact->setCompanyName(0, companiesQuery.value(companiesRecord.indexOf(Attribute::Name)).toString());
        contact->setCompanyPhone(0, companiesQuery.value(companiesRecord.indexOf(Attribute::Phone)).toString());
        contact->setDepartment(0, companiesQuery.value(companiesRecord.indexOf(Attribute::Department)).toString());
        contact->setPost(0, companiesQuery.value(companiesRecord.indexOf(Attribute::Post)).toString());
        contact->setCompanyAddress(0, companiesQuery.value(companiesRecord.indexOf(Attribute::Address)).toString());
        contact->setDateIn(0, companiesQuery.value(companiesRecord.indexOf(Attribute::DateIn)).toString());
        contact->setDateOut(0, companiesQuery.value(companiesRecord.indexOf(Attribute::DateOut)).toString());
    }

    QSqlQuery channelsQuery;
    channelsQuery.exec(QUERY_SELECT_FULL_2.arg(QString("Channels"), USER, QString::number(index)));
    QSqlRecord channelsRecord = channelsQuery.record();
    while (channelsQuery.next()) {
        QString format = channelsQuery.value(channelsRecord.indexOf("format")).toString();
        QString value = channelsQuery.value(channelsRecord.indexOf("value")).toString();
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
