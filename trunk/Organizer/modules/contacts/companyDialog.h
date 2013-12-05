#ifndef COMPANYDIALOG_H
#define COMPANYDIALOG_H

#include "dialog.h"

class CompanyDialog : public Dialog
{
    Q_OBJECT
public:
    explicit CompanyDialog(QWidget *parent = 0);
    virtual QStringList *data();

private:
    //FIXME
};

#endif // COMPANYDIALOG_H
