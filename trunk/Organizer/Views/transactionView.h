#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;
class QSpinBox;

class TransactionView : public QWidget
{
    Q_OBJECT
public:
    explicit TransactionView(QWidget *parent = 0);

signals:
    void deleted();

private:
    QLabel *m_name;
    QComboBox *m_type;
    QPushButton *m_delete;
    QSpinBox *m_value;
};

#endif // TRANSACTIONVIEW_H
