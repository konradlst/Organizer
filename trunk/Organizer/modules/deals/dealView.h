#ifndef DEALVIEW_H
#define DEALVIEW_H

#include <QGroupBox>

class QDateEdit;
class QTimeEdit;
class QComboBox;
class QSpinBox;
class QLineEdit;
class QPushButton;

//! \class DealView
//! \brief Класс-представление записи о деле.
class DealView : public QGroupBox
{
    Q_OBJECT
public:
    explicit DealView(const int type, const QDate &created, const int price,
                      const QTime &duration, const QDate &deadline,
                      const QString &humans, const QString &description,
                      QGroupBox *parent = 0);

signals:
    void deleted();

private:
    QDateEdit *m_created;
    QTimeEdit *m_duration;
    QComboBox *m_type;
    QSpinBox *m_price;
    QDateEdit *m_deadline;
    QLineEdit *m_humans;
    QLineEdit *m_description;
    QPushButton *m_delete;
};

#endif // DEALVIEW_H
