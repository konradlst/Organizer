#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QHash>
#include <QVector>
#include <QDate>

class QString;

namespace Data {
#define DEFAULT_DATE QDate(1900,1,1)
#define DEFAULT_DATE_FORMAT "dd.MM.yyyy"
#define DEFAULT_USER_PIC ":/logo"

struct Address
{
    QString country;
    QString city;
    QString street;
    QString home;
    QString apartment;
};

struct Communication
{
    QString subType;
    QString value;
};

struct Organization
{
    QString name;
    QString department;
    QString post;
    QString address;
    QString phone;
    QDate dateIn;
    QDate dateOut;
};

enum typeCommunication
{ typePhone, typeEmail, typeSkype, typeSite};

typedef QPair<typeCommunication,Communication> CommunicationData;

struct ContactData
{
    QString m_alias;
    QString m_name;
    QString m_surName;
    QString m_otherName;
    QDate m_birthday;
    QVector<Address> m_addresses;
    QVector<CommunicationData> m_communications;
    QVector<Organization> m_organizations;
    QString m_pathToUserPic;
    QString m_comment;
};

typedef QVector<ContactData *> Contacts;

};

#endif // CONTACTDATA_H
