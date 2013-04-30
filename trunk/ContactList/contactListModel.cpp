#include <QFile>
#include <QTextStream>
#include <QSettings>
#include "contactListModel.h"
#include "driverXml.h"

namespace {
const int ENGLISH = 0;
const QString defaultPathToLog("ContactList.log");

namespace Settings {
const QString LANGUAGE("main/Language");
const QString DEFAULTDATA("main/DefaultData");
const QString PATH_TO_DEFAULTDATA("main/PathToDefaultData");
const QString LOGGING("main/Logging");
const QString PATH_TO_LOGFILE("main/PathToLogFile");
}
}

ContactListModel::ContactListModel(ContactListController *controller, QWidget *parent) :
    QWidget(parent),
    m_controller(controller),
    m_driverXml(new DriverXml()),
    m_pathToCurrentData(new QString()),
    m_data(new Data::Contacts()),
    m_settings(new SettingsData()),
    m_settingsIni(new QSettings(QSettings::IniFormat,QSettings::UserScope,
                                "AnBat","ContactList"))
{
    loadSettings();
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
    else {
        return false;
    }
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
    Data::ContactData data;
    data.m_alias = QString("New contact");
    data.m_birthday = QString(DEFAULT_DATE_STR);
    data.m_addresses.insert(0,Data::Address());
    data.m_communications.insert(0,Data::CommunicationData());

    Data::Organization company;
    company.dateIn = QDate::currentDate().toString(DEFAULT_DATE_FORMAT);
    company.dateOut = QDate::currentDate().toString(DEFAULT_DATE_FORMAT);
    QHash<int,Data::ContactData>::iterator i = m_data->insert(m_data->size(),data);
    return new Data::ContactData(m_data->value(i.key()));
}

Data::ContactData *ContactListModel::copyContact(const int index) const
{
    m_data->insert(m_data->size(),m_data->value(index));
    return new Data::ContactData(m_data->value(m_data->size()-1));
}

void ContactListModel::deleteContact(const int index)
{
    //FIXME I apologize for this stupid code.
    for(int i=index;i<m_data->size()-1;++i) {
        m_data->insert(i,m_data->value(i+1));
    }
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
    else {
        return false;
    }
}

void ContactListModel::changeSettings(const SettingsData &data)
{
    *m_settings = data;
    m_settingsIni->setValue(Settings::LANGUAGE,QVariant(m_settings->language));
    m_settingsIni->setValue(Settings::DEFAULTDATA,QVariant(m_settings->defaultData));
    m_settingsIni->setValue(Settings::PATH_TO_DEFAULTDATA,QVariant(m_settings->pathToDefaultData));
    m_settingsIni->setValue(Settings::LOGGING,QVariant(m_settings->logging));
    m_settingsIni->setValue(Settings::PATH_TO_LOGFILE,QVariant(m_settings->pathToLogFile));
}

SettingsData *ContactListModel::getSettings()
{
    return m_settings;
}

void ContactListModel::loadSettings()
{
    if(QFile(m_settingsIni->fileName()).exists()) {
        m_settings->language = m_settingsIni->value(Settings::LANGUAGE).toInt();
        m_settings->defaultData = m_settingsIni->value(Settings::DEFAULTDATA).toBool();
        m_settings->pathToDefaultData = m_settingsIni->value(Settings::PATH_TO_DEFAULTDATA).toString();
        m_settings->logging = m_settingsIni->value(Settings::LOGGING).toBool();
        m_settings->pathToLogFile = m_settingsIni->value(Settings::PATH_TO_LOGFILE).toString();
    }
    else {
        setDefaultSettings();
    }
}

void ContactListModel::setDefaultSettings()
{
    m_settings->language = ENGLISH;
    m_settings->defaultData = false;
    m_settings->pathToDefaultData = QString();
    m_settings->logging = true;
    m_settings->pathToLogFile = defaultPathToLog;
    changeSettings(*m_settings);
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
