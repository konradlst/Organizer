#ifndef TIMEDATA_H
#define TIMEDATA_H

#include "abstractModule.h"

struct TimeData : public AbstractData
{
    int type;
    QTime started;
    QTime stoped;
    QTime duration;
    QString description;
};

#endif // TIMEDATA_H
