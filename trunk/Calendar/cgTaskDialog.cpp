#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "cgTaskDialog.h"

cgTaskDialog::cgTaskDialog(QWidget *parent)
    : QWidget(parent),
      m_type(new QComboBox(this)),
      m_frequency(new QComboBox(this)),
      m_description(new QLineEdit(this)),
      m_price(new QDoubleSpinBox(this)),
      m_deadline(new QComboBox(this)),
      m_ok(new QPushButton("Ok", this)),
      m_cancel(new QPushButton("Cancel", this))
{
    createInterface();
}

void cgTaskDialog::init(Calendar::TaskType type,
                        Calendar::Duration frequency,
                        QString description,
                        double price,
                        Calendar::Duration deadline)
{
    m_type->setCurrentIndex(type);
    m_frequency->setCurrentIndex(frequency.second);
    m_description->setText(description);
    m_price->setValue(price);
    m_deadline->setCurrentIndex(deadline.second);
}

QStringList cgTaskDialog::data()
{
    QStringList list;
    return list << m_type->currentText()
                << m_frequency->currentText()
                << m_description->text()
                << QString::number(m_price->value())
                << m_deadline->currentText();
}

void cgTaskDialog::createInterface()
{
    // Create gialog.
    // type: Holiday\Task
    // frequency: every___Day\every___Week\every___Mounth\every___Year
    // description: ____
    // price: ___
    // deadline: __day\__date\__week\__mouth\__year
    // Ok & Cancel

    m_type->addItems(QString("Holiday;Task").split(";"));
    m_frequency->addItems(QString("every Day;every Week;every Mounth;every Year").split(";"));
    m_deadline->addItems(QString("Today;Date;Week;Mouth;Year").split(";"));

    static const QStringList labels = QString("Type :;Frequency :;Description :;Price :;Deadline :").split(";");
    QFormLayout *mLay = new QFormLayout(this);
    mLay->addRow(labels[0], m_type);
    mLay->addRow(labels[1], m_frequency);
    mLay->addRow(labels[2], m_description);
    mLay->addRow(labels[3], m_price);
    mLay->addRow(labels[4], m_deadline);
    mLay->addWidget(m_ok);
    mLay->addWidget(m_cancel);
    setLayout(mLay);

    setWindowTitle("Add new Task");
    setWindowModality(Qt::ApplicationModal);
}
