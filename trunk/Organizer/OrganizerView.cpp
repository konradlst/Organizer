﻿#include <QTableWidget>
#include "OrganizerView.h"
#include "ui_OrganizerView.h"
#include "Dialog.h"

namespace
{
enum Calendars { Today = 0, ThreeDay, Week, Mounth, Year };
enum Tabs { ContactsTab, FinanceTab, TimeTab, DealTab, CalendarTab, StatisticTab };

const QChar Separator = ';';
const QString TimePattern = "hh:mm";
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
        int row = 0;
        int column = 0;
        if (QDate::currentDate().month() < 4)
        {
            ui->tblCalendar1_3->setCurrentCell(row, column);
        }
        else if (QDate::currentDate().month() < 7)
        {
            ui->tblCalendar4_6->setCurrentCell(row, column);
        }
        else if (QDate::currentDate().month() < 10)
        {
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
    ui->tblCalendar1_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCalendar4_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCalendar7_9->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCalendar10_12->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCalendar1_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCalendar4_6->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCalendar7_9->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCalendar10_12->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    QTime time(0, 0);
    for (int i = 0; i <= 48; ++i)
    {
        list << time.toString(TimePattern);
        time = time.addSecs(1800);
    }
}
