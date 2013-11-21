#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QDate>
#include "yearCalendar.h"

namespace
{
const QChar Separator = ';';
const QStringList DayOfWeekShort = QObject::trUtf8("Mo;Tu;We;Th;Fr;Sa;Su").split(Separator);
const QStringList MonthNames = QObject::trUtf8("January;February;March;"
                                               "April;May;June;"
                                               "July;August;September;"
                                               "October;November;December").split(Separator);
const int InvalidPosition = -1;
const int SectionSize = 15;
const int MaxWeekInMonth = 6;
const int MonthOfYear = MonthNames.count();
const int DayOfWeek = DayOfWeekShort.count();
}

YearCalendar::YearCalendar(QWidget *parent)
    : QWidget(parent),
      m_months(new QVector<QTableWidget*>()),
      m_datesToPosition(new QMap<QDate, Position>())
{
    init();
}

void YearCalendar::setSelectedDate(const QDate &date)
{
    for (int i = 0; i < m_months->count(); ++i)
        m_months->at(i)->setCurrentCell(InvalidPosition, InvalidPosition);

    m_months->at(date.month() - 1)->setCurrentCell(m_datesToPosition->value(date).first,
                                                   m_datesToPosition->value(date).second);
    m_months->at(date.month())->setFocus();
}

void YearCalendar::init()
{
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    for (int i = 0; i < MonthOfYear; ++i)
    {
        QLabel *lblMounth = new QLabel(MonthNames.at(i));
        QFont font = lblMounth->font();
        font.setBold(true);
        lblMounth->setFont(font);
        lblMounth->setAlignment(Qt::AlignCenter);
        layout->addWidget(lblMounth, ((i / 3) * 2), i % 3);
        layout->addWidget(monthCalendar(i + 1), ((i / 3) * 2 + 1), i % 3);
    }

    setLayout(layout);
}

QTableWidget* YearCalendar::monthCalendar(const int monthNum)
{
    QDate date = QDate(QDate::currentDate().year(), monthNum, 1);
    const int Skip = date.dayOfWeek() - 1;
    const int TotalCell = Skip + date.daysInMonth();

    QTableWidget *month = new QTableWidget(DayOfWeek, MaxWeekInMonth);
//        month->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//4.8.4
    month->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//5.1.0
    month->horizontalHeader()->setMinimumSectionSize(SectionSize);
    month->horizontalHeader()->setDefaultSectionSize(SectionSize);
    month->horizontalHeader()->hide();
//    month->verticalHeader()->setResizeMode(QHeaderView::Stretch);//4.8.4
    month->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//5.1.0
    month->verticalHeader()->setMinimumSectionSize(SectionSize);
    month->verticalHeader()->setDefaultSectionSize(SectionSize);
    if (monthNum % 3 != 1)
        month->verticalHeader()->hide();

    month->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    month->setVerticalHeaderLabels(DayOfWeekShort);
    month->setSelectionMode(QAbstractItemView::SingleSelection);
    month->setMinimumSize(145, 105);
    m_months->append(month);

    int counter = 0;
    for (int column = 0; column < MaxWeekInMonth; ++column)
    {
        for (int row = 0; row < DayOfWeek; ++row)
        {
            if (counter < Skip || counter >= TotalCell)
            {
                month->model()->setData(month->model()->index(row, column), QString());
                month->item(row, column)->setBackgroundColor(QColor(230, 230, 230));
                month->item(row, column)->setFlags(!Qt::ItemIsSelectable);
            }
            else
            {
                m_datesToPosition->insert(date, Position(row, column));
                month->model()->setData(month->model()->index(row, column), date.day());
                date = date.addDays(1);
            }
            ++counter;
        }
    }

    return month;
}
