#ifndef CONTACTLISTCONTROLLER_H
#define CONTACTLISTCONTROLLER_H

#include <QWidget>
#include "contactData.h"
#include "settingsData.h"
#include "myLog.h"

class ContactListView;
class ContactListModel;

class ContactListController : public QWidget
{
    Q_OBJECT
public:
    explicit ContactListController(QWidget *parent = 0);

    QStringList *contactList() const;
    QString *pathToData() const;
    Data::ContactData *contact(int index) const;
    Data::ContactData *newData() const;
    Data::ContactData *newContact() const;
    Data::ContactData *copyContact(const int index) const;
    void deleteContact(const int index);

    Data::ContactData *loadContact(const QString &path);
    bool saveContact(const Data::ContactData &data, const QString &path);

    QStringList *loadData(const QString &path);
    bool saveData(const QString &path);

    void changeSettings(const SettingsData &data);
    SettingsData *getDefaultSettings();

private:
    ContactListModel *m_model;
    ContactListView *m_view;
    myLog *m_log;
};

#endif // CONTACTLISTCONTROLLER_H
