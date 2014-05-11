#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include <QWidget>

class QPushButton;
class QDateEdit;
class QLineEdit;
class QDate;
struct DealData;

//! \class EventView
//! \brief Класс-представление записи из календаря,
//!        позволяет переходить к более детальному описанию события.
class EventView : public QWidget
{
    Q_OBJECT
public:
    explicit EventView(const QDate &date, const QString &description = QString(),
                       QWidget *parent = 0);
    explicit EventView(const DealData &data);

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

    void createInterface();
};

#endif // EVENTVIEW_H
