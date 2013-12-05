#include <QDomElement>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
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
    if (!m_db.open())
        return Error::cannotOpen();

    if (!m_db.tables().isEmpty())
    {
        qDebug() << DbExist.arg(m_pathToDb);
        return true;
    }
    m_db.close();

    QDomElement scheme;
    if (!Scheme::loadScheme(scheme, m_scheme) || !generateTables(scheme)
            || (fillTable && !fillTables(scheme)))
        return false;
    return true;
}

bool dbGenerator::generateTables(const QDomElement &scheme)
{
    QDomNode tablesNode = scheme.firstChildElement(Scheme::tagTables);
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
        QString table = tableNode.toElement().attribute(Scheme::attrName);
        queryList << SQL::Create.arg(table, fields.join(SQL::Comma));
        tableNode = tableNode.nextSibling();
    }
    return execQueries(queryList);
}

bool dbGenerator::fillTables(const QDomElement &scheme)
{
    QDomNode valuesNode = scheme.firstChildElement(Scheme::tagValues);
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
            fieldNames << Quotes.arg(field.attribute(Scheme::attrName));
            fieldValues << Quotes.arg(field.attribute(Scheme::attrValue));

            fldNode = fldNode.nextSibling();
        }
        QString table = tableNode.toElement().attribute(Scheme::attrName);
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
    d << field.attribute(Scheme::attrName)
      << field.attribute(Scheme::attrType);

    if (field.hasAttribute(Scheme::attrPk) && field.attribute(Scheme::attrPk) == True)
        d << SQL::PrimaryKey;
    else if (field.hasAttribute(Scheme::attrFk) && field.hasAttribute(Scheme::attrFkField))
        d << SQL::ForeignKey.arg(field.attribute(Scheme::attrName))
                             .arg(field.attribute(Scheme::attrFk))
                             .arg(field.attribute(Scheme::attrFkField));

    if (field.hasAttribute(Scheme::attrNullable) && field.attribute(Scheme::attrNullable) == False)
        d << SQL::NotNull;
    if (field.hasAttribute(Scheme::attrUnq) && field.attribute(Scheme::attrUnq) == True)
        d << SQL::Unique;
    if (field.hasAttribute(Scheme::attrDefault))
        d << SQL::Default.arg(field.attribute(Scheme::attrDefault));

    data.append(d.join(" "));
}

bool dbGenerator::execQueries(const QStringList &list)
{
    m_db.open();
    QSqlQuery query(m_db);
    foreach (const QString &q, list)
    {
        if (!query.exec(q))
            qDebug() << query.lastError() << query.lastQuery();
    }
    m_db.close();
    return true;
}
