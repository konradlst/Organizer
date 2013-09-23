#include <QCalendarWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QGroupBox>
#include "cgCalendarView.h"

CgCalendarView::CgCalendarView(QWidget *parent)
    : QMainWindow(parent),
      m_calendars(new QTabWidget)
{
    setCentralWidget(m_calendars);

    QCalendarWidget *mounthCalendar = new QCalendarWidget();
    mounthCalendar->setSelectedDate(QDate::currentDate());
    mounthCalendar->setFirstDayOfWeek(Qt::Monday);

    QTableWidget *weekTable = new QTableWidget(24, 7);
    QTableWidget *threeDayTable = new QTableWidget(24, 3);
    QTableWidget *todayTable = new QTableWidget(24, 1);

    addTab(mounthCalendar, "Month");
    addTab(weekTable, "Week");
    addTab(threeDayTable, "Three day");
    addTab(todayTable, "Today");
}

void CgCalendarView::addTab(QWidget *calendar, const QString &name, int position)
{
    QPushButton *pbToday = new QPushButton("Today");
    QPushButton *pbAddHoliday = new QPushButton("Add Holiday");
    QPushButton *pbAddTask = new QPushButton("Add Task");

    QHBoxLayout *hLayButton = new QHBoxLayout();
    hLayButton->addWidget(pbToday);
    hLayButton->addWidget(pbAddHoliday);
    hLayButton->addWidget(pbAddTask);

    QGroupBox *gbHolidays = new QGroupBox("Holidays");
    QGroupBox *gbTasks = new QGroupBox("Tasks");

    QVBoxLayout *vLayTasks = new QVBoxLayout();
    vLayTasks->addWidget(gbHolidays);
    vLayTasks->addWidget(gbTasks);

    QVBoxLayout *vLayMounth = new QVBoxLayout();
    vLayMounth->addWidget(calendar);
    vLayMounth->addLayout(hLayButton);

    QHBoxLayout *hLayMounth = new QHBoxLayout();
    hLayMounth->addLayout(vLayMounth);
    hLayMounth->addLayout(vLayTasks);

    QWidget *tab = new QWidget;
    tab->setLayout(hLayMounth);
    if (position == -1)
        position = m_calendars->count();

    m_calendars->insertTab(position, tab, name);
}
