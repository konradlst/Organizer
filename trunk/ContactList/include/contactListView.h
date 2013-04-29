#ifndef CONTACTLISTVIEW_H
#define CONTACTLISTVIEW_H

#include <QMainWindow>
#include "contactListController.h"

namespace Ui {
class ContactListView;
}
class QLabel;
class SettingsView;

class ContactListView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ContactListView(ContactListController *controller, QWidget *parent = 0);
    ~ContactListView();

signals:
    void dataChanged(QString data, QString key, int contactId);

private:
    void activateContactBotton();
    void setContactData(const Data::ContactData *contact);

private slots:
    void setEditable(bool flag);
    void loadData();
    void saveData();
    void saveAsData();
    void newData();
    void clear();
    void clearContact();
    void newContact();
    void loadContact();
    void saveContact();
    void copyContact();
    void deleteContact();
    void settings();
    void currentContactChanged(int index);
    void loadUserPic();
    void textChanged(QString text);
    void about();

private:
    Ui::ContactListView *ui;
    ContactListController *m_controller;
    QLabel *m_path;
    SettingsView *m_settings;
};

#endif // CONTACTLISTVIEW_H
