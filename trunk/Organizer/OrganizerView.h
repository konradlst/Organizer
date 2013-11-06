#ifndef CONCIERGEVIEW_H
#define CONCIERGEVIEW_H

#include <QMainWindow>

namespace Ui {
class OrganizerView;
}

class OrganizerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrganizerView(QWidget *parent = 0);
    ~OrganizerView();

private slots:
    void setToday();

private:
    Ui::OrganizerView *ui;

private:
    void createInterface();
    void initTimeList(QStringList &list);
};

#endif // CONCIERGEVIEW2_H
