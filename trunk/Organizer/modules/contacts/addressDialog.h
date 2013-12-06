#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include "dialog.h"

class QLineEdit;

class AddressDialog : public Dialog
{
    Q_OBJECT
public:
    explicit AddressDialog(QWidget *parent = 0);
    virtual QStringList *data();

private:
    QLineEdit *m_country;
    QLineEdit *m_city;
    QLineEdit *m_street;
    QLineEdit *m_home;
    QLineEdit *m_apartment;
};

#endif // ADDRESSDIALOG_H
