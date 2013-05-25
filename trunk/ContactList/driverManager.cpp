#include <QMessageBox>
#include "driverManager.h"
#include "driverXml.h"
#include "driverSqlite.h"

namespace File {
const QString XML(".xml");
const QString SQLITE(".sqlite");
}

DriverManager::DriverManager() :
    m_xml(new DriverXml()),
    m_sqlite(new DriverSqlite())
{
}

DriverManager::~DriverManager()
{
}

bool DriverManager::saveData(const Data::Contacts &data, const QString &path)
{
    if(path.endsWith(File::XML))
    {
        return m_xml->saveData(data, path);
    }
    else if(path.endsWith(File::SQLITE))
    {
        return m_sqlite->saveData(data, path);
    }
    else
    {
        //FIXME msgbox incorrect format, save as sqlite
        return m_sqlite->saveData(data, path + File::SQLITE);
    }
}

Data::Contacts *DriverManager::loadData(const QString &path)
{
    if(path.endsWith(File::XML))
    {
        return m_xml->loadData(path);
    }
    else if(path.endsWith(File::SQLITE))
    {
        return m_sqlite->loadData(path);
    }
    else
    {
        //FIXME msgbox incorrect format
        return 0;
    }
}

bool DriverManager::saveContact(const Data::ContactData &data, const QString &path)
{
    if(path.endsWith(File::XML))
    {
        return m_xml->saveContact(data, path);
    }
    else
    {
        //FIXME msgbox incorrect format, save as xml
        return m_xml->saveContact(data, path + File::XML);
    }
}

Data::ContactData *DriverManager::loadContact(const QString &path)
{
    if(path.endsWith(File::XML))
    {
        return m_xml->loadContact(path);
    }
    else
    {
        //FIXME msgbox incorrect format
        return 0;
    }
}
