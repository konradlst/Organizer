#include <QPixmap>
#include "contactData.h"

namespace {
const QString CONTACT("contact");
const QString COMPANY("company");
const QString ADDRESS("address");

QDate string2Date(QString data) {
    if(data.isEmpty())
        return DEFAULT_DATE;
    return QDate::fromString(data, DEFAULT_DATE_FORMAT);
}

QString date2String(QDate data) {
    return data.toString(DEFAULT_DATE_FORMAT);
}
}

namespace Data {
namespace Addr
{
const QString Country("country");
const QString City("city");
const QString Street("street");
const QString Home("home");
const QString Apartment("apartment");
}

ContactData::ContactData() :
    m_addresses(new QVector<Address>),
    m_phones(new Channels),
    m_emails(new Channels),
    m_skypes(new Channels),
    m_sites(new Channels),
    m_companies(new QVector<Company>)
{
    m_alias = QString("New contact");
    m_birthday = DEFAULT_DATE;
    m_addresses->append(Address());

    Company company;
    company.dateIn = QDate::currentDate();
    company.dateOut = QDate::currentDate();
    m_companies->append(company);
    m_phones->insert(Channel::Phone,QString());
    m_emails->insert(Channel::Email,QString());
    m_skypes->insert(Channel::Skype,QString());
    m_sites->insert(Channel::Site,QString());
}

QStringList ContactData::data(const QString &type, const int &index) const
{
    QStringList list;
    if(type == CONTACT)
    {
        list << m_alias
             << m_name
             << m_surName
             << m_otherName
             << date2String(m_birthday)
             << m_pathToUserPic
             << m_comment;
    }
    else if(type == COMPANY)
    {
        list << m_companies->at(index).name
             << m_companies->at(index).phone
             << m_companies->at(index).department
             << m_companies->at(index).post
             << m_companies->at(index).address
             << date2String(m_companies->at(index).dateIn)
             << date2String(m_companies->at(index).dateOut);
    }
    else if(type == ADDRESS)
    {
        list << m_addresses->at(index).country
             << m_addresses->at(index).city
             << m_addresses->at(index).street
             << m_addresses->at(index).home
             << m_addresses->at(index).apartment;
    }
    return list;
}

void ContactData::setMainData(const QString &type, const QString &value)
{
    if(type == Attribute::Alias)
        m_alias = value;
    else if(type == Attribute::Name)
        m_name = value;
    else if(type == Attribute::SurName)
        m_surName = value;
    else if(type == Attribute::OtherName)
        m_otherName = value;
    else if(type == Attribute::Birthday)
        m_birthday = string2Date(value);
    else if(type == Attribute::PathToUserPic)
        m_pathToUserPic = value;
    else if(type == Attribute::Comment)
        m_comment = value;
}

void ContactData::setBirthday(const QDate &data)
{
    m_birthday = data;
}

void ContactData::setUserPic(const QPixmap &data)
{
    m_userPic = data;
}

void ContactData::setMainData(const QStringList &data)
{
    if(data.size() > 4)
    {
        m_alias = data.at(0);
        m_name = data.at(1);
        m_surName = data.at(2);
        m_otherName = data.at(3);
        m_birthday = string2Date(data.at(4));
        if(data.size() == 7)
        {
            m_pathToUserPic = data.at(5);
            m_comment = data.at(6);
        }
    }
}

void ContactData::setAddressData(const QString &type, const QString &data,
                                 const int &index)
{
    Address temp = m_addresses->at(index);
    if(type == Addr::Country)
        temp.country = data;
    else if(type == Addr::City)
        temp.city = data;
    else if(type == Addr::Street)
        temp.street = data;
    else if(type == Addr::Home)
        temp.home = data;
    else if(type == Addr::Apartment)
        temp.apartment = data;
    m_addresses->replace(index, temp);
}

void ContactData::setAddressData(const QStringList &data, const int &index)
{
    if(data.size() == 5)
    {
        Address temp = m_addresses->at(index);
        temp.country = data.at(0);
        temp.city = data.at(1);
        temp.street = data.at(2);
        temp.home = data.at(3);
        temp.apartment = data.at(4);
        m_addresses->replace(index, temp);
    }
}

void ContactData::setCompanyData(const QString &type, const QString &data,
                                 const int &index)
{
    Company temp = m_companies->at(index);
    if(type == Attribute::NameOrganization)
        temp.name = data;
    else if(type == Attribute::Department)
        temp.department = data;
    else if(type == Attribute::Post)
        temp.post = data;
    else if(type == Attribute::AddressOrganization)
        temp.address = data;
    else if(type == Attribute::PhoneOrganization)
        temp.phone = data;
    else if(type == Attribute::DateIn)
        temp.dateIn = string2Date(data);
    else if(type == Attribute::DateOut)
        temp.dateOut = string2Date(data);
    m_companies->replace(index, temp);
}

void ContactData::setCompanyData(const QString &type, const QDate &data,
                                 const int &index)
{
    Company temp = m_companies->at(index);
    if(type == Attribute::DateIn)
        temp.dateIn = data;
    else if(type == Attribute::DateOut)
        temp.dateOut = data;

    m_companies->replace(index, temp);
}

void ContactData::setCompanyData(const QStringList &data, const int &index)
{
    if(data.size() == 7)
    {
        Company temp = m_companies->at(index);
        temp.name = data.at(0);
        temp.department = data.at(1);
        temp.post = data.at(2);
        temp.address = data.at(3);
        temp.phone = data.at(4);
        temp.dateIn = string2Date(data.at(5));
        temp.dateOut = string2Date(data.at(6));
        m_companies->replace(index, temp);
    }
}

void ContactData::setChannel(const QString &type, const QString &subType, const QString &value)
{
    if(type == Channel::Phone)
    {
        if(m_phones->contains(Channel::Phone))
            m_phones->remove(Channel::Phone);
        m_phones->insert(subType,value);
    }
    else if(type == Channel::Email)
    {
        if(m_emails->contains(Channel::Email))
            m_emails->remove(Channel::Email);
        m_emails->insert(subType,value);
    }
    else if(type == Channel::Skype)
    {
        if(m_skypes->contains(Channel::Skype))
            m_skypes->remove(Channel::Skype);
        m_skypes->insert(subType,value);
    }
    else if(type == Channel::Site)
    {
        if(m_sites->contains(Channel::Site))
            m_sites->remove(Channel::Site);
        m_sites->insert(subType,value);
    }
}

QDate ContactData::birthday() const
{
    return m_birthday;
}

QPixmap ContactData::userPic() const
{
    return m_userPic;
}

QDate ContactData::dateIn(int index) const
{
    return m_companies->at(index).dateIn;
}

QDate ContactData::dateOut(int index) const
{
    return m_companies->at(index).dateOut;
}

int ContactData::countCompanies() const
{
    return m_companies->size();
}

int ContactData::countAddresses() const
{
    return m_addresses->size();
}

int ContactData::countChannels(const QString &type) const
{
    int count;
    if(type == Channel::Phone)
        count = m_phones->size();
    else if(type == Channel::Email)
        count = m_emails->size();
    else if(type == Channel::Skype)
        count = m_skypes->size();
    else if(type == Channel::Site)
        count = m_sites->size();
    else
        count = m_phones->size() +
                m_emails->size() +
                m_skypes->size() +
                m_sites->size();
    return count;
}

QList<QString> ContactData::channels(const QString &type) const
{
    if(type == Channel::Phone)
        return m_phones->values();
    else if(type == Channel::Email)
        return m_emails->values();
    else if(type == Channel::Skype)
        return m_skypes->values();
    else if(type == Channel::Site)
        return m_sites->values();
    else
        return QList<QString>();
}

QList<QString> ContactData::channelsTypes(const QString &type) const
{
    if(type == Channel::Phone)
        return m_phones->keys();
    else if(type == Channel::Email)
        return m_emails->keys();
    else if(type == Channel::Skype)
        return m_skypes->keys();
    else if(type == Channel::Site)
        return m_sites->keys();
    else
        return QList<QString>();
}

bool ContactData::isExistChannel(const QString type, const QString &key) const
{
    if(type == Channel::Phone)
        return m_phones->contains(key);
    else if(type == Channel::Email)
        return m_emails->contains(key);
    else if(type == Channel::Skype)
        return m_skypes->contains(key);
    else if(type == Channel::Site)
        return m_sites->contains(key);
    else
        return false;
}

int ContactData::appendAddress(const QStringList &value)
{
    Address data;
    data.country = value.at(0);
    data.city = value.at(1);
    data.street = value.at(2);
    data.home = value.at(3);
    data.apartment = value.at(4);

    if(m_addresses->size() > 0 && m_addresses->at(0).isEmpty())
        m_addresses->remove(0);
    m_addresses->append(data);
    return m_addresses->size() - 1;
}

int ContactData::appendCompany(const QStringList &value)
{
    Company data;
    data.name = value.at(0);
    data.department = value.at(1);
    data.post = value.at(2);
    data.address = value.at(3);
    data.phone = value.at(4);
    data.dateIn = string2Date(value.at(5));
    data.dateOut = string2Date(value.at(6));

    if(m_companies->at(0).isEmpty())
        m_companies->remove(0);
    m_companies->append(data);
    return m_companies->size() - 1;
}
}
