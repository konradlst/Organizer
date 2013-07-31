#include "cgFinanceView.h"
#include <QDoubleSpinBox>
#include <QFrame>
#include <QProgressBar>
#include <QDateEdit>

cgFinanceView::cgFinanceView(QWidget *parent) :
    QWidget(parent)
{
}

QDoubleSpinBox *cgFinanceView::getDoubleSpinBox()
{
    QDoubleSpinBox *dsbox = new QDoubleSpinBox();
    dsbox->setReadOnly(true);
    dsbox->setButtonSymbols(QDoubleSpinBox::NoButtons);
    dsbox->setSuffix(" p.");
    dsbox->setMinimum(-100000);
    dsbox->setMaximum(100000);
    return dsbox;
}

QFrame *cgFinanceView::getLine()
{
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}

QProgressBar *cgFinanceView::getProgressBar()
{
    QProgressBar *bar = new QProgressBar();
    bar->setTextVisible(true);
    bar->setFormat("%v p.");
    return bar;
}

QDateEdit *cgFinanceView::getDateWidget()
{
    QDateEdit *date = new QDateEdit(QDate::currentDate());
    date->setFrame(false);
    date->setReadOnly(true);
    date->setButtonSymbols(QDateEdit::NoButtons);
    date->setAlignment(Qt::AlignCenter);
    date->setDisplayFormat("ddd, dd MMMM yyyy года");
    return date;
}
