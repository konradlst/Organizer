#include "aboutView.h"
#include "ui_aboutView.h"

AboutView::AboutView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutView)
{
    ui->setupUi(this);
}

AboutView::~AboutView()
{
    delete ui;
}
