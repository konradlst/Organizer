#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>

namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT
signals:
    void languageChanged(int);

public:
    explicit SettingsView(QWidget *parent = 0);
    ~SettingsView();

private slots:
    void chooseContactList();
    void choosePathToLog();
    void setDefaultSettings();

private:
    Ui::SettingsView *ui;
};

#endif // SETTINGSVIEW_H
