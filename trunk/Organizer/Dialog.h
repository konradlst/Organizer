#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QPushButton;
class QFormLayout;

//! \class Dialog
//! \brief Абстрактный преднастроенный класс диалога.
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);

protected:
    QPushButton *m_ok;
    QFormLayout *m_lay;
};

//! \class TimeDialog
//! \brief Диалог добавления записи о потраченном времени.
class TimeDialog : public Dialog
{
    Q_OBJECT
public:
    explicit TimeDialog(QWidget *parent = 0);
};

//! \class DealDialog
//! \brief Диалог добавления нового дела.
class DealDialog : public Dialog
{
    Q_OBJECT
public:
    explicit DealDialog(QWidget *parent = 0);
};

//! \class DealDialog
//! \brief Диалог добавления нового финансового счета.
class AccountDialog : public Dialog
{
    Q_OBJECT
public:
    explicit AccountDialog(QWidget *parent = 0);
};

//! \class DealDialog
//! \brief Диалог добавления новой финансовой операции.
class TransactionDialog : public Dialog
{
    Q_OBJECT
public:
    explicit TransactionDialog(QWidget *parent = 0);
};

#endif // DIALOG_H
