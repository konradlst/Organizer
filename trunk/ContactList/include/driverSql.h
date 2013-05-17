#ifndef DRIVERSQL_H
#define DRIVERSQL_H

#include "driver.h"

class DriverSql : public Driver
{
public:
    explicit DriverSql();
    ~DriverSql();
    bool saveData(const Data::Contacts &data, const QString &path) const;
    Data::Contacts *loadData(const QString &path) const;

    bool saveContact(const Data::ContactData &data, const QString &path) const;
    Data::ContactData *loadContact(const QString &path) const;
};

#endif // DRIVERSQL_H
