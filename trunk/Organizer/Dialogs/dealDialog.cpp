#include <QPlainTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include "dialogConst.h"
#include "dealDialog.h"

DealDialog::DealDialog(const int type, QWidget *parent)
    : Dialog(parent),
      m_date(new QDateEdit()),
      m_duration(new QTimeEdit()),
      m_deadLine(new QDateEdit()),
      m_money(new QSpinBox()),
      m_humans(new QLineEdit())
{
    setWindowTitle(DealTitle);

    m_type->addItems(DealTypes);
    m_type->setCurrentIndex(type);
    m_humans->setPlaceholderText(HumansPlaceholder);

    m_lay->addRow(LblType, m_type);
    m_lay->addRow(LblDate, m_date);
    m_lay->addRow(LblDuration, m_duration);
    m_lay->addRow(LblDeadLine, m_deadLine);
    m_lay->addRow(LblMoney, m_money);
    m_lay->addRow(LblHumans, m_humans);
    m_lay->addRow(LblDescription, m_description);
    m_lay->addWidget(m_ok);
}

QStringList *DealDialog::data()
{
    QStringList *data = new QStringList();
    *data << m_type->currentText()
          << m_date->date().toString(DateFormat)
          << m_duration->time().toString(TimeFormat)
          << m_deadLine->date().toString(DateFormat)
          << QString::number(m_money->value())
          << m_humans->text()
          << m_description->toPlainText();
    return data;
}
