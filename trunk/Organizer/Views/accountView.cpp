#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include "accountView.h"

namespace
{
const QChar Separator = ';';
const QStringList Accounts = QObject::trUtf8("cash;card;deposit").split(Separator);
}

AccountView::AccountView(QWidget *parent)
    : QWidget(parent),
      m_name(new QLabel()),
      m_type(new QComboBox()),
      m_delete(new QPushButton()),
      m_value(new QProgressBar())
{
    m_type->addItems(Accounts);
    m_value->setMaximum(999999);
    m_value->setMaximum(0);
    m_value->setFormat("%v rub.");
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/deleteContact"));

    //test
    m_value->setValue(24);
    m_value->setMaximum(100);
    m_name->setText("Test Account");
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

void AccountView::rename(const QString &name)
{
    m_name->setText(name);
}

void AccountView::setValue(qint64 value)
{
    m_value->setValue(value);
}
