#ifndef COMPANYDIALOG_H
#define COMPANYDIALOG_H

#include "dialog.h"

class QLineEdit;
class QDateEdit;
struct CompanyData;

class CompanyDialog : public Dialog
{
    Q_OBJECT
public:
    explicit CompanyDialog(QWidget *parent = 0);
    virtual QStringList *data();
    virtual CompanyData data2() const;

private:
    QLineEdit *m_name;
    QLineEdit *m_phone;
    QLineEdit *m_department;
    QLineEdit *m_post;
    QLineEdit *m_address;
    QDateEdit *m_dateIn;
    QDateEdit *m_dateOut;
};

#endif // COMPANYDIALOG_H
