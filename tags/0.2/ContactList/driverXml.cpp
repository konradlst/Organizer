#include <QApplication>
#include "driverXml.h"
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include "cgErrorMessage.h"

namespace Tag
{
const QString Tree("tree");
const QString Record("record");
const QString Data("data");
const QString DataType("dataType");
const QString Addresses("addresses");
const QString Channels("channels");
const QString Organizations("organizations");
}

namespace
{
QDate string2Data(QString data)
{
    if(data.isEmpty())
        return DEFAULT_DATE;
    return QDate::fromString(data, DEFAULT_DATE_FORMAT);
}

QString data2String(QDate data)
{
    return data.toString(DEFAULT_DATE_FORMAT);
}
}

DriverXml::DriverXml()
{
}

DriverXml::~DriverXml()
{
}

bool DriverXml::saveData(const Data::Contacts &data, const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        ERROR_CANNOT_OPEN;
        return false;
    }

    QDomDocument doc;
    QDomElement root = doc.createElement(Tag::Tree);
    root.setAttribute(Attribute::Version, qApp->applicationVersion());
    doc.appendChild(root);
    for (int i=0; i < data.size(); ++i)
    {
        QDomElement record = doc.createElement(Tag::Record);
        QDomElement field = doc.createElement(Tag::Data);
        QDomElement addresses = doc.createElement(Tag::Addresses);
        QDomElement channels = doc.createElement(Tag::Channels);
        QDomElement companies = doc.createElement(Tag::Organizations);

        root.appendChild(record);
        record.appendChild(field);
        record.appendChild(addresses);
        record.appendChild(channels);
        record.appendChild(companies);
        int countAddr = data.at(i)->countData(ADDRESS);
        for (int id = 0; id < countAddr; ++id)
        {
            QDomElement address = doc.createElement(Tag::Data);
            addresses.appendChild(address);
        }

        for (int id = 0; id < data.at(i)->countData(Channel::All); ++id)
        {
            QDomElement channel = doc.createElement(Tag::Data);
            channels.appendChild(channel);
        }

        int countComp = data.at(i)->countData(COMPANY);
        for (int id = 0; id < countComp; ++id)
        {
            QDomElement company = doc.createElement(Tag::Data);
            companies.appendChild(company);
        }
        contactDataToXml(record, *data.at(i));
    }

    QTextStream out(&file);

    doc.save(out,0);
    file.close();
    return true;
}

Data::Contacts *DriverXml::loadData(const QString &path)
{
    QDomDocument *doc = new QDomDocument();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ERROR_CANNOT_OPEN;
        return 0;
    }
    if (!doc->setContent(&file))
    {
        ERROR_INCORRECT_FORMAT;
        return 0;
    }
    file.close();

    QDomElement rootElement = doc->documentElement();
    if (rootElement.nodeName() != Tag::Tree)
    {
        ERROR_INCORRECT_FORMAT;
        return 0;
    }
    if (rootElement.attribute(Attribute::Version) != qApp->applicationVersion())
    {
        ERROR_INCORRECT_VERSION;
        return 0;
    }

    Data::Contacts *contacts = new Data::Contacts();
    QDomNode recordNode = rootElement.firstChild();
    while(!recordNode.isNull())
    {
        QDomElement recordElement = recordNode.toElement();
        if(!recordElement.isNull())
        {
            ContactData *currentContact = new ContactData();
            xmlToContactData(recordElement, *currentContact);
            contacts->append(currentContact);
        }
        recordNode = recordNode.nextSibling();
    }
    return contacts;
}

bool DriverXml::saveContact(const ContactData &data, const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        ERROR_CANNOT_OPEN;
        return false;
    }

    QDomDocument doc;
    QDomElement record = doc.createElement(Tag::Record);
    record.setAttribute(Attribute::Version, qApp->applicationVersion());
    QDomElement field = doc.createElement(Tag::Data);
    QDomElement addresses = doc.createElement(Tag::Addresses);
    QDomElement channels = doc.createElement(Tag::Channels);
    QDomElement companies = doc.createElement(Tag::Organizations);

    doc.appendChild(record);
    record.appendChild(field);
    record.appendChild(addresses);
    record.appendChild(channels);
    record.appendChild(companies);
    int countAddr = data.countData(ADDRESS);
    for (int id = 0; id < countAddr; ++id)
    {
        QDomElement address = doc.createElement(Tag::Data);
        addresses.appendChild(address);
    }

    for (int id = 0; id < data.countData(Channel::All); ++id)
    {
        QDomElement channel = doc.createElement(Tag::Data);
        channels.appendChild(channel);
    }

    int countComp = data.countData(COMPANY);
    for (int id = 0; id < countComp; ++id)
    {
        QDomElement company = doc.createElement(Tag::Data);
        companies.appendChild(company);
    }
    contactDataToXml(record,data);

    QTextStream out(&file);
    doc.save(out,0);
    file.close();
    return true;
}

