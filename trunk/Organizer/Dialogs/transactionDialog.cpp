#include <QPlainTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include "dialogConst.h"
#include "transactionDialog.h"

TransactionDialog::TransactionDialog(QWidget *parent)
    : Dialog(parent),
      m_created(new QDateEdit()),
      m_name(new QLineEdit()),
      m_value(new QSpinBox())
{
    setWindowTitle(TransactionTitle);

    m_name->setPlaceholderText(TransactionNamePlaceholder);

    m_lay->addRow(LblType, m_type);
    m_lay->addRow(LblCreated, m_created);
    m_lay->addRow(LblName, m_name);
    m_lay->addRow(LblValue, m_value);
    m_lay->addRow(LblDescription, m_description);
    m_lay->addWidget(m_ok);
}

QStringList *TransactionDialog::data()
{
    QStringList *data = new QStringList();
    *data << m_type->currentText()
          << m_created->date().toString(DateFormat)
          << m_name->text()
          << QString::number(m_value->value())
          << m_description->toPlainText();
    return data;
}
