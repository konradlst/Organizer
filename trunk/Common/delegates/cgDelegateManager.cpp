#include "cgDelegateManager.h"
#include <QDomElement>
#include "cgComboBoxDelegate.h"
#include "cgCheckBoxDelegate.h"
#include "cgSpinBoxDelegate.h"
#include "cgDateDelegate.h"
#include "cgDateTimeDelegate.h"
#include "cgTimeDelegate.h"
#include "cgLineEditDelegate.h"
#include "cgMetaschemeConst.h"

QList<QAbstractItemDelegate *> *cgDelegateManager::getDelegateList(const QString &tableName)
{
    QList<QAbstractItemDelegate *> *list = new QList<QAbstractItemDelegate*>();

    QDomElement scheme;
    if(!Scheme::loadScheme(scheme))
        return list;

    QDomNode tables = scheme.firstChildElement(Scheme::tagTables);
    if(tables.isNull())
        return list;

    QDomNode table = tables.firstChildElement(Scheme::tagTable);
    if(table.isNull())
        return list;

    while (table.toElement().attribute(Scheme::attrName) != tableName)
        table = table.nextSibling();

    QDomElement delegates = scheme.firstChildElement(Scheme::tagDelegates);
    QDomNode field = table.firstChild();
    while(!field.isNull())
    {
        QString delegateName = field.toElement().attribute(Scheme::attrDelegate);
        if(delegateName.isNull())
        {
            list->append(0);
            field = field.nextSibling();
            continue;
        }
        QDomNode delegateNode = delegates.firstChildElement(Scheme::tagDelegate);
        while (delegateNode.toElement().attribute(Scheme::attrName)!= delegateName)
            delegateNode = delegateNode.nextSibling();

        QStringList lst;
        QDomElement delegate = delegateNode.toElement();
        lst << delegate.attribute(Scheme::attrType);

        int i = 1;
        while (delegate.hasAttribute(Scheme::attrParam + QString::number(i)))
            lst << delegate.attribute(Scheme::attrParam + QString::number(i++));
        list->append(createDelegate(lst));
        field = field.nextSibling();
    }
    return list;
}

QAbstractItemDelegate *cgDelegateManager::createDelegate(const QStringList &list)
{
    QString type = list.at(0);
    if(type == delegateName::line)
    {
        return new cgLineEditDelegate(list.at(1).toInt(), list.at(2));
    }
    else if(type == delegateName::comboBox)
    {
        return new cgComboBoxDelegate(list.at(1).split(Scheme::SPLITTER),
                                      list.at(2).toInt());
    }
    else if(type == delegateName::spinBox)
    {
        return new cgSpinBoxDelegate(list.at(1).toInt());
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
