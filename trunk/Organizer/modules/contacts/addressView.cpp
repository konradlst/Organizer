#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "contactsConst.h"
#include "addressView.h"

AddressView::AddressView(const QString &country, const QString &city,
                         const QString &street, const QString &home,
                         const QString &apartment, QWidget *parent)
    : QWidget(parent),
      m_country(new QPushButton(country + Comma)),
      m_city(new QPushButton(city + Comma)),
      m_street(new QLabel(street)),
      m_home(new QLabel(home)),
      m_apartment(new QLabel(apartment)),
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
