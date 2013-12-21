#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include "dialog.h"

class QDateEdit;
class QSpinBox;
class QLineEdit;
struct TransactionData;

//! \class TransactionDialog
//! \brief Диалог добавления новой финансовой операции.
class TransactionDialog : public Dialog
{
    Q_OBJECT
public:
    explicit TransactionDialog(QWidget *parent = 0);
    virtual QStringList *data();
    virtual TransactionData data2();

private:
    QDateEdit *m_created;
    QLineEdit *m_name;
    QSpinBox *m_value;
};


#endif // TRANSACTIONDIALOG_H
