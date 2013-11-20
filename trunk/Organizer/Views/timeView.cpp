#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTimeEdit>
#include <QLineEdit>
#include <QLabel>
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

TimeView::TimeView(QWidget *parent)
    : QWidget(parent),
      m_type(new QComboBox),
      m_start(new QTimeEdit),
      m_stop(new QTimeEdit),
      m_duration(new QTimeEdit),
      m_comment(new QLineEdit),
      m_delete(new  QPushButton)
{
    m_type->addItems(TimeType);
    m_comment->setPlaceholderText(CommentPlaceholder);
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/deleteContact"));

    //test
    m_start->setTime(QTime(7, 15));
    m_stop->setTime(QTime(21, 30));
    m_duration->setTime(QTime(14, 15));
    //end test

    QHBoxLayout *lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(m_type);
    lay->addWidget(vLine());
    lay->addWidget(m_duration);
    lay->addWidget(vLine());
    lay->addWidget(m_start);
    lay->addWidget(new QLabel(" - "));
    lay->addWidget(m_stop);
    lay->addWidget(vLine());
    lay->addWidget(m_comment);
    lay->addWidget(m_delete);
    setLayout(lay);

    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}
