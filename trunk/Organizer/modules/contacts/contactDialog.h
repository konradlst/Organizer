#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <dialog.h>

class QLineEdit;
class QDateEdit;
class QPair<QString, QLineEdit*>;
class ContactData;

class ContactDialog : public Dialog
{
    Q_OBJECT
public:
    explicit ContactDialog(QWidget *parent = 0);
    virtual QStringList *data();
    ContactData data2() const;

private:
    //FIXME
    QLineEdit *m_alias;
    QLineEdit *m_name;
    QLineEdit *m_surName;
    QLineEdit *m_otherName;
    QDateEdit *m_birthday;
};

#endif // CONTACTDIALOG_H
