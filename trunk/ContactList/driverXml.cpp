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
const QString Communications("communications");
const QString Organizations("organizations");
}

namespace Attribute {
const QString Id("id");
const QString Alias("alias");
const QString Name("name");
const QString SurName("surName");
const QString OtherName("otherName");
const QString Birthday("birthday");
const QString Userpic("userpic");
const QString Comment("comment");
const QString Country("country");
const QString City("city");
const QString Street("street");
const QString Home("home");
const QString Apartment("apartment");
const QString Type("type");
const QString Subtype("subtype");
const QString Value("value");
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

#define ERROR QObject::trUtf8("Error")
#define ERR_INCORRECT QObject::trUtf8("This file has not correct format!")
#define ERR_CANNOT_OPEN QObject::trUtf8("Can not open this file for read or this file has not a text format!")

#define ERROR_MESSAGE_INCORRECT QMessageBox::warning(this, ERROR, ERR_INCORRECT)
#define ERROR_MESSAGE_CANNOT_OPEN QMessageBox::warning(this, ERROR, ERR_CANNOT_OPEN)
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
        QDomElement communications = doc.createElement(Tag::Communications);
        QDomElement companies = doc.createElement(Tag::Organizations);

        root.appendChild(record);
        record.appendChild(field);
        record.appendChild(addresses);
        record.appendChild(communications);
        record.appendChild(companies);
        int countAddr = data.value(i).m_addresses.size();
        for(int id = 0; id < countAddr; ++id) {
            QDomElement address = doc.createElement(Tag::Data);
            addresses.appendChild(address);
        }

        int countCommun = data.value(i).m_communications.size();
        for(int id = 0; id < countCommun; ++id) {
            QDomElement communication = doc.createElement(Tag::Data);
            communications.appendChild(communication);
        }

        int countComp = data.value(i).m_organizations.size();
        for(int id = 0; id < countComp; ++id) {
            QDomElement company = doc.createElement(Tag::Data);
            companies.appendChild(company);
        }

