#include <QPlainTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QLineEdit>
#include "contactsConst.h"
#include "contactData.h"
#include "contactDialog.h"

ContactDialog::ContactDialog(QWidget *parent)
    : Dialog(parent),
      m_alias(new QLineEdit),
      m_name(new QLineEdit),
      m_surName(new QLineEdit),
      m_otherName(new QLineEdit),
      m_birthday(new QDateEdit)
{
    setWindowTitle(Title::contact);

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
    QStringList *data = new QStringList();
    *data << m_alias->text()
          << m_name->text()
          << m_surName->text()
          << m_otherName->text()
          << m_birthday->date().toString(DateFormat);
    return data;
}

ContactData ContactDialog::data2() const
{
    ContactData data;
    data.name = m_name->text();
    data.surName = m_surName->text();
    data.otherName = m_otherName->text();
    data.nickName = m_alias->text();
    data.birthday = m_birthday->date().toString(DateFormat);
    return data;
}
