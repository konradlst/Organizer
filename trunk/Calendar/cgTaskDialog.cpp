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
    connect(m_ok, SIGNAL(clicked()), SLOT(close()));
    connect(m_cancel, SIGNAL(clicked()), SLOT(close()));
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

QStringList cgTaskDialog::data() const
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
    m_type->addItems(QString("Task;Holiday").split(";"));
    m_frequency->addItems(QString("every Day;every Three day;every Week;every Mounth;every Year").split(";"));
    m_price->setMaximum(999999);
    m_price->setMinimum(-999999);
    m_deadline->addItems(QString("Today;Tomorrow;This Week;This Mouth;This Year").split(";"));

    static const QStringList labels = QString("Type :;Frequency :;Description :;Price :;Deadline :").split(";");
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(5);
    buttonsLayout->addWidget(m_ok);
    buttonsLayout->addWidget(m_cancel);

    QFormLayout *mLay = new QFormLayout(this);
    mLay->addRow(labels[0], m_type);
    mLay->addRow(labels[1], m_frequency);
    mLay->addRow(labels[2], m_description);
    mLay->addRow(labels[3], m_price);
    mLay->addRow(labels[4], m_deadline);
    mLay->addItem(buttonsLayout);
    setLayout(mLay);
    mLay->setSpacing(10);

    setWindowTitle("Add new Task");
    setFixedSize(350, 200);
    setWindowModality(Qt::ApplicationModal);
}
