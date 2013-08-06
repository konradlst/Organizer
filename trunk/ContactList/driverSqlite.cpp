#include "driverSqlite.h"
#include <QtSql>

namespace {
const QString QSQLITE("QSQLITE");
const QString USER("user");
const QString MAIN("main");
const QString FORMAT("format");
const QString VALUE("value");
const QString ID("id");

const QString CONTACT("contact");
const QString COMPANY("company");
const QString ADDRESS("address");

const QString QUERY_CREATE_TABLE_CONTACTS("CREATE TABLE Contacts ("
                                                  "id INTEGER PRIMARY KEY, "
                                                  "alias VARCHAR(255) NOT NULL, "
                                                  "name VARCHAR(255), "
                                                  "surName VARCHAR(255), "
                                                  "otherName VARCHAR(255), "
                                                  "birthday VARCHAR(255), "
                                                  "pathToUserPic VARCHAR(255), "
                                                  "comment VARCHAR(255));");
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

const QString INSERT_CONTACTS("INSERT INTO Contacts(alias, name, surName, otherName, birthday, pathToUserPic, comment) VALUES (%1);");
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

    Data::Contacts *data = new Data::Contacts();

    while (query.next())
    {
        Data::ContactData *contact = new Data::ContactData();
        sqlToContactData(query, contact);
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

    QStringList contactVal = contact->data(CONTACT);
    QStringList companyVal = contact->data(COMPANY);
    companyVal << index;
    QStringList addressVal = contact->data(ADDRESS);
    addressVal << USER
               << index;

    QStringList phoneVal;
    phoneVal << Channel::Phone
             << MAIN
             << contact->channels(Channel::Phone).at(0)
             << USER
             << index;

    QStringList emailVal;
    emailVal << Channel::Email
             << MAIN
             << contact->channels(Channel::Email).at(0)
             << USER
             << index;

    QStringList skypeVal;
    skypeVal << Channel::Skype
             << MAIN
             << contact->channels(Channel::Skype).at(0)
             << USER
             << index;

    QStringList siteVal;
    siteVal << Channel::Site
            << MAIN
            << contact->channels(Channel::Site).at(0)
            << USER
            << index;

    query.exec(INSERT_CONTACTS.arg(quotesValue(contactVal)));
    query.exec(INSERT_COMPANIES.arg(quotesValue(companyVal)));
    query.exec(INSERT_ADDRESSES.arg(quotesValue(addressVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(phoneVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(emailVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(skypeVal)));
    query.exec(INSERT_CHANNELS.arg(quotesValue(siteVal)));
}

void DriverSqlite::sqlToContactData(const QSqlQuery &query, Data::ContactData *contact) const
{
    QStringList list;
    list << query.record().value(Attribute::Alias).toString()
         << query.record().value(Attribute::Name).toString()
         << query.record().value(Attribute::SurName).toString()
         << query.record().value(Attribute::OtherName).toString()
         << query.record().value(Attribute::Birthday).toString();
    contact->setMainData(list);

    int index = query.record().value(ID).toInt();

    QSqlQuery tempQuery;
    tempQuery.exec(QUERY_SELECT_FULL_2.arg(Table::Addresses, USER,
                                           QString::number(index)));
    while (tempQuery.next())
    {
        QStringList list;
        list << tempQuery.record().value(Address::Country).toString()
             << tempQuery.record().value(Address::City).toString()
             << tempQuery.record().value(Address::Street).toString()
             << tempQuery.record().value(Address::Home).toString()
             << tempQuery.record().value(Address::Apartment).toString();
        contact->setAddressData(list);
    }

    tempQuery.clear();
    tempQuery.exec(QUERY_SELECT_FULL.arg(Table::Companies, QString::number(index)));
    while (tempQuery.next())
    {
        QStringList list;
        list << tempQuery.record().value(Attribute::Name).toString()
             << tempQuery.record().value(Attribute::Phone).toString()
             << tempQuery.record().value(Attribute::Department).toString()
             << tempQuery.record().value(Attribute::Post).toString()
             << tempQuery.record().value(Attribute::Address).toString()
             << tempQuery.record().value(Attribute::DateIn).toString()
             << tempQuery.record().value(Attribute::DateOut).toString();
        contact->setCompanyData(list);
    }

    tempQuery.clear();
    tempQuery.exec(QUERY_SELECT_FULL_2.arg(Table::Channels, USER, QString::number(index)));
    while (tempQuery.next())
    {
        QString format = tempQuery.record().value(FORMAT).toString();
        QString value = tempQuery.record().value(VALUE).toString();

        contact->setChannel(format, MAIN, value);
    }
}
