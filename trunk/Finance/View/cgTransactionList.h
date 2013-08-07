#ifndef CGTRANSACTIONLIST_H
#define CGTRANSACTIONLIST_H

#include <QObject>
#include <QDateTime>
class QDoubleSpinBox;
class QFormLayout;

struct cgTransaction
{
    cgTransaction() :
        m_datetime(QDateTime::currentDateTime()),
        m_value(0)
    {}
    QDateTime m_datetime;
    QString m_from;
    QString m_to;
    QString m_operation;
    qint64 m_value;
    QString m_comment;
};

class cgTransactionList
{
public:
    cgTransactionList();
    QWidget *view();
    void addTransaction(const cgTransaction &trans);

private:
    QWidget *m_view;
    QFormLayout *m_mainLayout;

    void createView();
    QDoubleSpinBox *doubleSpinBox();
};

#endif // CGTRANSACTIONLIST_H
