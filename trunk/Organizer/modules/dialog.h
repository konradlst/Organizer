#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QPushButton;
class QFormLayout;
class QComboBox;
class QPlainTextEdit;

//! \class Dialog
//! \brief Абстрактный преднастроенный класс диалога.
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    virtual QStringList *data() = 0;

protected:
    QPushButton *m_ok;
    QFormLayout *m_lay;
    QComboBox *m_type;
    QPlainTextEdit *m_description;
};

#endif // DIALOG_H
