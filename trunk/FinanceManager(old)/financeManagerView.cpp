#include "financeManagerView.h"
#include "ui_financeManagerView.h"

FinanceManagerView::FinanceManagerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinanceManagerView)
{
    ui->setupUi(this);
    centralWidget()->setLayout(ui->mainLayout);
    ui->tabLog->setLayout(ui->vLayStatistic);
    ui->gbAccounts->setLayout(ui->fLayAccounts);
    ui->deCurrentDate->setDate(QDate::currentDate());
}

FinanceManagerView::~FinanceManagerView()
{
    delete ui;
}
