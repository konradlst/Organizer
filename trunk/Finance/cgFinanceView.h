#ifndef CGFINANCEVIEW_H
#define CGFINANCEVIEW_H

#include <QMainWindow>

namespace Ui {
class cgFinanceView;
}

class cgFinanceView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit cgFinanceView(QWidget *parent = 0);
    ~cgFinanceView();
    
private:
    Ui::cgFinanceView *ui;

    void createAccountTab();
};

#endif // CGFINANCEVIEW_H
