#ifndef DRIVER_H
#define DRIVER_H

#include "contactData.h"

/*! \class Driver
    \brief Абстрактный драйвер для манипуляций с данными определенного формата.
*/
class Driver
{
public:
    explicit Driver(){};
    virtual ~Driver(){};
    virtual bool saveData(const Data::Contacts &data, const QString &path) = 0;
    virtual Data::Contacts *loadData(const QString &path) = 0;

    virtual bool saveContact(const ContactData &data, const QString &path) = 0;
    virtual ContactData *loadContact(const QString &path) = 0;
};

#endif // DRIVER_H
