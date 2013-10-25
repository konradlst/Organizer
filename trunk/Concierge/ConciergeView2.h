#ifndef CONCIERGEVIEW2_H
#define CONCIERGEVIEW2_H

#include <QMainWindow>

namespace Ui {
class ConciergeView2;
}

class ConciergeView2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConciergeView2(QWidget *parent = 0);
    ~ConciergeView2();

private:
    Ui::ConciergeView2 *ui;
};

#endif // CONCIERGEVIEW2_H
