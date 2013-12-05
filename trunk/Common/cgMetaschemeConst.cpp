#include <QDomDocument>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include "logger.h"
#include "cgMetaschemeConst.h"

namespace
{
const QString DefaultMetaScheme = "./metascheme.xml";
}

bool Scheme::loadScheme(QDomElement &scheme, const QString &path)
{
    QDomDocument doc;
    QFile file((path.isEmpty()) ? DefaultMetaScheme : path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return Error::cannotOpen();

    QString error;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(&file, &error, &errorLine, &errorColumn))
        return Error::incorrectFormat(error, errorLine, errorColumn);

    file.close();

    scheme = doc.documentElement();
    if (scheme.nodeName() != SchemeTag::Root)
        return Error::incorrectMainNode(scheme.nodeName(), SchemeTag::Root);

    if (scheme.attribute(SchemeAttr::Version) != qApp->applicationVersion())
        return Error::incorrectVersion(scheme.attribute(SchemeAttr::Version), qApp->applicationVersion());

    return true;
}
