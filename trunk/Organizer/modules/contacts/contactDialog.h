#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <dialog.h>

class QLineEdit;
class QDateEdit;
class QPair<QString, QLineEdit*>;

class ContactDialog : public Dialog
{
    Q_OBJECT
public:
    explicit ContactDialog(QWidget *parent = 0);
    virtual QStringList *data();

private:
    //FIXME
    QLineEdit *m_alias;
    QLineEdit *m_name;
    QLineEdit *m_surName;
    QLineEdit *m_otherName;
    QDateEdit *m_birthday;
    //channnels
    typedef QPair<QString, QLineEdit*> Channel;
    QList<Channel> *m_channels;
    //addressess
    QLineEdit *m_country;
    QLineEdit *m_city;
    QLineEdit *m_street;
    QLineEdit *m_home;
    QLineEdit *m_apartment;
    //employers
    QLineEdit *m_companyName;
    QLineEdit *m_companyPhone;
    QLineEdit *m_department;
    QLineEdit *m_post;
    QLineEdit *m_companyAddress;
    QDateEdit *m_startWork;
    QDateEdit *m_endWork;
};

#endif // CONTACTDIALOG_H
