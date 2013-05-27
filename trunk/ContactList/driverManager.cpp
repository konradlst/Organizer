#include <QMessageBox>
#include "driverManager.h"
#include "driverXml.h"
#include "driverSqlite.h"

namespace File {
const QString XML(".xml");
const QString SQLITE(".sqlite");
}

namespace {
#define ERROR QObject::trUtf8("Error")
#define ERR_INCORRECT QObject::trUtf8("This file has incorrect format!")
#define ERR_INCORRECT_SAVE_AS QObject::trUtf8("This file has incorrect format! File will be save as %1")
#define ERROR_MESSAGE_INCORRECT QMessageBox::warning(new QWidget(), ERROR, ERR_INCORRECT)
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
        return m_xml->saveData(data, path);
    else if(path.endsWith(File::SQLITE))
        return m_sqlite->saveData(data, path);
    else
        return m_sqlite->saveData(data, path + File::SQLITE);
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
        ERROR_MESSAGE_INCORRECT;
        return 0;
    }
}

bool DriverManager::saveContact(const Data::ContactData &data, const QString &path)
{
    if(path.endsWith(File::XML))
        return m_xml->saveContact(data, path);
    else
        return m_xml->saveContact(data, path + File::XML);
}

Data::ContactData *DriverManager::loadContact(const QString &path)
{
    if(path.endsWith(File::XML))
    {
        return m_xml->loadContact(path);
    }
    else
    {
        ERROR_MESSAGE_INCORRECT;
        return 0;
    }
}
