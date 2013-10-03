﻿#ifndef CONTACTLISTVIEW_H
#define CONTACTLISTVIEW_H

#include <QMainWindow>
#include <QDate>
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
    void dataChanged(QString, QString, int);
    void dataChanged(QDate, QString, int);
    void deleteContact(int);
    void saveData(QString);
    void saveContact(const ContactData &, const QString &);

private:
    void activateContactBotton();
    void setContactData(const ContactData *contact);
    void setDefaultSettings();
    void clearAll();
    void refreshContactList(int currentIndex = 0);
    void emptyContactList(bool flag = true);
    void connectSignals();
    void disconnectSignals();

private slots:
    void setEditable(bool flag);
    void loadData();
    void loadData(const QString &path);
    void saveData();
    void saveAsData();
    void newData();
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
    void dateChanged(QDate date);
    void about();

private:
    Ui::ContactListView *ui;
    ContactListController *m_controller;
    QLabel *m_path;
    SettingsView *m_settings;
};

#endif // CONTACTLISTVIEW_H