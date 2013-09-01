#include <QFile>
#include <QTextStream>
#include "contactListModel.h"
#include "driverManager.h"

ContactListModel::ContactListModel(ContactListController *controller, QWidget *parent)
    : QWidget(parent),
      m_controller(controller),
      m_driver(new DriverManager()),
      m_pathToCurrentData(new QString()),
      m_data(new Data::Contacts())
{
}

QStringList *ContactListModel::loadData(const QString &path)
{
    Data::Contacts *data = m_driver->loadData(path);
    if (data)
    {
        *m_pathToCurrentData = path;
        *m_data = *data;
    }
    return contactList();
}

void ContactListModel::saveData(const QString &path)
{
    if (m_driver->saveData(*m_data, path))
        *m_pathToCurrentData = path;
}

QStringList *ContactListModel::contactList() const
{
    QStringList *data = new QStringList();
    for (int i=0; i<m_data->size(); ++i)
        data->append(m_data->at(i)->data(CONTACT).at(ALIAS));
    return data;
}

QString *ContactListModel::pathToData() const
{
    return m_pathToCurrentData;
}

ContactData *ContactListModel::contact(int index) const
{
    return m_data->at(index);
}

ContactData *ContactListModel::newData() const
{
    m_data->clear();
    m_pathToCurrentData->clear();
    newContact();
    return m_data->at(0);
}

ContactData *ContactListModel::newContact() const
{
    m_data->append(new ContactData());
    return m_data->last();
}

ContactData *ContactListModel::copyContact(const int index) const
{
    m_data->append(new ContactData(*m_data->at(index)));
    return m_data->last();
}

void ContactListModel::deleteContact(const int index)
{
    if (m_data->size())
        m_data->remove(index);
}

ContactData *ContactListModel::loadContact(const QString &path)
{
    ContactData *data = m_driver->loadContact(path);
    if (!data)
        return 0;

    m_data->append(data);
    return data;
}

void ContactListModel::saveContact(const ContactData &data, const QString &path)
{
    if (m_driver->saveContact(data, path))
        *m_pathToCurrentData = path;
}

void ContactListModel::dataChanged(const QString data, QString key, int contactId)
{
    ContactData *contact = m_data->at(contactId);

    if (key == Attribute::Alias ||
        key == Attribute::Name ||
        key == Attribute::LastName ||
        key == Attribute::OtherName ||
        key == Attribute::Birthday ||
        key == Attribute::PathToUserPic ||
        key == Attribute::Comment)
    {
        contact->setMainData(key, data);
    }
    else if (key == Address::Country ||
             key == Address::City ||
             key == Address::Street ||
             key == Address::Home ||
             key == Address::Apartment)
    {
        contact->setAddressData(key, data);
    }
    else if (key == Attribute::NameOrganization ||
             key == Attribute::Department ||
             key == Attribute::Post ||
             key == Attribute::AddressOrganization ||
             key == Attribute::PhoneOrganization)
    {
        contact->setCompanyData(key, data);
    }
    else if (key == Channel::Phone ||
             key == Channel::Email ||
             key == Channel::Skype ||
             key == Channel::Site)
    {
        contact->setChannel(key, contact->data(Channel::All).at(1), data);
    }
}

void ContactListModel::dataChanged(const QDate data, QString key, int contactId)
{
    ContactData *contact = m_data->at(contactId);
    if (key == Attribute::Birthday)
        contact->setBirthday(data);
    else if (key == Attribute::DateIn ||
             key == Attribute::DateOut)
        contact->setCompanyData(key, data);
}
