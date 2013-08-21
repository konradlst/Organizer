#include "contactView.h"
#include <QLayout>
#include <QFormLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QDateEdit>
#include <QLineEdit>
#include <QLabel>
#include "contactData.h"

ContactView::ContactView(QWidget *parent)
    : QWidget(parent),
      m_mainLay(new QVBoxLayout),
      m_property(new QTabWidget),
      m_userPic(new QLabel),
      m_setUserPic(new QPushButton("...")),
      m_alias(new QLineEdit),
      m_name(new QLineEdit),
      m_surName(new QLineEdit),
      m_otherName(new QLineEdit),
      m_birthday(new QDateEdit)
{
    createInterface();
    createGrid();
}

void ContactView::createInterface()
{
    m_birthday->setCalendarPopup(true);
    m_userPic->setPixmap(QPixmap(":/logo"));
    m_setUserPic->setFixedSize(20, 20);
}

void ContactView::createGrid()
{
    QGridLayout *gridLay = new QGridLayout;
    gridLay->addWidget(m_userPic, 0, 0, 5, 5);
    gridLay->addWidget(m_setUserPic, 0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft);

    QFormLayout *formLay = new QFormLayout;
    formLay->addRow(Attribute::Alias, m_alias);
    formLay->addRow(Attribute::Name, m_name);
    formLay->addRow(Attribute::LastName, m_surName);
    formLay->addRow(Attribute::OtherName, m_otherName);
    formLay->addRow(Attribute::Birthday, m_birthday);

    QHBoxLayout *hLay = new QHBoxLayout;
    hLay->addLayout(gridLay);
    hLay->addLayout(formLay);

    QWidget *address = new QWidget;
    address->setLayout(new QFormLayout);
    m_property->addTab(address, Attribute::Address);

    m_mainLay->addLayout(hLay);
    m_mainLay->addWidget(m_property);
    setLayout(m_mainLay);
}
