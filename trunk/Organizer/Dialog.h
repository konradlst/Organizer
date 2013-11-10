#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class TimeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TimeDialog(QWidget *parent = 0);
};

class DealDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DealDialog(QWidget *parent = 0);
};

class AccountDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AccountDialog(QWidget *parent = 0);
};

#endif // DIALOG_H
