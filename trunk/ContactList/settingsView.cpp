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
    m_controller(controller)
{
    ui->setupUi(this);
    QPair<bool,QString> status = *m_controller->loggingStatus();
    ui->gbLogging->setChecked(status.first);
    ui->lePathToLogFile->setText(status.second);

    connect(ui->pbCancel,SIGNAL(clicked()),SLOT(close()));
    connect(ui->pbChooseContactList,SIGNAL(clicked()),SLOT(chooseContactList()));
    connect(ui->pbChooseLogFile,SIGNAL(clicked()),SLOT(choosePathToLog()));
    connect(ui->pbDefault,SIGNAL(clicked()),SLOT(setDefaultSettings()));
    connect(ui->cbLanguage,SIGNAL(currentIndexChanged(int)),SIGNAL(languageChanged(int)));
    connect(ui->gbLogging,SIGNAL(clicked(bool)),SLOT(loggingChanged(bool)));
    connect(ui->lePathToLogFile,SIGNAL(textChanged(QString)),SLOT(pathToLogChanged(QString)));
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
    ui->cbLanguage->setCurrentIndex(0);
    ui->lePathToContactList->clear();
    ui->lePathToLogFile->clear();
    ui->gbDefaultContactList->setChecked(false);
    ui->gbLogging->setChecked(false);
    emit languageChanged(0);
}

void SettingsView::loggingChanged(bool flag)
{
    if(flag && !ui->lePathToLogFile->text().isEmpty())
        m_controller->logging(flag,ui->lePathToLogFile->text());
    else
        m_controller->logging(flag);
}

void SettingsView::pathToLogChanged(QString path)
{
    m_controller->logging(true,path);
}
