#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include "transactionView.h"
#include "dialogConst.h"

namespace
{
const QString DefaultTransactionName = QObject::trUtf8("Test Account");
}

TransactionView::TransactionView(int type, const QString &name,
                                 const qint64 &value, const QString &comment,
                                 QWidget *parent)
    : QWidget(parent),
      m_name(new QLabel(name.isEmpty() ? DefaultTransactionName : name)),
      m_type(new QComboBox()),
      m_delete(new QPushButton()),
      m_value(new QSpinBox())
{
    m_type->addItems(TransactionTypes);
    m_type->setCurrentIndex(type);
    m_value->setMaximum(999999);
    m_value->setMinimum(-999999);
    m_value->setSuffix(" rub.");
    m_value->setValue(value);
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/delete"));

    QHBoxLayout *lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(m_type);
    lay->addWidget(m_name);
    lay->addWidget(m_value);
    lay->addWidget(m_delete);
    setLayout(lay);
    setToolTip(comment);

    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}

void TransactionView::editableMode(bool flag)
{
    //FIXME add hide\show openDetailButton
    m_type->setEnabled(flag);
    m_value->setReadOnly(!flag);
    m_value->setButtonSymbols(flag ? QAbstractSpinBox::PlusMinus
                                   : QAbstractSpinBox::NoButtons);
}
