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
};

#endif // ADDRESSDATA_H
