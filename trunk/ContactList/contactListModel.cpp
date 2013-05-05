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

bool ContactListModel::saveData(const QString &path)
{
    if(m_driverXml->saveData(*m_data, path)) {
        *m_pathToCurrentData = path;
        return true;
    }
    return false;
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

bool ContactListModel::saveContact(const Data::ContactData &data, const QString &path)
{
    if(m_driverXml->saveContact(data, path)) {
        *m_pathToCurrentData = path;
        return true;
    }
    return false;
}

void ContactListModel::dataChanged(const QString data, QString key, int contactId)
{
    //FIXME change process saving data.
    Data::ContactData *contact = m_data->at(contactId);
    if(key == "alias")
        contact->m_alias = data;
    else if(key == "userpic")
        contact->m_pathToUserPic = data;
    else if(key == "name")
        contact->m_name = data;
    else if(key == "surName")
        contact->m_surName = data;
    else if(key == "otherName")
        contact->m_otherName = data;

    m_data->replace(contactId,contact);
}
