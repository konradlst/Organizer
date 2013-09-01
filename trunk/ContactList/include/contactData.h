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

struct Data
{
    Data() {}
    Data(QString _country, QString _city, QString _street, QString _home,
         QString _apartment)
        : country(_country),
          city(_city),
          street(_street),
          home(_home),
          apartment(_apartment)
    {}
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

struct Data
{
    Data() {}
    Data(QString type, QString subType, QString value)
        : m_type(type),
          m_subType(subType),
          m_value(value)
    {}
    QString m_type;
    QString m_subType;
    QString m_value;
    bool isEmpty() const
    {
        return m_type.isEmpty() && m_subType.isEmpty() && m_value.isEmpty();
    }
};
}

namespace Company
{
struct Data
{
    Data() {}
    Data(QString _name, QString _department, QString _post, QString _address,
         QString _phone, QDate _dateIn, QDate _dateOut)
        : name(_name),
          department(_department),
          post(_post),
          address(_address),
          phone(_phone),
          dateIn(_dateIn),
          dateOut(_dateOut)
    {}
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

    //! Получает данные заданного типа \param по заданному индексу \param index.
    QStringList data(const QString &type, const int &index = 0) const;
    //! Устанавливает у контакта значение \param value для заданного параметра \param type.
    void setMainData(const QString &type, const QString &value);
    //! Устанавливает день рождения \param data контакта.
    void setBirthday(const QDate &data);
    //! Устанавливает основные данные \param data контакта.
    void setMainData(const QStringList &data);
    //! Устанавливает данные \param data заданного типа \param type
    //! для адреса по заданному индексу \param index.
    void setAddressData(const QString &type, const QString &data, const int &index = 0);
    //! Устанавливает данные \param data адреса по заданному индексу \param index.
    void setAddressData(const QStringList &data, const int &index = 0);

    //! Устанавливает данные \param data заданного типа \param type
    //! для компании по заданному индексу \param index.
    void setCompanyData(const QString &type, const QString &data, const int &index = 0);
    //! Устанавливает данные \param data заданного типа \param type
    //! для компании по заданному индексу \param index.
    void setCompanyData(const QString &type, const QDate &data, const int &index = 0);
    //! Устанавливает данные \param data компании по заданному индексу \param index.
    void setCompanyData(const QStringList &data, const int &index = 0);
    //! Устанавливает данные \param value канала связи заданного вида \param type
    //! указанного типа \param subType.
    void setChannel(const QString &type, const QString &subType,
                    const QString &value);
    //! Возвращает количество данные указанного типа \param type.
    int countData(const QString &type = QString()) const;

private:
    QString m_alias;
    QString m_name;
    QString m_surName;
    QString m_otherName;
    QDate m_birthday;
    QVector<Address::Data*> *m_addresses;
    QVector<Channel::Data*> *m_channels;
    QVector<Company::Data*> *m_companies;
    QString m_pathToUserPic;
    QString m_comment;
};

namespace Data
{
#define DEFAULT_DATE QDate(1900,1,1)
#define DEFAULT_DATE_FORMAT "dd.MM.yyyy"
#define DEFAULT_USER_PIC ":/logo"
typedef QVector<ContactData*> Contacts;
};

#endif // CONTACTDATA_H
