#include <QCalendarWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "contactListView.h"
#include "ui_contactListView.h"
#include "settingsView.h"

namespace {
#define NEW_CONTACT_TEXT QString("New contact")
#define DEFAULT_PHONE_TEXT QString("+ ()   ")
#define OPEN_TITLE QObject::trUtf8("Open Contact List")
#define SAVE_TITLE QObject::trUtf8("Save Contact List")
#define LOAD_USERPIC QObject::trUtf8("Load User Pic")
#define DEFAULT_PATH QDir::currentPath()
#define FILE_TYPES QObject::trUtf8("All Files (*.*);;Text files (*.txt);;XML files (*.xml);;SQL files (*.sqlite);;JSON files (*.json)")
#define OPEN_FILE_DIALOG QFileDialog::getOpenFileName(this, OPEN_TITLE, DEFAULT_PATH, FILE_TYPES)
#define SAVE_FILE_DIALOG QFileDialog::getSaveFileName(this, SAVE_TITLE, DEFAULT_PATH, FILE_TYPES)

#define APP_NAME QObject::trUtf8("Contact List")
#define APP_VERSION "v.0.1.1"
#define ABOUT_TITLE QObject::trUtf8("About %1").arg(APP_NAME)
#define VERSION QObject::trUtf8("Version: %1")
#define ABOUT_TEXT QObject::trUtf8("<b>%1 %2</b><br><br>" \
                                    "Based on Qt 4.8.1<br><br>" \
                                    "Copyright 2013, Anton Batyaev. All rights reserved.").arg(APP_NAME,APP_VERSION)

QString pathToData(const QString *path) {
    if(!path->isEmpty())
        return QString(QObject::trUtf8("Path: %1")).arg(*path);
    else
        return QString();
}

QPixmap pathToPixmap(QString path) {
    QPixmap pix = QPixmap(path);
    if(pix.isNull())
        pix = QPixmap(":/logo");
    return pix.scaled(pix.size());
}
}

ContactListView::ContactListView(ContactListController *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactListView),
    m_controller(controller),
    m_path(new QLabel()),
    m_settings(new SettingsView(m_controller))
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->hLayoutMain);
    ui->gbAddress->setLayout(ui->gLayAddress);
    ui->gbCommunications->setLayout(ui->gLayCommunication);
    ui->gbOrganization->setLayout(ui->gLayOrganization);
//    ui->menuBar->hide();
    setEditable(false);
    setDefaultSettings();

    ui->lePhone->setInputMask("+9 (999) 999 99 99;_");
    ui->deStartWork->setDate(QDate::currentDate());
    ui->deEndWork->setDate(QDate::currentDate());
    ui->deBirthday->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    ui->statusBar->addWidget(new QLabel(VERSION.arg(APP_VERSION)));

    m_path->setText(*m_controller->pathToData());
    ui->statusBar->addWidget(m_path);
    MYLOG << Log::StartApp;

    connect(ui->actionNew,SIGNAL(triggered()),SLOT(newData()));
    connect(ui->actionOpen,SIGNAL(triggered()),SLOT(loadData()));
    connect(ui->actionSave,SIGNAL(triggered()),SLOT(saveData()));
    connect(ui->actionSave_as,SIGNAL(triggered()),SLOT(saveAsData()));
    connect(ui->actionNew_Contact,SIGNAL(triggered()),SLOT(newContact()));
    connect(ui->actionLoad_Contact,SIGNAL(triggered()),SLOT(loadContact()));
    connect(ui->actionSave_Contact,SIGNAL(triggered()),SLOT(saveContact()));
    connect(ui->actionCopy_Contact,SIGNAL(triggered()),SLOT(copyContact()));
    connect(ui->actionDelete_Contact,SIGNAL(triggered()),SLOT(deleteContact()));
    connect(ui->actionSettings,SIGNAL(triggered()),SLOT(settings()));
    connect(ui->actionEditable,SIGNAL(triggered(bool)),SLOT(setEditable(bool)));
    connect(ui->lwContactList,SIGNAL(currentRowChanged(int)),SLOT(currentContactChanged(int)));
    connect(ui->pbEditUserPic,SIGNAL(clicked()),SLOT(loadUserPic()));
    connect(ui->actionExit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui->actionAbout,SIGNAL(triggered()),SLOT(about()));
    connectSignals();
}

