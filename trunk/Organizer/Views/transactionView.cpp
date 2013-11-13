#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include "transactionView.h"

namespace
{
const QChar Separator = ';';
const QStringList FinanceOperation = QObject::trUtf8("debet;credit;transfer").split(Separator);
}

TransactionView::TransactionView(QWidget *parent)
    : QWidget(parent),
      m_name(new QLabel()),
      m_type(new QComboBox()),
      m_delete(new QPushButton()),
      m_value(new QSpinBox())
{
    m_type->addItems(FinanceOperation);
    m_value->setMaximum(999999);
    m_value->setMaximum(-999999);
    m_value->setSuffix(" rub.");
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/deleteContact"));

    //test
    m_value->setMaximum(100);
    m_value->setValue(24);
    m_name->setText("Test Transaction");
    //end test

    QHBoxLayout *lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(m_type);
    lay->addWidget(m_name);
    lay->addWidget(m_value);
    lay->addWidget(m_delete);
    setLayout(lay);

    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}
