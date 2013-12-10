﻿#ifndef CONCIERGEVIEW_H
#define CONCIERGEVIEW_H

#include <QMainWindow>

namespace Ui
{
class OrganizerView;
}

class TransactionView;
class AccountView;
class EventView;
class TimeView;
class DealView;
class AddressModule;

class OrganizerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrganizerView(QWidget *parent = 0);
    ~OrganizerView();

private slots:
    void setToday();
    void timeDialog();
    void dealDialog();
    void eventDialog();
    void accountDialog();
    void transactionDialog();
    void about();
    void deleteRecord();
    void settings();
    void settingsFinaceStatistic(bool value);
    void settingsTimeStatistic(bool value);
    void openDbDialog();
    void saveDbDialog();
    void addContact();
    void addChannel();
    void addAddress();
    void addCompany();
    void deleteContact();
    void openDialog();
    void saveDialog();
    void pathToDb();
    void pathToLogFile();
    void editableMode(bool flag);

private:
    Ui::OrganizerView *ui;
    QList<TimeView*> *m_times;
    QList<DealView*> *m_deals;
    QList<EventView*> *m_events;
    QList<AccountView*> *m_accounts;
    QList<TransactionView*> *m_transactions;
    QList<AddressModule*> *m_addresses;
    int m_flagFinanceStatistic;
    int m_flagTimeStatistic;

private:
    void createInterface();
    void initTimeList(QStringList &list);
};

#endif // CONCIERGEVIEW_H
