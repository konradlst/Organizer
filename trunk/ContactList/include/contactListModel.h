#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QWidget>
#include "contactData.h"
#include "settingsData.h"

class QSettings;
class ContactListController;
class DriverXml;

class ContactListModel : public QWidget
{
    Q_OBJECT
public:
    explicit ContactListModel(ContactListController *controller, QWidget *parent = 0);
    QStringList *loadData(const QString &path);
    bool saveData(const QString &path);

    QStringList *contactList() const;
    QString *pathToData() const;
    Data::ContactData *contact(int index) const;
    Data::ContactData *newData() const;
    Data::ContactData *newContact() const;
    Data::ContactData *copyContact(const int index) const;
    void deleteContact(const int index);

    Data::ContactData *loadContact(const QString &path);
    bool saveContact(const Data::ContactData &data, const QString &path);

    void changeSettings(const SettingsData &data);
    SettingsData *getSettings();
    void loadSettings();
    void setDefaultSettings();

public slots:
    void dataChanged(const QString data, QString key, int contactId);

private:
    ContactListController *m_controller;
    DriverXml *m_driverXml;
    QString *m_pathToCurrentData;
    Data::Contacts *m_data;
    SettingsData *m_settings;
    QSettings *m_settingsIni;
};

#endif // CONTACTLISTMODEL_H
