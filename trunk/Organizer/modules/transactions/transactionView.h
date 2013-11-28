#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;
class QSpinBox;

//! \class TimeView
//! \brief Класс-представление записи о финансовой транзакции.
class TransactionView : public QWidget
{
    Q_OBJECT
public:
    explicit TransactionView(int type = 0, const QString &name = QString(),
                             const qint64 &value = 0,
                             const QString &comment = QString(),
                             QWidget *parent = 0);

signals:
    void deleted();

private:
    QLabel *m_name;
    QComboBox *m_type;
    QPushButton *m_delete;
    QSpinBox *m_value;
};

#endif // TRANSACTIONVIEW_H
