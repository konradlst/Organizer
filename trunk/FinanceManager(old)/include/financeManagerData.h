#ifndef FINANCEMANAGERDATA_H
#define FINANCEMANAGERDATA_H

#include <QHash>
#include <QVector>
#include <QDateTime>

enum AccountType
{
    DebitCard = 0,
    CreditCard,
    Deposit,
    Credit,
    Cash
};

typedef QString AccountName;

struct Account
{
    qint16 id;
    AccountName name;
    qint64 maxValue;
    qint64 value;
    AccountType type;
};

enum TransactionType
{
    Income = 0,
    Outcome,
    Remittance
};

struct Transaction
{
    QDateTime dateTime;
    TransactionType type;
    qint64 value;
    AccountName from;
    AccountName to;
    QString comment;
};

typedef QVector<Transaction *> ListOfTransaction;
typedef QHash<AccountName, Account *> Accounts;


#endif // FINANCEMANAGERDATA_H
