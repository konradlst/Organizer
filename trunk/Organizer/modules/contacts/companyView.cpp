#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "companyView.h"

CompanyView::CompanyView(QWidget *parent)
    : QWidget(parent),
      m_company(new QPushButton("Atol,")),//TEST
      m_post(new QPushButton("software developer,")),//TEST
      m_dateIn(new QLabel("25.02.2012")),//TEST
      m_dateOut(new QLabel("today")),//TEST
      m_detail(new QPushButton),
      m_delete(new QPushButton)
{
    m_company->setFlat(true);
    m_post->setFlat(true);
    m_detail->setFlat(true);
    m_detail->setIcon(QIcon(":/detailInfo"));
    m_delete->setFlat(true);
    m_delete->setIcon(QIcon(":/delete"));
    QHBoxLayout *lay = new QHBoxLayout();
    lay->setMargin(0);
    lay->setSpacing(0);
    lay->addWidget(m_company);
    lay->addWidget(m_post);
    lay->addWidget(new QLabel(" ( "));
    lay->addWidget(m_dateIn);
    lay->addWidget(new QLabel(" - "));
    lay->addWidget(m_dateOut);
    lay->addWidget(new QLabel(" )"));
    lay->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    lay->addWidget(m_detail);
    lay->addWidget(m_delete);
    setLayout(lay);
    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}
