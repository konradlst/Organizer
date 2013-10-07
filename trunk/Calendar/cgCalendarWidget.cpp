#include <QCalendarWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QBoxLayout>
#include <QGroupBox>
#include "cgCalendarWidget.h"

cgCalendarWidget::cgCalendarWidget(const TypeCalendar type,
                                   bool shTasks,
                                   bool shSysButton,
                                   QWidget *parent)
    : QWidget(parent),
      m_calendar(0),
      m_holidays(new QGroupBox(QObject::trUtf8("Holidays"))),
      m_tasks(new QGroupBox(QObject::trUtf8("Tasks"))),
      m_setToday(new QPushButton(QObject::trUtf8("Today"))),
      m_addHoliday(new QPushButton(QObject::trUtf8("Add Holiday"))),
      m_addTask(new QPushButton(QObject::trUtf8("Add Task"))),
      m_type(type)
{
    createCalendarWidget();
    createInterface();
    showSystemButton(shSysButton);
    showTasks(shTasks);
}

void cgCalendarWidget::showTasks(bool status)
{
    m_tasks->setVisible(status);
    m_holidays->setVisible(status);
}

void cgCalendarWidget::showSystemButton(bool status)
{
    m_setToday->setVisible(status);
    m_addHoliday->setVisible(status);
    m_addTask->setVisible(status);
}

void cgCalendarWidget::setDate(const QDate &date)
{
    switch (m_type)
    {
    case Mounth:
        qobject_cast<QCalendarWidget*>(m_calendar)->setSelectedDate(date);
        break;
    case Week:
        qobject_cast<QTableWidget*>(m_calendar)->setCurrentCell(QTime::currentTime().hour(),
                                                                QDate::currentDate().dayOfWeek()-1);
        break;
    case ThreeDay:
        qobject_cast<QTableWidget*>(m_calendar)->setCurrentCell(QTime::currentTime().hour(), 1);
        break;
    case Today:
        qobject_cast<QTableWidget*>(m_calendar)->setCurrentCell(QTime::currentTime().hour(), 0);
    }
}

QPushButton *cgCalendarWidget::pbSetToday() const
{
    return m_setToday;
}

QPushButton *cgCalendarWidget::pbAddHoliday() const
{
    return m_addHoliday;
}

QPushButton *cgCalendarWidget::pbAddTask() const
{
    return m_addTask;
}

QString cgCalendarWidget::name() const
{
    return m_name;
}

void cgCalendarWidget::createCalendarWidget()
{
    static const QChar Separator = ';';
    static const QStringList TodayName = QObject::trUtf8("Today").split(Separator);
    static const QStringList ThreeDayNames = QObject::trUtf8("Yesterday;Today;Tomorrow").split(Separator);
    static const QStringList DayOfWeek = QObject::trUtf8("Monday;Tuesday;Wednesday;Thursday;Friday;Saturday;Sunday").split(Separator);

    QStringList timeList;
    initTimeList(timeList);
    switch (m_type)
    {
        case Mounth:
        {
            QCalendarWidget *mounthCalendar = new QCalendarWidget;
            mounthCalendar->setSelectedDate(QDate::currentDate());
            mounthCalendar->setFirstDayOfWeek(Qt::Monday);
            m_calendar = mounthCalendar;
            m_name = QObject::trUtf8("Month");
        }
            break;
        case Week:
        {
            QTableWidget *weekCalendar = new QTableWidget(24, 7);
            weekCalendar->setVerticalHeaderLabels(timeList);
            weekCalendar->setHorizontalHeaderLabels(DayOfWeek);
            weekCalendar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            m_calendar = weekCalendar;
            m_name = QObject::trUtf8("Week");
        }
            break;
        case ThreeDay:
        {
            QTableWidget *threeDayCalendar = new QTableWidget(24, 3);
            threeDayCalendar->setVerticalHeaderLabels(timeList);
            threeDayCalendar->setHorizontalHeaderLabels(ThreeDayNames);
            threeDayCalendar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            m_calendar = threeDayCalendar;
            m_name = QObject::trUtf8("Three day");
        }
            break;
        case Today:
        {
            QTableWidget *todayCalendar = new QTableWidget(24, 1);
            todayCalendar->setVerticalHeaderLabels(timeList);
            todayCalendar->setHorizontalHeaderLabels(TodayName);
            todayCalendar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            m_calendar = todayCalendar;
            m_name = TodayName.at(0);
        }
    }
}

void cgCalendarWidget::createInterface()
{
    m_holidays->setMinimumWidth(250);
    m_tasks->setMinimumWidth(250);

    QHBoxLayout *hlButton = new QHBoxLayout();
    hlButton->addWidget(m_setToday);
    hlButton->addWidget(m_addHoliday);
    hlButton->addWidget(m_addTask);

    QVBoxLayout *vlTasks = new QVBoxLayout();
    vlTasks->addWidget(m_holidays);
    vlTasks->addWidget(m_tasks);

    QVBoxLayout *vlMain = new QVBoxLayout();
    vlMain->addWidget(m_calendar);
    vlMain->addLayout(hlButton);

    QHBoxLayout *hlMain = new QHBoxLayout();
    hlMain->addLayout(vlMain);
    hlMain->addLayout(vlTasks);

    setLayout(hlMain);
}

void cgCalendarWidget::initTimeList(QStringList &list)
{
    static const QString TimePattern = "hh:mm";

    QTime time(0, 0);
    for (int i = 0; i <= 24; ++i)
    {
        list << time.toString(TimePattern);
        time = time.addSecs(3600);
    }
}
