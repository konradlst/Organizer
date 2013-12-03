#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include <QWidget>

class QDateEdit;
class QLineEdit;
class QPushButton;

//! \class EventView
//! \brief Класс-представление записи из календаря,
//!        позволяет переходить к более детальному описанию события.
class EventView : public QWidget
{
    Q_OBJECT
public:
    explicit EventView(const QDate &date, const QString &description = QString(),
                       QWidget *parent = 0);

signals:
    void deleted();
    void openDetail();

public slots:
    void editableMode(bool flag);

private:
    QDateEdit *m_date;
    QLineEdit *m_description;
    QPushButton *m_delete;
    QPushButton *m_detail;
};

#endif // EVENTVIEW_H
