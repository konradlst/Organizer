#include "cgDelegateManager.h"
#include <QDomDocument>
#include <QFile>
#include "cgComboBoxDelegate.h"
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
}

namespace
{
const QString metascheme("./metascheme.xml");
}

QList<QAbstractItemDelegate *> *cgDelegateManager::getDelegateList(const QString &tableName)
{
    QDomElement scheme;
    if(!loadScheme(scheme))
        return 0;
    QDomNode tablesNode = scheme.firstChildElement(Scheme::tagTables);
    QList<QAbstractItemDelegate *> *list = new QList<QAbstractItemDelegate *>();
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
