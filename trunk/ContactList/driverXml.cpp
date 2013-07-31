#include <QApplication>
#include "driverXml.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDomDocument>

namespace {
namespace Tag {
const QString Tree("tree");
const QString Record("record");
const QString Data("data");
const QString DataType("dataType");
const QString Addresses("addresses");
const QString Channels("channels");
const QString Organizations("organizations");
}

#define ERROR QObject::trUtf8("Error")
#define ERR_INCORRECT QObject::trUtf8("This file has incorrect format!")
#define ERR_INCORRECT_VERSION QObject::trUtf8("This file has incorrect version!")
#define ERR_CANNOT_OPEN QObject::trUtf8("Can not open this file for read or this file has not a text format!")

#define ERROR_MESSAGE_INCORRECT QMessageBox::warning(new QWidget(), ERROR, ERR_INCORRECT)
#define ERROR_MESSAGE_INCORRECT_VERSION QMessageBox::warning(new QWidget(), ERROR, ERR_INCORRECT_VERSION)
#define ERROR_MESSAGE_CANNOT_OPEN QMessageBox::warning(new QWidget(), ERROR, ERR_CANNOT_OPEN)

QDate string2Data(QString data) {
    if(data.isEmpty())
        return DEFAULT_DATE;
    return QDate::fromString(data,DEFAULT_DATE_FORMAT);
}

QString data2String(QDate data) {
    return data.toString(DEFAULT_DATE_FORMAT);
}

const QString CONTACT("contact");
const QString COMPANY("company");
const QString ADDRESS("address");
enum { ALIAS = 0, NAME, SURNAME, OTHERNAME, BIRTHDAY, USER_PIC, COMMENT };
enum { COMP_NAME = 0, PHONE, DEPARTMENT, POST, COMP_ADDRESS, DATEIN, DATEOUT };
enum { COUNTRY = 0, CITY, STREET, HOME, APARTMENT };
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
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ERROR_MESSAGE_CANNOT_OPEN;
        return false;
    }

    QDomDocument doc;
    QDomElement root = doc.createElement(Tag::Tree);
    root.setAttribute(Attribute::Version,qApp->applicationVersion());
    doc.appendChild(root);
    for(int i=0; i<data.size(); ++i) {
        QDomElement record = doc.createElement(Tag::Record);
        QDomElement field = doc.createElement(Tag::Data);
        QDomElement addresses = doc.createElement(Tag::Addresses);
        QDomElement communications = doc.createElement(Tag::Channels);
        QDomElement companies = doc.createElement(Tag::Organizations);

        root.appendChild(record);
        record.appendChild(field);
        record.appendChild(addresses);
        record.appendChild(communications);
        record.appendChild(companies);
        int countAddr = data.at(i)->countAddresses();
        for(int id = 0; id < countAddr; ++id) {
            QDomElement address = doc.createElement(Tag::Data);
            addresses.appendChild(address);
        }

        int countCommun = data.at(i)->countChannels();
        for(int id = 0; id < countCommun; ++id) {
            QDomElement communication = doc.createElement(Tag::Data);
            communications.appendChild(communication);
        }

        int countComp = data.at(i)->countCompanies();
        for(int id = 0; id < countComp; ++id) {
            QDomElement company = doc.createElement(Tag::Data);
            companies.appendChild(company);
        }
        contactDataToXml(record,*data.at(i));
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
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ERROR_MESSAGE_CANNOT_OPEN;
        return 0;
    }
    if (!doc->setContent(&file)) {
        ERROR_MESSAGE_INCORRECT;
        return 0;
    }
    file.close();

    QDomElement rootElement = doc->documentElement();
    if (rootElement.nodeName() != Tag::Tree) {
        ERROR_MESSAGE_INCORRECT;
        return 0;
    }
    if(rootElement.attribute(Attribute::Version) != qApp->applicationVersion()) {
        ERROR_MESSAGE_INCORRECT_VERSION;
        return 0;
    }

    Data::Contacts *contacts = new Data::Contacts();
    QDomNode recordNode = rootElement.firstChild();
     // Read every tag in tree
    while(!recordNode.isNull()) {
        QDomElement recordElement = recordNode.toElement();
        if(!recordElement.isNull()) {
            Data::ContactData *currentContact = new Data::ContactData();
            // Read every contact data
            xmlToContactData(recordElement,*currentContact);
            contacts->append(currentContact);
        }
        recordNode = recordNode.nextSibling();
    }
    return contacts;
}

