#ifndef CONTACTVIEW_H
#define CONTACTVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include "contactData.h"
#include "channel.h"

class QVBoxLayout;
class QTabWidget;
class QPushButton;
class QDateEdit;

struct AddressView
{
    QLabel lbCountry;
    QLabel lbCity;
    QLabel lbStreet;
    QLabel lbHome;
    QLabel lbApartment;

    QLineEdit country;
    QLineEdit city;
    QLineEdit street;
    QLineEdit home;
    QLineEdit apartment;
};

typedef QVector<Channel::View *> ChannelViewList;

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
    QTabWidget *m_property;
    QLabel *m_userPic;
    QPushButton *m_setUserPic;
    QLineEdit *m_alias;
    QLineEdit *m_name;
    QLineEdit *m_surName;
    QLineEdit *m_otherName;
    QDateEdit *m_birthday;
    ChannelViewList *m_channelList;
    AddressView *m_address;
};

#endif // CONTACTVIEW_H
