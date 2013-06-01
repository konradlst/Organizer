#include "financeManagerView.h"
#include "ui_financeManagerView.h"

FinanceManagerView::FinanceManagerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinanceManagerView)
{
    ui->setupUi(this);
    centralWidget()->setLayout(ui->mainLayout);
    ui->tab_3->setLayout(ui->vlayPlanning);
    ui->tab->setLayout(ui->vLayStatistic);
    ui->gbAccounts->setLayout(ui->fLayAccounts);
    ui->gbCurrentMounth->setLayout(ui->fLayCurrentMounth);
    ui->gbToday->setLayout(ui->fLayToday);


    ui->deCurrentDate->setDate(QDate::currentDate());
    ui->deCurrentDayOfWeek->setDate(QDate::currentDate());
}

FinanceManagerView::~FinanceManagerView()
{
    delete ui;
}
