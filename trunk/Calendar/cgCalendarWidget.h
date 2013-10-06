#ifndef CGCALENDARWIDGET_H
#define CGCALENDARWIDGET_H

#include <QWidget>

class QCalendarWidget;
class QTableWidget;
class QGroupBox;
class QPushButton;

class cgCalendarWidget : public QWidget
{
    Q_OBJECT
public:
    enum TypeCalendar { Today = 0, ThreeDay, Week, Mounth };
    explicit cgCalendarWidget(const TypeCalendar type, bool shTasks = true,
                              bool shSysButton = true, QWidget *parent = 0);
    void showTasks(bool status);
    void showSystemButton(bool status);

    void setDate(const QDate &date);

    QPushButton* pbSetToday() const;
    QPushButton* pbAddHoliday() const;
    QPushButton* pbAddTask() const;
    QString name() const;

private:
    QWidget *m_calendar;
    QGroupBox *m_holidays;
    QGroupBox *m_tasks;
    QPushButton *m_setToday;
    QPushButton *m_addHoliday;
    QPushButton *m_addTask;
    QString m_name;
    TypeCalendar m_type;

private:
    void createCalendarWidget();
    void createInterface();
    void initTimeList(QStringList &list);
};

#endif // CGCALENDARWIDGET_H
