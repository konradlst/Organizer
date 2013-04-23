#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>

namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT
    
public:
    explicit SettingsView(QWidget *parent = 0);
    ~SettingsView();

private slots:
    //! Слот выбора списка контактов.
    void chooseContactList();
    //! Слот выбора пути для файла лога.
    void choosePathToLog();
    //! Слот для сброса настроек по умолчанию.
    void setDefaultSettings();
private:
    Ui::SettingsView *ui;
};

#endif // SETTINGSVIEW_H
