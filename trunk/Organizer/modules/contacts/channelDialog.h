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
    QComboBox *m_type;
    QLineEdit *m_subType;
    QLineEdit *m_value;
};

#endif // CHANNELDIALOG_H
