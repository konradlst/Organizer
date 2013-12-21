#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;
class QSpinBox;
struct TransactionData;

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
    explicit TransactionView(const TransactionData &data);

signals:
    void deleted();

public slots:
    void editableMode(bool flag);

private:
    QLabel *m_name;
    QComboBox *m_type;
    QPushButton *m_delete;
    QSpinBox *m_value;

    void createInterface(const TransactionData &data);
};

#endif // TRANSACTIONVIEW_H
