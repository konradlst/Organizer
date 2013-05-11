#include "contactData.h"

namespace {
QDate string2Date(QString data) {
    if(data.isEmpty())
        return DEFAULT_DATE;
    return QDate::fromString(data,DEFAULT_DATE_FORMAT);
}

QString date2String(QDate data) {
    return data.toString(DEFAULT_DATE_FORMAT);
}
}

namespace Data {
ContactData::ContactData()
{
    m_alias = QString("New contact");
    m_birthday = DEFAULT_DATE;
    m_addresses.append(Address());

    Company company;
    company.dateIn = QDate::currentDate();
    company.dateOut = QDate::currentDate();
    m_companies.append(company);
    m_phones.insert(Value::Phone,QString());
    m_emails.insert(Value::Email,QString());
    m_skypes.insert(Value::Skype,QString());
    m_sites.insert(Value::Site,QString());
}

QString ContactData::alias() const
{
    return m_alias;
}

QString ContactData::name() const
{
    return m_name;
}

QString ContactData::surName() const
{
    return m_surName;
}

QString ContactData::otherName() const
{
    return m_otherName;
}

QDate ContactData::birthday() const
{
    return m_birthday;
}

QString ContactData::birthdayAsString() const
{
    return date2String(m_birthday);
}

QString ContactData::pathToUserPic() const
{
    return m_pathToUserPic;
}

QPixmap ContactData::userPic() const
{
    return m_userPic;
}

QString ContactData::comment() const
{
    return m_comment;
}

QString ContactData::country(int index) const
{
    return m_addresses.at(index).country;
}

QString ContactData::city(int index) const
{
    return m_addresses.at(index).city;
}

QString ContactData::street(int index) const
{
    return m_addresses.at(index).street;
}

QString ContactData::home(int index) const
{
    return m_addresses.at(index).home;
}

QString ContactData::apartment(int index) const
{
    return m_addresses.at(index).apartment;
}

int ContactData::countAddresses() const
{
    return m_addresses.size();
}

QString ContactData::companyName(int index) const
{
    return m_companies.at(index).name;
}

QString ContactData::department(int index) const
{
    return m_companies.at(index).department;
}

QString ContactData::post(int index) const
{
    return m_companies.at(index).post;
}

QString ContactData::companyAddress(int index) const
{
    return m_companies.at(index).address;
}

QString ContactData::companyPhone(int index) const
{
    return m_companies.at(index).phone;
}

QDate ContactData::dateIn(int index) const
{
    return m_companies.at(index).dateIn;
}

QString ContactData::dateInAsString(int index) const
{
    return date2String(m_companies.at(index).dateIn);
}

QDate ContactData::dateOut(int index) const
{
    return m_companies.at(index).dateOut;
}

QString ContactData::dateOutAsString(int index) const
{
    return date2String(m_companies.at(index).dateOut);
}

int ContactData::countCompanies() const
{
    return m_companies.size();
}

QList<QString> ContactData::phones() const
{
    return m_phones.values();
}

QList<QString> ContactData::emails() const
{
    return m_emails.values();
}

QList<QString> ContactData::skypes() const
{
    return m_skypes.values();
}

QList<QString> ContactData::sites() const
{
    return m_sites.values();
}

QList<QString> ContactData::phoneTypes() const
{
    return m_phones.keys();
}

QList<QString> ContactData::emailTypes() const
{
    return m_emails.keys();
}

QList<QString> ContactData::skypeTypes() const
{
    return m_skypes.keys();
}

QList<QString> ContactData::siteTypes() const
{
    return m_sites.keys();
}

QString ContactData::phone(const QString &type) const
{
    return m_phones.value(type);
}

QString ContactData::email(const QString &type) const
{
    return m_emails.value(type);
}

QString ContactData::skype(const QString &type) const
{
    return m_skypes.value(type);
}

QString ContactData::site(const QString &type) const
{
    return m_sites.value(type);
}

int ContactData::countChannels() const
{
    return countPhones() + countEmails() + countSkypes() + countSites();
}

int ContactData::countPhones() const
{
    return m_phones.size();
}

int ContactData::countEmails() const
{
    return m_emails.size();
}

int ContactData::countSkypes() const
{
    return m_skypes.size();
}

int ContactData::countSites() const
{
    return m_sites.size();
}

bool ContactData::isExistChannel(const QString type, const QString &key) const
{
    if(type == Value::Phone)
        return m_phones.contains(key);
    else if(type == Value::Email)
        return m_emails.contains(key);
    else if(type == Value::Skype)
        return m_skypes.contains(key);
    else if(type == Value::Site)
        return m_sites.contains(key);
    else
        return false;
}

void ContactData::setAlias(const QString &data)
{
    m_alias = data;
}

void ContactData::setName(const QString &data)
{
    m_name = data;
}

void ContactData::setSurName(const QString &data)
{
    m_surName = data;
}

void ContactData::setOtherName(const QString &data)
{
    m_otherName = data;
}

void ContactData::setBirthday(const QDate &data)
{
    m_birthday = data;
}

void ContactData::setBirthday(const QString &data)
{
    m_birthday = string2Date(data);
}

int ContactData::appendAddress(const Address &data)
{
    if(m_addresses.size() > 0 && m_addresses.at(0).isEmpty())
        m_addresses.remove(0);
    m_addresses.append(data);
    return m_addresses.size() - 1;
}

int ContactData::appendAddress(const QString &country, const QString &city,
                            const QString &street, const QString &home,
                            const QString &apartment)
{
    Address data;
    data.country = country;
    data.city = city;
    data.street = street;
    data.home = home;
    data.apartment = apartment;
    return appendAddress(data);
}

int ContactData::appendCompany(const Company &data)
{
    if(m_companies.at(0).isEmpty())
        m_companies.remove(0);
    m_companies.append(data);
    return m_companies.size() - 1;
}

int ContactData::appendCompany(const QString &name, const QString &department,
                                    const QString &post, const QString &address,
                                    const QString &phone, const QString &dateIn,
                                    const QString &dateOut)
{
    Company data;
    data.name = name;
    data.department = department;
    data.post = post;
    data.address = address;
    data.phone = phone;
    data.dateIn = string2Date(dateIn);
    data.dateOut = string2Date(dateOut);
    return appendCompany(data);

}

void ContactData::setPathToUserPic(const QString &data)
{
    m_pathToUserPic = data;
}

void ContactData::setUserPic(const QPixmap &data)
{
    m_userPic = data;
}

void ContactData::setComment(const QString &data)
{
    m_comment = data;
}

void ContactData::setCountry(const int index, const QString &data)
{
    Address temp = m_addresses.at(index);
    temp.country = data;
    m_addresses.replace(index, temp);
}

void ContactData::setCity(const int index, const QString &data)
{
    Address temp = m_addresses.at(index);
    temp.city = data;
    m_addresses.replace(index, temp);
}

void ContactData::setStreet(const int index, const QString &data)
{
    Address temp = m_addresses.at(index);
    temp.street = data;
    m_addresses.replace(index, temp);
}

void ContactData::setHome(const int index, const QString &data)
{
    Address temp = m_addresses.at(index);
    temp.home = data;
    m_addresses.replace(index, temp);
}

void ContactData::setApartment(const int index, const QString &data)
{
    Address temp = m_addresses.at(index);
    temp.apartment = data;
    m_addresses.replace(index, temp);
}

void ContactData::setCompanyName(const int index, const QString &data)
{
    Company temp = m_companies.at(index);
    temp.name = data;
    m_companies.replace(index, temp);
}

void ContactData::setDepartment(const int index, const QString &data)
{
    Company temp = m_companies.at(index);
    temp.department = data;
    m_companies.replace(index, temp);
}

void ContactData::setPost(const int index, const QString &data)
{
    Company temp = m_companies.at(index);
    temp.post = data;
    m_companies.replace(index, temp);
}

void ContactData::setCompanyAddress(const int index, const QString &data)
{
    Company temp = m_companies.at(index);
    temp.address = data;
    m_companies.replace(index, temp);
}

void ContactData::setCompanyPhone(const int index, const QString &data)
{
    Company temp = m_companies.at(index);
    temp.phone = data;
    m_companies.replace(index, temp);
}

void ContactData::setDateIn(const int index, const QDate &data)
{
    Company temp = m_companies.at(index);
    temp.dateIn = data;
    m_companies.replace(index, temp);
}

void ContactData::setDateIn(const int index, const QString &data)
{
    Company temp = m_companies.at(index);
    temp.dateIn = string2Date(data);
    m_companies.replace(index, temp);
}

void ContactData::setDateOut(const int index, const QDate &data)
{
    Company temp = m_companies.at(index);
    temp.dateOut = data;
    m_companies.replace(index, temp);
}

void ContactData::setDateOut(const int index, const QString &data)
{
    Company temp = m_companies.at(index);
    temp.dateOut = string2Date(data);
    m_companies.replace(index, temp);
}

void ContactData::setPhone(const QString &type, const QString &value)
{
    if(m_phones.contains(Value::Phone))
        m_phones.remove(Value::Phone);
    m_phones.insert(type,value);
}

void ContactData::setEmail(const QString &type, const QString &value)
{
    if(m_emails.contains(Value::Email))
        m_emails.remove(Value::Email);
    m_emails.insert(type,value);
}

void ContactData::setSkype(const QString &type, const QString &value)
{
    if(m_skypes.contains(Value::Skype))
        m_skypes.remove(Value::Skype);
    m_skypes.insert(type,value);
}

void ContactData::setSite(const QString &type, const QString &value)
{
    if(m_sites.contains(Value::Site))
        m_sites.remove(Value::Site);
    m_sites.insert(type,value);
}
}
