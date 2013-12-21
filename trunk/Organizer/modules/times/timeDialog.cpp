#include <QPlainTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QTimeEdit>
#include <QComboBox>
#include "timeData.h"
#include "dialogConst.h"
#include "timeDialog.h"

TimeDialog::TimeDialog(QWidget *parent)
    : Dialog(parent),
      m_duration(new QTimeEdit()),
      m_started(new QTimeEdit(QTime::currentTime())),
      m_stoped(new QTimeEdit(QTime::currentTime())),
      m_lock(false)
{
    setWindowTitle(TimeTitle);

    m_type->addItems(TimeTypes);

    m_lay->addRow(LblType, m_type);
    m_lay->addRow(LblDuration, m_duration);
    m_lay->addRow(LblStarted, m_started);
    m_lay->addRow(LblStoped, m_stoped);
    m_lay->addRow(LblDescription, m_description);
    m_lay->addWidget(m_ok);

    connect(m_started, SIGNAL(timeChanged(QTime)), SLOT(changeDuration(QTime)));
    connect(m_stoped, SIGNAL(timeChanged(QTime)), SLOT(changeDuration(QTime)));
    connect(m_duration, SIGNAL(timeChanged(QTime)), SLOT(changeDuration(QTime)));
}

QStringList *TimeDialog::data()
{
    QStringList *data = new QStringList();
    *data << QString::number(m_type->currentIndex())
          << m_started->time().toString(TimeFormat)
          << m_stoped->time().toString(TimeFormat)
          << m_duration->time().toString(TimeFormat)
          << m_description->toPlainText();
    return data;
}

TimeData TimeDialog::data2()
{
    TimeData data;
    data.type = m_type->currentIndex();
    data.started = m_started->time();
    data.stoped = m_stoped->time();
    data.duration = m_duration->time();
    data.description = m_description->toPlainText();
    return data;
}

void TimeDialog::changeDuration(const QTime &time)
{
    if (m_lock)
        return;

    m_lock = true;
    if (sender() == m_duration)
    {
        m_stoped->setTime(m_started->time().addSecs(QTime(0,0).secsTo(time)));
    }
    else if (sender() == m_started)
    {
        if (time > m_stoped->time())
            m_stoped->setTime(time);
        m_duration->setTime(QTime(0,0).addSecs(time.secsTo(m_stoped->time())));
    }
    else if (sender() == m_stoped)
    {
        if (time < m_started->time())
            m_started->setTime(time);
        m_duration->setTime(QTime(0,0).addSecs(m_started->time().secsTo(time)));
    }
    m_lock = false;
}
