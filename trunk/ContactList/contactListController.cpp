#include "contactListController.h"
#include "contactListView.h"
#include "contactListModel.h"

ContactListController::ContactListController(QWidget *parent) :
    QWidget(parent),
    m_log(myLog::instance()),
    m_model(new ContactListModel(this)),
    m_view(new ContactListView(this))
{
    m_view->show();
    connect(m_view,SIGNAL(dataChanged(QString,QString,int)),m_model,SLOT(dataChanged(QString,QString,int)));
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

void ContactListController::deleteContact(const int index)
{
    m_model->deleteContact(index);
}

Data::ContactData *ContactListController::loadContact(const QString &path)
{
    return m_model->loadContact(path);
}

bool ContactListController::saveContact(const Data::ContactData &data, const QString &path)
{
    return m_model->saveContact(data,path);
}

QStringList *ContactListController::loadData(const QString &path)
{
    return m_model->loadData(path);
}

bool ContactListController::saveData(const QString &path)
{
    return m_model->saveData(path);
}

void ContactListController::logging(bool flag, const QString &path)
{
    m_log->logging(flag,path);
}
