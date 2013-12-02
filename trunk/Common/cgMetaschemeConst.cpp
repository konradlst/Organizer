#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include "logger.h"
#include "cgMetaschemeConst.h"

bool Scheme::loadScheme(QDomElement &scheme, const QString &path)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return Error::cannotOpen();

    QString error;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(&file, &error, &errorLine, &errorColumn))
        return Error::incorrectFormat(error, errorLine, errorColumn);

    file.close();

    scheme = doc.documentElement();
    if (scheme.nodeName() != Scheme::tagRoot)
        return Error::incorrectMainNode(scheme.nodeName(), Scheme::tagRoot);

    if (scheme.attribute(Scheme::attrVersion) != Scheme::Version)
        return Error::incorrectVersion(scheme.attribute(Scheme::attrVersion), Scheme::Version);

    return true;
}
