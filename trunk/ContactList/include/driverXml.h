#ifndef DRIVERXML_H
#define DRIVERXML_H

#include <QWidget>
#include "contactData.h"

class QDomDocument;
class QDomElement;

class DriverXml : public QWidget
{
    Q_OBJECT
public:
    explicit DriverXml(QWidget *parent = 0);
    bool saveData(const Data::Contacts &data, const QString &path);
    Data::Contacts *loadData(const QString &path);

    bool saveContact(const Data::ContactData &data, const QString &path);
    Data::ContactData *loadContact(const QString &path);

private:
    void xmlToContactData(const QDomElement &recordElement, Data::ContactData &currentContact);
    void contactDataToXml(QDomElement &record, const Data::ContactData &data);

private:
    //! Путь до xml файла.
    QString *m_path;
    //! Хэш с данными.
    Data::Contacts *m_contacts;
};

#endif // DRIVERXML_H
