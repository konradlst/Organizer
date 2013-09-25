#ifndef CGCALENDARVIEW_H
#define CGCALENDARVIEW_H

#include <QMainWindow>

class cgCalendarWidget;

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
    QTabWidget *m_calendars;
    QVector<cgCalendarWidget*> *m_tabs;
};

#endif // CGCALENDARVIEW_H
