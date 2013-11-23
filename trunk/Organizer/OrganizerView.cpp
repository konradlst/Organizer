#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include "transactionDialog.h"
#include "accountDialog.h"
#include "timeDialog.h"
#include "dealDialog.h"
#include "transactionView.h"
#include "accountView.h"
#include "eventView.h"
#include "timeView.h"
#include "dealView.h"
#include "dialogConst.h"
#include "ui_OrganizerView.h"
#include "OrganizerView.h"

#include <QDebug>

namespace
{
enum Calendars { Today = 0, ThreeDay, Week, Mounth, Year };
enum Tabs { ContactsTab, FinanceTab, TimeTab, DealTab, CalendarTab, StatisticTab, SettingTab };

const int InvalidPosition = -1;
const int DayToHour = 24;
const int HourToSec = 3600;
const double TimeStep = 0.5; //30 min - step in calendars
const QString SettingsTabName = QObject::trUtf8("Settings");
const QString TodayName = QObject::trUtf8("Today");
const QString ThreeDayNames = QObject::trUtf8("Yesterday;Today;Tomorrow");
const QString DayOfWeek =
        QObject::trUtf8("Monday;Tuesday;Wednesday;Thursday;Friday;Saturday;Sunday");
const QStringList CalendarLabels = QStringList() << DayOfWeek << ThreeDayNames << TodayName;

const QString AboutTitle = QObject::trUtf8("About %1");
const QString AboutText =
        QObject::trUtf8("<b>%1 %2 for %3</b><br><br>Based on Qt 5.1.1<br><br>"
                        "Copyright 2013, Anton Batyaev.<br>All rights reserved.");
}

OrganizerView::OrganizerView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::OrganizerView),
      m_times(new QList<TimeView*>),
      m_deals(new QList<DealView*>),
      m_events(new QList<EventView*>),
      m_accounts(new QList<AccountView*>),
      m_transactions(new QList<TransactionView*>)
{
    createInterface();
    connect(ui->actionToday, SIGNAL(triggered()), SLOT(setToday()));
    connect(ui->actionAdd_Time, SIGNAL(triggered()), SLOT(timeDialog()));
    connect(ui->actionAdd_Deal, SIGNAL(triggered()), SLOT(dealDialog()));
    connect(ui->actionAdd_Holiday, SIGNAL(triggered()), SLOT(eventDialog()));
    connect(ui->actionAdd_Event, SIGNAL(triggered()), SLOT(eventDialog()));
    connect(ui->actionAdd_Account, SIGNAL(triggered()), SLOT(accountDialog()));
    connect(ui->actionAdd_Transaction, SIGNAL(triggered()), SLOT(transactionDialog()));
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(about()));
    connect(ui->actionSettings, SIGNAL(triggered()), SLOT(settings()));
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
        QStringList *data = d->data();
        TimeView *view = new TimeView(data->at(0).toLongLong(),
                                      QTime::fromString(data->at(1), TimeFormat),
                                      QTime::fromString(data->at(2), TimeFormat),
                                      QTime::fromString(data->at(3), TimeFormat),
                                      data->at(4));
        m_times->append(view);
        ui->Times->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        qDebug() << "Add new time record: " << d->data()->join("# ");
    }
}

void OrganizerView::dealDialog()
{
    ui->tabWidget->setCurrentIndex(DealTab);
    DealDialog *d = new DealDialog();
    if (d->exec())
    {
        QStringList *data = d->data();
        DealView *view = new DealView(data->at(0).toLongLong(),
                                      QDate::fromString(data->at(1), DateFormat),
                                      data->at(2).toLongLong(),
                                      QTime::fromString(data->at(3), TimeFormat),
                                      QDate::fromString(data->at(4), DateFormat),
                                      data->at(5),
                                      data->at(6));
        m_deals->append(view);
        ui->Deals->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        qDebug() << "Add new deal: " << d->data()->join("# ");
    }
}

void OrganizerView::eventDialog()
{
    ui->tabWidget->setCurrentIndex(CalendarTab);
    DealDialog *d = 0;
    if (sender() == ui->actionAdd_Event)
        d = new DealDialog(2);
    else if (sender() == ui->actionAdd_Holiday)
        d = new DealDialog(1);
    if (d->exec())
    {
        QStringList *data = d->data();
        EventView *view = new EventView(QDate::fromString(data->at(1), DateFormat),
                                        data->at(2));
        m_events->append(view);
        ui->Events->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        qDebug() << "Add new event: " << d->data()->join("# ");
    }
}

