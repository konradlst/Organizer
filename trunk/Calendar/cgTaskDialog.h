#ifndef CGTASKDIALOG_H
#define CGTASKDIALOG_H

#include <QDialog>

class cgTaskDialog : public QWidget
{
    Q_OBJECT
public:
    explicit cgTaskDialog(QWidget *parent = 0);

private:
    void createInterface();
};

#endif // CGTASKDIALOG_H
