#include "cgDelegateManager.h"
#include <QDomDocument>
#include <QFile>
#include "cgComboBoxDelegate.h"
#include "cgCheckBoxDelegate.h"
#include "cgDateDelegate.h"
#include "cgDateTimeDelegate.h"
#include "cgTimeDelegate.h"
#include "cgLineEditDelegate.h"
#include "cgErrorMessage.h"

namespace Scheme {
const QString tagRoot("cg_db_scheme");
const QString tagTables("tables");
const QString tagTable("table");
const QString tagDelegates("delegates");
const QString tagDelegate("delegate");
const QString attrVersion("version");
const QString attrName("name");
const QString attrDelegate("delegate");
const QString attrType("type");
const QString attrParam("param");
}

namespace delegateName {
const QString line("lineEdit");
const QString comboBox("comboBoxEdit");
const QString checkBox("checkBoxEdit");
const QString date("dateEdit");
const QString time("timeEdit");
const QString dateTime("dateTimeEdit");
const QString dSpinBox("doubleSpinBoxEdit");
}

namespace
{
const QString metascheme("./metascheme.xml");
const int MAX_PARAMS = 3;
const QString VERSION("0.1");
}

QList<QAbstractItemDelegate *> *cgDelegateManager::getDelegateList(const QString &tableName)
{
    QDomElement scheme;
    if(!loadScheme(scheme))
        return 0;

    QList<QAbstractItemDelegate *> *list = new QList<QAbstractItemDelegate *>();
    QDomNode tablesNode = scheme.firstChildElement(Scheme::tagTables);
    QDomElement delegates = scheme.firstChildElement(Scheme::tagDelegates);
    if(!tablesNode.isNull())
    {
        QDomElement tableElement = tablesNode.firstChildElement(tableName);
        if(!tableElement.isNull())
        {
            QString delegateName = tableElement.attribute(Scheme::attrDelegate);
            QDomElement delegate = delegates.firstChildElement(Scheme::tagDelegate);
            while (delegate.attribute(Scheme::attrName) != delegateName)
                delegate.nextSiblingElement(Scheme::tagDelegate);

            QStringList lst;
            lst << delegate.attribute(Scheme::attrType);

            int i = 1;
            while (delegate.hasAttribute(Scheme::attrParam + QString::number(i)))
            {
                lst << delegate.attribute(Scheme::attrParam + QString::number(i));
                ++i;
            }
            list->append(createDelegate(lst));
        }
    }
    return list;
}

bool cgDelegateManager::loadScheme(QDomElement &scheme)
{
    QDomDocument doc;
    QFile file(metascheme);
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


QAbstractItemDelegate *cgDelegateManager::createDelegate(QStringList &list)
{
    QString type = list.at(0);
    if(type == delegateName::line)
    {
        return new cgLineEditDelegate(list.at(1).toInt(), list.at(2), list.at(3).toInt());
    }
    else if(type == delegateName::comboBox)
    {
        return new cgComboBoxDelegate(QStringList(list.at(1)), list.at(2).toInt());
    }
    else if(type == delegateName::checkBox)
    {
        return new cgCheckBoxDelegate();
    }
    else if(type == delegateName::date)
    {
        return new cgDateDelegate();
    }
    else if(type == delegateName::time)
    {
        return new cgTimeDelegate();
    }
    else if(type == delegateName::dateTime)
    {
        return new cgDateTimeDelegate();
    }
    return 0;
}
