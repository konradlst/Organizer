#include <QPushButton>
#include <QDate>
#include <QDebug>
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
    // Create gialog.
    // type: Holiday\Task
    // frequency: every___Day\every___Week\every___Mounth\every___Year
    // description: ____
    // price: ___
    // deadline: __day\__date\__week\__mouth\__year
    // Ok & Cancel
    Duration d = Duration(QDate::currentDate().day(), DurationType(m_calendars->currentIndex()));
    createDialog(Holiday, d, QString(), 0, d);
}

void CgCalendarView::addTask()
{
    Duration d = Duration(QDate::currentDate().day(), DurationType(m_calendars->currentIndex()));
    createDialog(Task, d, QString(), 0, d);
}

void CgCalendarView::createDialog(TaskType type, CgCalendarView::Duration frequency,
                                  QString description, double price,
                                  CgCalendarView::Duration deadline)
{
    //FIXME:
    qDebug() << type << frequency << description << price << deadline;
}
