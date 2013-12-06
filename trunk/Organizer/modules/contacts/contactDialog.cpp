#include <QPlainTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QLineEdit>
#include "contactsConst.h"
#include "contactDialog.h"

ContactDialog::ContactDialog(QWidget *parent)
    : Dialog(parent),
      m_alias(new QLineEdit),
      m_name(new QLineEdit),
      m_surName(new QLineEdit),
      m_otherName(new QLineEdit),
      m_birthday(new QDateEdit),
      m_channels(new QList<Channel>),
      m_country(new QLineEdit),
      m_city(new QLineEdit),
      m_street(new QLineEdit),
      m_home(new QLineEdit),
      m_apartment(new QLineEdit),
      m_companyName(new QLineEdit),
      m_companyPhone(new QLineEdit),
      m_department(new QLineEdit),
      m_post(new QLineEdit),
      m_companyAddress(new QLineEdit),
      m_startWork(new QDateEdit),
      m_endWork(new QDateEdit)
{
    setWindowTitle(Title::contact);
    //FIXME correct init and create view

    m_alias->setPlaceholderText(Placeholder::alias);
    m_name->setPlaceholderText(Placeholder::name);
    m_surName->setPlaceholderText(Placeholder::surName);
    m_otherName->setPlaceholderText(Placeholder::otherName);

    m_lay->addRow(Label::alias, m_alias);
    m_lay->addRow(Label::name, m_name);
    m_lay->addRow(Label::surName, m_surName);
    m_lay->addRow(Label::otherName, m_otherName);
    m_lay->addRow(Label::birthday, m_birthday);
    m_lay->addRow(Label::description, m_description);
    m_lay->addWidget(m_ok);
}

QStringList *ContactDialog::data()
{
    //FIXME add channels
    QStringList *data = new QStringList();
    *data << m_alias->text()
          << m_name->text()
          << m_surName->text()
          << m_otherName->text()
          << m_birthday->date().toString(DateFormat)
          << m_country->text()
          << m_city->text()
          << m_street->text()
          << m_home->text()
          << m_apartment->text()
          << m_companyName->text()
          << m_companyPhone->text()
          << m_department->text()
          << m_post->text()
          << m_startWork->date().toString(DateFormat)
          << m_endWork->date().toString(DateFormat)
          << m_companyAddress->text();
    return data;
}