bool DriverXml::saveContact(const Data::ContactData &data, const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ERROR_MESSAGE_CANNOT_OPEN;
        return false;
    }

    QDomDocument doc;
    QDomElement record = doc.createElement(Tag::Record);
    record.setAttribute(Attribute::Version,qApp->applicationVersion());
    QDomElement field = doc.createElement(Tag::Data);
    QDomElement addresses = doc.createElement(Tag::Addresses);
    QDomElement communications = doc.createElement(Tag::Channels);
    QDomElement companies = doc.createElement(Tag::Organizations);

    doc.appendChild(record);
    record.appendChild(field);
    record.appendChild(addresses);
    record.appendChild(communications);
    record.appendChild(companies);
    int countAddr = data.countAddresses();
    for(int id = 0; id < countAddr; ++id) {
        QDomElement address = doc.createElement(Tag::Data);
        addresses.appendChild(address);
    }

    for(int id = 0; id < data.countChannels(); ++id) {
        QDomElement communication = doc.createElement(Tag::Data);
        communications.appendChild(communication);
    }

    int countComp = data.countCompanies();
    for(int id = 0; id < countComp; ++id) {
        QDomElement company = doc.createElement(Tag::Data);
        companies.appendChild(company);
    }
    contactDataToXml(record,data);

    QTextStream out(&file);

    doc.save(out,0);
    file.close();
    return true;
}

Data::ContactData *DriverXml::loadContact(const QString &path)
{
    QDomDocument *doc = new QDomDocument();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ERROR_MESSAGE_CANNOT_OPEN;
        return 0;
    }
    if (!doc->setContent(&file)) {
        ERROR_MESSAGE_INCORRECT;
        return 0;
    }
    file.close();

    QDomElement recordElement = doc->documentElement();
    if (recordElement.nodeName() != Tag::Record) {
        ERROR_MESSAGE_INCORRECT;
        return 0;
    }
    if(recordElement.attribute(Attribute::Version) != qApp->applicationVersion()) {
        ERROR_MESSAGE_INCORRECT_VERSION;
        return 0;
    }

    Data::ContactData *currentContact = new Data::ContactData;
    xmlToContactData(recordElement,*currentContact);

    return currentContact;
}

void DriverXml::xmlToContactData(const QDomElement &record, Data::ContactData &data) const
{
    QDomNode fieldNode = record.firstChild();
    while(!fieldNode.isNull()) {
        QDomElement fieldElement = fieldNode.toElement();
        if(!fieldElement.isNull()) {
            if(fieldElement.tagName() == Tag::Data)
            {
                QStringList list;
                list << fieldElement.attribute(Attribute::Alias)
                     << fieldElement.attribute(Attribute::Name)
                     << fieldElement.attribute(Attribute::SurName)
                     << fieldElement.attribute(Attribute::OtherName)
                     << fieldElement.attribute(Attribute::Birthday)
                     << fieldElement.attribute(Attribute::PathToUserPic)
                     << fieldElement.attribute(Attribute::Comment);
                data.setMainData(list);
            }
            else if(fieldElement.tagName() == Tag::Addresses)
            {
                QDomNode dataNode = fieldElement.firstChild();
                // Read all address in contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();
                    QStringList list;
                    list << dataElement.attribute(Address::Country)
                         << dataElement.attribute(Address::City)
                         << dataElement.attribute(Address::Street)
                         << dataElement.attribute(Address::Home)
                         << dataElement.attribute(Address::Apartment);
                    data.appendAddress(list);
                    dataNode = dataNode.nextSibling();
                }
            }
            else if(fieldElement.tagName() == Tag::Channels)
            {
                QDomNode dataNode = fieldElement.firstChild();
                // Read all communications from the contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();

                    QString type = dataElement.attribute(Attribute::Type);

                    data.setChannel(type, dataElement.attribute(Attribute::Subtype),
                                    dataElement.attribute(Attribute::Value));
                    dataNode = dataNode.nextSibling();
                }
            }
            else if(fieldElement.tagName() == Tag::Organizations) {
                QDomNode dataNode = fieldElement.firstChild();
                // Read every organization when working this contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();
                    QStringList list;
                    list << dataElement.attribute(Attribute::Name)
                         << dataElement.attribute(Attribute::Department)
                         << dataElement.attribute(Attribute::Post)
                         << dataElement.attribute(Attribute::Address)
                         << dataElement.attribute(Attribute::Phone)
                         << dataElement.attribute(Attribute::DateIn)
                         << dataElement.attribute(Attribute::DateOut);
                    data.appendCompany(list);
                    dataNode = dataNode.nextSibling();
                }
            }
        }
        fieldNode = fieldNode.nextSibling();
    }
}

