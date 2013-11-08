#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTimeEdit>
#include <QSpinBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include "Dialog.h"

TimeDialog::TimeDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Time Dialog");

    QPushButton *ok = new QPushButton("Ok");
    QFormLayout *mLay = new QFormLayout();
    QComboBox *type = new QComboBox();
    QTimeEdit *duration = new QTimeEdit();
    QTimeEdit *started = new QTimeEdit();
    QTimeEdit *stoped = new QTimeEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(QString("Type :"), type);
    mLay->addRow(QString("Duration :"), duration);
    mLay->addRow(QString("Started :"), started);
    mLay->addRow(QString("Stoped :"), stoped);
    mLay->addRow(QString("Description :"), description);
    mLay->addWidget(ok);

    setLayout(mLay);
}


NoteDialog::NoteDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Note Dialog");

    QPushButton *ok = new QPushButton("Ok");
    QFormLayout *mLay = new QFormLayout();
    QTimeEdit *duration = new QTimeEdit();
    QDateTimeEdit *deadLine = new QDateTimeEdit();
    QSpinBox *money = new QSpinBox();
    QLineEdit *humans = new QLineEdit();
    QPlainTextEdit *description = new QPlainTextEdit();

    mLay->addRow(QString("Duration :"), duration);
    mLay->addRow(QString("DeadLine :"), deadLine);
    mLay->addRow(QString("Money :"), money);
    mLay->addRow(QString("Humans :"), humans);
    mLay->addRow(QString("Description :"), description);
    mLay->addWidget(ok);

    setLayout(mLay);
}
