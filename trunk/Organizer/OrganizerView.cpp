#include <QTableWidget>
#include "OrganizerView.h"
#include "ui_OrganizerView.h"
#include "Dialog.h"

namespace
{
enum Calendars { Today = 0, ThreeDay, Week, Mounth, Year };
enum Tabs { ContactsTab, FinanceTab, TimeTab, DealTab, CalendarTab, StatisticTab };

const int InvalidPosition = -1;
const QChar Separator = ';';
const QString TimePattern = "hh:mm";
const QStringList TimeType = QString("sleep;work;travel;study;sport;read").split(Separator);
const QStringList TodayName = QObject::trUtf8("Today").split(Separator);
const QStringList ThreeDayNames = QObject::trUtf8("Yesterday;Today;Tomorrow").split(Separator);
const QStringList DayOfWeek = QObject::trUtf8("Monday;Tuesday;Wednesday;Thursday;Friday;Saturday;Sunday").split(Separator);
const QStringList DayOfWeekShort = QObject::trUtf8("Mo;Tu;We;Th;Fr;Sa;Su").split(Separator);
}

OrganizerView::OrganizerView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::OrganizerView),
      m_yearDate(new QMap<QDate, Position>())
{
    createInterface();
    connect(ui->actionToday, SIGNAL(triggered()), this, SLOT(setToday()));
    connect(ui->actionAdd_Time, SIGNAL(triggered()), this, SLOT(timeDialog()));
    connect(ui->actionAdd_Deal, SIGNAL(triggered()), this, SLOT(dealDialog()));
    connect(ui->actionAdd_Account, SIGNAL(triggered()), this, SLOT(accountDialog()));
    connect(ui->actionAdd_Transaction, SIGNAL(triggered()), this, SLOT(transactionDialog()));
}

OrganizerView::~OrganizerView()
{
    delete ui;
}

void OrganizerView::setToday()
{
    int time = QTime::currentTime().hour() * 2;
    if (QTime::currentTime().minute() > 30)
        ++time;

    switch (ui->twCalendar->currentIndex())
    {
    case Today :
        ui->todayCalendar->setCurrentCell(time, 0);
        break;
    case ThreeDay :
        ui->threeDayCalendar->setCurrentCell(time, 1);
        break;
    case Week :
        ui->weekCalendar->setCurrentCell(time, QDate::currentDate().dayOfWeek() - 1);
        break;
    case Mounth :
        ui->mounthCalendar->setSelectedDate(QDate::currentDate());
        break;
    case Year :
    {
        int row = m_yearDate->value(QDate::currentDate()).first;
        int column = m_yearDate->value(QDate::currentDate()).second;

        QList<QTableWidget*> calendars;
        calendars << ui->tblCalendar1_3
                  << ui->tblCalendar4_6
                  << ui->tblCalendar7_9
                  << ui->tblCalendar10_12;
        foreach (QTableWidget *table, calendars)
            table->setCurrentCell(InvalidPosition, InvalidPosition);

        if (QDate::currentDate().month() < 4)
        {
            ui->tblCalendar1_3->setFocus();
            ui->tblCalendar1_3->setCurrentCell(row, column);
        }
        else if (QDate::currentDate().month() < 7)
        {
            ui->tblCalendar4_6->setFocus();
            ui->tblCalendar4_6->setCurrentCell(row, column);
        }
        else if (QDate::currentDate().month() < 10)
        {
            ui->tblCalendar7_9->setFocus();
            ui->tblCalendar7_9->setCurrentCell(row, column);
        }
        else
        {
            ui->tblCalendar10_12->setFocus();
            ui->tblCalendar10_12->setCurrentCell(row, column);
        }
    }
    }
}

void OrganizerView::timeDialog()
{
    ui->tabWidget->setCurrentIndex(TimeTab);
    TimeDialog *d = new TimeDialog();
    d->show();
}

void OrganizerView::dealDialog()
{
    ui->tabWidget->setCurrentIndex(DealTab);
    DealDialog *d = new DealDialog();
    d->show();
}

void OrganizerView::accountDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    AccountDialog *d = new AccountDialog();
    d->show();
}

void OrganizerView::transactionDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    TransactionDialog *d = new TransactionDialog();
    d->show();
}

void OrganizerView::createInterface()
{
    ui->setupUi(this);

    ui->dateViewEvents->calendarPopup(false);

    QStringList timeList;
    initTimeList(timeList);

    QList<QTableWidget*> calendars;
    calendars << ui->weekCalendar
              << ui->threeDayCalendar
              << ui->todayCalendar;
    QList<const QStringList*> labels;
    labels << &DayOfWeek
           << &ThreeDayNames
           << &TodayName;
    int i = 0;
    foreach (QTableWidget *table, calendars)
    {
        table->setVerticalHeaderLabels(timeList);
        table->setHorizontalHeaderLabels(*labels.at(i++));
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    initYearCalendar();
}

void OrganizerView::initYearCalendar()
{
    m_yearDate->clear();
    QDate date = QDate(QDate::currentDate().year(), 1, 1);

    QList<QTableWidget*> list;
    list << ui->tblCalendar1_3
         << ui->tblCalendar4_6
         << ui->tblCalendar7_9
         << ui->tblCalendar10_12;
    int column = 0;
    int row = 0;
    int month = 1;
    bool active = false;
    foreach (QTableWidget *table, list)
    {
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->setVerticalHeaderLabels(DayOfWeekShort);
        column = 0;
        row = 0;
        month = 1;
        active = (date.dayOfWeek() == 1);

        while (month < 4 || (column < 16))
        {
            if (!active)
            {
                table->model()->setData(table->model()->index(row, column), QString());
                table->item(row, column)->setBackgroundColor(QColor(230, 230, 230));
                table->item(row, column)->setFlags(!Qt::ItemIsSelectable);

                if (((row == 6) && (date.dayOfWeek() == 1)) || (row == (date.dayOfWeek() - 2)))
                    active = true;
            }
            else
            {
                m_yearDate->insert(date, Position(row, column));
                table->model()->setData(table->model()->index(row, column), date.day());
                date = date.addDays(1);
                if (date.month() != month)
                    ++month;
                if (date.day() == 1)
                    active = false;
            }
            if (row == 6)
            {
                ++column;
                row = 0;
            }
            else
            {
                ++row;
            }
        }
    }
}

void OrganizerView::initTimeList(QStringList &list)
{
    QTime time(0, 0);
    for (int i = 0; i <= 48; ++i)
    {
        list << time.toString(TimePattern);
        time = time.addSecs(1800);
    }
}
