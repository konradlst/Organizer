#ifndef CHANNELDATA_H
#define CHANNELDATA_H

#include "abstractModule.h"

struct ChannelData : public AbstractData
{
    QString type;
    QString subType;
    QString value;
    int contactId;
};

#endif // CHANNELDATA_H
