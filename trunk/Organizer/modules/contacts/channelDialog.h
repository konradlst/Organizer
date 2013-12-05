#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H

#include "dialog.h"

class ChannelDialog : public Dialog
{
    Q_OBJECT
public:
    explicit ChannelDialog(QWidget *parent = 0);
    virtual QStringList *data();

private:
    //FIXME

};

#endif // CHANNELDIALOG_H
