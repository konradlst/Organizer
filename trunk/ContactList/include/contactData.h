#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QVector>
#include <QDate>
#include <QPixmap>

class QString;

namespace Attribute {
const QString Alias("alias");
const QString Name("name");
const QString SurName("surName");
const QString OtherName("otherName");
const QString Birthday("birthday");
const QString PathToUserPic("pathToUserPic");
const QString Userpic("userPic");
const QString Comment("comment");
const QString Country("country");
const QString City("city");
const QString Street("street");
const QString Home("home");
const QString Apartment("apartment");
const QString Type("type");
const QString Subtype("subtype");
const QString Value("value");
const QString NameOrganization("nameOrganization");
const QString PhoneOrganization("phoneOrganization");
const QString AddressOrganization("addressOrganization");
const QString Department("department");
const QString Post("post");
const QString Address("address");
const QString Phone("phone");
const QString DateIn("dateIn");
const QString DateOut("dateOut");
}

namespace Value {
const QString Phone("phone");
const QString Email("email");
const QString Skype("skype");
const QString Site("site");
}

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
    QPixmap m_userPic;
    QString m_comment;
};

typedef QVector<ContactData *> Contacts;

};

#endif // CONTACTDATA_H
