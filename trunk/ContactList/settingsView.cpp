#include <QFileDialog>
#include <QPair>
#include "settingsView.h"
#include "ui_settingsView.h"

namespace {
#define DIALOG_CHOOSE_LOG_FILE QFileDialog::getSaveFileName(this,QObject::trUtf8("Choose Log File"))
#define DIALOG_CHOOSE_CONTACT_LIST QFileDialog::getOpenFileName(this,QObject::trUtf8("Choose Contact List"))
}

SettingsView::SettingsView(ContactListController *controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsView),
    m_controller(controller),
    m_settings(new SettingsData)
{
    ui->setupUi(this);
    m_settings = m_controller->getDefaultSettings();
    setSettings(*m_settings);

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
    SettingsData data;
    data.language = 0;
    data.defaultData = false;
    data.pathToDefaultData = QString();
    data.logging = false;
    data.pathToLogFile = QString();
    setSettings(data);
}

void SettingsView::languageChanged(int language)
{
    (*m_settings).language = language;
    setSettings(*m_settings);
}

void SettingsView::loggingChanged(bool flag)
{
    (*m_settings).logging = flag;
    (*m_settings).pathToLogFile = ui->lePathToLogFile->text();
    setSettings(*m_settings);
}

void SettingsView::pathToLogChanged(QString path)
{
    (*m_settings).logging = true;
    (*m_settings).pathToLogFile = path;
    setSettings(*m_settings);
}

void SettingsView::defaultDataChanged(bool flag)
{
    (*m_settings).defaultData = flag;
    (*m_settings).pathToDefaultData = ui->lePathToContactList->text();
    setSettings(*m_settings);
}

void SettingsView::pathToDefaultData(QString path)
{
    (*m_settings).defaultData = true;
    (*m_settings).pathToDefaultData = path;
    setSettings(*m_settings);
}

void SettingsView::setSettings(const SettingsData &data)
{
    *m_settings = data;
    m_controller->changeSettings(*m_settings);
    ui->cbLanguage->setCurrentIndex(data.language);
    ui->lePathToContactList->setText(data.pathToDefaultData);
    ui->lePathToLogFile->setText(data.pathToLogFile);
    ui->gbDefaultContactList->setChecked(data.defaultData);
    ui->gbLogging->setChecked(data.logging);
}
