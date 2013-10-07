#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include "cgTaskDialog.h"

cgTaskDialog::cgTaskDialog(QWidget *parent)
    : QWidget(parent),
      m_type(new QComboBox(this)),
      m_frequency(new QComboBox(this)),
      m_description(new QLineEdit(this)),
      m_price(new QDoubleSpinBox(this)),
      m_deadline(new QComboBox(this)),
      m_ok(new QPushButton(QObject::trUtf8("Ok"), this)),
      m_cancel(new QPushButton(QObject::trUtf8("Cancel"), this))
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
    static const double PriceExtremum = 999999;
    static const QChar Separator = ';';
    static const QString Title = QObject::trUtf8("Add new Task");
    static const QStringList Types = QObject::trUtf8("Task;Holiday").split(Separator);
    static const QStringList Labels = QObject::trUtf8("Type :;Frequency :;Description :;Price :;Deadline :").split(Separator);
    static const QStringList Frequencies = QObject::trUtf8("every Day;every Three day;every Week;every Mounth;every Year").split(Separator);
    static const QStringList Deadlines = QObject::trUtf8("Today;Tomorrow;This Week;This Mouth;This Year").split(Separator);

    m_type->addItems(Types);
    m_frequency->addItems(Frequencies);
    m_price->setMaximum(PriceExtremum);
    m_price->setMinimum(-PriceExtremum);
    m_deadline->addItems(Deadlines);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(5);
    buttonsLayout->addWidget(m_ok);
    buttonsLayout->addWidget(m_cancel);

    QFormLayout *mLay = new QFormLayout(this);
    mLay->addRow(Labels[0], m_type);
    mLay->addRow(Labels[1], m_frequency);
    mLay->addRow(Labels[2], m_description);
    mLay->addRow(Labels[3], m_price);
    mLay->addRow(Labels[4], m_deadline);
    mLay->addItem(buttonsLayout);
    setLayout(mLay);
    mLay->setSpacing(10);

    setWindowTitle(Title);
    setFixedSize(350, 200);
    setWindowModality(Qt::ApplicationModal);
}
