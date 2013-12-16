#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include "abstractModule.h"

struct ContactData : public AbstractData
{
    QString name;
    QString surName;
    QString otherName;
    QString nickName;
    QString birthday;
    QPixmap userPic;
};

#endif // CONTACTDATA_H
