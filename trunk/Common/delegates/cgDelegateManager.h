#ifndef CGDELEGATEMANAGER_H
#define CGDELEGATEMANAGER_H

#include <QList>

class QString;
class QStringList;
class QAbstractItemDelegate;

namespace cgDelegateManager
{
    QList<QAbstractItemDelegate *> *getDelegateList(const QString &tableName);
    QAbstractItemDelegate *createDelegate(QStringList &list);
};

#endif // CGDELEGATEMANAGER_H