ContactListView::~ContactListView()
{
    delete ui;
    delete m_controller;
    delete m_path;
    delete m_settings;
}

void ContactListView::activateContactBotton()
{
    ui->actionSave->setEnabled(true);
    ui->actionNew_Contact->setEnabled(true);
    ui->actionLoad_Contact->setEnabled(true);
    ui->actionSave_Contact->setEnabled(true);
    ui->actionCopy_Contact->setEnabled(true);
    ui->actionDelete_Contact->setEnabled(true);
    ui->actionEditable->setEnabled(true);
}

void ContactListView::setEditable(bool flag)
{
    ui->actionEditable->setChecked(flag);
    ui->pbEditUserPic->setEnabled(flag);
    ui->leAlias->setEnabled(flag);
    ui->leName->setEnabled(flag);
    ui->leSurName->setEnabled(flag);
    ui->leOtherName->setEnabled(flag);
    ui->deBirthday->setEnabled(flag);
    ui->gbAddress->setEnabled(flag);
    ui->gbCommunications->setEnabled(flag);
    ui->gbOrganization->setEnabled(flag);
}

void ContactListView::setContactData(const Data::ContactData *contact)
{
    disconnectSignals();
    ui->leAlias->setText(contact->m_alias);
    ui->leName->setText(contact->m_name);
    ui->leSurName->setText(contact->m_surName);
    ui->leOtherName->setText(contact->m_otherName);
    ui->deBirthday->setDate(contact->m_birthday);
    ui->lbUserPic->setPixmap(pathToPixmap(contact->m_pathToUserPic));

    Data::Address address = contact->m_addresses.at(0);
    ui->leCountry->setText(address.country);
    ui->leCity->setText(address.city);
    ui->leStreet->setText(address.street);
    ui->leHome->setText(address.home);
    ui->leApartment->setText(address.apartment);

    ui->lePhone->clear();
    ui->leEmail->clear();
    ui->leSkype->clear();
    ui->leSite->clear();
    int count = contact->m_communications.size()-1;
    while(count >= 0) {
        Data::CommunicationData data = contact->m_communications.at(count);
        if(data.first == Data::typePhone)
            ui->lePhone->setText(data.second.value);
        if(data.first == Data::typeEmail)
            ui->leEmail->setText(data.second.value);
        if(data.first == Data::typeSkype)
            ui->leSkype->setText(data.second.value);
        if(data.first == Data::typeSite)
            ui->leSite->setText(data.second.value);
        --count;
    }

    Data::Organization company = contact->m_organizations.at(0);
    ui->leNameOrganization->setText(company.name);
    ui->lePhoneOrganization->setText(company.phone);
    ui->leDepartment->setText(company.department);
    ui->lePost->setText(company.post);
    ui->leAddressOrganization->setText(company.address);
    ui->deStartWork->setDate(company.dateIn);
    ui->deEndWork->setDate(company.dateIn);

    connectSignals();
}

void ContactListView::setDefaultSettings()
{
    QPair<bool, QString> data = *m_settings->defaultData();
    if(data.first && QFile(data.second).exists())
        loadData(data.second);
}

void ContactListView::about()
{
    QMessageBox::about(this,ABOUT_TITLE,ABOUT_TEXT);
}

void ContactListView::loadData()
{
    QString path = OPEN_FILE_DIALOG;
    loadData(path);
}

void ContactListView::loadData(const QString &path)
{
    if(!path.isEmpty()) {
        QStringList list = *m_controller->loadData(path);
        if(!list.isEmpty()) {
            clearAll();
            activateContactBotton();
            setEditable(true);
            setContactData(m_controller->contact(0));
            refreshContactList();
            m_path->setText(pathToData(m_controller->pathToData()));
            MYLOG << Log::LoadContactList;
        }
    }
    if(ui->lwContactList->count() == 1)
        emptyContactList(false);
}

void ContactListView::saveData()
{
    if(!m_controller->pathToData()->isEmpty()) {
        m_controller->saveData(*m_controller->pathToData());
        MYLOG << Log::SaveContactList.arg(*m_controller->pathToData());
    }
    else {
        saveAsData();
	}
}

