#include <QPushButton>
#include <QDate>
#include "cgCalendarView.h"
#include "cgCalendarWidget.h"
#include "cgTaskDialog.h"

CgCalendarView::CgCalendarView(QWidget *parent)
    : QMainWindow(parent),
      m_calendars(new QTabWidget),
      m_tabs(new QVector<cgCalendarWidget*>()),
      m_taskDialog(new cgTaskDialog())
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
    Calendar::Duration d(QDate::currentDate().day(), Calendar::DurationType(m_calendars->currentIndex()));
    createDialog(Calendar::Holiday, d, QString("add new Holiday"), 500, d);
}

void CgCalendarView::addTask()
{
    Calendar::Duration d(QDate::currentDate().day(), Calendar::DurationType(m_calendars->currentIndex()));
    createDialog(Calendar::Task, d, QString("add new Task"), 0, d);
}

void CgCalendarView::createDialog(Calendar::TaskType type,
                                  Calendar::Duration frequency,
                                  QString description,
                                  double price,
                                  Calendar::Duration deadline)
{
    m_taskDialog->init(type, frequency, description, price, deadline);
    m_taskDialog->show();
}
