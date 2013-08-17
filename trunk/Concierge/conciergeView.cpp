#include "conciergeView.h"
#include "ui_conciergeView.h"

ConciergeView::ConciergeView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConciergeView)
{
    ui->setupUi(this);
}

ConciergeView::~ConciergeView()
{
    delete ui;
}
