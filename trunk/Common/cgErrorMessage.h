#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QString>

namespace Error
{
bool incorrectFormat(const QString error = QString(), const int errorLine = 0,
                     const int errorColumn = 0);
bool incorrectMainNode(const QString current = QString(), const QString need = QString());
bool incorrectVersion(const QString current = QString(), const QString need = QString());
bool cannotOpen();
}

#endif // ERRORMESSAGE_H
