#ifndef FINANCEMANAGERMODEL_H
#define FINANCEMANAGERMODEL_H

#include <QWidget>
#include "financeManagerData.h"

class FinanceManagerModel : public QWidget
{
    Q_OBJECT
public:
    explicit FinanceManagerModel(QWidget *parent = 0);
    void init();

private:
    Accounts *m_accounts;
    ListOfTransaction *m_transactions;
};

#endif // FINANCEMANAGERMODEL_H
