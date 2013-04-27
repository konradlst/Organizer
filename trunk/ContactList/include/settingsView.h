#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include "contactListController.h"

namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT
signals:
    void languageChanged(int);

public:
    explicit SettingsView(ContactListController *controller, QWidget *parent = 0);
    ~SettingsView();

private slots:
    void chooseContactList();
    void choosePathToLog();
    void setDefaultSettings();
    void loggingChanged(bool flag);
    void pathToLogChanged(QString path);

private:
    Ui::SettingsView *ui;
    ContactListController *m_controller;
};

#endif // SETTINGSVIEW_H
