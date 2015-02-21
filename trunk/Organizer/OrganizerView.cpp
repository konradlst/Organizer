#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include "transactionDialog.h"
#include "transactionData.h"
#include "transactionView.h"
#include "accountDialog.h"
#include "contactDialog.h"
#include "channelDialog.h"
#include "companyDialog.h"
#include "addressDialog.h"
#include "contactData.h"
#include "companyData.h"
#include "channelData.h"
#include "channelView.h"
#include "companyView.h"
#include "addressData.h"
#include "addressView.h"
#include "accountData.h"
#include "accountView.h"
#include "dialogConst.h"
#include "dbGenerator.h"
#include "timeDialog.h"
#include "dealDialog.h"
#include "eventView.h"
#include "timeData.h"
#include "timeView.h"
#include "dealData.h"
#include "dealView.h"
#include "logger.h"
#include "ui_OrganizerView.h"
#include "OrganizerView.h"

namespace
{
enum Calendars { Today = 0, ThreeDay, Week, Mounth, Year };
enum Tabs { ContactsTab, FinanceTab, TimeTab, DealTab, CalendarTab, StatisticTab, SettingTab };

const int InvalidPosition = -1;
const int DayToHour = 24;
const int HourToSec = 3600;
const double TimeStep = 0.5; //30 min - step in calendars
const QString DbName = "db.sqlite";
const QString monthTemplate = "( MMMM yyyy )";
const QString weekTemplate = "( dd.MM - %1 )";
const QString dayTemplate = "( ddd, dd.MM.yyyy )";
const QString Add = QObject::trUtf8("Add");
const QString ErrorGenerateDb = QObject::trUtf8("Generate database is fail");
const QString TitlePathToDb = QObject::trUtf8("Choose path to DB");
const QString TitlePathToLogFile = QObject::trUtf8("Choose path to log file");
const QString OpenTitle = QObject::trUtf8("Open database");
const QString SaveTitle = QObject::trUtf8("Save database");
const QString OpenContactTitle = QObject::trUtf8("Open contact");
const QString SaveContactTitle = QObject::trUtf8("Save contact");
const QString FileTypes = QObject::trUtf8("All Files (*.*);;SQLite files (*.sqlite)");
const QString SettingsTabName = QObject::trUtf8("Settings");
const QString TodayName = QObject::trUtf8("Today");
const QString ThreeDayNames = QObject::trUtf8("Yesterday;Today;Tomorrow");
const QString DayOfWeek =
        QObject::trUtf8("Monday;Tuesday;Wednesday;Thursday;Friday;Saturday;Sunday");
const QStringList CalendarLabels = QStringList() << DayOfWeek << ThreeDayNames << TodayName;

const QString AboutTitle = QObject::trUtf8("About %1");
const QString AboutText =
        QObject::trUtf8("<b>%1 %2</b><br><br>Based on Qt 4.8.1<br><br>"
                        "Copyright 2013, Anton Batyaev.<br>All rights reserved.");
}

OrganizerView::OrganizerView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::OrganizerView),
      m_times(new QList<TimeView*>),
      m_deals(new QList<DealView*>),
      m_events(new QList<EventView*>),
      m_accounts(new QList<AccountView*>),
      m_transactions(new QList<TransactionView*>),
      m_channels(new QList<ChannelView*>),
      m_addresses(new QList<AddressView*>),
      m_companies(new QList<CompanyView*>),
      m_contacts(new QHash<QString, ContactData>),
      m_flagFinanceStatistic(19),
      m_flagTimeStatistic(9)
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
    connect(ui->actionChoose_Database, SIGNAL(triggered()), SLOT(openDbDialog()));
    connect(ui->actionNew_Database, SIGNAL(triggered()), SLOT(saveDbDialog()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), SLOT(saveDbDialog()));
    connect(ui->actionAdd_Contact, SIGNAL(triggered()), SLOT(addContact()));
    connect(ui->actionAdd_channel, SIGNAL(triggered()), SLOT(addChannel()));
    connect(ui->actionAdd_address, SIGNAL(triggered()), SLOT(addAddress()));
    connect(ui->actionAdd_company, SIGNAL(triggered()), SLOT(addCompany()));
    connect(ui->actionDelete_Contact, SIGNAL(triggered()), SLOT(deleteContact()));
    connect(ui->actionLoad_Contact, SIGNAL(triggered()), SLOT(openDialog()));
    connect(ui->actionSave_Contact, SIGNAL(triggered()), SLOT(saveDialog()));
    connect(ui->actionEditingMode, SIGNAL(triggered(bool)), SLOT(editableMode(bool)));
    connect(ui->lwContactList, SIGNAL(currentRowChanged(int)), SLOT(contactChanged()));
}

