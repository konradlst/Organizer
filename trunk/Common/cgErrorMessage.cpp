#include <QMessageBox>
#include <QDebug>
#include "cgErrorMessage.h"


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
        qDebug() << LogInvalidFile;
    else
        qDebug() << LogInvalidFileFormat.arg(error).arg(errorLine).arg(errorColumn);
    return 0;
}

bool incorrectMainNode(const QString current, const QString need)
{
    QMessageBox::warning(new QWidget(), Title, MsgIncorrectFormat);
    qDebug() << LogIncorrectMainNode.arg(current).arg(need);
    return 0;
}

bool incorrectVersion(const QString current, const QString need)
{
    QMessageBox::warning(new QWidget(), Title, MsgIncorrectVersion);
    qDebug() << LogIncorrectVersion.arg(current).arg(need);
    return 0;
}

bool cannotOpen()
{
    QMessageBox::warning(new QWidget(), Title, MsgCannotOpenFile);
    return 0;
}

}
