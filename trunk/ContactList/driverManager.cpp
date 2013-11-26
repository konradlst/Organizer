﻿#include "cgErrorMessage.h"
#include "driverSqlite.h"
#include "driverXml.h"
#include "driverManager.h"

namespace File
{
const QString XML(".xml");
const QString SQLITE(".sqlite");
}

DriverManager::DriverManager()
    : m_xml(new DriverXml()),
      m_sqlite(new DriverSqlite())
{
}

DriverManager::~DriverManager()
{
}

bool DriverManager::saveData(const Data::Contacts &data, const QString &path)
{
    if (path.endsWith(File::XML))
        return m_xml->saveData(data, path);
    else if (path.endsWith(File::SQLITE))
        return m_sqlite->saveData(data, path);

    return m_sqlite->saveData(data, path + File::SQLITE);
}

Data::Contacts *DriverManager::loadData(const QString &path)
{
    if (path.endsWith(File::XML))
        return m_xml->loadData(path);
    else if (path.endsWith(File::SQLITE))
        return m_sqlite->loadData(path);

    ERROR_INCORRECT_FORMAT(QString(), QString(), QString()); //FIXME
    return 0;
}

bool DriverManager::saveContact(const ContactData &data, const QString &path)
{
    if (path.endsWith(File::XML))
        return m_xml->saveContact(data, path);
    else
        return m_xml->saveContact(data, path + File::XML);
}

ContactData *DriverManager::loadContact(const QString &path)
{
    if (path.endsWith(File::XML))
        return m_xml->loadContact(path);

    ERROR_INCORRECT_FORMAT(QString(), QString(), QString()); //FIXME
    return 0;
}
