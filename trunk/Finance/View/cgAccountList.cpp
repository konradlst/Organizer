#include "cgAccountList.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QProgressBar>

cgAccount::cgAccount(QString &name, qint64 &value) :
    m_name(name),
    m_value(value)
{
}

QString cgAccount::name() const
{
    return m_name;
}

qint64 cgAccount::value() const
{
    return m_value;
}

cgAccountList::cgAccountList() :
    m_view(new QGroupBox("Accounts")),
    m_mainLayout(new QFormLayout),
    m_totalView(new QDoubleSpinBox),
    m_accounts(new QList<cgAccount>())
{
    createView();
    m_total = 500;
    m_totalView->setValue(m_total);
}

QWidget *cgAccountList::view()
{
    return m_view;
}

void cgAccountList::addAccount(cgAccount &account)
{
    m_accounts->append(account);
    m_total += account.value();

    QProgressBar *bar = new QProgressBar();
    bar->setTextVisible(true);
    bar->setFormat("%v p.");
    bar->setValue(account.value());
    bar->setMaximum(m_total);

    m_mainLayout->insertRow(0, account.name(), bar);
}

bool cgAccountList::removeAccount(const int &index)
{
    m_total -= m_accounts->at(index).value();
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
    m_totalView->setSuffix(" p.");
    m_totalView->setMinimum(-100000);
    m_totalView->setMaximum(100000);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    m_mainLayout->addRow(line);
    m_mainLayout->addRow("Total :", m_totalView);

    m_view = new QGroupBox("Accounts");
    m_view->setLayout(m_mainLayout);
}


qint64 cgAccountList::total()
{
    return m_total;
}
