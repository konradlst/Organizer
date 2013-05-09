#include "contactListController.h"
#include "contactListView.h"
#include "contactListModel.h"
#include "settingsView.h"

ContactListController::ContactListController(QWidget *parent) :
    QWidget(parent),
    m_log(myLog::instance()),
    m_settings(new SettingsView(this)),
    m_model(new ContactListModel(this)),
    m_view(new ContactListView(this))
{
    m_view->show();
    connect(m_view, SIGNAL(dataChanged(QString,QString,int)), m_model, SLOT(dataChanged(QString,QString,int)));
    connect(m_view, SIGNAL(dataChanged(QPixmap,QString,int)), m_model, SLOT(dataChanged(QPixmap,QString,int)));
    connect(m_view, SIGNAL(dataChanged(QDate,QString,int)), m_model, SLOT(dataChanged(QDate,QString,int)));
    connect(m_view, SIGNAL(deleteContact(int)), m_model, SLOT(deleteContact(int)));
    connect(m_view, SIGNAL(saveData(QString)), m_model, SLOT(saveData(QString)));
    connect(m_view, SIGNAL(saveContact(Data::ContactData,QString)), m_model, SLOT(saveContact(Data::ContactData,QString)));
}

QStringList *ContactListController::contactList() const
{
    return m_model->contactList();
}

QString *ContactListController::pathToData() const
{
    return m_model->pathToData();
}

Data::ContactData *ContactListController::contact(int index) const
{
    return m_model->contact(index);
}

Data::ContactData *ContactListController::newData() const
{
    return m_model->newData();
}

Data::ContactData *ContactListController::newContact() const
{
    return m_model->newContact();
}

Data::ContactData *ContactListController::copyContact(const int index) const
{
    return m_model->copyContact(index);
}

Data::ContactData *ContactListController::loadContact(const QString &path)
{
    return m_model->loadContact(path);
}

QStringList *ContactListController::loadData(const QString &path)
{
    return m_model->loadData(path);
}

void ContactListController::logging(bool flag, const QString &path)
{
    m_log->logging(flag,path);
}

SettingsView *ContactListController::getSettingsPtr()
{
    return m_settings;
}