void ContactListView::saveAsData()
{
    QString path = SAVE_FILE_DIALOG;
    if(!path.isEmpty()) {
        m_controller->saveData(path);
        m_path->setText(pathToData(m_controller->pathToData()));
        MYLOG << Log::SaveContactList.arg(m_path->text());
    }
}

void ContactListView::newData()
{
    clearAll();
    activateContactBotton();
    setEditable(true);
    setContactData(m_controller->newData());
    refreshContactList();
    ui->leAlias->setFocus();
    ui->leAlias->selectAll();
    MYLOG << Log::NewContactList;
    if(ui->lwContactList->count() == 1)
        emptyContactList(false);
}

void ContactListView::clearAll()
{
    refreshContactList();
    clearContact();
    m_path->clear();
}

void ContactListView::refreshContactList(int currentIndex)
{
    disconnect(ui->lwContactList,SIGNAL(currentRowChanged(int)),this,SLOT(currentContactChanged(int)));
    ui->lwContactList->clear();
    ui->lwContactList->addItems(*m_controller->contactList());
    connect(ui->lwContactList,SIGNAL(currentRowChanged(int)),SLOT(currentContactChanged(int)));
    ui->lwContactList->setCurrentRow(currentIndex);
}

void ContactListView::emptyContactList(bool flag)
{
    flag = !flag;
    ui->actionSave->setEnabled(flag);
    ui->actionSave_Contact->setEnabled(flag);
    ui->actionCopy_Contact->setEnabled(flag);
    ui->actionDelete_Contact->setEnabled(flag);
    ui->actionEditable->setEnabled(flag);
    setEditable(flag);
    if(!flag)
        clearContact();
}

