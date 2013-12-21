#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include "dialog.h"

class QDateEdit;
class QSpinBox;
class QLineEdit;
struct AccountData;

//! \class AccountDialog
//! \brief Диалог добавления нового финансового счета.
class AccountDialog : public Dialog
{
    Q_OBJECT
public:
    explicit AccountDialog(QWidget *parent = 0);
    virtual QStringList *data();
    virtual AccountData data2();

private:
    QDateEdit *m_created;
    QLineEdit *m_name;
    QSpinBox *m_value;
    QSpinBox *m_total;
};


#endif // ACCOUNTDIALOG_H
