#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H

#include "dialog.h"

class QLineEdit;

class ChannelDialog : public Dialog
{
    Q_OBJECT
public:
    explicit ChannelDialog(QWidget *parent = 0);
    virtual QStringList *data();

private:
    QLineEdit *m_phone;
    QLineEdit *m_email;
    QLineEdit *m_skype;
    QLineEdit *m_site;

};

#endif // CHANNELDIALOG_H
