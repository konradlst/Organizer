#include <QtSql>
#include "driverSqlite.h"
#include "dbGenerator.h"

namespace {
const QString metascheme("./metascheme.xml");

const QString QSQLITE("QSQLITE");
const QString USER("user");
const QString MAIN("main");
const QString FORMAT("format");
const QString VALUE("value");
const QString ID("id");

const QString FLD_CONTACT("alias, name, lastName, otherName, birthday, pathToUserPic, comment");
const QString FLD_COMPANY("name, phone, department, post, address, dateIn, dateOut, ownerId");
const QString FLD_ADDRESS("country, city, street, home, apartment, type, ownerId");
const QString FLD_CHANNEL("format, title, value, type, ownerId");

const QString QUERY_INSERT("INSERT INTO %1(%2) VALUES (%3);");
const QString QUERY_SELECT_SHORT("SELECT * FROM %1");
const QString QUERY_SELECT_FULL("SELECT * FROM %1 WHERE ownerId = '%2'");
const QString QUERY_SELECT_FULL_2("SELECT * FROM %1 WHERE type = '%2' AND ownerId = '%3'");

QString quotesValue(QStringList list)
{
    for(int i = 0; i < list.count(); ++i)
        list.replace(i, QString("'%1'").arg(list.at(i)));
    return list.join(", ");
}
}

namespace Table {
const QString Contacts("CG_CONTACTS");
const QString Companies("CG_COMPANIES");
const QString Addresses("CG_ADDRESSES");
const QString Channels("CG_CHANNELS");
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

    dbGenerator gen = dbGenerator(metascheme, path);
    gen.generate();

    for(int i=0; i < data.size(); ++i)
        contactDataToSql(data.at(i), i);
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

void DriverSqlite::contactDataToSql(const Data::ContactData *contact, const int i) const
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

    QSqlQuery query;
    if(!query.exec(QUERY_INSERT.arg(Table::Contacts, FLD_CONTACT,
                                    quotesValue(contactVal))))
        qDebug() << query.lastError();
    if(!query.exec(QUERY_INSERT.arg(Table::Companies, FLD_COMPANY,
                                   quotesValue(companyVal))))
        qDebug() << query.lastError();
    if(!query.exec(QUERY_INSERT.arg(Table::Addresses, FLD_ADDRESS,
                                   quotesValue(addressVal))))
        qDebug() << query.lastError();
    if(!query.exec(QUERY_INSERT.arg(Table::Channels, FLD_CHANNEL, quotesValue(phoneVal))))
        qDebug() << query.lastError();
    if(!query.exec(QUERY_INSERT.arg(Table::Channels, FLD_CHANNEL, quotesValue(emailVal))))
        qDebug() << query.lastError();
    if(!query.exec(QUERY_INSERT.arg(Table::Channels, FLD_CHANNEL, quotesValue(skypeVal))))
        qDebug() << query.lastError();
    if(!query.exec(QUERY_INSERT.arg(Table::Channels, FLD_CHANNEL, quotesValue(siteVal))))
        qDebug() << query.lastError();
}

void DriverSqlite::sqlToContactData(const QSqlQuery &query, Data::ContactData *contact) const
{
    QStringList list;
    for(int i=1; i<query.record().count(); ++i)
        list << query.record().value(i).toString();
    contact->setMainData(list);

    int index = query.record().value(ID).toInt();

    QSqlQuery tmpQ;
    tmpQ.exec(QUERY_SELECT_FULL_2.arg(Table::Addresses, USER,
                                           QString::number(index)));
    while (tmpQ.next())
    {
        QStringList list;
        for(int i = 1; i < tmpQ.record().count() - 2; ++i)
            list << tmpQ.record().value(i).toString();
        contact->setAddressData(list);
    }

    tmpQ.clear();
    tmpQ.exec(QUERY_SELECT_FULL.arg(Table::Companies, QString::number(index)));
    while (tmpQ.next())
    {
        QStringList list;
        for(int i = 1; i < tmpQ.record().count() - 1; ++i)
            list << tmpQ.record().value(i).toString();
        contact->setCompanyData(list);
    }

    tmpQ.clear();
    tmpQ.exec(QUERY_SELECT_FULL_2.arg(Table::Channels, USER, QString::number(index)));
    while (tmpQ.next())
    {
        QString format = tmpQ.record().value(FORMAT).toString();
        QString value = tmpQ.record().value(VALUE).toString();
        contact->setChannel(format, MAIN, value);
    }
}
