#include "dbGenerator.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QtSql>
#include <QDebug>
#include "cgErrorMessage.h"

namespace Scheme {
const QString tagRoot("cg_db_scheme");
const QString tagTables("tables");
const QString tagValues("values");
const QString tagTable("table");
const QString attrVersion("version");
const QString attrName("name");
const QString attrValue("value");
const QString attrType("type");
const QString attrPk("pk");
const QString attrNullable("nullable");
const QString attrUnq("unq");
const QString attrDefault("default");
}

namespace {
const QString COMMA(", ");
const QString INSERT("INSERT INTO %1(%2) VALUES(%3);");
const QString CREATE("CREATE TABLE %1 (%2);");
const QString MSG_INSERT("Added new data in '%1'");
const QString VERSION("0.1");

QString setQuotes(QString str)
{
    return QString("'%1'").arg(str);
}
}

dbGenerator::dbGenerator(const QString &metascheme, const QString &pathToDb) :
    m_metascheme(metascheme),
    m_pathToDb(pathToDb)
{
}

bool dbGenerator::generate(const bool fillTable)
{
    m_db = QSqlDatabase::addDatabase(Db::SQLITE, "generateDb");
    m_db.setDatabaseName(m_pathToDb);
    if (!m_db.open())
    {
        ERROR_CANNOT_OPEN;
        return false;
    }

    if(!m_db.tables().isEmpty())
    {
        qDebug() << QString("Database %1 already exist").arg(m_pathToDb);
        return true;
    }
    m_db.close();

    QDomElement scheme;
    if(!loadScheme(scheme))
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
            queryList << CREATE.arg(table, fields.join(COMMA));
            tableNode = tableNode.nextSibling();
        }
        execQueries(queryList);
    }

    if(fillTable)
    {
        tablesNode = scheme.firstChildElement(Scheme::tagValues);
        if(!tablesNode.isNull())
        {
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
                queryList << INSERT.arg(table)
                                   .arg(fieldNames.join(COMMA))
                                   .arg(fieldValues.join(COMMA));
                tableNode = tableNode.nextSibling();
            }
            execQueries(queryList);
        }
    }
    return true;
}

bool dbGenerator::loadScheme(QDomElement &scheme)
{
    QDomDocument doc;
    QFile file(m_metascheme);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ERROR_CANNOT_OPEN;
        return false;
    }
    if (!doc.setContent(&file))
    {
        ERROR_INCORRECT_FORMAT;
        return false;
    }
    file.close();

    scheme = doc.documentElement();
    if (scheme.nodeName() != Scheme::tagRoot)
    {
        ERROR_INCORRECT_FORMAT;
        return false;
    }
    if(scheme.attribute(Scheme::attrVersion) != VERSION)
    {
        ERROR_INCORRECT_VERSION;
        return false;
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
       field.attribute(Scheme::attrPk) == "1")
    {
        d << " PRIMARY KEY";
    }
    if(field.hasAttribute(Scheme::attrNullable) &&
       field.attribute(Scheme::attrNullable) == "0")
    {
        d << " NOT NULL";
    }
    if(field.hasAttribute(Scheme::attrUnq) &&
       field.attribute(Scheme::attrUnq) == "1")
    {
        d << " UNIQUE";
    }
    if(field.hasAttribute(Scheme::attrDefault))
    {
        d << QString(" DEFAULT %1").arg(field.attribute(Scheme::attrDefault));
    }
    data.append(d.join(""));
}

bool dbGenerator::execQueries(const QStringList &list)
{
    m_db.open();
    QSqlQuery query(m_db);
    foreach (QString q, list)
    {
        qDebug() << QString("execQuery: %1").arg(q);
        if(!query.exec(q))
            query.lastError();
    }
    m_db.close();
    return true;
}
