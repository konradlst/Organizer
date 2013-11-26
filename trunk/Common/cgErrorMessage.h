#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QMessageBox>
#include <QObject>
#include <QDebug>

namespace Error
{
const QString Title = QObject::trUtf8("Error");
const QString MsgIncorrectFormat = QObject::trUtf8("This file has incorrect format!");
const QString MsgIncorrectVersion = QObject::trUtf8("This file has incorrect version!");
const QString MsgCannotOpenFile = QObject::trUtf8("Can not open this file for read or "
                                                  "this file has not a text format!");

const QString LogInvalidFileFormat = QObject::trUtf8("Invalid file format: %1 in line: %2 in column: %3");
const QString LogIncorrectMainNode = QObject::trUtf8("Incorrect main node. Current: %1, Need: %2");
const QString LogIncorrectVersion = QObject::trUtf8("Incorrect version. Current: %1, Need: %2");
}

#define ERROR_INCORRECT_FORMAT(error, errorLine, errorColumn) \
    QMessageBox::warning(new QWidget(), Error::Title, Error::MsgIncorrectFormat); \
    qDebug() << Error::LogInvalidFileFormat.arg(error).arg(errorLine).arg(errorColumn)

#define ERROR_INCORRECT_MAIN_NODE(current, need) \
    QMessageBox::warning(new QWidget(), Error::Title, Error::MsgIncorrectFormat); \
    qDebug() << Error::LogIncorrectMainNode.arg(current).arg(need)

#define ERROR_INCORRECT_VERSION(current, need) \
    QMessageBox::warning(new QWidget(), Error::Title, Error::MsgIncorrectVersion); \
    qDebug() << Error::LogIncorrectVersion.arg(current).arg(need)

#define ERROR_CANNOT_OPEN \
    QMessageBox::warning(new QWidget(), Error::Title, Error::MsgCannotOpenFile)

#endif // ERRORMESSAGE_H
