#include <QTableWidget>
#include <QHeaderView>
#include "transactionDialog.h"
#include "accountDialog.h"
#include "timeDialog.h"
#include "dealDialog.h"
#include "ui_OrganizerView.h"
#include "OrganizerView.h"

#include <QDebug>

namespace
{
enum Calendars { Today = 0, ThreeDay, Week, Mounth, Year };
enum Tabs { ContactsTab, FinanceTab, TimeTab, DealTab, CalendarTab, StatisticTab };

const int InvalidPosition = -1;
const QChar Separator = ';';
const QString TimePattern = "hh:mm";
const QStringList TodayName = QObject::trUtf8("Today").split(Separator);
const QStringList ThreeDayNames = QObject::trUtf8("Yesterday;Today;Tomorrow").split(Separator);
const QStringList DayOfWeek =
        QObject::trUtf8("Monday;Tuesday;Wednesday;Thursday;Friday;Saturday;Sunday").split(Separator);
}

OrganizerView::OrganizerView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::OrganizerView)
{
    createInterface();
    connect(ui->actionToday, SIGNAL(triggered()), this, SLOT(setToday()));
    connect(ui->actionAdd_Time, SIGNAL(triggered()), this, SLOT(timeDialog()));
    connect(ui->actionAdd_Deal, SIGNAL(triggered()), this, SLOT(dealDialog()));
    connect(ui->actionAdd_Task, SIGNAL(triggered()), this, SLOT(taskDialog()));
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
        ui->yearCalendar->setSelectedDate(QDate::currentDate());
    }
}

void OrganizerView::timeDialog()
{
    ui->tabWidget->setCurrentIndex(TimeTab);
    TimeDialog *d = new TimeDialog();
    if (d->exec())
    {
        qDebug() << "# " << d->data()->join("\n# ");
    }
}

void OrganizerView::dealDialog()
{
    ui->tabWidget->setCurrentIndex(DealTab);
    DealDialog *d = new DealDialog();
    if (d->exec())
    {
        qDebug() << "# " << d->data()->join("\n# ");
    }
}

void OrganizerView::taskDialog()
{
    ui->tabWidget->setCurrentIndex(DealTab);
    DealDialog *d = new DealDialog(2);
    if (d->exec())
    {
        qDebug() << "# " << d->data()->join("\n# ");
    }
}

void OrganizerView::accountDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    AccountDialog *d = new AccountDialog();
    if (d->exec())
    {
        qDebug() << "# " << d->data()->join("\n# ");
    }
}

void OrganizerView::transactionDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    TransactionDialog *d = new TransactionDialog();
    if (d->exec())
    {
        qDebug() << "# " << d->data()->join("\n# ");
    }
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
    labels << &DayOfWeek << &ThreeDayNames << &TodayName;
    int i = 0;
    foreach (QTableWidget *table, calendars)
    {
        table->setVerticalHeaderLabels(timeList);
        table->setHorizontalHeaderLabels(*labels.at(i++));
//        table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//4.8.4
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//5.1.0
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
