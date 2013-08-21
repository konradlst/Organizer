#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QVector>
#include <QHash>
#include <QDate>

enum { ALIAS = 0, NAME, LASTNAME, OTHERNAME, BIRTHDAY, USER_PIC, COMMENT };
enum { COMP_NAME = 0, PHONE, DEPARTMENT, POST, COMP_ADDRESS, DATEIN, DATEOUT };
enum { COUNTRY = 0, CITY, STREET, HOME, APARTMENT };

const QString CONTACT("contact");
const QString COMPANY("company");
const QString ADDRESS("address");

namespace Attribute
{
const QString Version("version");
const QString Alias("alias");
const QString Name("name");
const QString LastName("lastName");
const QString OtherName("otherName");
const QString Birthday("birthday");
const QString PathToUserPic("pathToUserPic");
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

namespace Channel
{
const QString All("All");
const QString Phone("Phone");
const QString Email("Email");
const QString Skype("Skype");
const QString Site("Site");
const QString PhoneType("PhoneType");
const QString EmailType("EmailType");
const QString SkypeType("SkypeType");
const QString SiteType("SiteType");
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
}

class ContactData
{
public:
    explicit ContactData();

    QStringList data(const QString &type, const int &index = 0) const;
    void setMainData(const QString &type, const QString &value);
    void setBirthday(const QDate &data);
    void setMainData(const QStringList &data);
    void setAddressData(const QString &type, const QString &data,
                        const int &index = 0);
    void setAddressData(const QStringList &data, const int &index = 0);
    void setCompanyData(const QString &type, const QString &data,
                        const int &index = 0);
    void setCompanyData(const QString &type, const QDate &data, const int &index = 0);
    void setCompanyData(const QStringList &data, const int &index = 0);
    void setChannel(const QString &type, const QString &subType,
                    const QString &value);

    int countData(const QString &type = QString()) const;
    QList<QString> channelsTypes(const QString &type) const;

private:
    QString m_alias;
    QString m_name;
    QString m_surName;
    QString m_otherName;
    QDate m_birthday;
    QVector<Data::Address> *m_addresses;
    typedef QHash<QString,QString> Channels;
    Channels *m_phones;
    Channels *m_emails;
    Channels *m_skypes;
    Channels *m_sites;
    QVector<Data::Company> *m_companies;
    QString m_pathToUserPic;
    QString m_comment;
};

namespace Data
{
typedef QVector<ContactData *> Contacts;
};

#endif // CONTACTDATA_H
