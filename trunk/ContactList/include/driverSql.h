#ifndef DRIVERSQL_H
#define DRIVERSQL_H

#include "driver.h"

class DriverSql : public Driver
{
public:
    explicit DriverSql();
    ~DriverSql();
    bool saveData(const Data::Contacts &data, const QString &path);
    Data::Contacts *loadData(const QString &path);

    bool saveContact(const Data::ContactData &data, const QString &path);
    Data::ContactData *loadContact(const QString &path);
};

#endif // DRIVERSQL_H
