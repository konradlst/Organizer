#include <QLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include "contactView.h"

ContactView::ContactView(QWidget *parent) :
    QWidget(parent),
    m_mainLay(new QVBoxLayout),
    m_property(new QTableWidget),
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
    setDefaultSettings();
}

void ContactView::createInterface()
{
    m_birthday->setCalendarPopup(true);
    m_userPic->setPixmap(QPixmap(":/logo"));
    m_setUserPic->setFixedSize(20,20);
}

void ContactView::createGrid()
{
    QHBoxLayout *hLay = new QHBoxLayout;
    QGridLayout *gridLay = new QGridLayout;
    gridLay->addWidget(m_userPic, 0, 0, 5, 5);
    gridLay->addWidget(m_setUserPic, 0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft);

    QFormLayout *formLay = new QFormLayout;
    formLay->addRow("Alias :", m_alias);
    formLay->addRow("Name :", m_name);
    formLay->addRow("SurName :", m_surName);
    formLay->addRow("OtherName :", m_otherName);
    formLay->addRow("Birthday :", m_birthday);

    hLay->addLayout(gridLay);
    hLay->addLayout(formLay);

    m_mainLay->addLayout(hLay);
    m_mainLay->addWidget(m_property);
    setLayout(m_mainLay);
}

void ContactView::setDefaultSettings()
{
}
