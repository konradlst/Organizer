﻿#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTimeEdit>
#include <QLineEdit>
#include <QLabel>
#include "timeData.h"
#include "timeView.h"

namespace
{
const QChar Separator = ';';
const QStringList TimeType = QString("sleep;work;travel;study;sport;read").split(Separator);
const QString CommentPlaceholder = QObject::trUtf8("Time description (comment)");

QWidget *vLine()
{
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}
}

TimeView::TimeView(const int type, const QTime &start, const QTime &stop,
                   const QTime &duration, const QString &comment,
                   QWidget *parent)
    : QWidget(parent),
      m_type(new QComboBox),
      m_start(new QTimeEdit),
      m_stop(new QTimeEdit),
      m_duration(new QTimeEdit),
      m_comment(new QLineEdit),
      m_delete(new  QPushButton),
      m_lock(false)
{
    TimeData data;
    data.type = type;
    data.started = start;
    data.stoped = stop;
    data.duration = duration;
    data.description = comment;

    createInterface(data);
}

TimeView::TimeView(const TimeData &data)
    : m_type(new QComboBox),
      m_start(new QTimeEdit),
      m_stop(new QTimeEdit),
      m_duration(new QTimeEdit),
      m_comment(new QLineEdit),
      m_delete(new  QPushButton),
      m_lock(false)
{
    createInterface(data);
}

void TimeView::editableMode(bool flag)
{
    //FIXME add hide\show openDetailButton
    m_type->setEnabled(flag);
    m_start->setReadOnly(!flag);
    m_start->setButtonSymbols(flag ? QAbstractSpinBox::UpDownArrows
                                   : QAbstractSpinBox::NoButtons);
    m_stop->setReadOnly(!flag);
    m_stop->setButtonSymbols(flag ? QAbstractSpinBox::UpDownArrows
                                  : QAbstractSpinBox::NoButtons);
    m_duration->setReadOnly(!flag);
    m_duration->setButtonSymbols(flag ? QAbstractSpinBox::UpDownArrows
                                      : QAbstractSpinBox::NoButtons);
    m_comment->setReadOnly(!flag);
}

void TimeView::changeDuration(const QTime &time)
{
    if (m_lock)
        return;

    m_lock = true;
    if (sender() == m_duration)
    {
        m_stop->setTime(m_start->time().addSecs(QTime(0,0).secsTo(time)));
    }
    else if (sender() == m_start)
    {
        if (time > m_stop->time())
            m_stop->setTime(time);
        m_duration->setTime(QTime(0,0).addSecs(time.secsTo(m_stop->time())));
    }
    else if (sender() == m_stop)
    {
        if (time < m_start->time())
            m_start->setTime(time);
        m_duration->setTime(QTime(0,0).addSecs(m_start->time().secsTo(time)));
    }
    m_lock = false;
}

void TimeView::createInterface(const TimeData &data)
{
    m_type->addItems(TimeType);
    m_type->setCurrentIndex(data.type);
    m_comment->setText(data.description);
    m_comment->setPlaceholderText(CommentPlaceholder);
    m_start->setTime(data.started);
    m_stop->setTime(data.stoped);
    m_duration->setTime(data.duration);
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/delete"));

    QHBoxLayout *lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(m_type);
    lay->addWidget(vLine());
    lay->addWidget(m_start);
    lay->addWidget(new QLabel(" - "));
    lay->addWidget(m_stop);
    lay->addWidget(vLine());
    lay->addWidget(m_duration);
    lay->addWidget(vLine());
    lay->addWidget(m_comment);
    lay->addWidget(m_delete);
    setLayout(lay);

    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
    connect(m_start, SIGNAL(timeChanged(QTime)), SLOT(changeDuration(QTime)));
    connect(m_stop, SIGNAL(timeChanged(QTime)), SLOT(changeDuration(QTime)));
    connect(m_duration, SIGNAL(timeChanged(QTime)), SLOT(changeDuration(QTime)));
}
