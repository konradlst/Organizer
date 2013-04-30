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
    if(data->size() != 0) {
        *m_pathToCurrentData = path;
        m_data = data;
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
        data->append(m_data->value(i).m_alias);
    return data;
}

QString *ContactListModel::pathToData() const
{
    return m_pathToCurrentData;
}

Data::ContactData *ContactListModel::contact(int index) const
{
    return new Data::ContactData(m_data->value(index));
}

Data::ContactData *ContactListModel::newData() const
{
    m_data->clear();
    m_pathToCurrentData->clear();
    Data::ContactData *data = newContact();
    m_data->insert(0,*data);
    return data;
}

Data::ContactData *ContactListModel::newContact() const
{
    Data::ContactData *data = new Data::ContactData;
    data->m_alias = QString("New contact");
    data->m_birthday = QString(DEFAULT_DATE_STR);
    data->m_addresses.insert(0,Data::Address());
    data->m_communications.insert(0,Data::CommunicationData());

    Data::Organization company;
    company.dateIn = QDate::currentDate().toString(DEFAULT_DATE_FORMAT);
    company.dateOut = QDate::currentDate().toString(DEFAULT_DATE_FORMAT);
    data->m_organizations.insert(0,company);
    m_data->insert(m_data->size(),*data);
    return data;
}

Data::ContactData *ContactListModel::copyContact(const int index) const
{
    m_data->insert(m_data->size(),m_data->value(index));
    return new Data::ContactData(m_data->value(m_data->size()-1));
}

void ContactListModel::deleteContact(const int index)
{
    //FIXME I apologize for this stupid code.
    for(int i=index;i<m_data->size()-1;++i)
        m_data->insert(i,m_data->value(i+1));
    m_data->remove(m_data->size()-1);
}

Data::ContactData *ContactListModel::loadContact(const QString &path)
{
    Data::ContactData data = *m_driverXml->loadContact(path);
    m_data->insert(m_data->size(),data);
    return new Data::ContactData(m_data->value(m_data->size()-1));
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
    Data::ContactData contact = m_data->value(contactId);
    if(key == "alias")
        contact.m_alias = data;
    else if(key == "userpic")
        contact.m_pathToUserPic = data;
    else if(key == "name")
        contact.m_name = data;
    else if(key == "surName")
        contact.m_surName = data;
    else if(key == "otherName")
        contact.m_otherName = data;

    m_data->insert(contactId,contact);
}