void DriverXml::contactDataToXml(QDomElement &record, const Data::ContactData &data) const
{
    QDomElement field = record.firstChildElement(Tag::Data);
    field.setAttribute(Attribute::Alias, data.data(CONTACT).at(ALIAS));
    field.setAttribute(Attribute::Name, data.data(CONTACT).at(NAME));
    field.setAttribute(Attribute::SurName, data.data(CONTACT).at(SURNAME));
    field.setAttribute(Attribute::OtherName, data.data(CONTACT).at(OTHERNAME));
    field.setAttribute(Attribute::Birthday, data.data(CONTACT).at(BIRTHDAY));
    field.setAttribute(Attribute::PathToUserPic, data.data(CONTACT).at(USER_PIC));
    field.setAttribute(Attribute::Comment, data.data(CONTACT).at(COMMENT));

    int countAddresses = data.countAddresses();
    QDomElement address = record.firstChildElement(Tag::Addresses).firstChildElement(Tag::Data);
    for(int addressId = 0; addressId < countAddresses; ++addressId) {
        address.setAttribute(Address::Country,data.data(ADDRESS, addressId).at(COUNTRY));
        address.setAttribute(Address::City,data.data(ADDRESS, addressId).at(CITY));
        address.setAttribute(Address::Street,data.data(ADDRESS, addressId).at(STREET));
        address.setAttribute(Address::Home,data.data(ADDRESS, addressId).at(HOME));
        address.setAttribute(Address::Apartment,data.data(ADDRESS, addressId).at(APARTMENT));
        address = address.nextSiblingElement(Tag::Data);
    }

    QDomElement communication = record.firstChildElement(Tag::Channels).firstChildElement(Tag::Data);

    QList<QString> phones = data.channels(Channel::Phone);
    QList<QString> phoneTypes = data.channelsTypes(Channel::Phone);
    for(int id = 0; id < data.countChannels(Channel::Phone); ++id)
    {
        communication.setAttribute(Attribute::Type, Channel::Phone);
        communication.setAttribute(Attribute::Subtype, phoneTypes.at(id));
        communication.setAttribute(Attribute::Value, phones.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }
    QList<QString> emails = data.channels(Channel::Email);
    QList<QString> emailTypes = data.channelsTypes(Channel::Email);
    for(int id = 0; id < data.countChannels(Channel::Email); ++id)
    {
        communication.setAttribute(Attribute::Type, Channel::Email);
        communication.setAttribute(Attribute::Subtype, emailTypes.at(id));
        communication.setAttribute(Attribute::Value, emails.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }
    QList<QString> skypes = data.channels(Channel::Skype);
    QList<QString> skypeTypes = data.channelsTypes(Channel::Skype);
    for(int id = 0; id < data.countChannels(Channel::Skype); ++id)
    {
        communication.setAttribute(Attribute::Type, Channel::Skype);
        communication.setAttribute(Attribute::Subtype, skypeTypes.at(id));
        communication.setAttribute(Attribute::Value, skypes.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }
    QList<QString> sites = data.channels(Channel::Site);
    QList<QString> siteTypes = data.channelsTypes(Channel::Site);
    for(int id = 0; id < data.countChannels(Channel::Site); ++id)
    {
        communication.setAttribute(Attribute::Type, Channel::Site);
        communication.setAttribute(Attribute::Subtype, siteTypes.at(id));
        communication.setAttribute(Attribute::Value, sites.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }

    int countCompanies = data.countCompanies();
    QDomElement company = record.firstChildElement(Tag::Organizations).firstChildElement(Tag::Data);
    for(int corpId = 0; corpId < countCompanies; ++corpId)
    {
        company.setAttribute(Attribute::Name, data.data(COMPANY, corpId).at(COMP_NAME));
        company.setAttribute(Attribute::Department, data.data(COMPANY, corpId).at(DEPARTMENT));
        company.setAttribute(Attribute::Post, data.data(COMPANY, corpId).at(POST));
        company.setAttribute(Attribute::Address, data.data(COMPANY, corpId).at(COMP_ADDRESS));
        company.setAttribute(Attribute::Phone, data.data(COMPANY, corpId).at(PHONE));
        company.setAttribute(Attribute::DateIn, data.data(COMPANY, corpId).at(DATEIN));
        company.setAttribute(Attribute::DateOut, data.data(COMPANY, corpId).at(DATEOUT));
        company = company.nextSiblingElement(Tag::Data);
    }
}
