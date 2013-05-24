#include <QFile>
#include <QTextStream>
#include "contactListModel.h"
#include "driverXml.h"
#include "driverSql.h"

namespace File {
const QString XML(".xml");
const QString SQLITE(".sqlite");
}

ContactListModel::ContactListModel(ContactListController *controller, QWidget *parent) :
    QWidget(parent),
    m_controller(controller),
    m_driverXml(new DriverXml()),
    m_driverSql(new DriverSql()),
    m_pathToCurrentData(new QString()),
    m_data(new Data::Contacts())
{
}

QStringList *ContactListModel::loadData(const QString &path)
{
    if(path.endsWith(File::XML))
    {
        Data::Contacts *data = m_driverXml->loadData(path);
        if(data != 0) {
            *m_pathToCurrentData = path;
            *m_data = *data;
        }
    }
    else if(path.endsWith(File::SQLITE))
    {
        Data::Contacts *data = m_driverSql->loadData(path);
        if(data != 0) {
            *m_pathToCurrentData = path;
            *m_data = *data;
        }
    }
    else
    {
        //FIXME incorrect format
    }
    return contactList();
}

void ContactListModel::saveData(const QString &path)
{
    if(path.endsWith(File::XML))
    {
        if(m_driverXml->saveData(*m_data, path))
            *m_pathToCurrentData = path;
    }
    else if(path.endsWith(File::SQLITE))
    {
        if(m_driverSql->saveData(*m_data, path))
            *m_pathToCurrentData = path;
    }
    else
    {
        //FIXME incorrect format
    }
}

QStringList *ContactListModel::contactList() const
{
    QStringList *data = new QStringList();
    for(int i=0; i<m_data->size(); ++i)
        data->append(m_data->at(i)->alias());
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
    m_data->append(new Data::ContactData());
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
    if(path.endsWith(File::XML))
    {
        Data::ContactData *data = m_driverXml->loadContact(path);
        if(data != 0) {
            m_data->append(data);
            return data;
        }
    }
    else
    {
        //FIXME incorrect format
    }
    return 0;
}

void ContactListModel::saveContact(const Data::ContactData &data, const QString &path)
{
    if(path.endsWith(File::XML))
    {
        if(m_driverXml->saveContact(data, path))
            *m_pathToCurrentData = path;
    }
    else
    {
        //FIXME incorrect format
    }
}

void ContactListModel::dataChanged(const QString data, QString key, int contactId)
{
    Data::ContactData *contact = m_data->at(contactId);

    if(key == Attribute::Alias)
        contact->setAlias(data);
    else if(key == Attribute::PathToUserPic)
        contact->setPathToUserPic(data);
    else if(key == Attribute::Name)
        contact->setName(data);
    else if(key == Attribute::SurName)
        contact->setSurName(data);
    else if(key == Attribute::OtherName)
        contact->setOtherName(data);
    else if(key == Attribute::Country)
        contact->setCountry(0, data);
    else if(key == Attribute::City)
        contact->setCity(0, data);
    else if(key == Attribute::Street)
        contact->setStreet(0, data);
    else if(key == Attribute::Home)
        contact->setHome(0, data);
    else if(key == Attribute::Apartment)
        contact->setApartment(0, data);
    else if(key == Attribute::NameOrganization)
        contact->setCompanyName(0, data);
    else if(key == Attribute::PhoneOrganization)
        contact->setCompanyPhone(0, data);
    else if(key == Attribute::Department)
        contact->setDepartment(0, data);
    else if(key == Attribute::Post)
        contact->setPost(0, data);
    else if(key == Attribute::AddressOrganization)
        contact->setCompanyAddress(0, data);
    else if(key == Value::Phone)
        contact->setPhone(contact->phoneTypes().at(0), data);
    else if(key == Value::Email)
        contact->setEmail(contact->phoneTypes().at(0), data);
    else if(key == Value::Skype)
        contact->setSkype(contact->phoneTypes().at(0), data);
    else if(key == Value::Site)
        contact->setSite(contact->phoneTypes().at(0), data);
}

void ContactListModel::dataChanged(const QPixmap data, QString key, int contactId)
{
    Data::ContactData *contact = m_data->at(contactId);
    if(key == Attribute::Userpic)
        contact->setUserPic(data);
}

void ContactListModel::dataChanged(const QDate data, QString key, int contactId)
{
    Data::ContactData *contact = m_data->at(contactId);
    if(key == Attribute::Birthday)
        contact->setBirthday(data);
    else if(key == Attribute::DateIn)
        contact->setDateIn(0, data);
    else if(key == Attribute::DateOut)
        contact->setDateOut(0, data);
}
