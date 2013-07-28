#include "driverSqlite.h"
#include <QtSql>

namespace {
const QString QSQLITE("QSQLITE");
const QString USER("user");
const QString MAIN("main");
const QString FORMAT("format");
const QString VALUE("value");
const QString ID("id");

const QString QUERY_CREATE_TABLE_CONTACTS("CREATE TABLE Contacts ("
                                                  "id INTEGER PRIMARY KEY, "
                                                  "alias VARCHAR(255) NOT NULL, "
                                                  "name VARCHAR(255), "
                                                  "surName VARCHAR(255), "
                                                  "otherName VARCHAR(255), "
                                                  "birthday VARCHAR(255));");
const QString QUERY_CREATE_TABLE_COMPANIES("CREATE TABLE Companies ("
                                                   "id INTEGER PRIMARY KEY, "
                                                   "name VARCHAR(255) NOT NULL, "
                                                   "phone VARCHAR(255), "
                                                   "department VARCHAR(255), "
                                                   "post VARCHAR(255), "
                                                   "address VARCHAR(255), "
                                                   "dateIn VARCHAR(255), "
                                                   "dateOut VARCHAR(255), "
                                                   "ownerId INTEGER);");
const QString QUERY_CREATE_TABLE_ADDRESSES("CREATE TABLE Addresses ("
                                                  "id INTEGER PRIMARY KEY, "
                                                  "country VARCHAR(255) NOT NULL, "
                                                  "city VARCHAR(255), "
                                                  "street VARCHAR(255), "
                                                  "home VARCHAR(255), "
                                                  "apartment VARCHAR(255), "
                                                  "type VARCHAR(255), "
                                                  "ownerId INTEGER);");
const QString QUERY_CREATE_TABLE_CHANNELS("CREATE TABLE Channels ("
                                                  "id INTEGER PRIMARY KEY, "
                                                  "format VARCHAR(255) NOT NULL, "
                                                  "title VARCHAR(255), "
                                                  "value VARCHAR(255), "
                                                  "type VARCHAR(255), "
                                                  "ownerId INTEGER);");

const QString INSERT_CONTACTS("INSERT INTO Contacts(alias, name, surName, otherName, birthday) VALUES (%1);");
const QString INSERT_COMPANIES("INSERT INTO Companies(name, phone, department, post, address, dateIn, dateOut, ownerId) VALUES (%1);");
const QString INSERT_ADDRESSES("INSERT INTO Addresses(country, city, street, home, apartment, type, ownerId) VALUES (%1);");
const QString INSERT_CHANNELS("INSERT INTO Channels(format, title, value, type, ownerId) VALUES (%1);");

const QString QUERY_SELECT_SHORT("SELECT * FROM %1");
const QString QUERY_SELECT_FULL("SELECT * FROM %1 WHERE ownerId = '%2'");
const QString QUERY_SELECT_FULL_2("SELECT * FROM %1 WHERE type = '%2' AND ownerId = '%3'");

QString quotesValue(QStringList list)
{
    foreach (QString str, list)
        str = QString("'%1'").arg(str);
    return list.join(", ");
}
}

namespace Table {
const QString Contacts("Contacts");
const QString Addresses("Addresses");
const QString Companies("Companies");
const QString Channels("Channels");
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
    QString index = QString::number(i+1);

    QStringList contactVal = contact->values("contact");
    QStringList companyVal = contact->values("company");
    companyVal << index;
    QStringList addressVal = contact->values("address");
    addressVal << USER << index;

    QStringList phoneVal;
    phoneVal << Channel::Phone << MAIN
             << contact->phones().at(0)
             << USER << index;

    QStringList emailVal;
    phoneVal << Channel::Email << MAIN
             << contact->emails().at(0)
             << USER << index;

    QStringList skypeVal;
    phoneVal << Channel::Skype << MAIN
             << contact->skypes().at(0)
             << USER << index;

    QStringList siteVal;
    phoneVal << Channel::Site << MAIN
             << contact->sites().at(0)
             << USER << index;

    query.exec(INSERT_CONTACTS.arg(quotesValue(contactVal)));
    query.exec(INSERT_COMPANIES.arg(quotesValue(companyVal)));
    query.exec(INSERT_ADDRESSES.arg(quotesValue(addressVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(phoneVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(emailVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(skypeVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(siteVal)));
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
        contact->setCountry(0, tempQuery.value(tempRecord.indexOf(Address::Country)).toString());
        contact->setCity(0, tempQuery.value(tempRecord.indexOf(Address::City)).toString());
        contact->setStreet(0, tempQuery.value(tempRecord.indexOf(Address::Street)).toString());
        contact->setHome(0, tempQuery.value(tempRecord.indexOf(Address::Home)).toString());
        contact->setApartment(0, tempQuery.value(tempRecord.indexOf(Address::Apartment)).toString());
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
        if(format == Channel::Phone)
            contact->setPhone(MAIN, value);
        else if(format == Channel::Email)
            contact->setEmail(MAIN, value);
        else if(format == Channel::Skype)
            contact->setSkype(MAIN, value);
        else if(format == Channel::Site)
            contact->setSite(MAIN, value);
    }
}
