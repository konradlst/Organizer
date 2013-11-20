#ifndef DATEVIEW_H
#define DATEVIEW_H

#include <QWidget>

class QCalendarWidget;
class QPushButton;
class QLabel;

//! \class DateView
//! \brief Класс-представление даты с заданным интервалом поиска записей
//!        и всплывающим календарем.
class DateView : public QWidget
{
    Q_OBJECT
public:
    enum Interval
    {
        Day = 0,
        Week,
        Mounth,
        Year
    };
    explicit DateView(QWidget *parent = 0);
    void calendarPopup(bool flag);
    void setDate(const QDate &date);

signals:
    void intervalChange(Interval i);

private slots:
    void showCalendarPopup();
    void intervalChanged(bool checked);
    void dateChanged(const QDate &date);

private:
    Interval m_interval;
    QLabel *m_date;
    QPushButton *m_day;
    QPushButton *m_week;
    QPushButton *m_mounth;
    QPushButton *m_year;
    QPushButton *m_calendar;
    QCalendarWidget *m_calendarWidget;
};

#endif // DATEVIEW_H
