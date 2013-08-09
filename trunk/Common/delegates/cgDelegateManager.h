#ifndef CGDELEGATEMANAGER_H
#define CGDELEGATEMANAGER_H

class QString;
class QAbstractItemDelegate;
class QList<QAbstractItemDelegate *>;
class QDomElement;

namespace cgDelegateManager
{
    QList<QAbstractItemDelegate *> *getDelegateList(const QString &tableName);
    bool loadScheme(QDomElement &scheme);
};

#endif // CGDELEGATEMANAGER_H
