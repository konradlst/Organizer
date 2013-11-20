#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "dateView.h"

namespace
{
const int defaultWidth = 25;
const QChar Separator = ';';
const QString Title = QObject::trUtf8("Date View");
const QString ChooseDate = QObject::trUtf8("Choose date");
const QString CurrentDay = QObject::trUtf8("Current day");
const QString DateFormat = QObject::trUtf8("Week %1, ddd, dd MMMM(M) yyyy");
const QStringList IntervalsTitle = QObject::trUtf8("Day;Week;Mounth;Year").split(Separator);
}

DateView::DateView(QWidget *parent)
    : QWidget(parent),
      m_interval(Day),
      m_date(new QLabel),
      m_day(new QPushButton(IntervalsTitle[Day][0])),
      m_week(new QPushButton(IntervalsTitle[Week][0])),
      m_mounth(new QPushButton(IntervalsTitle[Mounth][0])),
      m_year(new QPushButton(IntervalsTitle[Year][0])),
      m_calendar(new QPushButton(QChar(9660))),
      m_calendarWidget(new QCalendarWidget(m_calendar))
{
    setWindowTitle(Title);

    m_day->setMaximumWidth(defaultWidth);
    m_week->setMaximumWidth(defaultWidth);
    m_mounth->setMaximumWidth(defaultWidth);
    m_year->setMaximumWidth(defaultWidth);
    m_calendar->setMaximumWidth(defaultWidth);

    m_day->setCheckable(true);
    m_week->setCheckable(true);
    m_mounth->setCheckable(true);
    m_year->setCheckable(true);
    m_day->setChecked(true);

    m_day->setToolTip(IntervalsTitle[Day]);
    m_week->setToolTip(IntervalsTitle[Week]);
    m_mounth->setToolTip(IntervalsTitle[Mounth]);
    m_year->setToolTip(IntervalsTitle[Year]);
    m_date->setToolTip(CurrentDay);
    m_calendar->setToolTip(ChooseDate);

    m_day->setFlat(true);
    m_week->setFlat(true);
    m_mounth->setFlat(true);
    m_year->setFlat(true);
    m_calendar->setFlat(true);

    m_date->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_date->setAlignment(Qt::AlignCenter);
    dateChanged(QDate::currentDate());

    m_calendarWidget->setWindowFlags(Qt::Popup);

    QHBoxLayout *lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);
    lay->addWidget(m_day);
    lay->addWidget(m_week);
    lay->addWidget(m_mounth);
    lay->addWidget(m_year);
    lay->addWidget(m_date);
    lay->addWidget(m_calendar);
    setLayout(lay);

    connect(m_day, SIGNAL(clicked(bool)), SLOT(intervalChanged(bool)));
    connect(m_week, SIGNAL(clicked(bool)), SLOT(intervalChanged(bool)));
    connect(m_mounth, SIGNAL(clicked(bool)), SLOT(intervalChanged(bool)));
    connect(m_year, SIGNAL(clicked(bool)), SLOT(intervalChanged(bool)));
    connect(m_calendar, SIGNAL(clicked()), SLOT(showCalendarPopup()));
    connect(m_calendarWidget, SIGNAL(clicked(QDate)), SLOT(dateChanged(QDate)));
}

void DateView::calendarPopup(bool flag)
{
    m_calendar->setVisible(flag);
}

void DateView::setDate(const QDate &date)
{
    dateChanged(date);
}

void DateView::showCalendarPopup()
{
    m_calendarWidget->show();
}

void DateView::intervalChanged(bool checked)
{
    if (!checked)
        return;

    if(sender() == m_day)
        m_interval = Day;
    else if (sender() == m_week)
        m_interval = Week;
    else if (sender() == m_mounth)
        m_interval = Mounth;
    else if (sender() == m_year)
        m_interval = Year;

    m_day->setChecked(sender() == m_day);
    m_week->setChecked(sender() == m_week);
    m_mounth->setChecked(sender() == m_mounth);
    m_year->setChecked(sender() == m_year);

    emit intervalChange(m_interval);
}

void DateView::dateChanged(const QDate &date)
{
    m_date->setText(date.toString(DateFormat.arg(date.weekNumber())));
    m_calendarWidget->hide();
}
