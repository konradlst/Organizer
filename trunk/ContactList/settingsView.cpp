#include <QFileDialog>
#include <QPair>
#include <QSettings>
#include <QTranslator>
#include "settingsView.h"
#include "ui_settingsView.h"

namespace Settings
{
const QString Language = "main/Language";
const QString DefaultData = "main/DefaultData";
const QString PathToDefaultData = "main/PathToDefaultData";
const QString Logging = "main/Logging";
const QString PathToLogFile = "main/PathToLogFile";
}

namespace
{
const int English = 0;
const int Russian = 1;
const QString LogPath = "ContactList.log";
const QString SettingsPath = QString("%2%1ContactList.ini").arg(QDir::separator());
}

SettingsView::SettingsView(ContactListController *controller, QDialog *parent)
    : QDialog(parent),
      ui(new Ui::SettingsView),
      m_controller(controller),
      m_settings(new QSettings(SettingsPath.arg(QCoreApplication::applicationDirPath()),
                               QSettings::IniFormat)),
      m_RuTranslator(new QTranslator),
      m_qtRuTranslator(new QTranslator)
{
    ui->setupUi(this);
    ui->lbChangeLangMsg->setVisible(false);
    setLayout(ui->mainLayout);
    setWindowModality(Qt::ApplicationModal);
    loadSettings();

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
    p->first = m_settings->value(Settings::DefaultData).toBool();
    p->second = m_settings->value(Settings::PathToDefaultData).toString();
    return p;
}

void SettingsView::chooseContactList()
{
    QString path = QFileDialog::getOpenFileName(this, QObject::trUtf8("Choose Contact List"));
    if(!path.isEmpty())
        ui->lePathToContactList->setText(path);
}

void SettingsView::choosePathToLog()
{
    QString path = QFileDialog::getSaveFileName(this, QObject::trUtf8("Choose Log File"));
    if(!path.isEmpty())
        ui->lePathToLogFile->setText(path);
}

void SettingsView::setDefaultSettings()
{
    m_currentLanguage = 0;
    ui->cbLanguage->setCurrentIndex(English);
    ui->gbDefaultContactList->setChecked(false);
    ui->lePathToContactList->setText(QString());
    ui->gbLogging->setChecked(true);
    ui->lePathToLogFile->setText(LogPath);

    m_settings->setValue(Settings::Language,QVariant(English));
    m_settings->setValue(Settings::DefaultData,QVariant(false));
    m_settings->setValue(Settings::PathToDefaultData,QVariant(QString()));
    m_settings->setValue(Settings::Logging,QVariant(true));
    m_settings->setValue(Settings::PathToLogFile,QVariant(LogPath));

    emit logging(true, LogPath);
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
    m_settings->setValue(Settings::Language, QVariant(language));
}

void SettingsView::loggingChanged(bool flag)
{
    m_settings->setValue(Settings::Logging,QVariant(flag));
    emit logging(flag, m_settings->value(Settings::PathToLogFile).toString());
}

void SettingsView::pathToLogChanged(QString path)
{
    m_settings->setValue(Settings::Logging,QVariant(true));
    m_settings->setValue(Settings::PathToLogFile,QVariant(path));
}

void SettingsView::defaultDataChanged(bool flag)
{
    m_settings->setValue(Settings::DefaultData,QVariant(flag));
}

void SettingsView::pathToDefaultData(QString path)
{
    m_settings->setValue(Settings::DefaultData,QVariant(true));
    m_settings->setValue(Settings::PathToDefaultData,QVariant(path));
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

    ui->cbLanguage->setCurrentIndex(m_settings->value(Settings::Language).toInt());
    ui->gbDefaultContactList->setChecked(m_settings->value(Settings::DefaultData).toBool());
    ui->lePathToContactList->setText(m_settings->value(Settings::PathToDefaultData).toString());
    ui->gbLogging->setChecked(m_settings->value(Settings::Logging).toBool());
    ui->lePathToLogFile->setText(m_settings->value(Settings::PathToLogFile).toString());

    emit logging(m_settings->value(Settings::Logging).toBool(),
                 m_settings->value(Settings::PathToLogFile).toString());

    if(ui->cbLanguage->currentIndex() == Russian)
    {
        qApp->installTranslator(m_RuTranslator);
        qApp->installTranslator(m_qtRuTranslator);
        m_currentLanguage = 1;
    }
}
