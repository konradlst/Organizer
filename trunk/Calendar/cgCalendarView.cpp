#include <QPushButton>
#include <QDate>
#include "cgCalendarView.h"
#include "cgCalendarWidget.h"

CgCalendarView::CgCalendarView(QWidget *parent)
    : QMainWindow(parent),
      m_calendars(new QTabWidget),
      m_tabs(new QVector<cgCalendarWidget*>())
{
    setCentralWidget(m_calendars);

    for (int i = 0; i < 4; ++i)
    {
        m_tabs->append(new cgCalendarWidget(cgCalendarWidget::TypeCalendar(i)));
        m_calendars->addTab(m_tabs->at(i), m_tabs->at(i)->name());
        connect(m_tabs->at(i)->pbSetToday(),   SIGNAL(clicked()), this, SLOT(setToday()));
        connect(m_tabs->at(i)->pbAddHoliday(), SIGNAL(clicked()), this, SLOT(addHoliday()));
        connect(m_tabs->at(i)->pbAddTask(),    SIGNAL(clicked()), this, SLOT(addTask()));
    }
    setMinimumSize(870, 500);
}

void CgCalendarView::setToday()
{
    m_tabs->at(m_calendars->currentIndex())->setDate(QDate::currentDate());
}

void CgCalendarView::addHoliday()
{
    //create dialog create new task(type=holiday)
}

void CgCalendarView::addTask()
{
    //create dialog create new task(type = task with current duration, duration depends on current calendar)
}
