#include "cgTransactionView.h"
#include "ui_cgTransactionView.h"

cgTransactionView::cgTransactionView(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::cgTransactionView)
{
    ui->setupUi(this);
}

cgTransactionView::~cgTransactionView()
{
    delete ui;
}