ContactData *DriverXml::loadContact(const QString &path)
{
    QDomDocument *doc = new QDomDocument();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ERROR_CANNOT_OPEN;
        return 0;
    }
    if (!doc->setContent(&file))
    {
        ERROR_INCORRECT_FORMAT;
        return 0;
    }
    file.close();

    QDomElement recordElement = doc->documentElement();
    if (recordElement.nodeName() != Tag::Record)
    {
        ERROR_INCORRECT_FORMAT;
        return 0;
    }
    if (recordElement.attribute(Attribute::Version) != qApp->applicationVersion())
    {
        ERROR_INCORRECT_VERSION;
        return 0;
    }

    ContactData *currentContact = new ContactData;
    xmlToContactData(recordElement, *currentContact);

    return currentContact;
}

void DriverXml::xmlToContactData(const QDomElement &record, ContactData &data) const
{
    QDomNode fieldNode = record.firstChild();
    while (!fieldNode.isNull())
    {
        QDomElement fieldElement = fieldNode.toElement();
        if (fieldElement.isNull())
            fieldNode = fieldNode.nextSibling();

        if (fieldElement.tagName() == Tag::Data)
        {
            QStringList list;
            list << fieldElement.attribute(Attribute::Alias)
                 << fieldElement.attribute(Attribute::Name)
                 << fieldElement.attribute(Attribute::LastName)
                 << fieldElement.attribute(Attribute::OtherName)
                 << fieldElement.attribute(Attribute::Birthday)
                 << fieldElement.attribute(Attribute::PathToUserPic)
                 << fieldElement.attribute(Attribute::Comment);
            data.setMainData(list);
        }
        else if (fieldElement.tagName() == Tag::Addresses)
        {
            QDomNode dataNode = fieldElement.firstChild();
            while (!dataNode.isNull())
            {
                QDomElement dataElement = dataNode.toElement();
                QStringList list;
                list << dataElement.attribute(Address::Country)
                     << dataElement.attribute(Address::City)
                     << dataElement.attribute(Address::Street)
                     << dataElement.attribute(Address::Home)
                     << dataElement.attribute(Address::Apartment);
                data.setAddressData(list, data.countData(ADDRESS));
                dataNode = dataNode.nextSibling();
            }
        }
        else if (fieldElement.tagName() == Tag::Channels)
        {
            QDomNode dataNode = fieldElement.firstChild();
            while(!dataNode.isNull())
            {
                QDomElement dataElement = dataNode.toElement();

                QString type = dataElement.attribute(Attribute::Type);

                data.setChannel(type, dataElement.attribute(Attribute::Subtype),
                                dataElement.attribute(Attribute::Value));
                dataNode = dataNode.nextSibling();
            }
        }
        else if (fieldElement.tagName() == Tag::Organizations)
        {
            QDomNode dataNode = fieldElement.firstChild();
            while (!dataNode.isNull())
            {
                QDomElement dataElement = dataNode.toElement();
                QStringList list;
                list << dataElement.attribute(Attribute::Name)
                     << dataElement.attribute(Attribute::Department)
                     << dataElement.attribute(Attribute::Post)
                     << dataElement.attribute(Attribute::Address)
                     << dataElement.attribute(Attribute::Phone)
                     << dataElement.attribute(Attribute::DateIn)
                     << dataElement.attribute(Attribute::DateOut);
                data.setCompanyData(list, data.countData(COMPANY));
                dataNode = dataNode.nextSibling();
            }
        }
        fieldNode = fieldNode.nextSibling();
    }
}