void ContactListView::connectSignals()
{
    connect(ui->leAlias,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leName,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leSurName,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leOtherName,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leCountry,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leCity,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leStreet,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leHome,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leApartment,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->lePhone,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leEmail,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leSkype,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leSite,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leNameOrganization,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->lePhoneOrganization,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leDepartment,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->lePost,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
    connect(ui->leAddressOrganization,SIGNAL(textChanged(QString)),SLOT(textChanged(QString)));
}

void ContactListView::disconnectSignals()
{
    disconnect(ui->leAlias,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leName,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leSurName,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leOtherName,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leCountry,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leCity,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leStreet,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leHome,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leApartment,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->lePhone,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leEmail,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leSkype,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leSite,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leNameOrganization,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->lePhoneOrganization,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leDepartment,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->lePost,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    disconnect(ui->leAddressOrganization,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
}

void ContactListView::clearContact()
{
    disconnectSignals();
    ui->leAlias->clear();
    ui->leName->clear();
    ui->leSurName->clear();
    ui->leOtherName->clear();
    ui->deBirthday->clear();
    ui->leCountry->clear();
    ui->leCity->clear();
    ui->leStreet->clear();
    ui->leHome->clear();
    ui->leApartment->clear();
    ui->lePhone->clear();
    ui->leEmail->clear();
    ui->leSkype->clear();
    ui->leSite->clear();
    ui->leNameOrganization->clear();
    ui->lePhoneOrganization->clear();
    ui->leDepartment->clear();
    ui->lePost->clear();
    ui->leAddressOrganization->clear();
    ui->deStartWork->clear();
    ui->deEndWork->clear();

    connectSignals();
}

void ContactListView::newContact()
{
    clearContact();
    setEditable(true);

    setContactData(m_controller->newContact());
    refreshContactList(ui->lwContactList->count());
    ui->leAlias->setFocus();
    ui->leAlias->selectAll();
    if(ui->lwContactList->count() == 1)
        emptyContactList(false);
    MYLOG << Log::NewContact;
}

void ContactListView::loadContact()
{
    QString path = OPEN_FILE_DIALOG;
    if(!path.isEmpty()) {
        Data::ContactData *data = m_controller->loadContact(path);
        if(data != 0) {
            setContactData(data);
            refreshContactList(ui->lwContactList->count());
            ui->leAlias->setFocus();
            ui->leAlias->selectAll();
            MYLOG << Log::LoadContact.arg(path);
        }
    }
    if(ui->lwContactList->count() == 1)
        emptyContactList(false);
}

void ContactListView::saveContact()
{
    QString path = SAVE_FILE_DIALOG;
    if(!path.isEmpty()) {
        m_controller->saveContact(*m_controller->contact(ui->lwContactList->currentRow()),path);
        MYLOG << Log::SaveContact.arg(path);
    }
}

void ContactListView::copyContact()
{
    int index = ui->lwContactList->currentRow();
    setContactData(m_controller->copyContact(index));
    refreshContactList(ui->lwContactList->count());
    emit textChanged(ui->leAlias->text());
    ui->leAlias->setFocus();
    ui->leAlias->selectAll();
    MYLOG << Log::CopyContact.arg(ui->leAlias->text());
}

void ContactListView::deleteContact()
{
    int index = ui->lwContactList->currentRow();
    m_controller->deleteContact(index);
    MYLOG << Log::DeleteContact.arg(ui->leAlias->text());
    if(index + 1 == ui->lwContactList->count())
        refreshContactList(index - 1);
    else
        refreshContactList(index);
    ui->leAlias->setFocus();
    if(!ui->lwContactList->count()) {
        emptyContactList();
    }
}

void ContactListView::settings()
{
    m_settings->show();
}

void ContactListView::currentContactChanged(int index)
{
    setContactData(m_controller->contact(index));
}

void ContactListView::loadUserPic()
{
    QString path = QFileDialog::getOpenFileName(this, LOAD_USERPIC, DEFAULT_PATH);
    if(!path.isEmpty()) {
        ui->lbUserPic->setPixmap(pathToPixmap(path));
        emit dataChanged(path, Attribute::Userpic, ui->lwContactList->currentRow());
    }
}

void ContactListView::textChanged(QString text)
{
    QLineEdit *send = qobject_cast<QLineEdit*>(sender());
    if(send == ui->leAlias)
        ui->lwContactList->item(ui->lwContactList->currentRow())->setText(text);

    if(send == ui->leAlias)
        emit dataChanged(text, Attribute::Alias, ui->lwContactList->currentRow());
    else if(send == ui->leName)
        emit dataChanged(text, Attribute::Name, ui->lwContactList->currentRow());
    else if(send == ui->leSurName)
        emit dataChanged(text, Attribute::SurName, ui->lwContactList->currentRow());
    else if(send == ui->leOtherName)
        emit dataChanged(text, Attribute::OtherName, ui->lwContactList->currentRow());
    else if(send == ui->leCountry)
        emit dataChanged(text, Attribute::Country, ui->lwContactList->currentRow());
    else if(send == ui->leCity)
        emit dataChanged(text, Attribute::City, ui->lwContactList->currentRow());
    else if(send == ui->leStreet)
        emit dataChanged(text, Attribute::Street, ui->lwContactList->currentRow());
    else if(send == ui->leHome)
        emit dataChanged(text, Attribute::Home, ui->lwContactList->currentRow());
    else if(send == ui->leApartment)
        emit dataChanged(text, Attribute::Apartment, ui->lwContactList->currentRow());
    else if(send == ui->lePhone)
        emit dataChanged(text, Value::Phone, ui->lwContactList->currentRow());
    else if(send == ui->leEmail)
        emit dataChanged(text, Value::Email, ui->lwContactList->currentRow());
    else if(send == ui->leSkype)
        emit dataChanged(text, Value::Skype, ui->lwContactList->currentRow());
    else if(send == ui->leSite)
        emit dataChanged(text, Value::Site, ui->lwContactList->currentRow());
    else if(send == ui->leNameOrganization)
        emit dataChanged(text, Attribute::NameOrganization, ui->lwContactList->currentRow());
    else if(send == ui->lePhoneOrganization)
        emit dataChanged(text, Attribute::PhoneOrganization, ui->lwContactList->currentRow());
    else if(send == ui->leDepartment)
        emit dataChanged(text, Attribute::Department, ui->lwContactList->currentRow());
    else if(send == ui->lePost)
        emit dataChanged(text, Attribute::Post, ui->lwContactList->currentRow());
    else if(send == ui->leAddressOrganization)
        emit dataChanged(text, Attribute::AddressOrganization, ui->lwContactList->currentRow());
}
