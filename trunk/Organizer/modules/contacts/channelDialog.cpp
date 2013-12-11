#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include "contactsConst.h"
#include "channelDialog.h"

ChannelDialog::ChannelDialog(QWidget *parent)
    : Dialog(parent),
      m_type(new QComboBox),
      m_subType(new QLineEdit),
      m_value(new QLineEdit)
{
    setWindowTitle(Title::channel);

    m_type->addItems(ChannelTypes);
    m_subType->setPlaceholderText(Placeholder::subType);
    m_value->setPlaceholderText(Placeholder::value);

    m_lay->addRow(Label::type, m_type);
    m_lay->addRow(Label::subType, m_subType);
    m_lay->addRow(Label::value, m_value);
    m_lay->addWidget(m_ok);
}

QStringList *ChannelDialog::data()
{
    QStringList *data = new QStringList();
    *data << m_type->currentText()
          << m_subType->text()
          << m_value->text();
    return data;
}
