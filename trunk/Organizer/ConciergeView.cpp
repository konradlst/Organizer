#include "ConciergeView.h"
#include "ui_ConciergeView.h"

namespace
{
const QChar Separator = ';';
const QStringList TimeType = QString("sleep;work;travel;study;sport;read").split(Separator);
const QStringList FinanceOperation = QObject::trUtf8("debet;credit;transfer").split(Separator);
const QStringList Accounts = QObject::trUtf8("cash;card;deposit").split(Separator);
}

ConciergeView::ConciergeView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ConciergeView)
{
    createInterface();
}

ConciergeView::~ConciergeView()
{
    delete ui;
}

void ConciergeView::createInterface()
{
    ui->setupUi(this);
    ui->comboBox->addItems(FinanceOperation);
    ui->comboBox_2->addItems(Accounts);
}
