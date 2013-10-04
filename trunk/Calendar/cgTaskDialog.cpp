#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "cgTaskDialog.h"

cgTaskDialog::cgTaskDialog(QWidget *parent)
    : QWidget(parent)
{
    createInterface();
    show();
}

void cgTaskDialog::createInterface()
{
    // Create gialog.
    // type: Holiday\Task
    // frequency: every___Day\every___Week\every___Mounth\every___Year
    // description: ____
    // price: ___
    // deadline: __day\__date\__week\__mouth\__year
    // Ok & Cancel
    QFormLayout *mLay = new QFormLayout(this);
    setLayout(mLay);

    QComboBox *type = new QComboBox(this);
    type->addItems(QString("Holiday;Task").split(";"));
    QComboBox *frequency = new QComboBox(this);
    frequency->addItems(QString("every Day;every Week;every Mounth;every Year").split(";"));
    QLineEdit *description = new QLineEdit();
    QDoubleSpinBox *price = new QDoubleSpinBox();
    QComboBox *deadline = new QComboBox(this);
    deadline->addItems(QString("Today;Date;Week;Mouth;Year").split(";"));
    QPushButton *btnOk = new QPushButton("Ok");
    QPushButton *btnCancel = new QPushButton("Ok");

    mLay->addRow(QString("Type :"), type);
    mLay->addRow(QString("Frequency :"), frequency);
    mLay->addRow(QString("Description :"), description);
    mLay->addRow(QString("Price :"), price);
    mLay->addRow(QString("Deadline :"), deadline);
    mLay->addWidget(btnOk);
    mLay->addWidget(btnCancel);
}
