#ifndef DEALDIALOG_H
#define DEALDIALOG_H

#include "dialog.h"

class QDateEdit;
class QTimeEdit;
class QSpinBox;
class QLineEdit;

//! \class DealDialog
//! \brief Диалог добавления нового дела.
class DealDialog : public Dialog
{
    Q_OBJECT
public:
    explicit DealDialog(const int type = 0, QWidget *parent = 0);
    virtual QStringList *data();

private:
    QDateEdit *m_date;
    QTimeEdit *m_duration;
    QDateEdit *m_deadLine;
    QSpinBox *m_money;
    QLineEdit *m_humans;
};

#endif // DEALDIALOG_H
