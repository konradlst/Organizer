#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTimeEdit>
#include <QSpinBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include "Dialog.h"

namespace
{
const QString Ok = "Ok";
const QString Type = "Type :";
const QString Description = "Description :";
}

TimeDialog::TimeDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Time Dialog");

    QPushButton *ok = new QPushButton(Ok);
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QTimeEdit *duration = new QTimeEdit();
    QTimeEdit *started = new QTimeEdit();
    QTimeEdit *stoped = new QTimeEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(QString(Type), type);
    mLay->addRow(QString("Duration :"), duration);
    mLay->addRow(QString("Started :"), started);
    mLay->addRow(QString("Stoped :"), stoped);
    mLay->addRow(QString(Description), description);
    mLay->addWidget(ok);

    setLayout(mLay);
}

DealDialog::DealDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Note Dialog");

    QPushButton *ok = new QPushButton(Ok);
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QDateEdit *date = new QDateEdit();
    QTimeEdit *duration = new QTimeEdit();
    QDateEdit *deadLine = new QDateEdit();
    QSpinBox *money = new QSpinBox();
    QLineEdit *humans = new QLineEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(QString(Type), type);
    mLay->addRow(QString("Date :"), date);
    mLay->addRow(QString("Duration :"), duration);
    mLay->addRow(QString("DeadLine :"), deadLine);
    mLay->addRow(QString("Money :"), money);
    mLay->addRow(QString("Humans :"), humans);
    mLay->addRow(QString(Description), description);
    mLay->addWidget(ok);

    setLayout(mLay);
}


AccountDialog::AccountDialog(QWidget *parent)
{
    setWindowTitle("Account Dialog");

    QPushButton *ok = new QPushButton(Ok);
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QDateEdit *created = new QDateEdit();
    QLineEdit *name = new QLineEdit();
    QSpinBox *value = new QSpinBox();
    QSpinBox *total = new QSpinBox();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(QString(Type), type);
    mLay->addRow(QString("Created :"), created);
    mLay->addRow(QString("Name :"), name);
    mLay->addRow(QString("Value :"), value);
    mLay->addRow(QString("Total :"), total);
    mLay->addRow(QString(Description), description);
    mLay->addWidget(ok);

    setLayout(mLay);
}
