#ifndef CGFINANCEVIEW_H
#define CGFINANCEVIEW_H

#include <QWidget>

class QDoubleSpinBox;
class QFrame;
class QProgressBar;
class QDateEdit;

class cgFinanceView : public QWidget
{
    Q_OBJECT
public:
    explicit cgFinanceView(QWidget *parent = 0);
    QDoubleSpinBox *getDoubleSpinBox();
    QFrame *getLine();
    QProgressBar *getProgressBar();
    QDateEdit *getDateWidget();
};

#endif // CGFINANCEVIEW_H
