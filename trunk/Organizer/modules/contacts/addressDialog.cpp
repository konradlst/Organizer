#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include "contactsConst.h"
#include "addressDialog.h"

AddressDialog::AddressDialog(QWidget *parent)
    : Dialog(parent),
      m_country(new QLineEdit()),
      m_city(new QLineEdit()),
      m_street(new QLineEdit()),
      m_home(new QLineEdit()),
      m_apartment(new QLineEdit())
{
    setWindowTitle(Title::address);

    m_country->setPlaceholderText(Placeholder::country);
    m_city->setPlaceholderText(Placeholder::city);
    m_street->setPlaceholderText(Placeholder::street);
    m_home->setPlaceholderText(Placeholder::home);
    m_apartment->setPlaceholderText(Placeholder::apartment);

    m_lay->addRow(Label::country, m_country);
    m_lay->addRow(Label::city, m_city);
    m_lay->addRow(Label::street, m_street);
    m_lay->addRow(Label::home, m_home);
    m_lay->addRow(Label::apartment, m_apartment);
    m_lay->addWidget(m_ok);
}

QStringList *AddressDialog::data()
{
    QStringList *data = new QStringList();
    *data << m_country->text()
          << m_city->text()
          << m_street->text()
          << m_home->text()
          << m_apartment->text();
    return data;
}
