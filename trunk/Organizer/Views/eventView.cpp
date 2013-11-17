#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include "eventView.h"

namespace
{
const QString EventDescription = QObject::trUtf8("Event description");
const QString DeleteEventToolTip = QObject::trUtf8("Delete this event");
const QString DetailInformation= QObject::trUtf8("Open detail information about event");

}

EventView::EventView(QWidget *parent)
    : QWidget(parent),
      m_date(new QDateEdit),
      m_description(new QLineEdit),
      m_delete(new QPushButton),
      m_detail(new QPushButton)
{
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/deleteContact"));
    m_delete->setToolTip(DeleteEventToolTip);

    m_date->setReadOnly(true);
    m_date->setButtonSymbols(QAbstractSpinBox::NoButtons);
    m_description->setPlaceholderText(EventDescription);
    m_description->setToolTip(EventDescription);
    m_detail->setFlat(true);
    m_detail->setToolTip(DetailInformation);
    m_detail->setIcon(QIcon(":/detailInfo"));

    QHBoxLayout *lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(m_date);
    lay->addWidget(m_description);
    lay->addWidget(m_detail);
    lay->addWidget(m_delete);
    setLayout(lay);

    connect(m_detail, SIGNAL(clicked()), SIGNAL(openDetail()));
    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}
