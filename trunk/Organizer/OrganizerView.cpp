#include <QTableWidget>
#include "OrganizerView.h"
#include "ui_OrganizerView.h"
#include "Dialog.h"

namespace
{
enum Calendars { Today = 0, ThreeDay, Week, Mounth };
enum Tabs { ContactsTab, FinanceTab, TimeTab, CalendarTab, StatisticTab, NoteTab };

const QChar Separator = ';';
const QStringList TimeType = QString("sleep;work;travel;study;sport;read").split(Separator);
const QStringList TodayName = QObject::trUtf8("Today").split(Separator);
const QStringList ThreeDayNames = QObject::trUtf8("Yesterday;Today;Tomorrow").split(Separator);
const QStringList DayOfWeek = QObject::trUtf8("Monday;Tuesday;Wednesday;Thursday;Friday;Saturday;Sunday").split(Separator);
}

OrganizerView::OrganizerView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::OrganizerView)
{
    createInterface();
    connect(ui->actionToday, SIGNAL(triggered()), this, SLOT(setToday()));
    connect(ui->actionAdd_Time, SIGNAL(triggered()), this, SLOT(timeDialog()));
    connect(ui->actionAdd_Note, SIGNAL(triggered()), this, SLOT(noteDialog()));
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
    case Mounth:
        ui->mounthCalendar->setSelectedDate(QDate::currentDate());
    }
}

void OrganizerView::timeDialog()
{
    ui->tabWidget->setCurrentIndex(TimeTab);
    TimeDialog *d = new TimeDialog();
    d->show();
}

void OrganizerView::noteDialog()
{
    ui->tabWidget->setCurrentIndex(NoteTab);
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

    QStringList timeList;
    initTimeList(timeList);

    ui->weekCalendar->setVerticalHeaderLabels(timeList);
    ui->weekCalendar->setHorizontalHeaderLabels(DayOfWeek);
    ui->weekCalendar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->threeDayCalendar->setVerticalHeaderLabels(timeList);
    ui->threeDayCalendar->setHorizontalHeaderLabels(ThreeDayNames);
    ui->threeDayCalendar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->todayCalendar->setVerticalHeaderLabels(timeList);
    ui->todayCalendar->setHorizontalHeaderLabels(TodayName);
    ui->todayCalendar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void OrganizerView::initTimeList(QStringList &list)
{
    static const QString TimePattern = "hh:mm";

    QTime time(0, 0);
    for (int i = 0; i <= 48; ++i)
    {
        list << time.toString(TimePattern);
        time = time.addSecs(1800);
    }
}
