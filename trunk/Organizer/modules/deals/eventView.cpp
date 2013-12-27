#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include "dealData.h"
#include "eventView.h"

namespace
{
const QString EventDescription = QObject::trUtf8("Event description");
const QString DeleteEventToolTip = QObject::trUtf8("Delete this event");
const QString DetailInformation= QObject::trUtf8("Open detail information about event");
}

EventView::EventView(const QDate &date, const QString &description, QWidget *parent)
    : QWidget(parent),
      m_date(new QDateEdit(date)),
      m_description(new QLineEdit(description)),
      m_delete(new QPushButton),
      m_detail(new QPushButton)
{
    createInterface();
}

EventView::EventView(const DealData &data)
    : m_date(new QDateEdit(data.created)),
      m_description(new QLineEdit(data.description)),
      m_delete(new QPushButton),
      m_detail(new QPushButton)
{
    createInterface();
}

void EventView::editableMode(bool flag)
{
    m_description->setReadOnly(!flag);
    m_date->setReadOnly(!flag);
    m_date->setCalendarPopup(flag);
    m_detail->setVisible(flag);
    m_date->setButtonSymbols(flag ? QAbstractSpinBox::UpDownArrows
                                  : QAbstractSpinBox::NoButtons);
}

void EventView::createInterface()
{
    m_date->setCalendarPopup(true);
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/delete"));
    m_delete->setToolTip(DeleteEventToolTip);

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
