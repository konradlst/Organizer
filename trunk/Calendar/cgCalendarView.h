#ifndef CGCALENDARVIEW_H
#define CGCALENDARVIEW_H

#include <QMainWindow>

namespace Ui {
class CgCalendarView;
}

class CgCalendarView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CgCalendarView(QWidget *parent = 0);
    ~CgCalendarView();

private:
    Ui::CgCalendarView *ui;
};

#endif // CGCALENDARVIEW_H
