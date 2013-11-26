#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include "cgErrorMessage.h"
#include "cgMetaschemeConst.h"

bool Scheme::loadScheme(QDomElement &scheme, const QString &path)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ERROR_CANNOT_OPEN;
        return false;
    }
    QString error;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(&file, &error, &errorLine, &errorColumn))
    {
        ERROR_INCORRECT_FORMAT(error, errorLine, errorColumn);
        return false;
    }
    file.close();

    scheme = doc.documentElement();
    if (scheme.nodeName() != Scheme::tagRoot)
    {
        ERROR_INCORRECT_MAIN_NODE(scheme.nodeName(), Scheme::tagRoot);
        return false;
    }
    if (scheme.attribute(Scheme::attrVersion) != Scheme::Version)
    {
        ERROR_INCORRECT_VERSION(scheme.attribute(Scheme::attrVersion), Scheme::Version);
        return false;
    }
    return true;
}
