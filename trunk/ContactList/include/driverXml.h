#ifndef DRIVERXML_H
#define DRIVERXML_H

#include "driver.h"

class QDomDocument;
class QDomElement;

class DriverXml : public Driver
{
public:
    explicit DriverXml();
    ~DriverXml();
    bool saveData(const Data::Contacts &data, const QString &path);
    Data::Contacts *loadData(const QString &path);

    bool saveContact(const ContactData &data, const QString &path);
    ContactData *loadContact(const QString &path);

private:
    void xmlToContactData(const QDomElement &record, ContactData &data) const;
    void contactDataToXml(QDomElement &record, const ContactData &data) const;
};

#endif // DRIVERXML_H
