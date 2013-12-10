#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

#include <QWidget>
#include <QDialog>

class AbstractView : public QWidget
{
};

class AbstractDialog : public QDialog
{
};

struct AbstractData
{
};

class AbstractModule : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractModule(AbstractData *data = 0, QWidget *parent = 0);
    AbstractData *data();
    AbstractView *view();
    AbstractDialog *dialog();

private:
    AbstractData *m_data;
    AbstractView *m_view;
    AbstractDialog *m_dialog;
};

#endif // ABSTRACTMODULE_H
