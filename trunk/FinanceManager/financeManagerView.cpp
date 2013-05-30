#include "financeManagerView.h"
#include "ui_financeManagerView.h"

FinanceManagerView::FinanceManagerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinanceManagerView)
{
    ui->setupUi(this);
}

FinanceManagerView::~FinanceManagerView()
{
    delete ui;
}
