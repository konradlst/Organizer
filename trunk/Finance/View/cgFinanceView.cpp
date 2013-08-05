#include "cgFinanceView.h"
#include <QDoubleSpinBox>
#include <QFrame>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QWidget>

QDoubleSpinBox *View::DoubleSpinBox()
{
    QDoubleSpinBox *dsbox = new QDoubleSpinBox();
    dsbox->setReadOnly(true);
    dsbox->setButtonSymbols(QDoubleSpinBox::NoButtons);
    dsbox->setSuffix(" p.");
    dsbox->setMinimum(-100000);
    dsbox->setMaximum(100000);
    return dsbox;
}


QFrame *View::Line()
{
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}


QDateEdit *View::DateWidget()
{
    QDateEdit *date = new QDateEdit(QDate::currentDate());
    date->setFrame(false);
    date->setReadOnly(true);
    date->setButtonSymbols(QDateEdit::NoButtons);
    date->setAlignment(Qt::AlignCenter);
    date->setDisplayFormat("ddd, dd MMMM yyyy года");
    return date;
}

QWidget *View::TodayList()
{
    QFrame *lineToday         = Line();
    QDateEdit *date           = DateWidget();
    QDoubleSpinBox *dsbTravel = DoubleSpinBox();
    QDoubleSpinBox *dsbZp     = DoubleSpinBox();
    dsbTravel->setValue(-20);
    dsbZp->setValue(15000);

    QFormLayout *layToday = new QFormLayout;
    layToday->addRow("travel", dsbTravel);
    layToday->addRow("ZP", dsbZp);

    QGroupBox *gbToday = new QGroupBox("Today");
    gbToday->setLayout(layToday);

    QVBoxLayout *vlay = new QVBoxLayout();
    vlay->addWidget(date);
    vlay->addWidget(new QPushButton("Add Transaction"));
    vlay->addWidget(lineToday);
    vlay->addWidget(gbToday);

    QWidget *wdt = new QWidget();
    wdt->setLayout(vlay);
    return wdt;
}