void DriverXml::contactDataToXml(QDomElement &record, const ContactData &data) const
{
    QDomElement field = record.firstChildElement(Tag::Data);
    field.setAttribute(Attribute::Alias, data.data(CONTACT).at(ALIAS));
    field.setAttribute(Attribute::Name, data.data(CONTACT).at(NAME));
    field.setAttribute(Attribute::LastName, data.data(CONTACT).at(LASTNAME));
    field.setAttribute(Attribute::OtherName, data.data(CONTACT).at(OTHERNAME));
    field.setAttribute(Attribute::Birthday, data.data(CONTACT).at(BIRTHDAY));
    field.setAttribute(Attribute::PathToUserPic, data.data(CONTACT).at(USER_PIC));
    field.setAttribute(Attribute::Comment, data.data(CONTACT).at(COMMENT));

    QDomElement address = record.firstChildElement(Tag::Addresses).firstChildElement(Tag::Data);
    for (int id = 0; id < data.countData(ADDRESS); ++id)
    {
        address.setAttribute(Address::Country, data.data(ADDRESS, id).at(COUNTRY));
        address.setAttribute(Address::City,  data.data(ADDRESS, id).at(CITY));
        address.setAttribute(Address::Street,  data.data(ADDRESS, id).at(STREET));
        address.setAttribute(Address::Home, data.data(ADDRESS, id).at(HOME));
        address.setAttribute(Address::Apartment, data.data(ADDRESS, id).at(APARTMENT));
        address = address.nextSiblingElement(Tag::Data);
    }

    QDomElement channels = record.firstChildElement(Tag::Channels).firstChildElement(Tag::Data);

    QStringList phones = data.data(Channel::Phone);
    QStringList phoneTypes = data.data(Channel::PhoneType);
    for (int id = 0; id < data.countData(Channel::Phone); ++id)
    {
        channels.setAttribute(Attribute::Type, Channel::Phone);
        channels.setAttribute(Attribute::Subtype, phoneTypes.at(id));
        channels.setAttribute(Attribute::Value, phones.at(id));
        channels = channels.nextSiblingElement(Tag::Data);
    }
    QStringList emails = data.data(Channel::Email);
    QStringList emailTypes = data.data(Channel::EmailType);
    for (int id = 0; id < data.countData(Channel::Email); ++id)
    {
        channels.setAttribute(Attribute::Type, Channel::Email);
        channels.setAttribute(Attribute::Subtype, emailTypes.at(id));
        channels.setAttribute(Attribute::Value, emails.at(id));
        channels = channels.nextSiblingElement(Tag::Data);
    }
    QStringList skypes = data.data(Channel::Skype);
    QStringList skypeTypes = data.data(Channel::SkypeType);
    for (int id = 0; id < data.countData(Channel::Skype); ++id)
    {
        channels.setAttribute(Attribute::Type, Channel::Skype);
        channels.setAttribute(Attribute::Subtype, skypeTypes.at(id));
        channels.setAttribute(Attribute::Value, skypes.at(id));
        channels = channels.nextSiblingElement(Tag::Data);
    }
    QStringList sites = data.data(Channel::Site);
    QStringList siteTypes = data.channelsTypes(Channel::Site);
    for (int id = 0; id < data.countData(Channel::Site); ++id)
    {
        channels.setAttribute(Attribute::Type, Channel::Site);
        channels.setAttribute(Attribute::Subtype, siteTypes.at(id));
        channels.setAttribute(Attribute::Value, sites.at(id));
        channels = channels.nextSiblingElement(Tag::Data);
    }

    QDomElement companies = record.firstChildElement(Tag::Organizations);
    if (companies.isNull())
        return;

    QDomElement company = companies.firstChildElement(Tag::Data);
    for (int id = 0; id < data.countData(COMPANY); ++id)
    {
        company.setAttribute(Attribute::Name, data.data(COMPANY, id).at(COMP_NAME));
        company.setAttribute(Attribute::Department,
                             data.data(COMPANY, id).at(DEPARTMENT));
        company.setAttribute(Attribute::Post, data.data(COMPANY, id).at(POST));
        company.setAttribute(Attribute::Address,
                             data.data(COMPANY, id).at(COMP_ADDRESS));
        company.setAttribute(Attribute::Phone, data.data(COMPANY, id).at(PHONE));
        company.setAttribute(Attribute::DateIn, data.data(COMPANY, id).at(DATEIN));
        company.setAttribute(Attribute::DateOut, data.data(COMPANY, id).at(DATEOUT));
        company = company.nextSiblingElement(Tag::Data);
    }
}
