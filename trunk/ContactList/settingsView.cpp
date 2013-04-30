#include <QFileDialog>
#include <QPair>
#include <QSettings>
#include "settingsView.h"
#include "ui_settingsView.h"

namespace {
const int ENGLISH = 0;
const QString defaultPathToLog("ContactList.log");

namespace Settings {
const QString LANGUAGE("main/Language");
const QString DEFAULTDATA("main/DefaultData");
const QString PATH_TO_DEFAULTDATA("main/PathToDefaultData");
const QString LOGGING("main/Logging");
const QString PATH_TO_LOGFILE("main/PathToLogFile");
}
#define DIALOG_CHOOSE_LOG_FILE QFileDialog::getSaveFileName(this,QObject::trUtf8("Choose Log File"))
#define DIALOG_CHOOSE_CONTACT_LIST QFileDialog::getOpenFileName(this,QObject::trUtf8("Choose Contact List"))
}

SettingsView::SettingsView(ContactListController *controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsView),
    m_controller(controller),
    m_settingsIni(new QSettings(QSettings::IniFormat,QSettings::UserScope,
                                "AnBat","ContactList"))
{
    ui->setupUi(this);
    loadSettings();

    connect(ui->pbCancel,SIGNAL(clicked()),SLOT(close()));
    connect(ui->pbChooseContactList,SIGNAL(clicked()),SLOT(chooseContactList()));
    connect(ui->pbChooseLogFile,SIGNAL(clicked()),SLOT(choosePathToLog()));
    connect(ui->pbDefault,SIGNAL(clicked()),SLOT(setDefaultSettings()));
    connect(ui->cbLanguage,SIGNAL(currentIndexChanged(int)),SLOT(languageChanged(int)));
    connect(ui->gbLogging,SIGNAL(clicked(bool)),SLOT(loggingChanged(bool)));
    connect(ui->lePathToLogFile,SIGNAL(textChanged(QString)),SLOT(pathToLogChanged(QString)));
    connect(ui->gbDefaultContactList,SIGNAL(clicked(bool)),SLOT(defaultDataChanged(bool)));
    connect(ui->lePathToContactList,SIGNAL(textChanged(QString)),SLOT(pathToDefaultData(QString)));
}

SettingsView::~SettingsView()
{
    delete ui;
}

void SettingsView::chooseContactList()
{
    QString path = DIALOG_CHOOSE_CONTACT_LIST;
    if(!path.isEmpty())
        ui->lePathToContactList->setText(path);
}

void SettingsView::choosePathToLog()
{
    QString path = DIALOG_CHOOSE_LOG_FILE;
    if(!path.isEmpty())
        ui->lePathToLogFile->setText(path);
}

void SettingsView::setDefaultSettings()
{
    ui->cbLanguage->setCurrentIndex(ENGLISH);
    ui->gbDefaultContactList->setChecked(false);
    ui->lePathToContactList->setText(QString());
    ui->gbLogging->setChecked(true);
    ui->lePathToLogFile->setText(defaultPathToLog);

    m_settingsIni->setValue(Settings::LANGUAGE,QVariant(ENGLISH));
    m_settingsIni->setValue(Settings::DEFAULTDATA,QVariant(false));
    m_settingsIni->setValue(Settings::PATH_TO_DEFAULTDATA,QVariant(QString()));
    m_settingsIni->setValue(Settings::LOGGING,QVariant(true));
    m_settingsIni->setValue(Settings::PATH_TO_LOGFILE,QVariant(defaultPathToLog));

    m_controller->logging(true,defaultPathToLog);
}

void SettingsView::languageChanged(int language)
{
    m_settingsIni->setValue(Settings::LANGUAGE,QVariant(language));
}

void SettingsView::loggingChanged(bool flag)
{
    m_settingsIni->setValue(Settings::LOGGING,QVariant(flag));
    m_controller->logging(flag,m_settingsIni->value(Settings::PATH_TO_LOGFILE).toString());
}

void SettingsView::pathToLogChanged(QString path)
{
    m_settingsIni->setValue(Settings::LOGGING,QVariant(true));
    m_settingsIni->setValue(Settings::PATH_TO_LOGFILE,QVariant(path));
}

void SettingsView::defaultDataChanged(bool flag)
{
    m_settingsIni->setValue(Settings::DEFAULTDATA,QVariant(flag));
}

void SettingsView::pathToDefaultData(QString path)
{
    m_settingsIni->setValue(Settings::DEFAULTDATA,QVariant(true));
    m_settingsIni->setValue(Settings::PATH_TO_DEFAULTDATA,QVariant(path));
}

void SettingsView::loadSettings()
{
    if(QFile(m_settingsIni->fileName()).exists()) {
        ui->cbLanguage->setCurrentIndex(m_settingsIni->value(Settings::LANGUAGE).toInt());
        ui->gbDefaultContactList->setChecked(m_settingsIni->value(Settings::DEFAULTDATA).toBool());
        ui->lePathToContactList->setText(m_settingsIni->value(Settings::PATH_TO_DEFAULTDATA).toString());
        ui->gbLogging->setChecked(m_settingsIni->value(Settings::LOGGING).toBool());
        ui->lePathToLogFile->setText(m_settingsIni->value(Settings::PATH_TO_LOGFILE).toString());

        m_controller->logging(m_settingsIni->value(Settings::LOGGING).toBool(),
                        m_settingsIni->value(Settings::PATH_TO_LOGFILE).toString());
    }
    else {
        setDefaultSettings();
    }
}
