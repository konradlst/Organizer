#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include "logger.h"

namespace Error
{
namespace
{
const QString Title = QObject::trUtf8("Error");
const QString MsgIncorrectFormat = QObject::trUtf8("This file has incorrect format!");
const QString MsgIncorrectVersion = QObject::trUtf8("This file has incorrect version!");
const QString MsgCannotOpenFile = QObject::trUtf8("Can not open this file for read or "
                                                  "this file has not a text format!");

const QString LogInvalidFile = QObject::trUtf8("Invalid file format.");
const QString LogInvalidFileFormat = QObject::trUtf8("Invalid file format: %1 in line: %2 in column: %3.");
const QString LogIncorrectMainNode = QObject::trUtf8("Incorrect main node. Current: %1, Need: %2");
const QString LogIncorrectVersion = QObject::trUtf8("Incorrect version. Current: %1, Need: %2");
}

bool incorrectFormat(const QString error, const int errorLine,
                            const int errorColumn)
{
    QMessageBox::warning(new QWidget(), Title, MsgIncorrectFormat);
    if (error.isEmpty() && !errorLine && !errorColumn)
        Log::error(LogInvalidFile);
    else
        Log::error(LogInvalidFileFormat.arg(error).arg(errorLine).arg(errorColumn));
    return 0;
}

bool incorrectMainNode(const QString current, const QString need)
{
    QMessageBox::warning(new QWidget(), Title, MsgIncorrectFormat);
    Log::error(LogIncorrectMainNode.arg(current).arg(need));
    return 0;
}

bool incorrectVersion(const QString current, const QString need)
{
    QMessageBox::warning(new QWidget(), Title, MsgIncorrectVersion);
    Log::error(LogIncorrectVersion.arg(current).arg(need));
    return 0;
}

bool cannotOpen()
{
    QMessageBox::warning(new QWidget(), Title, MsgCannotOpenFile);
    Log::error(MsgCannotOpenFile);
    return 0;
}

}

namespace Log
{
namespace
{
enum LogLevel {ErrorLevel, WarningLevel, InfoLevel, DebugLevel };
const LogLevel CurrentLevel = DebugLevel;
const QString DateTimeFormat = "";
const QString Debug = QObject::trUtf8("Debug : ");
const QString Info = QObject::trUtf8("Info : ");
const QString Warning = QObject::trUtf8("Warning : ");
const QString Error = QObject::trUtf8("Error : ");
}

void debug(const QString &lastError)
{
    if (CurrentLevel >= DebugLevel)
        qDebug() << QDateTime::currentDateTime().toString(DateTimeFormat) + Debug + lastError;
}

void info(const QString &lastError)
{
    if (CurrentLevel >= InfoLevel)
        qDebug() << QDateTime::currentDateTime().toString(DateTimeFormat) + Info + lastError;
}

void warning(const QString &lastError)
{
    if (CurrentLevel >= WarningLevel)
        qDebug() << QDateTime::currentDateTime().toString(DateTimeFormat) + Warning + lastError;
}

void error(const QString &lastError)
{
    if (CurrentLevel >= ErrorLevel)
        qDebug() << QDateTime::currentDateTime().toString(DateTimeFormat) + Error + lastError;
}
}
