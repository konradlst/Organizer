#ifndef DRIVERSQLITE_H
#define DRIVERSQLITE_H

#include "driver.h"

class QSqlQuery;
class QSqlRecord;

class DriverSqlite : public Driver
{
public:
    explicit DriverSqlite();
    ~DriverSqlite();
    bool saveData(const Data::Contacts &data, const QString &path);
    Data::Contacts *loadData(const QString &path);

    bool saveContact(const ContactData &, const QString &);
    ContactData *loadContact(const QString &);

private:
    void contactDataToSql(const ContactData *contact, const int i) const;
    void sqlToContactData(const QSqlQuery &query, ContactData *contact) const;
};

#endif // DRIVERSQLITE_H