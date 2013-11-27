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

namespace Log
{
void debug(const QString &lastError);
void info(const QString &lastError);
void warning(const QString &lastError);
void error(const QString &lastError);
}

#endif // ERRORMESSAGE_H
