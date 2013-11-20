#ifndef YEARCALENDAR_H
#define YEARCALENDAR_H

#include <QWidget>

class QTableWidget;
class QDate;

class YearCalendar : public QWidget
{
    Q_OBJECT
public:
    explicit YearCalendar(QWidget *parent = 0);

public slots:
    void setSelectedDate(const QDate &date);

private:
    void init();
    QTableWidget* monthCalendar(const int monthNum);

private:
    typedef QPair<int, int> Position;

    QVector<QTableWidget*> *m_months;
    QMap<QDate, Position> *m_datesToPosition;
};

#endif // YEARCALENDAR_H
