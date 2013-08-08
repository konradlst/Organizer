#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QObject>
#include <QMessageBox>

namespace Error
{
const QString title = QObject::trUtf8("Error");
const QString incorrectFormat = QObject::trUtf8("This file has incorrect format!");
const QString incorrectVersion = QObject::trUtf8("This file has incorrect version!");
const QString cannotOpen = QObject::trUtf8("Can not open this file for read or "
                                           "this file has not a text format!");
}

#define ERROR_INCORRECT_FORMAT QMessageBox::warning(new QWidget(), Error::title,\
                                                    Error::incorrectFormat)
#define ERROR_INCORRECT_VERSION QMessageBox::warning(new QWidget(), Error::title,\
                                                     Error::incorrectVersion)
#define ERROR_CANNOT_OPEN QMessageBox::warning(new QWidget(), Error::title,\
                                               Error::cannotOpen)

#endif // ERRORMESSAGE_H
