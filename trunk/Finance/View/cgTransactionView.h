#ifndef CGTRANSACTIONVIEW_H
#define CGTRANSACTIONVIEW_H

#include <QDialog>

namespace Ui {
class cgTransactionView;
}

class cgTransactionView : public QDialog
{
    Q_OBJECT
    
public:
    explicit cgTransactionView(QWidget *parent = 0);
    ~cgTransactionView();
    
private:
    Ui::cgTransactionView *ui;
};

#endif // CGTRANSACTIONVIEW_H
