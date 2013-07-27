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

const QString INSERT = QString("INSERT INTO %1(%2) VALUES(%3);");
const QString CREATE = QString("CREATE TABLE %1 (%2);");
const QString MSG_INSERT = QString("Added new data in '%1'");

const QString VERSION = QString("0.1");
}

namespace Scheme {
const QString tagRoot = QString("cg_db_scheme");
const QString tagTables = QString("tables");
const QString tagTable = QString("table");
const QString attrVersion = QString("version");
const QString attrName = QString("name");
const QString attrType = QString("type");
const QString attrPk = QString("pk");
const QString attrNullable = QString("nullable");
const QString attrUnq = QString("unq");
}

dbGenerator::dbGenerator(QString &metascheme, QString &pathToDb) :
    m_metascheme(metascheme),
    m_pathToDb(pathToDb)
{
}

bool dbGenerator::generate()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("concierge.sqlite");
    if (!db.open())
    {
        ERROR_MESSAGE_CANNOT_OPEN;
        return false;
    }

    QDomElement scheme;
    if(!loadScheme(scheme))
        return false;

    QDomNode tablesNode = scheme.firstChild();
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
    QSqlQuery query;
    if(query.exec(INSERT.arg("CG_FINANCEACCOUNTS")
               .arg("number,status,type,name,value")
               .arg("'1234567890','1','3','vtb debet','5000'")))
        qDebug() << MSG_INSERT.arg("CG_FINANCEACCOUNTS");

    if(query.exec(INSERT.arg("CG_FINANCELOG")
               .arg("timestamp,operation,value,sendfrom,sendto,comment")
               .arg("'2013.07.25 15:01','1','3000','vtb debet','rsb card','test'")))
        qDebug() << MSG_INSERT.arg("CG_FINANCELOG");

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

void dbGenerator::parseField(const QDomElement &fieldElement, QString &data)
{
    data.append(fieldElement.attribute(Scheme::attrName));
    data.append(" ");
    data.append(fieldElement.attribute(Scheme::attrType));

    if(fieldElement.hasAttribute(Scheme::attrPk) && fieldElement.attribute(Scheme::attrPk) == "1")
    {
        data.append(" PRIMARY KEY");
    }
    if(fieldElement.hasAttribute(Scheme::attrNullable) && fieldElement.attribute(Scheme::attrNullable) == "0")
    {
        data.append(" NOT NULL");
    }
    if(fieldElement.hasAttribute(Scheme::attrUnq) && fieldElement.attribute(Scheme::attrUnq) == "1")
    {
        data.append(" UNIQUE");
    }
}

bool dbGenerator::createTable(QString &tableName, QString &fieldsData)
{
    QSqlQuery query;

    qDebug() << "execQuery:" << CREATE.arg(tableName, fieldsData);
    return query.exec(CREATE.arg(tableName, fieldsData));
}
