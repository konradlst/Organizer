#ifndef CGDELEGATEMANAGER_H
#define CGDELEGATEMANAGER_H

#include <QList>

class QString;
class QStringList;
class QAbstractItemDelegate;
class QDomElement;

namespace cgDelegateManager
{
    QList<QAbstractItemDelegate *> *getDelegateList(const QString &tableName);
    bool loadScheme(QDomElement &scheme);
    QAbstractItemDelegate *createDelegate(QStringList &list);
};

#endif // CGDELEGATEMANAGER_H
