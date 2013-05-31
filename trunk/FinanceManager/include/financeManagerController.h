#ifndef FINANCEMANAGERCONTROLLER_H
#define FINANCEMANAGERCONTROLLER_H

#include <QWidget>

class FinanceManagerView;
class FinanceManagerModel;

class FinanceManagerController : public QWidget
{
    Q_OBJECT
public:
    explicit FinanceManagerController(QWidget *parent = 0);
    
private:
    FinanceManagerView *m_view;
    FinanceManagerModel *m_model;
};

#endif // FINANCEMANAGERCONTROLLER_H
