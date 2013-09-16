#include "cgCalendarView.h"
#include "ui_cgCalendarView.h"

CgCalendarView::CgCalendarView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CgCalendarView)
{
    ui->setupUi(this);
}

CgCalendarView::~CgCalendarView()
{
    delete ui;
}
