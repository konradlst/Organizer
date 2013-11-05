﻿#include <QTableWidget>
#include "ConciergeView.h"
#include "ui_ConciergeView.h"

namespace
{
enum Calendars { Today = 0, ThreeDay, Week, Mounth };

const QChar Separator = ';';
const QStringList TimeType = QString("sleep;work;travel;study;sport;read").split(Separator);
const QStringList FinanceOperation = QObject::trUtf8("debet;credit;transfer").split(Separator);
const QStringList Accounts = QObject::trUtf8("cash;card;deposit").split(Separator);
const QStringList TodayName = QObject::trUtf8("Today").split(Separator);
const QStringList ThreeDayNames = QObject::trUtf8("Yesterday;Today;Tomorrow").split(Separator);
const QStringList DayOfWeek = QObject::trUtf8("Monday;Tuesday;Wednesday;Thursday;Friday;Saturday;Sunday").split(Separator);
}

ConciergeView::ConciergeView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ConciergeView)
{
    createInterface();
    connect(ui->actionToday, SIGNAL(triggered()), this, SLOT(setToday()));
}

ConciergeView::~ConciergeView()
{
    delete ui;
}

void ConciergeView::setToday()
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

void ConciergeView::createInterface()
{
    ui->setupUi(this);
    ui->comboBox->addItems(FinanceOperation);
    ui->comboBox_2->addItems(Accounts);

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

void ConciergeView::initTimeList(QStringList &list)
{
    static const QString TimePattern = "hh:mm";

    QTime time(0, 0);
    for (int i = 0; i <= 48; ++i)
    {
        list << time.toString(TimePattern);
        time = time.addSecs(1800);
    }
}
