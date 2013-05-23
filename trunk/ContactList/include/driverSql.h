#ifndef DRIVERSQL_H
#define DRIVERSQL_H

#include "driver.h"

class QSqlQuery;
class QSqlRecord;

class DriverSql : public Driver
{
public:
    explicit DriverSql();
    ~DriverSql();
    bool saveData(const Data::Contacts &data, const QString &path);
    Data::Contacts *loadData(const QString &path);

    bool saveContact(const Data::ContactData &data, const QString &path);
    Data::ContactData *loadContact(const QString &path);

private:
    void contactDataToSql(QSqlQuery &query, const Data::ContactData *contact, const int i) const;
    void sqlToContactData(const QSqlQuery &query, const QSqlRecord &record, Data::ContactData *contact) const;
};

#endif // DRIVERSQL_H
