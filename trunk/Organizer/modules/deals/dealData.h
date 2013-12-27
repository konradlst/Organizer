#ifndef DEALDATA_H
#define DEALDATA_H

#include "abstractModule.h"

struct DealData : public AbstractData
{
    int type;
    QDate created;
    qint64 price;
    QTime duration;
    QDate deadLine;
    QString humans;
    QString description;
};

#endif // DEALDATA_H
