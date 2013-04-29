#ifndef SETTINGSDATA_H
#define SETTINGSDATA_H

#include <QString>

struct SettingsData {
    int language;
    bool defaultData;
    QString pathToDefaultData;
    bool logging;
    QString pathToLogFile;
};

#endif // SETTINGSDATA_H
