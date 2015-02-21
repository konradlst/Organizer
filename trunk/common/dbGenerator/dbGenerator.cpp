#include <QDomElement>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include "cgMetaschemeConst.h"
#include "logger.h"
#include "dbGenerator.h"

namespace
{
const QString ConnectionName = "generateDb";
const QString DbExist = QObject::trUtf8("Database %1 already exist");
const QString True = "1";
const QString False = "0";
const QString Quotes = "'%1'";
}

dbGenerator::dbGenerator(const QString &pathToDb, const QString &scheme)
    : m_pathToDb(pathToDb),
      m_scheme(scheme)
{
}

bool dbGenerator::generate(const bool fillTable)
{
    m_db = QSqlDatabase::addDatabase(SQL::Sqlite, ConnectionName);
    m_db.setDatabaseName(m_pathToDb);
    if (!m_db.isOpen() && !m_db.open())
        return Error::cannotOpen();

    if (!m_db.tables().isEmpty())
    {
        m_lastError = DbExist.arg(m_pathToDb);
        Log::error(m_lastError);
        return true;
    }
    m_db.close();

    QDomElement scheme;
    if (!Scheme::load(scheme, m_scheme)
            || !generateTables(scheme)
            || (fillTable && !fillTables(scheme)))
        return false;
    return true;
}

QString dbGenerator::lastError()
{
    return m_lastError;
}

bool dbGenerator::generateTables(const QDomElement &scheme)
{
    QDomNode tablesNode = scheme.firstChildElement(SchemeTag::Tables);
    if (tablesNode.isNull())
        return false;
    QDomNode tableNode = tablesNode.firstChild();
    QStringList queryList;
    while (!tableNode.isNull())
    {
        QDomNode fieldNode = tableNode.firstChild();
        QStringList fields;
        while (!fieldNode.isNull())
        {
            QDomElement fieldElement = fieldNode.toElement();
            QString fieldData;
            parseField(fieldElement, fieldData);
            fields << fieldData;

            fieldNode = fieldNode.nextSibling();
        }
        QString table = tableNode.toElement().attribute(SchemeAttr::Name);
        queryList << SQL::Create.arg(table, fields.join(SQL::Comma));
        tableNode = tableNode.nextSibling();
    }
    return execQueries(queryList);
}

bool dbGenerator::fillTables(const QDomElement &scheme)
{
    QDomNode valuesNode = scheme.firstChildElement(SchemeTag::Values);
    if (valuesNode.isNull())
        return false;
    QDomNode tableNode = valuesNode.firstChild();
    QStringList queryList;
    while (!tableNode.isNull())
    {
        QDomNode fldNode = tableNode.firstChild();
        QStringList fieldNames;
        QStringList fieldValues;
        while (!fldNode.isNull())
        {
            QDomElement field = fldNode.toElement();
            fieldNames << Quotes.arg(field.attribute(SchemeAttr::Name));
            fieldValues << Quotes.arg(field.attribute(SchemeAttr::Value));

            fldNode = fldNode.nextSibling();
        }
        QString table = tableNode.toElement().attribute(SchemeAttr::Name);
        queryList << SQL::Insert.arg(table)
                                .arg(fieldNames.join(SQL::Comma))
                                .arg(fieldValues.join(SQL::Comma));
        tableNode = tableNode.nextSibling();
    }
    return execQueries(queryList);
}

void dbGenerator::parseField(const QDomElement &field, QString &data) const
{
    QStringList d;
    d << field.attribute(SchemeAttr::Name)
      << field.attribute(SchemeAttr::Type);

    if (field.hasAttribute(SchemeAttr::Pk) && field.attribute(SchemeAttr::Pk) == True)
        d << SQL::PrimaryKey;
    else if (field.hasAttribute(SchemeAttr::Fk) && field.hasAttribute(SchemeAttr::FkField))
        d << SQL::ForeignKey.arg(field.attribute(SchemeAttr::Name))
                             .arg(field.attribute(SchemeAttr::Fk))
                             .arg(field.attribute(SchemeAttr::FkField));

    if (field.hasAttribute(SchemeAttr::Nullable) && field.attribute(SchemeAttr::Nullable) == False)
        d << SQL::NotNull;
    if (field.hasAttribute(SchemeAttr::Unq) && field.attribute(SchemeAttr::Unq) == True)
        d << SQL::Unique;
    if (field.hasAttribute(SchemeAttr::Default))
        d << SQL::Default.arg(field.attribute(SchemeAttr::Default));

    data.append(d.join(" "));
}

bool dbGenerator::execQueries(const QStringList &list)
{
    if (m_db.isOpen())
        m_db.open();
    QSqlQuery query(m_db);
    foreach (const QString &q, list)
    {
        if (!query.exec(q))
        {
            m_lastError = query.lastError().text() + query.lastQuery();
            Log::error(m_lastError);
        }
    }
    m_db.close();
    return true;
}
