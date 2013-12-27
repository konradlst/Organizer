#ifndef ADDRESSDATA_H
#define ADDRESSDATA_H

#include "abstractModule.h"

struct AddressData : public AbstractData
{
    QString country;
    QString city;
    QString street;
    QString home;
    QString apartment;
    int contactId;
};

#endif // ADDRESSDATA_H