OrganizerView::~OrganizerView()
{
    delete ui;
}

void OrganizerView::setToday()
{
    ui->tabWidget->setCurrentIndex(CalendarTab);
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
        TimeView *view = new TimeView(d->data2());
        m_times->append(view);
        ui->Times->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        connect(ui->actionEditingMode, SIGNAL(triggered(bool)), view, SLOT(editableMode(bool)));

        Log::info("Add new time record: " + d->data()->join("# "));
    }
}

void OrganizerView::dealDialog()
{
    ui->tabWidget->setCurrentIndex(DealTab);
    DealDialog *d = new DealDialog();
    if (d->exec())
    {
        DealView *view = new DealView(d->data2());
        m_deals->append(view);
        ui->Deals->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        connect(ui->actionEditingMode, SIGNAL(triggered(bool)), view, SLOT(editableMode(bool)));
        Log::info("Add new deal: " + d->data()->join("# "));
    }
}

void OrganizerView::eventDialog()
{
    ui->tabWidget->setCurrentIndex(CalendarTab);

    int type = 0;
    if (sender() == ui->actionAdd_Event)
        type = 2;
    else if (sender() == ui->actionAdd_Holiday)
        type = 1;

    DealDialog *d = new DealDialog(type);
    if (d->exec())
    {
        EventView *view = new EventView(d->data2());
        m_events->append(view);
        ui->Events->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        connect(ui->actionEditingMode, SIGNAL(triggered(bool)), view, SLOT(editableMode(bool)));
        Log::info("Add new event: " + d->data()->join("# "));
    }
}

void OrganizerView::accountDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    AccountDialog *d = new AccountDialog();
    if (d->exec())
    {
        AccountView *view = new AccountView(d->data2());
        m_accounts->append(view);
        ui->Accounts->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        connect(ui->actionEditingMode, SIGNAL(triggered(bool)), view, SLOT(editableMode(bool)));
        Log::info("Add new account: " + d->data()->join("# "));
    }
}

