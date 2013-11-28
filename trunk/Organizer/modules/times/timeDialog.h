#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

#include "dialog.h"

class QTimeEdit;

//! \class TimeDialog
//! \brief Диалог добавления записи о потраченном времени.
class TimeDialog : public Dialog
{
    Q_OBJECT
public:
    explicit TimeDialog(QWidget *parent = 0);
    virtual QStringList *data();

private slots:
    void changeDuration(const QTime &time);

private:
    QTimeEdit *m_duration;
    QTimeEdit *m_started;
    QTimeEdit *m_stoped;
    bool m_lock;
};


#endif // TIMEDIALOG_H
