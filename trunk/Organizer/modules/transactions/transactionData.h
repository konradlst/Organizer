#ifndef TRANSACTIONDATA_H
#define TRANSACTIONDATA_H

#include <QDate>
#include "abstractModule.h"

struct TransactionData : public AbstractData
{
    int type;
    QDate created;
    QString name;
    qint64 value;
    QString description;
};

#endif // TRANSACTIONDATA_H
