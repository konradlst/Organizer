#include "dbGenerator.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDomDocument>
#include <QtSql>
#include <QDebug>

namespace {
#define ERROR QObject::trUtf8("Error")
#define ERR_INCORRECT QObject::trUtf8("This file has incorrect format!")
#define ERR_INCORRECT_VERSION QObject::trUtf8("This file has incorrect version!")
#define ERR_CANNOT_OPEN QObject::trUtf8("Can not open this file for read or this file has not a text format!")
#define ERROR_MESSAGE_INCORRECT QMessageBox::warning(new QWidget(), ERROR, ERR_INCORRECT)
#define ERROR_MESSAGE_INCORRECT_VERSION QMessageBox::warning(new QWidget(), ERROR, ERR_INCORRECT_VERSION)
#define ERROR_MESSAGE_CANNOT_OPEN QMessageBox::warning(new QWidget(), ERROR, ERR_CANNOT_OPEN)

const QString QSQLITE("QSQLITE");
const QString INSERT("INSERT INTO %1(%2) VALUES(%3);");
const QString CREATE("CREATE TABLE %1 (%2);");
const QString MSG_INSERT("Added new data in '%1'");
const QString VERSION("0.1");

QString setQuotes(QString str)
{
    return QString("'%1'").arg(str);
}
}

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

dbGenerator::dbGenerator(QString &metascheme, QString &pathToDb) :
    m_metascheme(metascheme),
    m_pathToDb(pathToDb)
{
}

bool dbGenerator::generate()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QSQLITE);
    db.setDatabaseName(m_pathToDb);
    if (!db.open())
    {
        ERROR_MESSAGE_CANNOT_OPEN;
        return false;
    }

    QDomElement scheme;
    if(!loadScheme(scheme))
        return false;

    QDomNode tablesNode = scheme.firstChildElement(Scheme::tagTables);
    if(!tablesNode.isNull())
    {
        QDomNode tableNode = tablesNode.firstChild();
        // Read every table in scheme
        while(!tableNode.isNull())
        {
            QDomNode fieldNode = tableNode.firstChild();
            QStringList fields;
            // Read every field in table
            while(!fieldNode.isNull())
            {
                QDomElement fieldElement = fieldNode.toElement();
                QString fieldData;
                parseField(fieldElement, fieldData);
                fields << fieldData;

                fieldNode = fieldNode.nextSibling();
            }
            QString tableName = tableNode.toElement().attribute(Scheme::attrName);
            QString tempFields = fields.join(", ");
            createTable(tableName, tempFields);

            tableNode = tableNode.nextSibling();
        }
    }

    //test data
    tablesNode = scheme.firstChildElement(Scheme::tagValues);
    if(!tablesNode.isNull())
    {
        QDomNode tableNode = tablesNode.firstChild();
        // Read every table in scheme
        while(!tableNode.isNull())
        {
            QDomNode fieldNode = tableNode.firstChild();
            QStringList fieldsName;
            QStringList fieldsValue;
            // Read every field in table
            while(!fieldNode.isNull())
            {
                QDomElement fieldElement = fieldNode.toElement();
                fieldsName << setQuotes(fieldElement.attribute(Scheme::attrName));
                fieldsValue << setQuotes(fieldElement.attribute(Scheme::attrValue));

                fieldNode = fieldNode.nextSibling();
            }
            QString tableName = tableNode.toElement().attribute(Scheme::attrName);

            QString insertQuery = INSERT.arg(tableName)
                    .arg(fieldsName.join(", "))
                    .arg(fieldsValue.join(", "));
            qDebug() << "insertQuery:" << insertQuery;
            QSqlQuery query;
            if(query.exec(insertQuery))
                qDebug() << MSG_INSERT.arg(tableName);

            tableNode = tableNode.nextSibling();
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
        ERROR_MESSAGE_CANNOT_OPEN;
        return false;
    }
    if (!doc.setContent(&file))
    {
        ERROR_MESSAGE_INCORRECT;
        return false;
    }
    file.close();

    scheme = doc.documentElement();
    if (scheme.nodeName() != Scheme::tagRoot)
    {
        ERROR_MESSAGE_INCORRECT;
        return false;
    }
    if(scheme.attribute(Scheme::attrVersion) != VERSION)
    {
        ERROR_MESSAGE_INCORRECT_VERSION;
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

bool dbGenerator::createTable(QString &tableName, QString &fieldsData)
{
    QSqlQuery query;

    qDebug() << "execQuery:" << CREATE.arg(tableName, fieldsData);
    return query.exec(CREATE.arg(tableName, fieldsData));
}
