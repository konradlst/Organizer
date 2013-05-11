#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QVector>
#include <QHash>
#include <QDate>
#include <QPixmap>
#include <QPair>

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
    bool isEmpty() const {
        return (country == QString()) && (city == QString())
               && (street == QString()) && (home == QString())
               && (apartment == QString());
    }
};

struct Communication
{
    QString subType;
    QString value;
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
    bool isEmpty() const {
        return (name == QString()) && (department == QString())
               && (post == QString()) && (address == QString())
               && (phone == QString());
    }
};

class ContactData
{
public:
    explicit ContactData();

    QString alias() const;
    QString name() const;
    QString surName() const;
    QString otherName() const;
    QDate birthday() const;
    QString birthdayAsString() const;
    QString pathToUserPic() const;
    QPixmap userPic() const;
    QString comment() const;

    QString country(int index) const;
    QString city(int index) const;
    QString street(int index) const;
    QString home(int index) const;
    QString apartment(int index) const;
    int countAddresses() const;

    QString companyName(int index) const;
    QString department(int index) const;
    QString post(int index) const;
    QString companyAddress(int index) const;
    QString companyPhone(int index) const;
    QDate dateIn(int index) const;
    QString dateInAsString(int index) const;
    QDate dateOut(int index) const;
    QString dateOutAsString(int index) const;
    int countCompanies() const;

    QList<QString> phones() const;
    QList<QString> emails() const;
    QList<QString> skypes() const;
    QList<QString> sites() const;
    QList<QString> phoneTypes() const;
    QList<QString> emailTypes() const;
    QList<QString> skypeTypes() const;
    QList<QString> siteTypes() const;
    QString phone(const QString &type) const;
    QString email(const QString &type) const;
    QString skype(const QString &type) const;
    QString site(const QString &type) const;
    int countChannels() const;
    int countPhones() const;
    int countEmails() const;
    int countSkypes() const;
    int countSites() const;
    bool isExistChannel(const QString type, const QString &key) const;

    void setAlias(const QString &data);
    void setName(const QString &data);
    void setSurName(const QString &data);
    void setOtherName(const QString &data);
    void setBirthday(const QDate &data);
    void setBirthday(const QString &data);
    int appendAddress(const QString &country, const QString &city,
                   const QString &street, const QString &home,
                   const QString &apartment);
    int appendCompany(const QString &name, const QString &department,
                           const QString &post, const QString &address,
                           const QString &phone, const QString &dateIn,
                           const QString &dateOut);
    void setPathToUserPic(const QString &data);
    void setUserPic(const QPixmap &data);
    void setComment(const QString &data);

    void setCountry(const int index, const QString &data);
    void setCity(const int index, const QString &data);
    void setStreet(const int index, const QString &data);
    void setHome(const int index, const QString &data);
    void setApartment(const int index, const QString &data);

    void setCompanyName(const int index, const QString &data);
    void setDepartment(const int index, const QString &data);
    void setPost(const int index, const QString &data);
    void setCompanyAddress(const int index, const QString &data);
    void setCompanyPhone(const int index, const QString &data);
    void setDateIn(const int index, const QDate &data);
    void setDateIn(const int index, const QString &data);
    void setDateOut(const int index, const QDate &data);
    void setDateOut(const int index, const QString &data);

    void setPhone(const QString &type, const QString &value);
    void setEmail(const QString &type, const QString &value);
    void setSkype(const QString &type, const QString &value);
    void setSite(const QString &type, const QString &value);

private:
    int appendAddress(const Address &data);
    int appendCompany(const Company &data);

    QString m_alias;
    QString m_name;
    QString m_surName;
    QString m_otherName;
    QDate m_birthday;
    QVector<Address> m_addresses;
    QHash<QString,QString> m_phones;
    QHash<QString,QString> m_emails;
    QHash<QString,QString> m_skypes;
    QHash<QString,QString> m_sites;
    QVector<Company> m_companies;
    QString m_pathToUserPic;
    QPixmap m_userPic;
    QString m_comment;
};

typedef QVector<ContactData *> Contacts;

};

#endif // CONTACTDATA_H
