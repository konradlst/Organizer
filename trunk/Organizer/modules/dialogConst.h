#ifndef DIALOGCONST_H
#define DIALOGCONST_H

#include <QObject>

class QChar;
class QString;
class QStringList;

namespace
{
const QChar Separator = ';';
const QString TimeFormat = "hh:mm";
const QString DateFormat = "dd.MM.yyyy";

const QString TimeTitle = QObject::trUtf8("Time Dialog");
const QString DealTitle = QObject::trUtf8("Deal Dialog");
const QString AccountTitle = QObject::trUtf8("Account Dialog");
const QString ContactTitle = QObject::trUtf8("Contact Dialog");
const QString TransactionTitle = QObject::trUtf8("Transaction Dialog");

const QString LblOk = QObject::trUtf8("Ok");
const QString LblType = QObject::trUtf8("Type :");
const QString LblDuration = QObject::trUtf8("Duration :");
const QString LblStarted = QObject::trUtf8("Started :");
const QString LblStoped = QObject::trUtf8("Stoped :");
const QString LblDescription = QObject::trUtf8("Description :");
const QString LblDate = QObject::trUtf8("Date :");
const QString LblDeadLine = QObject::trUtf8("DeadLine :");
const QString LblMoney = QObject::trUtf8("Money :");
const QString LblHumans = QObject::trUtf8("Humans :");
const QString LblCreated = QObject::trUtf8("Created :");
const QString LblName = QObject::trUtf8("Name :");
const QString LblValue = QObject::trUtf8("Value :");
const QString LblTotal = QObject::trUtf8("Total :");

const QString AccountNamePlaceholder = QObject::trUtf8("account name");
const QString TransactionNamePlaceholder = QObject::trUtf8("short transaction comment");
const QString HumansPlaceholder = QObject::trUtf8("Associated users separated by commas");

const QStringList DealTypes = QObject::trUtf8("Deal;Holiday;Task").split(Separator);
const QStringList AccountTypes = QObject::trUtf8("Cash;Card;Account;Deposit;Credit").split(Separator);
const QStringList TransactionTypes = QObject::trUtf8("In;Out;Transfer").split(Separator);
const QStringList TimeTypes = QObject::trUtf8("Sleep;Work;Study;Travel;Drive;Sport").split(Separator);
}

#endif // DIALOGCONST_H
