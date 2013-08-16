#ifndef CONTACTVIEW_H
#define CONTACTVIEW_H

#include <QWidget>

class QVBoxLayout;
class QTabWidget;
class QLabel;
class QPushButton;
class QLineEdit;
class QDateEdit;

class ContactView : public QWidget
{
    Q_OBJECT
public:
    explicit ContactView(QWidget *parent = 0);

private:
    QVBoxLayout *m_mainLay;
    QTabWidget *m_property;
    QLabel *m_userPic;
    QPushButton *m_setUserPic;
    QLineEdit *m_alias;
    QLineEdit *m_name;
    QLineEdit *m_surName;
    QLineEdit *m_otherName;
    QDateEdit *m_birthday;

    void createInterface();
    void createGrid();
};

#endif // CONTACTVIEW_H
