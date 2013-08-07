#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QVector>
#include <QHash>
#include <QDate>
#include <QPixmap>
#include "channel.h"

enum { ALIAS = 0, NAME, LASTNAME, OTHERNAME, BIRTHDAY, USER_PIC, COMMENT };
enum { COMP_NAME = 0, PHONE, DEPARTMENT, POST, COMP_ADDRESS, DATEIN, DATEOUT };
enum { COUNTRY = 0, CITY, STREET, HOME, APARTMENT };

namespace Attribute
{
const QString Version("version");
const QString Alias("alias");
const QString Name("name");
const QString LastName("lastName");
const QString OtherName("otherName");
const QString Birthday("birthday");
const QString PathToUserPic("pathToUserPic");
const QString Userpic("userPic");
const QString Comment("comment");
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

namespace Address
{
const QString Country("country");
const QString City("city");
const QString Street("street");
const QString Home("home");
const QString Apartment("apartment");
}

namespace Data
{
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
    bool isEmpty() const
    {
        return country.isEmpty() &&
               city.isEmpty() &&
               street.isEmpty() &&
               home.isEmpty() &&
               apartment.isEmpty();
    }
};

struct Company
{
    QString name;
    QString department;
    QString post;
    QString address;
    QString phone;
    QDate dateIn;
    QDate dateOut;
    bool isEmpty() const
    {
        return name.isEmpty() &&
               department.isEmpty() &&
               post.isEmpty() &&
               address.isEmpty() &&
               phone.isEmpty();
    }
};

//FIXME !!!!!
class ContactData
{
public:
    explicit ContactData();

    QStringList data(const QString &type, const int &index = 0) const;
    void setMainData(const QString &type, const QString &value);
    void setBirthday(const QDate &data);
    void setUserPic(const QPixmap &data);
    void setMainData(const QStringList &data);
    void setAddressData(const QString &type, const QString &data, const int &index = 0);
    void setAddressData(const QStringList &data, const int &index = 0);
    void setCompanyData(const QString &type, const QString &data, const int &index = 0);
    void setCompanyData(const QString &type, const QDate &data, const int &index = 0);
    void setCompanyData(const QStringList &data, const int &index = 0);
    void setChannel(const QString &type, const QString &subType, const QString &value);

    QDate   birthday()           const;
    QPixmap userPic()            const;
    QDate dateIn(int index = 0)  const;
    QDate dateOut(int index = 0) const;

    int countCompanies() const;
    int countAddresses() const;
    int countChannels(const QString &type = QString()) const;

    QList<QString> channels(const QString &type) const;
    QList<QString> channelsTypes(const QString &type) const;

    bool isExistChannel(const QString type, const QString &key) const;

    int appendAddress(const QStringList &value);
    int appendCompany(const QStringList &value);

private:
    QString m_alias;
    QString m_name;
    QString m_surName;
    QString m_otherName;
    QDate m_birthday;
    QVector<Address> *m_addresses;
    typedef QHash<QString,QString> Channels;
    Channels *m_phones;
    Channels *m_emails;
    Channels *m_skypes;
    Channels *m_sites;
    QVector<Company> *m_companies;
    QString m_pathToUserPic;
    QPixmap m_userPic;
    QString m_comment;
};

typedef QVector<ContactData *> Contacts;
};

#endif // CONTACTDATA_H
