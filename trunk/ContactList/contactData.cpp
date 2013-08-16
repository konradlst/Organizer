#include <QPixmap>
#include "contactData.h"

namespace
{
QDate string2Date(QString data)
{
    if(data.isEmpty())
        return DEFAULT_DATE;
    return QDate::fromString(data, DEFAULT_DATE_FORMAT);
}

QString date2String(QDate data)
{
    return data.toString(DEFAULT_DATE_FORMAT);
}
}

ContactData::ContactData() :
    m_addresses(new QVector<Data::Address>),
    m_phones(new Channels),
    m_emails(new Channels),
    m_skypes(new Channels),
    m_sites(new Channels),
    m_companies(new QVector<Data::Company>)
{
    m_alias = QString("New contact");
    m_birthday = DEFAULT_DATE;

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
    else if(type == COMPANY && index < m_companies->count())
    {
        list << m_companies->at(index).name
             << m_companies->at(index).phone
             << m_companies->at(index).department
             << m_companies->at(index).post
             << m_companies->at(index).address
             << date2String(m_companies->at(index).dateIn)
             << date2String(m_companies->at(index).dateOut);
    }
    else if(type == ADDRESS && index < m_addresses->count())
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
    else if(type == Attribute::LastName)
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
    Data::Address temp;
    if(type == Address::Country)
        temp.country = data;
    else if(type == Address::City)
        temp.city = data;
    else if(type == Address::Street)
        temp.street = data;
    else if(type == Address::Home)
        temp.home = data;
    else if(type == Address::Apartment)
        temp.apartment = data;
    if(index < m_addresses->count())
        m_addresses->replace(index, temp);
    else
        m_addresses->append(temp);
}

void ContactData::setAddressData(const QStringList &data, const int &index)
{
    if(data.size() == 5)
    {
        Data::Address temp;
        temp.country = data.at(0);
        temp.city = data.at(1);
        temp.street = data.at(2);
        temp.home = data.at(3);
        temp.apartment = data.at(4);
        if(index < m_addresses->count())
            m_addresses->replace(index, temp);
        else
            m_addresses->append(temp);
    }
}

void ContactData::setCompanyData(const QString &type, const QString &data,
                                 const int &index)
{
    Data::Company temp;
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
    if(index < m_companies->count())
        m_companies->replace(index, temp);
    else
        m_companies->append(temp);
}

void ContactData::setCompanyData(const QString &type, const QDate &data,
                                 const int &index)
{
    Data::Company temp;
    if(type == Attribute::DateIn)
        temp.dateIn = data;
    else if(type == Attribute::DateOut)
        temp.dateOut = data;

    if(index < m_companies->count())
        m_companies->replace(index, temp);
    else
        m_companies->append(temp);
}

void ContactData::setCompanyData(const QStringList &data, const int &index)
{
    if(data.size() == 7)
    {
        Data::Company temp;
        temp.name = data.at(0);
        temp.department = data.at(1);
        temp.post = data.at(2);
        temp.address = data.at(3);
        temp.phone = data.at(4);
        temp.dateIn = string2Date(data.at(5));
        temp.dateOut = string2Date(data.at(6));
        if(index < m_companies->count())
            m_companies->replace(index, temp);
        else
            m_companies->append(temp);
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
    return m_companies->count();
}

int ContactData::countAddresses() const
{
    return m_addresses->count();
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
