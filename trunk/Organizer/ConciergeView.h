#ifndef CONCIERGEVIEW_H
#define CONCIERGEVIEW_H

#include <QMainWindow>

namespace Ui {
class ConciergeView;
}

class ConciergeView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConciergeView(QWidget *parent = 0);
    ~ConciergeView();

private:
    Ui::ConciergeView *ui;

private:
    void createInterface();
};

#endif // CONCIERGEVIEW2_H
