#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include "driver.h"

class DriverXml;
class DriverSqlite;

/*! \class DriverManager
    \brief Класс для управления драйверами, вызывает необходимый драйвер,
            в зависимости от расширения файла.
*/
class DriverManager : public Driver
{
public:
    DriverManager();
    ~DriverManager();
    bool saveData(const Data::Contacts &data, const QString &path);
    Data::Contacts *loadData(const QString &path);

    bool saveContact(const ContactData &data, const QString &path);
    ContactData *loadContact(const QString &path);

private:
    DriverXml *m_xml;
    DriverSqlite *m_sqlite;
};

#endif // DRIVERMANAGER_H
