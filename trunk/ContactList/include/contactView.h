#ifndef CONTACTVIEW_H
#define CONTACTVIEW_H

#include <QWidget>

class QVBoxLayout;
class QTableWidget;
class QPushButton;
class QLabel;
class QLineEdit;
class QDateEdit;

class ContactView : public QWidget
{
    Q_OBJECT
public:
    explicit ContactView(QWidget *parent = 0);

private:
    void createInterface();
    void createGrid();
    void setDefaultSettings();

private:
    QVBoxLayout *m_mainLay;
    QTableWidget *m_property;
    QLabel *m_userPic;
    QPushButton *m_setUserPic;
    QLineEdit *m_alias;
    QLineEdit *m_name;
    QLineEdit *m_surName;
    QLineEdit *m_otherName;
    QDateEdit *m_birthday;

};

#endif // CONTACTVIEW_H
