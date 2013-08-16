#include "dbGenerator.h"
#include <QDomElement>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "cgErrorMessage.h"
#include "cgMetaschemeConst.h"

namespace
{
const QString CONNECTION_NAME("generateDb");
const QString DB_EXIST("Database %1 already exist");
const QString TRUE("1");
const QString FALSE("0");

QString setQuotes(QString str)
{
    return QString("'%1'").arg(str);
}
}

dbGenerator::dbGenerator(const QString &pathToDb)
    : m_pathToDb(pathToDb)
{
}

bool dbGenerator::generate(const bool fillTable)
{
    m_db = QSqlDatabase::addDatabase(SQL::SQLITE, CONNECTION_NAME);
    m_db.setDatabaseName(m_pathToDb);
    if (!m_db.open())
    {
        ERROR_CANNOT_OPEN;
        return false;
    }

    if(!m_db.tables().isEmpty())
    {
        qDebug() << DB_EXIST.arg(m_pathToDb);
        return true;
    }
    m_db.close();

    QDomElement scheme;
    if(!Scheme::loadScheme(scheme))
        return false;

    QDomNode tablesNode = scheme.firstChildElement(Scheme::tagTables);
    if(!tablesNode.isNull())
    {
        QDomNode tableNode = tablesNode.firstChild();
        QStringList queryList;
        while(!tableNode.isNull())
        {
            QDomNode fieldNode = tableNode.firstChild();
            QStringList fields;
            while(!fieldNode.isNull())
            {
                QDomElement fieldElement = fieldNode.toElement();
                QString fieldData;
                parseField(fieldElement, fieldData);
                fields << fieldData;

                fieldNode = fieldNode.nextSibling();
            }
            QString table = tableNode.toElement().attribute(Scheme::attrName);
            queryList << SQL::CREATE.arg(table, fields.join(SQL::COMMA));
            tableNode = tableNode.nextSibling();
        }
        execQueries(queryList);
    }

    if(fillTable)
    {
        tablesNode = scheme.firstChildElement(Scheme::tagValues);
        if(tablesNode.isNull())
            return false;

        QDomNode tableNode = tablesNode.firstChild();
        QStringList queryList;
        while(!tableNode.isNull())
        {
            QDomNode fldNode = tableNode.firstChild();
            QStringList fieldNames;
            QStringList fieldValues;
            while(!fldNode.isNull())
            {
                QDomElement field = fldNode.toElement();
                fieldNames << setQuotes(field.attribute(Scheme::attrName));
                fieldValues << setQuotes(field.attribute(Scheme::attrValue));

                fldNode = fldNode.nextSibling();
            }
            QString table = tableNode.toElement().attribute(Scheme::attrName);
            queryList << SQL::INSERT.arg(table)
                         .arg(fieldNames.join(SQL::COMMA))
                         .arg(fieldValues.join(SQL::COMMA));
            tableNode = tableNode.nextSibling();
        }
        execQueries(queryList);
    }
    return true;
}

void dbGenerator::parseField(const QDomElement &field, QString &data)
{
    QStringList d;
    d << field.attribute(Scheme::attrName)
      << " "
      << field.attribute(Scheme::attrType);

    if(field.hasAttribute(Scheme::attrPk) &&
       field.attribute(Scheme::attrPk) == TRUE)
    {
        d << SQL::PRIMARY_KEY;
    }
    if(field.hasAttribute(Scheme::attrNullable) &&
       field.attribute(Scheme::attrNullable) == FALSE)
    {
        d << SQL::NOT_NULL;
    }
    if(field.hasAttribute(Scheme::attrUnq) &&
       field.attribute(Scheme::attrUnq) == TRUE)
    {
        d << SQL::UNIQUE;
    }
    if(field.hasAttribute(Scheme::attrDefault))
    {
        d << SQL::DEFAULT.arg(field.attribute(Scheme::attrDefault));
    }
    data.append(d.join(""));
}

bool dbGenerator::execQueries(const QStringList &list)
{
    m_db.open();
    QSqlQuery query(m_db);
    foreach (QString q, list)
    {
        if(!query.exec(q))
            qDebug() << query.lastError() << query.lastQuery();
    }
    m_db.close();
    return true;
}
