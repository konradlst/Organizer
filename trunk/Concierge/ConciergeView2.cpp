#include "ConciergeView2.h"
#include "ui_ConciergeView2.h"

ConciergeView2::ConciergeView2(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ConciergeView2)
{
    ui->setupUi(this);
}

ConciergeView2::~ConciergeView2()
{
    delete ui;
}
