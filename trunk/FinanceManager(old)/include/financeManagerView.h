#ifndef FINANCEMANAGERVIEW_H
#define FINANCEMANAGERVIEW_H

#include <QMainWindow>

namespace Ui {
class FinanceManagerView;
}

class FinanceManagerView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FinanceManagerView(QWidget *parent = 0);
    ~FinanceManagerView();
    
private:
    Ui::FinanceManagerView *ui;
};

#endif // FINANCEMANAGERVIEW_H
