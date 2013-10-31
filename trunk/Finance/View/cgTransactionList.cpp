#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QDateEdit>
#include "cgTransactionList.h"

namespace
{
const QString DateFormat = QObject::trUtf8("ddd, dd MMMM yyyy года");
const QString AddTransaction = QObject::trUtf8("Add Transaction");
const QString Today = QObject::trUtf8("Today");
const QString FinanceSuffix = " p.";
}

cgTransactionList::cgTransactionList()
    : m_view(new QGroupBox(Today)),
      m_mainLayout(new QFormLayout(m_view))
{
    createView();
}

QWidget* cgTransactionList::view()
{
    return m_view;
}

void cgTransactionList::addTransaction(const cgTransaction &trans)
{
    QDoubleSpinBox *value = doubleSpinBox();
    value->setValue(trans.m_value);
    m_mainLayout->addRow(trans.m_comment, value);
}

void cgTransactionList::createView()
{
    QDateEdit *date = new QDateEdit(QDate::currentDate());
    date->setFrame(false);
    date->setReadOnly(true);
    date->setButtonSymbols(QDateEdit::NoButtons);
    date->setAlignment(Qt::AlignCenter);
    date->setDisplayFormat(DateFormat);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    m_mainLayout->addRow(date);
    m_mainLayout->addRow(new QPushButton(AddTransaction));
    m_mainLayout->addRow(line);
}

QDoubleSpinBox *cgTransactionList::doubleSpinBox()
{
    QDoubleSpinBox *dsbox = new QDoubleSpinBox();
    dsbox->setReadOnly(true);
    dsbox->setButtonSymbols(QDoubleSpinBox::NoButtons);
    dsbox->setSuffix(FinanceSuffix);
    dsbox->setMinimum(-100000);
    dsbox->setMaximum(100000);
    return dsbox;
}
