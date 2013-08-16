#include <QFileDialog>
#include <QPair>
#include <QSettings>
#include <QTranslator>
#include "settingsView.h"
#include "ui_settingsView.h"

namespace Settings
{
const QString LANGUAGE("main/Language");
const QString DEFAULTDATA("main/DefaultData");
const QString PATH_TO_DEFAULTDATA("main/PathToDefaultData");
const QString LOGGING("main/Logging");
const QString PATH_TO_LOGFILE("main/PathToLogFile");
}

namespace
{
const int ENGLISH = 0;
const int RUSSIAN = 1;
const QString defaultPathToLog("ContactList.log");

#define DIALOG_CHOOSE_LOG_FILE QFileDialog::getSaveFileName(this, QObject::trUtf8("Choose Log File"))
#define DIALOG_CHOOSE_CONTACT_LIST QFileDialog::getOpenFileName(this, QObject::trUtf8("Choose Contact List"))
}

SettingsView::SettingsView(ContactListController *controller, QDialog *parent)
    : QDialog(parent),
      ui(new Ui::SettingsView),
      m_controller(controller),
      m_settings(new QSettings(QSettings::IniFormat,QSettings::UserScope,
                               "AnBat","ContactList")),
      m_RuTranslator(new QTranslator),
      m_qtRuTranslator(new QTranslator)
{
    ui->setupUi(this);
    ui->lbChangeLangMsg->setVisible(false);
    setLayout(ui->mainLayout);
    loadSettings();

    connect(ui->pbCancel, SIGNAL(clicked()), SLOT(close()));
    connect(ui->pbChooseContactList, SIGNAL(clicked()), SLOT(chooseContactList()));
    connect(ui->pbChooseLogFile, SIGNAL(clicked()), SLOT(choosePathToLog()));
    connect(ui->pbDefault, SIGNAL(clicked()),
            SLOT(setDefaultSettings()));
    connect(ui->cbLanguage, SIGNAL(currentIndexChanged(int)),
            SLOT(languageChanged(int)));
    connect(ui->gbLogging, SIGNAL(clicked(bool)),
            SLOT(loggingChanged(bool)));
    connect(ui->lePathToLogFile, SIGNAL(textChanged(QString)),
            SLOT(pathToLogChanged(QString)));
    connect(ui->gbDefaultContactList, SIGNAL(clicked(bool)),
            SLOT(defaultDataChanged(bool)));
    connect(ui->lePathToContactList, SIGNAL(textChanged(QString)),
            SLOT(pathToDefaultData(QString)));
}

SettingsView::~SettingsView()
{
    delete ui;
}

QPair<bool, QString> *SettingsView::defaultData()
{
    QPair<bool, QString> *p = new QPair<bool, QString>();
    p->first = m_settings->value(Settings::DEFAULTDATA).toBool();
    p->second = m_settings->value(Settings::PATH_TO_DEFAULTDATA).toString();
    return p;
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
    m_currentLanguage = 0;
    ui->cbLanguage->setCurrentIndex(ENGLISH);
    ui->gbDefaultContactList->setChecked(false);
    ui->lePathToContactList->setText(QString());
    ui->gbLogging->setChecked(true);
    ui->lePathToLogFile->setText(defaultPathToLog);

    m_settings->setValue(Settings::LANGUAGE,QVariant(ENGLISH));
    m_settings->setValue(Settings::DEFAULTDATA,QVariant(false));
    m_settings->setValue(Settings::PATH_TO_DEFAULTDATA,QVariant(QString()));
    m_settings->setValue(Settings::LOGGING,QVariant(true));
    m_settings->setValue(Settings::PATH_TO_LOGFILE,QVariant(defaultPathToLog));

    emit logging(true, defaultPathToLog);
}

void SettingsView::languageChanged(int language)
{
    if(language != m_currentLanguage)
    {
        setFixedSize(width(), height()+15);
        ui->lbChangeLangMsg->setVisible(true);
    }
    else
    {
        setFixedSize(width(), height()-15);
        ui->lbChangeLangMsg->setVisible(false);
    }
    m_settings->setValue(Settings::LANGUAGE, QVariant(language));
}

void SettingsView::loggingChanged(bool flag)
{
    m_settings->setValue(Settings::LOGGING,QVariant(flag));
    emit logging(flag, m_settings->value(Settings::PATH_TO_LOGFILE).toString());
}

void SettingsView::pathToLogChanged(QString path)
{
    m_settings->setValue(Settings::LOGGING,QVariant(true));
    m_settings->setValue(Settings::PATH_TO_LOGFILE,QVariant(path));
}

void SettingsView::defaultDataChanged(bool flag)
{
    m_settings->setValue(Settings::DEFAULTDATA,QVariant(flag));
}

void SettingsView::pathToDefaultData(QString path)
{
    m_settings->setValue(Settings::DEFAULTDATA,QVariant(true));
    m_settings->setValue(Settings::PATH_TO_DEFAULTDATA,QVariant(path));
}

void SettingsView::loadSettings()
{
    m_RuTranslator->load(":/lang_ru_RU");
    m_qtRuTranslator->load(":/qt_ru_RU");

    if(!QFile(m_settings->fileName()).exists())
    {
        setDefaultSettings();
        return;
    }

    ui->cbLanguage->setCurrentIndex(m_settings->value(Settings::LANGUAGE).toInt());
    ui->gbDefaultContactList->setChecked(m_settings->value(Settings::DEFAULTDATA).toBool());
    ui->lePathToContactList->setText(m_settings->value(Settings::PATH_TO_DEFAULTDATA).toString());
    ui->gbLogging->setChecked(m_settings->value(Settings::LOGGING).toBool());
    ui->lePathToLogFile->setText(m_settings->value(Settings::PATH_TO_LOGFILE).toString());

    emit logging(m_settings->value(Settings::LOGGING).toBool(),
                 m_settings->value(Settings::PATH_TO_LOGFILE).toString());

    if(ui->cbLanguage->currentIndex() == RUSSIAN)
    {
        qApp->installTranslator(m_RuTranslator);
        qApp->installTranslator(m_qtRuTranslator);
        m_currentLanguage = 1;
    }
}