        contactDataToXml(record,data.value(i));
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
        close();
        return new Data::Contacts();
    }
    if (!doc->setContent(&file)) {
        ERROR_MESSAGE_INCORRECT;
        close();
        return new Data::Contacts();
    }
    file.close();

    QDomElement rootElement = doc->documentElement();
    QDomNode recordNode = rootElement.firstChild();
     // Read every tag in tree
    int RecordId = 0;
    while(!recordNode.isNull()) {
        QDomElement recordElement = recordNode.toElement();
        if(!recordElement.isNull()) {
            Data::ContactData currentContact;
            // Read every contact data
            xmlToContactData(recordElement,currentContact);
            m_contacts->insert(RecordId,currentContact);
            ++RecordId;
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
        close();
        return false;
    }

    QDomDocument doc;
    QDomElement record = doc.createElement(Tag::Record);
    QDomElement field = doc.createElement(Tag::Data);
    QDomElement addresses = doc.createElement(Tag::Addresses);
    QDomElement communications = doc.createElement(Tag::Communications);
    QDomElement companies = doc.createElement(Tag::Organizations);

    doc.appendChild(record);
    record.appendChild(field);
    record.appendChild(addresses);
    record.appendChild(communications);
    record.appendChild(companies);
    int countAddr = data.m_addresses.size();
    for(int id = 0; id < countAddr; ++id) {
        QDomElement address = doc.createElement(Tag::Data);
        addresses.appendChild(address);
    }

    int countCommun = data.m_communications.size();
    for(int id = 0; id < countCommun; ++id) {
        QDomElement communication = doc.createElement(Tag::Data);
        communications.appendChild(communication);
    }

    int countComp = data.m_organizations.size();
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
        close();
        return new Data::ContactData();
    }
    if (!doc->setContent(&file)) {
        ERROR_MESSAGE_INCORRECT;
        close();
        return new Data::ContactData();
    }
    file.close();

    QDomElement recordElement = doc->documentElement();
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
                currentContact.m_alias = fieldElement.attribute(Attribute::Alias);
                currentContact.m_name = fieldElement.attribute(Attribute::Name);
                currentContact.m_surName = fieldElement.attribute(Attribute::SurName);
                currentContact.m_otherName = fieldElement.attribute(Attribute::OtherName);
                currentContact.m_birthday = fieldElement.attribute(Attribute::Birthday);
                currentContact.m_pathToUserPic = fieldElement.attribute(Attribute::Userpic);
                currentContact.m_comment = fieldElement.attribute(Attribute::Comment);
            }
            else if(fieldElement.tagName() == Tag::Addresses) {
                QDomNode dataNode = fieldElement.firstChild();
                // Read all address in contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();
                    int addressID = dataElement.attribute(Attribute::Id).toInt();
                    Data::Address currentAddress;
                    currentAddress.country = dataElement.attribute(Attribute::Country);
                    currentAddress.city = dataElement.attribute(Attribute::City);
                    currentAddress.street = dataElement.attribute(Attribute::Street);
                    currentAddress.home = dataElement.attribute(Attribute::Home);
                    currentAddress.apartment = dataElement.attribute(Attribute::Apartment);

                    currentContact.m_addresses.insert(addressID,currentAddress);
                    dataNode = dataNode.nextSibling();
                }
            }
            else if(fieldElement.tagName() == Tag::Communications) {
                QDomNode dataNode = fieldElement.firstChild();
                // Read all communications from the contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();
                    int communicationId = dataElement.attribute(Attribute::Id).toInt();

                    Data::CommunicationData currentCommunicationData;
                    QString type = dataElement.attribute(Attribute::Type);
                    if(type == Value::Phone)
                        currentCommunicationData.first = Data::typePhone;
                    else if(type == Value::Email)
                        currentCommunicationData.first = Data::typeEmail;
                    else if(type == Value::Skype)
                        currentCommunicationData.first = Data::typeSkype;
                    else if(type == Value::Site)
                        currentCommunicationData.first = Data::typeSite;

                    Data::Communication currentCommunication;
                    currentCommunication.subType = dataElement.attribute(Attribute::Subtype);
                    currentCommunication.value = dataElement.attribute(Attribute::Value);
                    currentCommunicationData.second = currentCommunication;

                    currentContact.m_communications.insert(communicationId,currentCommunicationData);
                    dataNode = dataNode.nextSibling();
                }
            }
            else if(fieldElement.tagName() == Tag::Organizations) {
                QDomNode dataNode = fieldElement.firstChild();
                // Read every organization when working this contact
                while(!dataNode.isNull()) {
                    QDomElement dataElement = dataNode.toElement();
                    int companyID = dataElement.attribute(Attribute::Id).toInt();
                    Data::Organization currentCompany;
                    currentCompany.name = dataElement.attribute(Attribute::Name);
                    currentCompany.department = dataElement.attribute(Attribute::Department);
                    currentCompany.post = dataElement.attribute(Attribute::Post);
                    currentCompany.address = dataElement.attribute(Attribute::Address);
                    currentCompany.phone = dataElement.attribute(Attribute::Phone);
                    currentCompany.dateIn = dataElement.attribute(Attribute::DateIn);
                    currentCompany.dateOut = dataElement.attribute(Attribute::DateOut);

                    currentContact.m_organizations.insert(companyID,currentCompany);
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
    field.setAttribute(Attribute::Alias,data.m_alias);
    field.setAttribute(Attribute::Name,data.m_name);
    field.setAttribute(Attribute::SurName,data.m_surName);
    field.setAttribute(Attribute::OtherName,data.m_otherName);
    field.setAttribute(Attribute::Birthday,data.m_birthday);
    field.setAttribute(Attribute::Userpic,data.m_pathToUserPic);
    field.setAttribute(Attribute::Comment,data.m_comment);

    int countAddresses = data.m_addresses.size();
    QDomElement address = record.firstChildElement(Tag::Addresses).firstChildElement(Tag::Data);
    for(int addressId = 0; addressId < countAddresses; ++addressId) {
        Data::Address addressData = data.m_addresses.value(addressId);
        address.setAttribute(Attribute::Id,addressId);
        address.setAttribute(Attribute::Country,addressData.country);
        address.setAttribute(Attribute::City,addressData.city);
        address.setAttribute(Attribute::Street,addressData.street);
        address.setAttribute(Attribute::Home,addressData.home);
        address.setAttribute(Attribute::Apartment,addressData.apartment);
        address = address.nextSiblingElement(Tag::Data);
    }

    int countCommunications = data.m_communications.size();
    QDomElement communication = record.firstChildElement(Tag::Communications).firstChildElement(Tag::Data);
    for(int communicationsId = 0; communicationsId < countCommunications; ++communicationsId) {
        Data::CommunicationData communicationData = data.m_communications.value(communicationsId);
        communication.setAttribute(Attribute::Id,communicationsId);

        Data::typeCommunication type = communicationData.first;
        if(type == Data::typePhone)
            communication.setAttribute(Attribute::Type,Value::Phone);
        else if(type == Data::typeEmail)
            communication.setAttribute(Attribute::Type,Value::Email);
        else if(type == Data::typeSkype)
            communication.setAttribute(Attribute::Type,Value::Skype);
        else if(type == Data::typeSite)
            communication.setAttribute(Attribute::Type,Value::Site);

        communication.setAttribute(Attribute::Subtype,communicationData.second.subType);
        communication.setAttribute(Attribute::Value,communicationData.second.value);
        communication = communication.nextSiblingElement(Tag::Data);
    }

    int countCompanies = data.m_organizations.size();
    QDomElement company = record.firstChildElement(Tag::Organizations).firstChildElement(Tag::Data);
    for(int companiesId = 0; companiesId < countCompanies; ++companiesId) {
        Data::Organization companyData = data.m_organizations.value(companiesId);
        company.setAttribute(Attribute::Id,companiesId);
        company.setAttribute(Attribute::Name,companyData.name);
        company.setAttribute(Attribute::Department,companyData.department);
        company.setAttribute(Attribute::Post,companyData.post);
        company.setAttribute(Attribute::Address,companyData.address);
        company.setAttribute(Attribute::Phone,companyData.phone);
        company.setAttribute(Attribute::DateIn,companyData.dateIn);
        company.setAttribute(Attribute::DateOut,companyData.dateOut);
        company = company.nextSiblingElement(Tag::Data);
    }
}
