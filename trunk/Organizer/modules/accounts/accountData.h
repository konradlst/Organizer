#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H

#include <QDate>
#include "abstractModule.h"

struct AccountData : public AbstractData
{
    int type;
    QDate created;
    QString name;
    qint64 value;
    qint64 total;
    QString description;
};

#endif // ACCOUNTDATA_H
