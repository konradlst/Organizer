#ifndef CONTACTLISTCONTROLLER_H
#define CONTACTLISTCONTROLLER_H

#include <QWidget>
#include "contactData.h"
#include "myLog.h"

class ContactListView;
class ContactListModel;
class SettingsView;

class ContactListController : public QWidget
{
    Q_OBJECT
public:
    explicit ContactListController(QWidget *parent = 0);

    QStringList *contactList() const;
    QString *pathToData() const;
    ContactData *contact(int index) const;
    ContactData *newData() const;
    ContactData *newContact() const;
    ContactData *copyContact(const int index) const;
    ContactData *loadContact(const QString &path);
    QStringList *loadData(const QString &path);

    SettingsView *getSettingsPtr();

private slots:
    void logging(bool flag, const QString &path);

private:
    myLog *m_log;
    SettingsView *m_settings;
    ContactListModel *m_model;
    ContactListView *m_view;
};

#endif // CONTACTLISTCONTROLLER_H
