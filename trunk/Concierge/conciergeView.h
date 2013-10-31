#ifndef CONCIERGEVIEW_H
#define CONCIERGEVIEW_H

#include <QMainWindow>

namespace Ui
{
class ConciergeView;
}

class ConciergeView : public QMainWindow
{
    Q_OBJECT
public:
    explicit ConciergeView(QWidget *parent = 0);
    ~ConciergeView();

private slots:
    void addTransaction();
    void addTimeRecord();
    void addDealRecord();

private:
    Ui::ConciergeView *ui;

    void createInterface();
};

#endif // CONCIERGEVIEW_H
