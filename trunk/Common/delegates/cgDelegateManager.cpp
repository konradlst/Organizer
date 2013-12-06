#include <QDomElement>
#include "cgComboBoxDelegate.h"
#include "cgCheckBoxDelegate.h"
#include "cgDateTimeDelegate.h"
#include "cgLineEditDelegate.h"
#include "cgMetaschemeConst.h"
#include "cgSpinBoxDelegate.h"
#include "cgDateDelegate.h"
#include "cgTimeDelegate.h"
#include "cgDelegateManager.h"

QList<QAbstractItemDelegate *> *cgDelegateManager::getDelegateList(const QString &tableName)
{
    QList<QAbstractItemDelegate *> *list = new QList<QAbstractItemDelegate*>();

    QDomElement scheme;
    if(!Scheme::load(scheme))
        return list;

    QDomNode tables = scheme.firstChildElement(SchemeTag::Tables);
    if(tables.isNull())
        return list;

    QDomNode table = tables.firstChildElement(SchemeTag::Table);
    if(table.isNull())
        return list;

    while (table.toElement().attribute(SchemeAttr::Name) != tableName)
        table = table.nextSibling();

    QDomElement delegates = scheme.firstChildElement(SchemeTag::Delegates);
    QDomNode field = table.firstChild();
    while(!field.isNull())
    {
        QString delegateName = field.toElement().attribute(SchemeAttr::Delegate);
        if(delegateName.isNull())
        {
            list->append(0);
            field = field.nextSibling();
            continue;
        }
        QDomNode delegateNode = delegates.firstChildElement(SchemeTag::Delegate);
        while (delegateNode.toElement().attribute(SchemeAttr::Name)!= delegateName)
            delegateNode = delegateNode.nextSibling();

        QStringList lst;
        QDomElement delegate = delegateNode.toElement();
        lst << delegate.attribute(SchemeAttr::Type);

        int i = 1;
        while (delegate.hasAttribute(SchemeAttr::Param + QString::number(i)))
            lst << delegate.attribute(SchemeAttr::Param + QString::number(i++));
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
        return new cgComboBoxDelegate(list.at(1).split(Scheme::Splitter),
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