void OrganizerView::accountDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    AccountDialog *d = new AccountDialog();
    if (d->exec())
    {
        QStringList *data = d->data();
        AccountView *view = new AccountView(data->at(0).toLongLong(),
                                            data->at(2),
                                            data->at(3).toLongLong(),
                                            data->at(4).toLongLong(),
                                            data->at(5));
        m_accounts->append(view);
        ui->Accounts->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        qDebug() << "Add new account: " << d->data()->join("# ");
    }
}

void OrganizerView::transactionDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    TransactionDialog *d = new TransactionDialog();
    if (d->exec())
    {
        QStringList *data = d->data();
        TransactionView *view = new TransactionView(data->at(0).toLongLong(),
                                                    data->at(2),
                                                    data->at(3).toLongLong(),
                                                    data->at(4));
        m_transactions->append(view);
        ui->Transactions->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        qDebug() << "Add new transaction: " << d->data()->join("# ");
    }
}

void OrganizerView::about()
{
    QMessageBox::about(this,
                       AboutTitle.arg(qApp->applicationName()),
                       AboutText.arg(qApp->applicationName())
                                .arg(qApp->applicationVersion())
                                .arg(qApp->platformName()));
}

void OrganizerView::deleteRecord()
{
    if (qobject_cast<TimeView*>(sender()))
    {
        for (int i = 0; i < m_times->count(); ++i)
        {
            if (sender() == m_times->at(i))
            {
                m_times->at(i)->hide();
                ui->Times->removeWidget(qobject_cast<QWidget*>(m_times->at(i)));
                m_times->removeAt(i);
                break;
            }
        }
    }
    else if (qobject_cast<DealView*>(sender()))
    {
        for (int i = 0; i < m_deals->count(); ++i)
        {
            if (sender() == m_deals->at(i))
            {
                m_deals->at(i)->hide();
                ui->Deals->removeWidget(qobject_cast<QWidget*>(m_deals->at(i)));
                m_deals->removeAt(i);
                break;
            }
        }
    }
    else if (qobject_cast<EventView*>(sender()))
    {
        for (int i = 0; i < m_events->count(); ++i)
        {
            if (sender() == m_events->at(i))
            {
                m_events->at(i)->hide();
                ui->Events->removeWidget(qobject_cast<QWidget*>(m_events->at(i)));
                m_events->removeAt(i);
                break;
            }
        }
    }
    else if (qobject_cast<AccountView*>(sender()))
    {
        for (int i = 0; i < m_accounts->count(); ++i)
        {
            if (sender() == m_accounts->at(i))
            {
                m_accounts->at(i)->hide();
                ui->Accounts->removeWidget(qobject_cast<QWidget*>(m_accounts->at(i)));
                m_accounts->removeAt(i);
                break;
            }
        }
    }
    else if (qobject_cast<TransactionView*>(sender()))
    {
        for (int i = 0; i < m_transactions->count(); ++i)
        {
            if (sender() == m_transactions->at(i))
            {
                m_transactions->at(i)->hide();
                ui->Transactions->removeWidget(qobject_cast<QWidget*>(m_transactions->at(i)));
                m_transactions->removeAt(i);
                break;
            }
        }
    }
}

void OrganizerView::settings()
{
    if (ui->tabWidget->tabBar()->count() == 6)
        ui->tabWidget->tabBar()->addTab(SettingsTabName);
    else
        ui->tabWidget->tabBar()->removeTab(SettingTab);
    ui->tabWidget->setCurrentIndex(SettingTab);
}

void OrganizerView::createInterface()
{
    ui->setupUi(this);

    ui->tabWidget->tabBar()->removeTab(SettingTab);
    ui->dateViewEvents->calendarPopup(false);

    QStringList timeList;
    initTimeList(timeList);

    QList<QTableWidget*> calendars;
    calendars << ui->weekCalendar << ui->threeDayCalendar << ui->todayCalendar;
    int i = 0;
    foreach (QTableWidget *table, calendars)
    {
        QStringList list = CalendarLabels.at(i++).split(Separator);
        table->setRowCount(timeList.count());
        table->setColumnCount(list.count());
        table->setVerticalHeaderLabels(timeList);
        table->setHorizontalHeaderLabels(list);
//        table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//4.8.4
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//5.1.0
    }
}

void OrganizerView::initTimeList(QStringList &list)
{
    QTime time(0, 0);
    for (int i = 0; i < (DayToHour / TimeStep); ++i)
    {
        list << time.toString(TimeFormat);
        time = time.addSecs(HourToSec * TimeStep);
    }
}
