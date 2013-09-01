#include "conciergeView.h"
#include "ui_conciergeView.h"

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
    ui->deToday->setDate(QDate::currentDate());
    ui->deDealDeadLine->setDate(QDate::currentDate());
    ui->centralWidget->setLayout(ui->mainLayout);
    ui->timePage->setLayout(ui->timeLayout);
    ui->financePage->setLayout(ui->financeLayout);
    ui->sportPage->setLayout(ui->sportLayout);
    ui->dealPage->setLayout(ui->dealLayout);

    ui->toolBox->setCurrentIndex(0);
    ui->cbTimeType->setEditable(true);

    //test
    ui->cbTimeType->addItems(QString("sleep;work;travel;study;sport;read").split(";"));
    ui->cbFinanceOperation->addItems(QString("debet;credit;transfer").split(";"));
    QString account("cash;card;deposit");
    ui->cbFinanceFrom->addItems(account.split(";"));
    ui->cbFinanceTo->addItems(account.split(";"));
}

void ConciergeView::addTransaction()
{
    if (ui->sbFinanceValue->value() == 0
            || !ui->cbFinanceOperation->count()
            || !ui->cbFinanceFrom->count()
            || !ui->cbFinanceTo->count())
        return;
    ui->lwFinanceList->addItem(ui->cbFinanceOperation->currentText() + " from "
                               + ui->cbFinanceFrom->currentText() + " to "
                               + ui->cbFinanceTo->currentText() + " : "
                               + ui->sbFinanceValue->text()
                               + QString(" ( %1 ).").arg(ui->leFinanceComment->text()));
}

void ConciergeView::addTimeRecord()
{
    if (!ui->cbTimeType->count())
        return;

    if (ui->teTimeDuration->time() != QTime(0, 0))
    {
        ui->lwTimeList->addItem(ui->teTimeDuration->text() + " : " + ui->cbTimeType->currentText());
    }
    else
    {
        ui->lwTimeList->addItem(ui->teTimeFrom->text() + " - " + ui->teTimeTo->text()
                                + " : " + ui->cbTimeType->currentText());
    }
}

void ConciergeView::addDealRecord()
{
    ui->leDealDescription->setText(ui->leDealDescription->text().trimmed());
    if (ui->leDealDescription->text().isEmpty())
        return;

    ui->lwDealList->addItem("Deadline: " + ui->deDealDeadLine->text()
                            + "; duration: " + ui->teDealDuration->text()
                            + "; price: " + ui->sbDealPrice->text()
                            + "; do: " + ui->leDealDescription->text());
}
