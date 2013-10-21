#ifndef CGFINANCEVIEW_H
#define CGFINANCEVIEW_H

#include <QMainWindow>

namespace Ui
{
class cgFinanceView;
}
class cgAccountList;
class cgTransactionList;

class cgFinanceView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit cgFinanceView(QWidget *parent = 0);
    ~cgFinanceView();
    bool addTransaction();

private slots:
    void chooseDb();

private:
    Ui::cgFinanceView *ui;
    cgAccountList *m_accounts;
    cgTransactionList *m_transactions;

    void createAccountTab();
};

#endif // CGFINANCEVIEW_H
