#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QWidget>
#include "contactData.h"

class ContactListController;
class DriverManager;

class ContactListModel : public QWidget
{
    Q_OBJECT
public:
    explicit ContactListModel(ContactListController *controller, QWidget *parent = 0);
    QStringList *loadData(const QString &path);

    QStringList *contactList() const;
    QString *pathToData() const;
    Data::ContactData *contact(int index) const;
    Data::ContactData *newData() const;
    Data::ContactData *newContact() const;
    Data::ContactData *copyContact(const int index) const;

    Data::ContactData *loadContact(const QString &path);

public slots:
    void dataChanged(const QString data, QString key, int contactId);
    void dataChanged(const QPixmap data, QString key, int contactId);
    void dataChanged(const QDate data, QString key, int contactId);
    void deleteContact(const int index);
    void saveData(const QString &path);
    void saveContact(const Data::ContactData &data, const QString &path);

private:
    ContactListController *m_controller;
    DriverManager *m_driver;
    QString *m_pathToCurrentData;
    Data::Contacts *m_data;
};

#endif // CONTACTLISTMODEL_H
