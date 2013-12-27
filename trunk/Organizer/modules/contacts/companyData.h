#ifndef COMPANYDATA_H
#define COMPANYDATA_H

#include "abstractModule.h"

struct CompanyData : public AbstractData
{
    QString company;
    QString post;
    QString dateIn;
    QString dateOut;
    int contactId;
};

#endif // COMPANYDATA_H
