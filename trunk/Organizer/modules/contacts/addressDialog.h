#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include "dialog.h"

class AddressDialog : public Dialog
{
    Q_OBJECT
public:
    explicit AddressDialog(QWidget *parent = 0);
    virtual QStringList *data();

private:
    //FIXME

};

#endif // ADDRESSDIALOG_H
