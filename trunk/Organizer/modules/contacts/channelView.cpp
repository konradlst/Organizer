#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "channelView.h"

ChannelView::ChannelView(const QString &type, const QString &subType,
                         const QString &value, QWidget *parent)
    : QWidget(parent),
      m_type(new QPushButton(type)),
      m_subType(new QLabel(subType)),
      m_value(new QLabel(value)),
      m_detail(new QPushButton()),
      m_delete(new QPushButton())
{
    m_type->setFlat(true);
    m_detail->setFlat(true);
    m_detail->setIcon(QIcon(":/detailInfo"));
    m_delete->setFlat(true);
    m_delete->setIcon(QIcon(":/delete"));
    QHBoxLayout *lay = new QHBoxLayout();
    lay->setMargin(0);
    lay->setSpacing(0);
    lay->addWidget(m_type);
    lay->addWidget(new QLabel("( "));
    lay->addWidget(m_subType);
    lay->addWidget(new QLabel(" ) : "));
    lay->addWidget(m_value);
    lay->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    lay->addWidget(m_detail);
    lay->addWidget(m_delete);
    setLayout(lay);
    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}
