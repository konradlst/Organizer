#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include "contactsConst.h"
#include "channelDialog.h"

ChannelDialog::ChannelDialog(QWidget *parent)
    : Dialog(parent),
      m_phone(new QLineEdit()),
      m_email(new QLineEdit()),
      m_skype(new QLineEdit()),
      m_site(new QLineEdit())
{
    setWindowTitle(Title::channel);

    m_phone->setPlaceholderText(Placeholder::phone);
    m_email->setPlaceholderText(Placeholder::email);
    m_skype->setPlaceholderText(Placeholder::skype);
    m_site->setPlaceholderText(Placeholder::site);

    m_lay->addRow(Label::phone, m_phone);
    m_lay->addRow(Label::email, m_email);
    m_lay->addRow(Label::skype, m_skype);
    m_lay->addRow(Label::site, m_site);
    m_lay->addWidget(m_ok);
}

QStringList *ChannelDialog::data()
{
    QStringList *data = new QStringList();
    *data << m_phone->text()
          << m_email->text()
          << m_skype->text()
          << m_site->text();
    return data;
}
