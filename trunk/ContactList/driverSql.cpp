#include "driverSql.h"
#include <QtSql>

namespace {
const QString QSQLITE("QSQLITE");
const QString QUERY_CREATE("CREATE TABLE Contacts ("
                           "alias VARCHAR(255) PRIMARY KEY NOT NULL, "
                           "name VARCHAR(255), "
                           "surName VARCHAR(255));");
const QString QUERY_INSERT("INSERT INTO Contacts(alias, name, surName) "
                           "VALUES ('%1', '%2', '%3');");
const QString QUERY_SELECT("SELECT * FROM Contacts");
}

DriverSql::DriverSql()
{
}

DriverSql::~DriverSql()
{
}

bool DriverSql::saveData(const Data::Contacts &data, const QString &path) const
{
    //FIXME add code
    QSqlDatabase db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(path);
    db.open();

    QSqlQuery query;
    query.exec(QUERY_CREATE);

    for(int i=0; i < data.size(); ++i) {
        Data::ContactData *contact = data.at(i);
        QString str_insert = QUERY_INSERT.arg(
                                contact->alias(),
                                contact->name(),
                                contact->surName());
        //...
        query.exec(str_insert);
    }
    return true;
}

Data::Contacts *DriverSql::loadData(const QString &path) const
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
        contact->setAlias(query.value(record.indexOf(Attribute::Name)).toString());
        contact->setAlias(query.value(record.indexOf(Attribute::SurName)).toString());
        //...
        data->append(contact);
    }
    return data;
}

bool DriverSql::saveContact(const Data::ContactData &data, const QString &path) const
{
    //FIXME add code
    return false;
}

Data::ContactData *DriverSql::loadContact(const QString &path) const
{
    //FIXME add code
    return 0;
}
