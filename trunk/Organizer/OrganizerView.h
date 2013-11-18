﻿#ifndef CONCIERGEVIEW_H
#define CONCIERGEVIEW_H

#include <QMainWindow>

namespace Ui
{
class OrganizerView;
}

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
    void accountDialog();
    void transactionDialog();

private:
    Ui::OrganizerView *ui;
    typedef QPair<int, int> Position;
    QMap<QDate, Position> *m_yearDate;

private:
    void createInterface();
    void initYearCalendar();
    void initTimeList(QStringList &list);
};

#endif // CONCIERGEVIEW2_H