void OrganizerView::transactionDialog()
{
    ui->tabWidget->setCurrentIndex(FinanceTab);
    TransactionDialog *d = new TransactionDialog();
    if (d->exec())
    {
        TransactionView *view = new TransactionView(d->data2());
        m_transactions->append(view);
        ui->Transactions->insertWidget(0, view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
        connect(ui->actionEditingMode, SIGNAL(triggered(bool)), view, SLOT(editableMode(bool)));
        Log::info("Add new transaction: " + d->data()->join("# "));
    }
}

void OrganizerView::about()
{
    QMessageBox::about(this,
                       AboutTitle.arg(qApp->applicationName()),
                       AboutText.arg(qApp->applicationName())
                                .arg(qApp->applicationVersion()));
}

void OrganizerView::deleteRecord()
{
    //FIXME create factory
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
    else if (qobject_cast<ChannelView*>(sender()))
    {
        for (int i = 0; i < m_channels->count(); ++i)
        {
            if (sender() == m_channels->at(i))
            {
                m_channels->at(i)->hide();
                ui->Channels->removeWidget(qobject_cast<QWidget*>(m_channels->at(i)));
                m_channels->removeAt(i);
                break;
            }
        }
    }
    else if (qobject_cast<AddressView*>(sender()))
    {
        for (int i = 0; i < m_addresses->count(); ++i)
        {
            if (sender() == m_addresses->at(i))
            {
                m_addresses->at(i)->hide();
                ui->Addresses->removeWidget(qobject_cast<QWidget*>(m_addresses->at(i)));
                m_addresses->removeAt(i);
                break;
            }
        }
    }
    else if (qobject_cast<CompanyView*>(sender()))
    {
        for (int i = 0; i < m_companies->count(); ++i)
        {
            if (sender() == m_companies->at(i))
            {
                m_companies->at(i)->hide();
                ui->Companies->removeWidget(qobject_cast<QWidget*>(m_companies->at(i)));
                m_companies->removeAt(i);
                break;
            }
        }
    }
}

void OrganizerView::settings()
{
    //work in QT 5.1.1
//    if (ui->actionSettings->isChecked())
//        ui->tabWidget->tabBar()->addTab(SettingsTabName);
//    else
//        ui->tabWidget->tabBar()->removeTab(SettingTab);
    ui->tabWidget->setCurrentIndex(SettingTab);
}

void OrganizerView::settingsFinaceStatistic(bool value)
{
    if (value)
    {
        if (sender() == ui->cbSelectAllFinanceStatistic)
        {
            ui->cbSelectAllFinanceStatistic->setCheckState(Qt::Checked);
            m_flagFinanceStatistic = 19; //FIXME magic number
            return;
        }
        ++m_flagFinanceStatistic;
        if (m_flagFinanceStatistic == 19) //FIXME magic number
            ui->cbSelectAllFinanceStatistic->setCheckState(Qt::Checked);
        else
            ui->cbSelectAllFinanceStatistic->setCheckState(Qt::PartiallyChecked);
    }
    else
    {
        if (sender() == ui->cbSelectAllFinanceStatistic)
        {
            ui->cbSelectAllFinanceStatistic->setCheckState(Qt::Unchecked);
            m_flagFinanceStatistic = 0;
            return;
        }
        --m_flagFinanceStatistic;
        if (!m_flagFinanceStatistic)
            ui->cbSelectAllFinanceStatistic->setCheckState(Qt::Unchecked);
        else
            ui->cbSelectAllFinanceStatistic->setCheckState(Qt::PartiallyChecked);
    }
}

void OrganizerView::settingsTimeStatistic(bool value)
{
    if (value)
    {
        if (sender() == ui->cbSelectAllTimeStatistic)
        {
            ui->cbSelectAllTimeStatistic->setCheckState(Qt::Checked);
            m_flagTimeStatistic = 9; //FIXME magic number
            return;
        }
        ++m_flagTimeStatistic;
        if (m_flagTimeStatistic == 9) //FIXME magic number
            ui->cbSelectAllTimeStatistic->setCheckState(Qt::Checked);
        else
            ui->cbSelectAllTimeStatistic->setCheckState(Qt::PartiallyChecked);
    }
    else
    {
        if (sender() == ui->cbSelectAllTimeStatistic)
        {
            ui->cbSelectAllTimeStatistic->setCheckState(Qt::Unchecked);
            m_flagTimeStatistic = 0;
            return;
        }
        --m_flagTimeStatistic;
        if (!m_flagTimeStatistic)
            ui->cbSelectAllTimeStatistic->setCheckState(Qt::Unchecked);
        else
            ui->cbSelectAllTimeStatistic->setCheckState(Qt::PartiallyChecked);
    }
}

void OrganizerView::openDbDialog()
{
    QString path = QFileDialog::getOpenFileName(this, OpenTitle,
                                                QDir::currentPath(), FileTypes);
    if (path.isEmpty())
        return;

    Log::info(path);

    dbGenerator gen = dbGenerator(path);
    if (gen.generate())
        ui->pathToDb->setText(path);
    else
        Log::error(ErrorGenerateDb);
}

void OrganizerView::saveDbDialog()
{
    QString path = QFileDialog::getSaveFileName(this, SaveTitle,
                                                QDir::currentPath(), FileTypes);
    if (path.isEmpty())
        return;

    Log::info(path);

    dbGenerator gen = dbGenerator(path);
    if (gen.generate())
        ui->pathToDb->setText(path);
    else
        Log::error(ErrorGenerateDb);
}

void OrganizerView::addContact()
{
    if (ui->tabWidget->currentIndex() != ContactsTab)
    {
        ui->tabWidget->setCurrentIndex(ContactsTab);
        return;
    }
    ContactDialog *d = new ContactDialog();
    if (d->exec())
    {
        ContactData data = d->data2();
        m_contacts->insert(data.nickName, data);
        ui->Contact->setData(data);
        ui->lwContactList->addItem(data.nickName);
        ui->lwContactList->setCurrentRow(ui->lwContactList->count() - 1);
    }
}

void OrganizerView::addChannel()
{
    if (ui->tabWidget->currentIndex() != ContactsTab)
    {
        ui->tabWidget->setCurrentIndex(ContactsTab);
        return;
    }
    ChannelDialog *d = new ChannelDialog();
    if (d->exec())
    {
        ChannelView *view = new ChannelView(d->data2());
        m_channels->append(view);
        ui->Channels->addWidget(view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
    }
}

void OrganizerView::addAddress()
{
    if (ui->tabWidget->currentIndex() != ContactsTab)
    {
        ui->tabWidget->setCurrentIndex(ContactsTab);
        return;
    }
    AddressDialog *d = new AddressDialog();
    if (d->exec())
    {
        AddressView *view = new AddressView(d->data2());
        m_addresses->append(view);
        ui->Addresses->addWidget(view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
    }
}

void OrganizerView::addCompany()
{
    if (ui->tabWidget->currentIndex() != ContactsTab)
    {
        ui->tabWidget->setCurrentIndex(ContactsTab);
        return;
    }
    CompanyDialog *d = new CompanyDialog();
    if (d->exec())
    {
        CompanyView *view = new CompanyView(d->data2());
        m_companies->append(view);
        ui->Companies->addWidget(view);
        connect(view, SIGNAL(deleted()), SLOT(deleteRecord()));
    }
}

void OrganizerView::deleteContact()
{
    if (ui->tabWidget->currentIndex() != ContactsTab)
    {
        ui->tabWidget->setCurrentIndex(ContactsTab);
        return;
    }
    ui->lwContactList->removeItemWidget(ui->lwContactList->currentItem());
    //FIXME
}

void OrganizerView::openDialog()
{
    QString path = QFileDialog::getOpenFileName(this, OpenContactTitle,
                                                QDir::currentPath(), FileTypes);
    if (path.isEmpty())
        Log::info(path);
}

void OrganizerView::saveDialog()
{
    QString path = QFileDialog::getSaveFileName(this, SaveContactTitle,
                                                QDir::currentPath(), FileTypes);
    if (path.isEmpty())
        Log::info(path);
}

void OrganizerView::pathToDb()
{
    QString path = QFileDialog::getOpenFileName(this, TitlePathToDb,
                                                QDir::currentPath(), FileTypes);
    if (!path.isEmpty())
        ui->pathToDb->setText(path);
}

void OrganizerView::pathToLogFile()
{
    QString path = QFileDialog::getOpenFileName(this, TitlePathToLogFile,
                                                QDir::currentPath(), FileTypes);
    if (!path.isEmpty())
        ui->pathToLogFile->setText(path);
}

void OrganizerView::editableMode(bool flag)
{
    ui->Contact->setVisibleEditUserPic(flag);
    //FIXME
}

void OrganizerView::contactChanged()
{
    ui->Contact->setData(m_contacts->value(ui->lwContactList->currentItem()->text()));
}

void OrganizerView::createInterface()
{
    ui->setupUi(this);

    QMenu *addMenu = new QMenu(Add);
    QList<QAction*> addActionList;
    addActionList.append(ui->actionAdd_channel);
    addActionList.append(ui->actionAdd_address);
    addActionList.append(ui->actionAdd_company);
    addMenu->addActions(addActionList);
    ui->pbAddInContact->setMenu(addMenu);

//    ui->tabWidget->tabBar()->removeTab(SettingTab);
    QList<int> sizes;
    sizes << ui->FinanceTab->width() / 2
          << ui->FinanceTab->width() / 2;
    ui->FinanceTab->setSizes(sizes);
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
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    ui->pathToDb->setText(QDir::toNativeSeparators(qApp->applicationDirPath() + QDir::separator() + DbName));
    connect(ui->pbOpenPathToDb, SIGNAL(clicked()), SLOT(pathToDb()));
    connect(ui->pbOpenPathToLogFile, SIGNAL(clicked()), SLOT(pathToLogFile()));

    //connect checkBox Select all in finance statistic
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageIncomePerDay, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageIncomePerWeek, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageIncomePerMonth, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageOutcomePerDay, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageOutcomePerWeek, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageOutcomePerMonth, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxIncomePerDay, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxIncomePerWeek, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxIncomePerMonth, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxOutcomePerDay, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxOutcomePerWeek, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxOutcomePerMonth, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbCurrentAmountOfFunds, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbCurrentCredit, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbCurrentDebet, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbTodayIncome, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbTodayOutcome, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbLastIncome, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            ui->cbLastOutcome, SLOT(setChecked(bool)));

    connect(ui->cbSelectAllFinanceStatistic, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbAverageIncomePerDay, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbAverageIncomePerWeek, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbAverageIncomePerMonth, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbAverageOutcomePerDay, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbAverageOutcomePerWeek, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbAverageOutcomePerMonth, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbMaxIncomePerDay, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbMaxIncomePerWeek, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbMaxIncomePerMonth, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbMaxOutcomePerDay, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbMaxOutcomePerWeek, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbMaxOutcomePerMonth, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbCurrentAmountOfFunds, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbCurrentCredit, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbCurrentDebet, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbTodayIncome, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbTodayOutcome, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbLastIncome, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));
    connect(ui->cbLastOutcome, SIGNAL(clicked(bool)),
            SLOT(settingsFinaceStatistic(bool)));

    //connect checkBox Select all in time statistic
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageDaily, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageWeekly, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbAverageMonthly, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxDaily, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxWeekly, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbMaxMonthly, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbMinDaily, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbMinWeekly, SLOT(setChecked(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->cbMinMonthly, SLOT(setChecked(bool)));

    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbAverageDaily, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbAverageWeekly, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbAverageMonthly, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbMaxDaily, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbMaxWeekly, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbMaxMonthly, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbMinDaily, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbMinWeekly, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));
    connect(ui->cbMinMonthly, SIGNAL(clicked(bool)),
            SLOT(settingsTimeStatistic(bool)));

    //connect checkBox in settings and info in time statistic
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblAverageDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teAverageDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateAverageDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblAverageWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teAverageWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateAverageWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblAverageMonthly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teAverageMonthly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateAverageMonthly, SLOT(setVisible(bool)));

    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblMinDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teMinDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateMinDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblMinWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teMinWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateMinWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblMinMonthly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teMinMonthly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateMinMonthly, SLOT(setVisible(bool)));

    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblMaxDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teMaxDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateMaxDaily, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblMaxWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teMaxWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateMaxWeekly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->lblMaxMonthly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->teMaxMonthly, SLOT(setVisible(bool)));
    connect(ui->cbSelectAllTimeStatistic, SIGNAL(clicked(bool)),
            ui->dateMaxMonthly, SLOT(setVisible(bool)));

    connect(ui->cbAverageDaily, SIGNAL(clicked(bool)),
            ui->lblAverageDaily, SLOT(setVisible(bool)));
    connect(ui->cbAverageDaily, SIGNAL(clicked(bool)),
            ui->teAverageDaily, SLOT(setVisible(bool)));
    connect(ui->cbAverageDaily, SIGNAL(clicked(bool)),
            ui->dateAverageDaily, SLOT(setVisible(bool)));
    connect(ui->cbAverageWeekly, SIGNAL(clicked(bool)),
            ui->lblAverageWeekly, SLOT(setVisible(bool)));
    connect(ui->cbAverageWeekly, SIGNAL(clicked(bool)),
            ui->teAverageWeekly, SLOT(setVisible(bool)));
    connect(ui->cbAverageWeekly, SIGNAL(clicked(bool)),
            ui->dateAverageWeekly, SLOT(setVisible(bool)));
    connect(ui->cbAverageMonthly, SIGNAL(clicked(bool)),
            ui->lblAverageMonthly, SLOT(setVisible(bool)));
    connect(ui->cbAverageMonthly, SIGNAL(clicked(bool)),
            ui->teAverageMonthly, SLOT(setVisible(bool)));
    connect(ui->cbAverageMonthly, SIGNAL(clicked(bool)),
            ui->dateAverageMonthly, SLOT(setVisible(bool)));

    connect(ui->cbMinDaily, SIGNAL(clicked(bool)),
            ui->lblMinDaily, SLOT(setVisible(bool)));
    connect(ui->cbMinDaily, SIGNAL(clicked(bool)),
            ui->teMinDaily, SLOT(setVisible(bool)));
    connect(ui->cbMinDaily, SIGNAL(clicked(bool)),
            ui->dateMinDaily, SLOT(setVisible(bool)));
    connect(ui->cbMinWeekly, SIGNAL(clicked(bool)),
            ui->lblMinWeekly, SLOT(setVisible(bool)));
    connect(ui->cbMinWeekly, SIGNAL(clicked(bool)),
            ui->teMinWeekly, SLOT(setVisible(bool)));
    connect(ui->cbMinWeekly, SIGNAL(clicked(bool)),
            ui->dateMinWeekly, SLOT(setVisible(bool)));
    connect(ui->cbMinMonthly, SIGNAL(clicked(bool)),
            ui->lblMinMonthly, SLOT(setVisible(bool)));
    connect(ui->cbMinMonthly, SIGNAL(clicked(bool)),
            ui->teMinMonthly, SLOT(setVisible(bool)));
    connect(ui->cbMinMonthly, SIGNAL(clicked(bool)),
            ui->dateMinMonthly, SLOT(setVisible(bool)));

    connect(ui->cbMaxDaily, SIGNAL(clicked(bool)),
            ui->lblMaxDaily, SLOT(setVisible(bool)));
    connect(ui->cbMaxDaily, SIGNAL(clicked(bool)),
            ui->teMaxDaily, SLOT(setVisible(bool)));
    connect(ui->cbMaxDaily, SIGNAL(clicked(bool)),
            ui->dateMaxDaily, SLOT(setVisible(bool)));
    connect(ui->cbMaxWeekly, SIGNAL(clicked(bool)),
            ui->lblMaxWeekly, SLOT(setVisible(bool)));
    connect(ui->cbMaxWeekly, SIGNAL(clicked(bool)),
            ui->teMaxWeekly, SLOT(setVisible(bool)));
    connect(ui->cbMaxWeekly, SIGNAL(clicked(bool)),
            ui->dateMaxWeekly, SLOT(setVisible(bool)));
    connect(ui->cbMaxMonthly, SIGNAL(clicked(bool)),
            ui->lblMaxMonthly, SLOT(setVisible(bool)));
    connect(ui->cbMaxMonthly, SIGNAL(clicked(bool)),
            ui->teMaxMonthly, SLOT(setVisible(bool)));
    connect(ui->cbMaxMonthly, SIGNAL(clicked(bool)),
            ui->dateMaxMonthly, SLOT(setVisible(bool)));

    //connect checkBox in settings and info in time statistic
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
