#include <QFile>
#include <QTextStream>
#include "contactListModel.h"
#include "driverXml.h"

ContactListModel::ContactListModel(ContactListController *controller, QWidget *parent) :
    QWidget(parent),
    m_controller(controller),
    m_driverXml(new DriverXml()),
    m_pathToCurrentData(new QString()),
    m_data(new Data::Contacts())
{
}

QStringList *ContactListModel::loadData(const QString &path)
{
    Data::Contacts *data = m_driverXml->loadData(path);
    if(data != 0) {
        *m_pathToCurrentData = path;
        *m_data = *data;
    }
    return contactList();
}

void ContactListModel::saveData(const QString &path)
{
    if(m_driverXml->saveData(*m_data, path))
        *m_pathToCurrentData = path;
}

QStringList *ContactListModel::contactList() const
{
    QStringList *data = new QStringList();
    for(int i=0; i<m_data->size(); ++i)
        data->append(m_data->at(i)->m_alias);
    return data;
}

QString *ContactListModel::pathToData() const
{
    return m_pathToCurrentData;
}

Data::ContactData *ContactListModel::contact(int index) const
{
    return m_data->at(index);
}

Data::ContactData *ContactListModel::newData() const
{
    m_data->clear();
    m_pathToCurrentData->clear();
    newContact();
    return m_data->at(0);
}

Data::ContactData *ContactListModel::newContact() const
{
    Data::ContactData *data = new Data::ContactData;
    data->m_alias = QString("New contact");
    data->m_birthday = DEFAULT_DATE;
    data->m_addresses.append(Data::Address());
    data->m_communications.append(Data::CommunicationData());

    Data::Organization company;
    company.dateIn = QDate::currentDate();
    company.dateOut = QDate::currentDate();
    data->m_organizations.append(company);
    m_data->append(data);
    return m_data->last();
}

Data::ContactData *ContactListModel::copyContact(const int index) const
{
    m_data->append(new Data::ContactData(*m_data->at(index)));
    return m_data->last();
}

void ContactListModel::deleteContact(const int index)
{
    if(m_data->size())
        m_data->remove(index);
}

Data::ContactData *ContactListModel::loadContact(const QString &path)
{
    Data::ContactData *data = m_driverXml->loadContact(path);
    if(data != 0) {
        m_data->append(data);
        return data;
    }
    return 0;
}

void ContactListModel::saveContact(const Data::ContactData &data, const QString &path)
{
    if(m_driverXml->saveContact(data, path))
        *m_pathToCurrentData = path;
}

void ContactListModel::dataChanged(const QString data, QString key, int contactId)
{
    Data::ContactData *contact = m_data->at(contactId);
    Data::Address address = contact->m_addresses.at(0);
    QVector<Data::CommunicationData> communications = contact->m_communications;
    Data::Organization organization = contact->m_organizations.at(0);

    if(key == Attribute::Alias)
        contact->m_alias = data;
    else if(key == Attribute::PathToUserPic)
        contact->m_pathToUserPic = data;
    else if(key == Attribute::Name)
        contact->m_name = data;
    else if(key == Attribute::SurName)
        contact->m_surName = data;
    else if(key == Attribute::OtherName)
        contact->m_otherName = data;
    else if(key == Attribute::Country)
        address.country = data;
    else if(key == Attribute::City)
        address.city = data;
    else if(key == Attribute::Street)
        address.street = data;
    else if(key == Attribute::Home)
        address.home = data;
    else if(key == Attribute::Apartment)
        address.apartment = data;
    else if(key == Attribute::NameOrganization)
        organization.name = data;
    else if(key == Attribute::PhoneOrganization)
        organization.phone = data;
    else if(key == Attribute::Department)
        organization.department = data;
    else if(key == Attribute::Post)
        organization.post = data;
    else if(key == Attribute::AddressOrganization)
        organization.address = data;

    Data::typeCommunication tempKey;
    if(key == Value::Email)
        tempKey = Data::typeEmail;
    else if(key == Value::Phone)
        tempKey = Data::typePhone;
    else if(key == Value::Skype)
        tempKey = Data::typeSkype;
    else if(key == Value::Site)
        tempKey = Data::typeSite;
    for(int i=0; i<communications.size();++i)
        if(communications.at(i).first == tempKey) {
            Data::CommunicationData com;
            com.first = tempKey;
            Data::Communication asd;
            asd.subType = QString();
            asd.value = data;
            com.second = asd;
            contact->m_communications.replace(i,com);
        }

    contact->m_addresses.replace(0,address);
    contact->m_organizations.replace(0,organization);
}

void ContactListModel::dataChanged(const QPixmap data, QString key, int contactId)
{
    Data::ContactData *contact = m_data->at(contactId);
    if(key == Attribute::Userpic)
        contact->m_userPic = data;
}

void ContactListModel::dataChanged(const QDate data, QString key, int contactId)
{
    Data::ContactData *contact = m_data->at(contactId);
    Data::Organization organization = contact->m_organizations.at(0);
    if(key == Attribute::Birthday)
        contact->m_birthday = data;
    else if(key == Attribute::DateIn)
        organization.dateIn = data;
    else if(key == Attribute::DateOut)
        organization.dateOut = data;

    contact->m_organizations.replace(0,organization);
}
