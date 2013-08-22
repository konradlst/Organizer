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

ContactData::ContactData()
    : m_addresses(new QVector<Address::Data*>),
      m_channels(new QVector<Channel::Data*>),
      m_companies(new QVector<Company::Data*>)
{
    m_alias = QString("New contact");
    m_birthday = DEFAULT_DATE;
}

QStringList ContactData::data(const QString &type, const int &index) const
{
    QStringList list;
    if (type == CONTACT)
    {
        list << m_alias
             << m_name
             << m_surName
             << m_otherName
             << date2String(m_birthday)
             << m_pathToUserPic
             << m_comment;
    }
    else if (type == COMPANY && index < m_companies->count())
    {
        list << m_companies->at(index)->name
             << m_companies->at(index)->phone
             << m_companies->at(index)->department
             << m_companies->at(index)->post
             << m_companies->at(index)->address
             << date2String(m_companies->at(index)->dateIn)
             << date2String(m_companies->at(index)->dateOut);
    }
    else if (type == ADDRESS && index < m_addresses->count())
    {
        list << m_addresses->at(index)->country
             << m_addresses->at(index)->city
             << m_addresses->at(index)->street
             << m_addresses->at(index)->home
             << m_addresses->at(index)->apartment;
    }
    else if (type == Channel::All && index < m_channels->count())
    {
        list << m_channels->at(index)->m_type
             << m_channels->at(index)->m_subType
             << m_channels->at(index)->m_value;
    }
    else if (m_channels->count() > 0
             && (type == Channel::Phone
                 || type == Channel::Email
                 || type == Channel::Skype
                 || type == Channel::Site))
    {
        int id = 0;
        while (type != m_channels->at(id)->m_type)
            ++id;
        list << m_channels->at(id)->m_type
             << m_channels->at(id)->m_subType
             << m_channels->at(id)->m_value;
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
    if(data.size() < 4)
        return;
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

void ContactData::setAddressData(const QString &type, const QString &data,
                                 const int &index)
{
    Address::Data *temp = new Address::Data;
    if(type == Address::Country)
        temp->country = data;
    else if(type == Address::City)
        temp->city = data;
    else if(type == Address::Street)
        temp->street = data;
    else if(type == Address::Home)
        temp->home = data;
    else if(type == Address::Apartment)
        temp->apartment = data;
    if(index < m_addresses->count())
        m_addresses->replace(index, temp);
    else
        m_addresses->append(temp);
}

void ContactData::setAddressData(const QStringList &data, const int &index)
{
    if(data.size() != 5)
        return;
    Address::Data *temp = new Address::Data(data.at(0), data.at(1), data.at(2),
                                            data.at(3), data.at(4));
    if(index < m_addresses->count())
        m_addresses->replace(index, temp);
    else
        m_addresses->append(temp);
}

void ContactData::setCompanyData(const QString &type, const QString &data,
                                 const int &index)
{
    Company::Data *temp = new Company::Data;
    if(type == Attribute::NameOrganization)
        temp->name = data;
    else if(type == Attribute::Department)
        temp->department = data;
    else if(type == Attribute::Post)
        temp->post = data;
    else if(type == Attribute::AddressOrganization)
        temp->address = data;
    else if(type == Attribute::PhoneOrganization)
        temp->phone = data;
    else if(type == Attribute::DateIn)
        temp->dateIn = string2Date(data);
    else if(type == Attribute::DateOut)
        temp->dateOut = string2Date(data);
    if(index < m_companies->count())
        m_companies->replace(index, temp);
    else
        m_companies->append(temp);
}

void ContactData::setCompanyData(const QString &type, const QDate &data,
                                 const int &index)
{
    Company::Data *temp = new Company::Data;
    if(type == Attribute::DateIn)
        temp->dateIn = data;
    else if(type == Attribute::DateOut)
        temp->dateOut = data;

    if(index < m_companies->count())
        m_companies->replace(index, temp);
    else
        m_companies->append(temp);
}

void ContactData::setCompanyData(const QStringList &data, const int &index)
{
    if(data.count() != 7)
        return;
    Company::Data *temp = new Company::Data(data.at(0), data.at(1), data.at(2),
                                            data.at(3), data.at(4),
                                            string2Date(data.at(5)),
                                            string2Date(data.at(6)));
    if(index < m_companies->count())
        m_companies->replace(index, temp);
    else
        m_companies->append(temp);
}

void ContactData::setChannel(const QString &type,
                             const QString &subType,
                             const QString &value)
{
    Channel::Data *channel = new Channel::Data(type, subType, value);
    m_channels->append(channel);
}

int ContactData::countData(const QString &type) const
{
    if(type == COMPANY)
        return m_companies->count();
    else if(type == ADDRESS)
        return m_addresses->count();
    else if(type == Channel::All)
        return m_channels->count();
    return 0;
}
