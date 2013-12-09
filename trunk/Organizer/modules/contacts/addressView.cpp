#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "addressView.h"

AddressView::AddressView(QWidget *parent)
    : QWidget(parent),
      m_country(new QPushButton("Russia,")),//TEST
      m_city(new QPushButton("Samara,")),//TEST
      m_street(new QLabel("st. Avrora")),//TEST
      m_home(new QLabel("45")),//TEST
      m_apartment(new QLabel("23")),//TEST
      m_detail(new QPushButton),
      m_delete(new QPushButton)
{
    m_country->setFlat(true);
    m_city->setFlat(true);
    m_detail->setFlat(true);
    m_detail->setIcon(QIcon(":/detailInfo"));
    m_delete->setFlat(true);
    m_delete->setIcon(QIcon(":/delete"));
    QHBoxLayout *lay = new QHBoxLayout();
    lay->setMargin(0);
    lay->setSpacing(0);
    lay->addWidget(m_country);
    lay->addWidget(m_city);
    lay->addWidget(m_street);
    lay->addWidget(new QLabel(", "));
    lay->addWidget(m_home);
    lay->addWidget(new QLabel(" - "));
    lay->addWidget(m_apartment);
    lay->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    lay->addWidget(m_detail);
    lay->addWidget(m_delete);
    setLayout(lay);
    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}
