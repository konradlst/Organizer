#include "conciergeView.h"
#include "ui_conciergeView.h"
#include "ConciergeView2.h"

ConciergeView::ConciergeView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ConciergeView)
{
    ui->setupUi(this);
    createInterface();

    connect(ui->pbAddTransaction, SIGNAL(clicked()), SLOT(addTransaction()));
    connect(ui->pbTimeSubmit, SIGNAL(clicked()), SLOT(addTimeRecord()));
    connect(ui->pbDealSubmit, SIGNAL(clicked()), SLOT(addDealRecord()));
}

ConciergeView::~ConciergeView()
{
    delete ui;
}

void ConciergeView::createInterface()
{
    ConciergeView2 *view = new ConciergeView2();
    view->show();
    ui->deToday->setDate(QDate::currentDate());
    ui->deDealDeadLine->setDate(QDate::currentDate());

    ui->toolBox->setCurrentIndex(0);
    ui->cbTimeType->setEditable(true);

    //test
    static const QChar Separator = ';';
    static const QStringList TimeType = QString("sleep;work;travel;study;sport;read").split(Separator);
    static const QStringList FinanceOperation = QString("debet;credit;transfer").split(Separator);
    static const QStringList Accounts = QString("cash;card;deposit").split(Separator);

    ui->cbTimeType->addItems(TimeType);
    ui->cbFinanceOperation->addItems(FinanceOperation);
    ui->cbFinanceFrom->addItems(Accounts);
    ui->cbFinanceTo->addItems(Accounts);
}

void ConciergeView::addTransaction()
{
    static const QString FinanceTransaction = QObject::trUtf8("%1 from %2 to %3 : %4 ( %5 ).");

    if (ui->sbFinanceValue->value() == 0
            || !ui->cbFinanceOperation->count()
            || !ui->cbFinanceFrom->count()
            || !ui->cbFinanceTo->count())
        return;
    ui->lwFinanceList->addItem(FinanceTransaction.arg(ui->cbFinanceOperation->currentText())
                                                 .arg(ui->cbFinanceFrom->currentText())
                                                 .arg(ui->cbFinanceTo->currentText())
                                                 .arg(ui->sbFinanceValue->text())
                                                 .arg(ui->leFinanceComment->text()));
}

void ConciergeView::addTimeRecord()
{
    if (!ui->cbTimeType->count())
        return;

    if (ui->teTimeDuration->time() != QTime(0, 0))
        ui->lwTimeList->addItem(ui->teTimeDuration->text() + " : " + ui->cbTimeType->currentText());
    else
        ui->lwTimeList->addItem(ui->teTimeFrom->text() + " - " + ui->teTimeTo->text()
                                + " : " + ui->cbTimeType->currentText());
}

void ConciergeView::addDealRecord()
{
    static const QString Deal = "Deadline: %1; duration: %2; price: %3; do: %4";

    ui->leDealDescription->setText(ui->leDealDescription->text().trimmed());
    if (ui->leDealDescription->text().isEmpty())
        return;

    ui->lwDealList->addItem(Deal.arg(ui->deDealDeadLine->text())
                                .arg(ui->teDealDuration->text())
                                .arg(ui->sbDealPrice->text())
                                .arg(ui->leDealDescription->text()));
}
