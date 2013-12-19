#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H

#include "abstractModule.h"

struct AccountData : public AbstractData
{
    QString type;
    QString created;
    QString name;
    QString value;
    QString total;
    QString description;
};

#endif // ACCOUNTDATA_H
