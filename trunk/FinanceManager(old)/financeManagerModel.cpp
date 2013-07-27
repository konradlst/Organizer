#include "financeManagerModel.h"

FinanceManagerModel::FinanceManagerModel(QWidget *parent) :
    QWidget(parent),
    m_accounts(new Accounts),
    m_transactions(new ListOfTransaction)
{
    init();
}

void FinanceManagerModel::init()
{
    m_accounts->insert("cash",new Account);
    for(int i = 1; i < 6; i++)
        m_accounts->insert(QString("card%1").arg(i), new Account);
    for(int i = 1; i < 3; i++)
        m_accounts->insert(QString("deposit%1").arg(i), new Account);
    //end init account

    Transaction *trans = new Transaction;
    trans->comment = QString("simple transaction");
    trans->dateTime = QDateTime::currentDateTime();
    trans->from = QString("Cash");
    trans->to = QString("out");
    trans->type = Outcome;
    trans->value = 18;
    m_transactions->append(trans);

    Transaction *trans1 = new Transaction;
    trans1->comment = QString("");
    trans1->dateTime = QDateTime::currentDateTime();
    trans1->from = QString("card1");
    trans1->to = QString("card2");
    trans1->type = Remittance;
    trans1->value = 500;
    m_transactions->append(trans1);

    Transaction *trans2 = new Transaction;
    trans2->comment = QString("avans");
    trans2->dateTime = QDateTime::currentDateTime();
    trans2->from = QString("in");
    trans2->to = QString("card1");
    trans2->type = Income;
    trans2->value = 20000;
    m_transactions->append(trans2);

    Transaction *trans3 = new Transaction;
    trans3->comment = QString("buy t-short");
    trans3->dateTime = QDateTime::currentDateTime();
    trans3->from = QString("card2");
    trans3->to = QString("out");
    trans3->type = Outcome;
    trans3->    value = 1500;
    m_transactions->append(trans3);

    //end init transaction
}
