#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "contactsConst.h"
#include "companyView.h"

CompanyView::CompanyView(const QString &company, const QString &post,
                         const QString &dateIn, const QString &dateOut,
                         QWidget *parent)
    : QWidget(parent),
      m_company(new QPushButton(company + Comma)),
      m_post(new QPushButton(post + Comma)),
      m_dateIn(new QLabel(dateIn)),
      m_dateOut(new QLabel((dateOut.isEmpty()) ? Today : dateOut)),
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
