#ifndef CGCALENDARVIEW_H
#define CGCALENDARVIEW_H

#include <QMainWindow>

class cgCalendarWidget;

enum TaskType { Task = 0, Holiday };
enum DurationType { Day = 0, Week, Mounth, Year };

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
    typedef QPair<int, DurationType> Duration;
    void createDialog(TaskType type, Duration frequency, QString description, double price, Duration deadline);

private:
    QTabWidget *m_calendars;
    QVector<cgCalendarWidget*> *m_tabs;
};

#endif // CGCALENDARVIEW_H
