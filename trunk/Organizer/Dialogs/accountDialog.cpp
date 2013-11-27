#include <QPlainTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include "dialogConst.h"
#include "accountDialog.h"

AccountDialog::AccountDialog(QWidget *parent)
    : Dialog(parent),
      m_created(new QDateEdit(QDate::currentDate())),
      m_name(new QLineEdit()),
      m_value(new QSpinBox()),
      m_total(new QSpinBox())
{
    setWindowTitle(AccountTitle);

    m_type->addItems(AccountTypes);
    m_value->setMaximum(999999);
    m_value->setMinimum(-999999);
    m_name->setPlaceholderText(AccountNamePlaceholder);

    m_lay->addRow(LblType, m_type);
    m_lay->addRow(LblCreated, m_created);
    m_lay->addRow(LblName, m_name);
    m_lay->addRow(LblValue, m_value);
    m_lay->addRow(LblTotal, m_total);
    m_lay->addRow(LblDescription, m_description);
    m_lay->addWidget(m_ok);
}

QStringList *AccountDialog::data()
{
    QStringList *data = new QStringList();
    *data << QString::number(m_type->currentIndex())
          << m_created->date().toString(DateFormat)
          << m_name->text()
          << QString::number(m_value->value())
          << QString::number(m_total->value())
          << m_description->toPlainText();
    return data;
}
