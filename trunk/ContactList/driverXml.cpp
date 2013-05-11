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
#define ERR_INCORRECT QObject::trUtf8("This file has not correct format!")
#define ERR_CANNOT_OPEN QObject::trUtf8("Can not open this file for read or this file has not a text format!")

#define ERROR_MESSAGE_INCORRECT QMessageBox::warning(this, ERROR, ERR_INCORRECT)
#define ERROR_MESSAGE_CANNOT_OPEN QMessageBox::warning(this, ERROR, ERR_CANNOT_OPEN)

QDate string2Data(QString data) {
    if(data.isEmpty())
        return DEFAULT_DATE;
    return QDate::fromString(data,DEFAULT_DATE_FORMAT);
}

QString data2String(QDate data) {
    return data.toString(DEFAULT_DATE_FORMAT);
}
}

DriverXml::DriverXml(QWidget *parent) :
    QWidget(parent),
    m_path(new QString()),
    m_contacts(new Data::Contacts)
{
}

bool DriverXml::saveData(const Data::Contacts &data, const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ERROR_MESSAGE_CANNOT_OPEN;
        close();
        return false;
    }

    QDomDocument doc;
    QDomElement root = doc.createElement(Tag::Tree);
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

    m_contacts->clear();
    QDomNode recordNode = rootElement.firstChild();
     // Read every tag in tree
    while(!recordNode.isNull()) {
        QDomElement recordElement = recordNode.toElement();
        if(!recordElement.isNull()) {
            Data::ContactData *currentContact = new Data::ContactData();
            // Read every contact data
            xmlToContactData(recordElement,*currentContact);
            m_contacts->append(currentContact);
        }
        recordNode = recordNode.nextSibling();
    }
    return m_contacts;
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

    Data::ContactData *currentContact = new Data::ContactData;
    xmlToContactData(recordElement,*currentContact);

    return currentContact;
}

void DriverXml::xmlToContactData(const QDomElement &recordElement, Data::ContactData &currentContact)
{
    QDomNode fieldNode = recordElement.firstChild();
    while(!fieldNode.isNull()) {
        QDomElement fieldElement = fieldNode.toElement();
        if(!fieldElement.isNull()) {
            if(fieldElement.tagName() == Tag::Data) {
                currentContact.setAlias(fieldElement.attribute(Attribute::Alias));
                currentContact.setName(fieldElement.attribute(Attribute::Name));
                currentContact.setSurName(fieldElement.attribute(Attribute::SurName));
                currentContact.setOtherName(fieldElement.attribute(Attribute::OtherName));
                currentContact.setBirthday(fieldElement.attribute(Attribute::Birthday));
                currentContact.setPathToUserPic(fieldElement.attribute(Attribute::PathToUserPic));
                currentContact.setComment(fieldElement.attribute(Attribute::Comment));
            }
            else if(fieldElement.tagName() == Tag::Addresses) {
                QDomNode dataNode = fieldElement.firstChild();
                // Read all address in contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();
                    currentContact.appendAddress(dataElement.attribute(Attribute::Country),
                                              dataElement.attribute(Attribute::City),
                                              dataElement.attribute(Attribute::Street),
                                              dataElement.attribute(Attribute::Home),
                                              dataElement.attribute(Attribute::Apartment));
                    dataNode = dataNode.nextSibling();
                }
            }
            else if(fieldElement.tagName() == Tag::Channels) {
                QDomNode dataNode = fieldElement.firstChild();
                // Read all communications from the contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();

                    QString type = dataElement.attribute(Attribute::Type);
                    if(type == Value::Phone)
                        currentContact.setPhone(dataElement.attribute(Attribute::Subtype),
                                                dataElement.attribute(Attribute::Value));
                    else if(type == Value::Email)
                        currentContact.setEmail(dataElement.attribute(Attribute::Subtype),
                                                dataElement.attribute(Attribute::Value));
                    else if(type == Value::Skype)
                        currentContact.setSkype(dataElement.attribute(Attribute::Subtype),
                                                dataElement.attribute(Attribute::Value));
                    else if(type == Value::Site)
                        currentContact.setSite(dataElement.attribute(Attribute::Subtype),
                                                dataElement.attribute(Attribute::Value));
                    dataNode = dataNode.nextSibling();
                }
            }
            else if(fieldElement.tagName() == Tag::Organizations) {
                QDomNode dataNode = fieldElement.firstChild();
                // Read every organization when working this contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();
                    currentContact.appendCompany(dataElement.attribute(Attribute::Name),
                                                 dataElement.attribute(Attribute::Department),
                                                 dataElement.attribute(Attribute::Post),
                                                 dataElement.attribute(Attribute::Address),
                                                 dataElement.attribute(Attribute::Phone),
                                                 dataElement.attribute(Attribute::DateIn),
                                                 dataElement.attribute(Attribute::DateOut));
                    dataNode = dataNode.nextSibling();
                }
            }
        }
        fieldNode = fieldNode.nextSibling();
    }
}

