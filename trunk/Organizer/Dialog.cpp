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
const QString TimeTitle = QObject::trUtf8("Time Dialog");
const QString DealTitle = QObject::trUtf8("Deal Dialog");
const QString AccountTitle = QObject::trUtf8("Account Dialog");
const QString TransactionTitle = QObject::trUtf8("Transaction Dialog");

const QString Ok = QObject::trUtf8("Ok");
const QString Type = QObject::trUtf8("Type :");
const QString Duration = QObject::trUtf8("Duration :");
const QString Started = QObject::trUtf8("Started :");
const QString Stoped = QObject::trUtf8("Stoped :");
const QString Description = QObject::trUtf8("Description :");
const QString Date = QObject::trUtf8("Date :");
const QString DeadLine = QObject::trUtf8("DeadLine :");
const QString Money = QObject::trUtf8("Money :");
const QString Humans = QObject::trUtf8("Humans :");
const QString Created = QObject::trUtf8("Created :");
const QString Name = QObject::trUtf8("Name :");
const QString Value = QObject::trUtf8("Value :");
const QString Total = QObject::trUtf8("Total :");
}

TimeDialog::TimeDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(TimeTitle);

    QPushButton *ok = new QPushButton(Ok);
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QTimeEdit *duration = new QTimeEdit();
    QTimeEdit *started = new QTimeEdit();
    QTimeEdit *stoped = new QTimeEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(Type, type);
    mLay->addRow(Duration, duration);
    mLay->addRow(Started, started);
    mLay->addRow(Stoped, stoped);
    mLay->addRow(Description, description);
    mLay->addWidget(ok);

    setLayout(mLay);
}

DealDialog::DealDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(DealTitle);

    QPushButton *ok = new QPushButton(Ok);
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QDateEdit *date = new QDateEdit();
    QTimeEdit *duration = new QTimeEdit();
    QDateEdit *deadLine = new QDateEdit();
    QSpinBox *money = new QSpinBox();
    QLineEdit *humans = new QLineEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(Type, type);
    mLay->addRow(Date, date);
    mLay->addRow(Duration, duration);
    mLay->addRow(DeadLine, deadLine);
    mLay->addRow(Money, money);
    mLay->addRow(Humans, humans);
    mLay->addRow(Description, description);
    mLay->addWidget(ok);

    setLayout(mLay);
}


AccountDialog::AccountDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(AccountTitle);

    QPushButton *ok = new QPushButton(Ok);
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QDateEdit *created = new QDateEdit();
    QLineEdit *name = new QLineEdit();
    QSpinBox *value = new QSpinBox();
    QSpinBox *total = new QSpinBox();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(Type, type);
    mLay->addRow(Created, created);
    mLay->addRow(Name, name);
    mLay->addRow(Value, value);
    mLay->addRow(Total, total);
    mLay->addRow(Description, description);
    mLay->addWidget(ok);

    setLayout(mLay);
}

TransactionDialog::TransactionDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(TransactionTitle);

    QPushButton *ok = new QPushButton(Ok);
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QDateEdit *created = new QDateEdit();
    QLineEdit *name = new QLineEdit();
    QSpinBox *value = new QSpinBox();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(Type, type);
    mLay->addRow(Created, created);
    mLay->addRow(Name, name);
    mLay->addRow(Value, value);
    mLay->addRow(Description, description);
    mLay->addWidget(ok);

    setLayout(mLay);
}
