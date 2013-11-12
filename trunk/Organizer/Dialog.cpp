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
    : Dialog(parent)
{
    setWindowTitle(TimeTitle);

    QComboBox *type = new QComboBox();
    QTimeEdit *duration = new QTimeEdit();
    QTimeEdit *started = new QTimeEdit();
    QTimeEdit *stoped = new QTimeEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    m_lay->addRow(Type, type);
    m_lay->addRow(Duration, duration);
    m_lay->addRow(Started, started);
    m_lay->addRow(Stoped, stoped);
    m_lay->addRow(Description, description);
    m_lay->addWidget(m_ok);
}

DealDialog::DealDialog(QWidget *parent)
    : Dialog(parent)
{
    setWindowTitle(DealTitle);

    QComboBox *type = new QComboBox();
    QDateEdit *date = new QDateEdit();
    QTimeEdit *duration = new QTimeEdit();
    QDateEdit *deadLine = new QDateEdit();
    QSpinBox *money = new QSpinBox();
    QLineEdit *humans = new QLineEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    m_lay->addRow(Type, type);
    m_lay->addRow(Date, date);
    m_lay->addRow(Duration, duration);
    m_lay->addRow(DeadLine, deadLine);
    m_lay->addRow(Money, money);
    m_lay->addRow(Humans, humans);
    m_lay->addRow(Description, description);
    m_lay->addWidget(m_ok);
}


AccountDialog::AccountDialog(QWidget *parent)
    : Dialog(parent)
{
    setWindowTitle(AccountTitle);

    QComboBox *type = new QComboBox();
    QDateEdit *created = new QDateEdit();
    QLineEdit *name = new QLineEdit();
    QSpinBox *value = new QSpinBox();
    QSpinBox *total = new QSpinBox();
    QPlainTextEdit *description = new QPlainTextEdit();

    m_lay->addRow(Type, type);
    m_lay->addRow(Created, created);
    m_lay->addRow(Name, name);
    m_lay->addRow(Value, value);
    m_lay->addRow(Total, total);
    m_lay->addRow(Description, description);
    m_lay->addWidget(m_ok);
}

TransactionDialog::TransactionDialog(QWidget *parent)
    : Dialog(parent)
{
    setWindowTitle(TransactionTitle);

    QComboBox *type = new QComboBox();
    QDateEdit *created = new QDateEdit();
    QLineEdit *name = new QLineEdit();
    QSpinBox *value = new QSpinBox();
    QPlainTextEdit *description = new QPlainTextEdit();

    m_lay->addRow(Type, type);
    m_lay->addRow(Created, created);
    m_lay->addRow(Name, name);
    m_lay->addRow(Value, value);
    m_lay->addRow(Description, description);
    m_lay->addWidget(m_ok);
}


Dialog::Dialog(QWidget *parent)
    : QDialog(parent),
      m_ok(new QPushButton(Ok)),
      m_lay(new QFormLayout())
{
    setLayout(m_lay);
}
