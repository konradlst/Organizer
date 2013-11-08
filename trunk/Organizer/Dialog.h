#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class TimeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TimeDialog(QWidget *parent = 0);
};

class NoteDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NoteDialog(QWidget *parent = 0);
};

#endif // DIALOG_H