void DriverXml::contactDataToXml(QDomElement &record, const Data::ContactData &data)
{
    QDomElement field = record.firstChildElement(Tag::Data);
    field.setAttribute(Attribute::Alias,data.alias());
    field.setAttribute(Attribute::Name,data.name());
    field.setAttribute(Attribute::SurName,data.surName());
    field.setAttribute(Attribute::OtherName,data.otherName());
    field.setAttribute(Attribute::Birthday,data.birthdayAsString());
    field.setAttribute(Attribute::PathToUserPic,data.pathToUserPic());
    field.setAttribute(Attribute::Comment,data.comment());

    int countAddresses = data.countAddresses();
    QDomElement address = record.firstChildElement(Tag::Addresses).firstChildElement(Tag::Data);
    for(int addressId = 0; addressId < countAddresses; ++addressId) {
        address.setAttribute(Attribute::Country,data.country(addressId));
        address.setAttribute(Attribute::City,data.city(addressId));
        address.setAttribute(Attribute::Street,data.street(addressId));
        address.setAttribute(Attribute::Home,data.home(addressId));
        address.setAttribute(Attribute::Apartment,data.apartment(addressId));
        address = address.nextSiblingElement(Tag::Data);
    }

    QDomElement communication = record.firstChildElement(Tag::Channels).firstChildElement(Tag::Data);

    QList<QString> phones = data.phones();
    QList<QString> phoneTypes = data.phoneTypes();
    for(int id = 0; id < data.countPhones(); ++id) {
        communication.setAttribute(Attribute::Type,Value::Phone);
        communication.setAttribute(Attribute::Subtype,phoneTypes.at(id));
        communication.setAttribute(Attribute::Value,phones.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }
    QList<QString> emails = data.emails();
    QList<QString> emailTypes = data.emailTypes();
    for(int id = 0; id < data.countEmails(); ++id) {
        communication.setAttribute(Attribute::Type,Value::Email);
        communication.setAttribute(Attribute::Subtype,emailTypes.at(id));
        communication.setAttribute(Attribute::Value,emails.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }
    QList<QString> skypes = data.skypes();
    QList<QString> skypeTypes = data.skypeTypes();
    for(int id = 0; id < data.countSkypes(); ++id) {
        communication.setAttribute(Attribute::Type,Value::Skype);
        communication.setAttribute(Attribute::Subtype,skypeTypes.at(id));
        communication.setAttribute(Attribute::Value,skypes.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }
    QList<QString> sites = data.sites();
    QList<QString> siteTypes = data.siteTypes();
    for(int id = 0; id < data.countSites(); ++id) {
        communication.setAttribute(Attribute::Type,Value::Site);
        communication.setAttribute(Attribute::Subtype,siteTypes.at(id));
        communication.setAttribute(Attribute::Value,sites.at(id));
        communication = communication.nextSiblingElement(Tag::Data);
    }

    int countCompanies = data.countCompanies();
    QDomElement company = record.firstChildElement(Tag::Organizations).firstChildElement(Tag::Data);
    for(int companiesId = 0; companiesId < countCompanies; ++companiesId) {
        company.setAttribute(Attribute::Name,data.companyName(companiesId));
        company.setAttribute(Attribute::Department,data.department(companiesId));
        company.setAttribute(Attribute::Post,data.post(companiesId));
        company.setAttribute(Attribute::Address,data.companyAddress(companiesId));
        company.setAttribute(Attribute::Phone,data.companyPhone(companiesId));
        company.setAttribute(Attribute::DateIn,data.dateInAsString(companiesId));
        company.setAttribute(Attribute::DateOut,data.dateOutAsString(companiesId));
        company = company.nextSiblingElement(Tag::Data);
    }
}
