#include <QtSql>
#include "driverSqlite.h"
#include "dbGenerator.h"
#include "cgMetaschemeConst.h"

namespace
{
const QString USER("user");
const QString MAIN("main");
const QString FORMAT("format");
const QString VALUE("value");
const QString ID("id");

const QString FLD_CONTACT("alias, name, lastName, otherName, birthday, pathToUserPic, comment");
const QString FLD_COMPANY("name, phone, department, post, address, dateIn, dateOut, ownerId");
const QString FLD_ADDRESS("country, city, street, home, apartment, type, ownerId");
const QString FLD_CHANNEL("format, title, value, type, ownerId");

QString quotesValue(QStringList list)
{
    for(int i = 0; i < list.count(); ++i)
        list.replace(i, QString("'%1'").arg(list.at(i)));
    return list.join(", ");
}
}

namespace Table
{
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
    QSqlDatabase db = QSqlDatabase::addDatabase(SQL::SQLITE);
    db.setDatabaseName(path);
    db.open();

    dbGenerator gen = dbGenerator(path);
    gen.generate();

    for(int i=0; i < data.size(); ++i)
        contactDataToSql(data.at(i), i);
    return true;
}

Data::Contacts *DriverSqlite::loadData(const QString &path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(SQL::SQLITE);
    db.setDatabaseName(path);
    db.open();

    QSqlQuery query;
    query.exec(SQL::SELECT_SHORT.arg(Table::Contacts));

    Data::Contacts *data = new Data::Contacts();

    while (query.next())
    {
        ContactData *contact = new ContactData();
        sqlToContactData(query, contact);
        data->append(contact);
    }
    return data;
}

bool DriverSqlite::saveContact(const ContactData &, const QString &)
{
    //not used
    return false;
}

ContactData *DriverSqlite::loadContact(const QString &)
{
    //not used
    return 0;
}

void DriverSqlite::contactDataToSql(const ContactData *contact, const int i) const
{
    QString index = QString::number(i+1);

    QStringList companyVal = contact->data(COMPANY);
    companyVal << index;

    QStringList addressVal = contact->data(ADDRESS);
    addressVal << USER << index;

    QStringList phoneVal;
    phoneVal << Channel::Phone
             << MAIN
             << contact->data(Channel::Phone).at(0)
             << USER
             << index;

    QStringList emailVal;
    emailVal << Channel::Email
             << MAIN
             << contact->data(Channel::Email).at(0)
             << USER
             << index;

    QStringList skypeVal;
    skypeVal << Channel::Skype
             << MAIN
             << contact->data(Channel::Skype).at(0)
             << USER
             << index;

    QStringList siteVal;
    siteVal << Channel::Site
            << MAIN
            << contact->data(Channel::Site).at(0)
            << USER
            << index;

    QString insertChannel = SQL::INSERT.arg(Table::Channels)
                                       .arg(FLD_CHANNEL);
    QStringList queries;
    queries << SQL::INSERT.arg(Table::Contacts)
                          .arg(FLD_CONTACT)
                          .arg(quotesValue(contact->data(CONTACT)))
            << SQL::INSERT.arg(Table::Companies)
                          .arg(FLD_COMPANY)
                          .arg(quotesValue(companyVal))
            << SQL::INSERT.arg(Table::Addresses)
                          .arg(FLD_ADDRESS)
                          .arg(quotesValue(addressVal))
            << insertChannel.arg(quotesValue(phoneVal))
            << insertChannel.arg(quotesValue(emailVal))
            << insertChannel.arg(quotesValue(skypeVal))
            << insertChannel.arg(quotesValue(siteVal));

    QSqlQuery query;
    foreach (QString q, queries)
    {
        if(!query.exec(q))
            qDebug() << query.lastError();
    }
}

void DriverSqlite::sqlToContactData(const QSqlQuery &query, ContactData *contact) const
{
    QStringList list;
    for(int i=1; i<query.record().count(); ++i)
        list << query.record().value(i).toString();

    contact->setMainData(list);

    int index = query.record().value(ID).toInt();

    QSqlQuery tmpQ;
    tmpQ.exec(SQL::SELECT_2.arg(Table::Addresses, USER, QString::number(index)));
    while (tmpQ.next())
    {
        QStringList list;
        for(int i = 1; i < tmpQ.record().count() - 2; ++i)
            list << tmpQ.record().value(i).toString();
        contact->setAddressData(list);
    }

    tmpQ.clear();
    tmpQ.exec(SQL::SELECT.arg(Table::Companies, QString::number(index)));
    while (tmpQ.next())
    {
        QStringList list;
        for(int i = 1; i < tmpQ.record().count() - 1; ++i)
            list << tmpQ.record().value(i).toString();
        contact->setCompanyData(list);
    }

    tmpQ.clear();
    tmpQ.exec(SQL::SELECT_2.arg(Table::Channels, USER, QString::number(index)));
    while (tmpQ.next())
    {
        QString format = tmpQ.record().value(FORMAT).toString();
        QString value = tmpQ.record().value(VALUE).toString();
        contact->setChannel(format, MAIN, value);
    }
}