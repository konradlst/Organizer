#ifndef CGCALENDARVIEW_H
#define CGCALENDARVIEW_H

#include <QMainWindow>
#include "cgCalendarConst.h"

class cgCalendarWidget;
class cgTaskDialog;

class CgCalendarView : public QMainWindow
{
    Q_OBJECT
public:
    explicit CgCalendarView(QWidget *parent = 0);

private slots:
    void setToday();
    void addHoliday();
    void addTask();

private:
    void createDialog(Calendar::TaskType type, Calendar::Duration frequency,
                      QString description, double price, Calendar::Duration deadline);

private:
    QTabWidget *m_calendars;
    QVector<cgCalendarWidget*> *m_tabs;
    cgTaskDialog *m_taskDialog;
};

#endif // CGCALENDARVIEW_H
