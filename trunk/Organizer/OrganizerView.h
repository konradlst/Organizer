#ifndef CONCIERGEVIEW_H
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
    void taskDialog();
    void accountDialog();
    void transactionDialog();

private:
    Ui::OrganizerView *ui;
    QList<TimeView*> *m_times;
    QList<DealView*> *m_deals;
    QList<EventView*> *m_events;
    QList<AccountView*> *m_accounts;
    QList<TransactionView*> *m_transactions;

private:
    void createInterface();
    void initTimeList(QStringList &list);
};

#endif // CONCIERGEVIEW_H
