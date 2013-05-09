#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QDialog>
#include "contactListController.h"

class QSettings;
class QTranslator;
namespace Ui {
class SettingsView;
}

class SettingsView : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsView(ContactListController *controller, QDialog *parent = 0);
    ~SettingsView();
    QPair<bool, QString> *defaultData();

private slots:
    void chooseContactList();
    void choosePathToLog();
    void setDefaultSettings();
    void languageChanged(int language);
    void loggingChanged(bool flag);
    void pathToLogChanged(QString path);
    void defaultDataChanged(bool flag);
    void pathToDefaultData(QString path);

private:
    void loadSettings();

private:
    Ui::SettingsView *ui;
    ContactListController *m_controller;
    QSettings *m_settings;
    QTranslator *m_RuTranslator;
    QTranslator *m_qtRuTranslator;
    int m_currentLanguage;
};

#endif // SETTINGSVIEW_H
