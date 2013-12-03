#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include "accountView.h"
#include "dialogConst.h"

namespace
{
const QString DefaultAccountName = QObject::trUtf8("Test Account");
}

AccountView::AccountView(int type, const QString &name,
                         const qint64 &value, const qint64 &maxValue,
                         const QString &comment, QWidget *parent)
    : QWidget(parent),
      m_name(new QLabel(name.isEmpty() ? DefaultAccountName : name)),
      m_type(new QComboBox()),
      m_delete(new QPushButton()),
      m_value(new QProgressBar())
{
    m_type->addItems(AccountTypes);
    m_type->setCurrentIndex(type);
    m_value->setMaximum(maxValue < value ? 999999 : maxValue);
    m_value->setMinimum(0);
    m_value->setFormat("%v rub.");
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

void AccountView::rename(const QString &name)
{
    m_name->setText(name);
}

void AccountView::setValue(qint64 value)
{
    m_value->setValue(value);
}

void AccountView::editableMode(bool flag)
{
    //FIXME add hide\show openDetailButton
    m_type->setEnabled(flag);
}
