#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include "contactListController.h"
#include "settingsData.h"

namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsView(ContactListController *controller, QWidget *parent = 0);
    ~SettingsView();

private slots:
    void chooseContactList();
    void choosePathToLog();
    void setDefaultSettings();
    void languageChanged(int language);
    void loggingChanged(bool flag);
    void pathToLogChanged(QString path);
    void defaultDataChanged(bool flag);
    void pathToDefaultData(QString path);
    void setSettings(const SettingsData &data);

private:
    Ui::SettingsView *ui;
    ContactListController *m_controller;
    SettingsData *m_settings;
};

#endif // SETTINGSVIEW_H
