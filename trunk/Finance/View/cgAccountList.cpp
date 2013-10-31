#include <QDoubleSpinBox>
#include <QProgressBar>
#include <QFormLayout>
#include <QGroupBox>
#include <QFrame>
#include "cgAccountList.h"

namespace
{
const QString Accounts = QObject::trUtf8("Accounts");
const QString Total = QObject::trUtf8("Total :");
const QString FinanceFormat = "%v p.";
const QString FinanceSuffix = " p.";
}

cgAccountList::cgAccountList()
    : m_view(new QGroupBox(Accounts)),
      m_mainLayout(new QFormLayout(m_view)),
      m_totalView(new QDoubleSpinBox),
      m_total(0),
      m_accounts(new QList<cgAccount>()),
      m_accountsView(new QHash<QString,QProgressBar *>())
{
    createView();
    m_totalView->setValue(m_total);
}

QWidget *cgAccountList::view()
{
    return m_view;
}

void cgAccountList::addAccount(const cgAccount &account)
{
    QProgressBar *bar = new QProgressBar();

    m_accountsView->insert(account.m_name, bar);
    m_accounts->append(account);
    m_total += account.m_value;

    bar->setTextVisible(true);
    bar->setFormat(FinanceFormat);
    QList<QString> list = m_accountsView->keys();
    foreach (QString key, list)
        m_accountsView->value(key)->setMaximum(m_total);
    bar->setValue(account.m_value);

    m_mainLayout->insertRow(0, account.m_name, bar);
}

bool cgAccountList::removeAccount(const int &index)
{
    m_accountsView->remove(m_accounts->at(index).m_name);
    m_total -= m_accounts->at(index).m_value;
    m_accounts->removeAt(index);

    delete m_mainLayout->itemAt(index, QFormLayout::LabelRole);
    delete m_mainLayout->itemAt(index, QFormLayout::FieldRole);
    m_mainLayout->invalidate();
    m_mainLayout->update();

    return true;
}

void cgAccountList::createView()
{
    m_totalView->setReadOnly(true);
    m_totalView->setButtonSymbols(QDoubleSpinBox::NoButtons);
    m_totalView->setSuffix(FinanceSuffix);
    m_totalView->setMinimum(-100000);
    m_totalView->setMaximum(100000);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    m_mainLayout->addRow(line);
    m_mainLayout->addRow(Total, m_totalView);
}


qint64 cgAccountList::total()
{
    return m_total;
}
