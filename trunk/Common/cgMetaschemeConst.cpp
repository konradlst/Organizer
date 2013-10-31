#include "cgMetaschemeConst.h"
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include "cgErrorMessage.h"

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
        ERROR_INCORRECT_FORMAT;
        qDebug() << QString("Invalid file format: %1 in line: %2 in column: %3")
                    .arg(error)
                    .arg(errorLine)
                    .arg(errorColumn);
        return false;
    }
    file.close();

    scheme = doc.documentElement();
    if (scheme.nodeName() != Scheme::tagRoot)
    {
        ERROR_INCORRECT_FORMAT;
        qDebug() << QString("Incorrect main node. Current: %1, Need: %2")
                    .arg(scheme.nodeName())
                    .arg(Scheme::tagRoot);
        return false;
    }
    if(scheme.attribute(Scheme::attrVersion) != Scheme::VERSION)
    {
        ERROR_INCORRECT_VERSION;
        qDebug() << QString("Incorrect version. Current: %1, Need: %2")
                    .arg(scheme.attribute(Scheme::attrVersion))
                    .arg(Scheme::VERSION);
        return false;
    }
    return true;
}
