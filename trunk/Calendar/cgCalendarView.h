#ifndef CGCALENDARVIEW_H
#define CGCALENDARVIEW_H

#include <QMainWindow>

class CgCalendarView : public QMainWindow
{
    Q_OBJECT
public:
    explicit CgCalendarView(QWidget *parent = 0);

private:
    QTabWidget *m_calendars;

private:
    void addTab(QWidget *calendar, const QString &name, int position = -1);
};

#endif // CGCALENDARVIEW_H
