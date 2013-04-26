#include "myLog.h"
//#include <QDebug>
#include <QFile>
#include <QDateTime>

namespace {
#define CURRENT_DATETIME QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz")

QString logMessage(QString data) {
    return CURRENT_DATETIME + " " + data + "\n";
}
}

myLog::myLog() :
    m_path(new QString),
    m_logFile(new QFile("ContactList.log"))
{
}

myLog::~myLog()
{
}

myLog* myLog::m_instance = 0;

myLog *myLog::instance()
{
    if(m_instance == 0) {
        m_instance = new myLog();
    }
    return m_instance;
}

void myLog::operator <<(const QString &data)
{
    m_logFile->open(QIODevice::Append | QIODevice::Text);
    m_logFile->write(logMessage(data).toAscii());
    m_logFile->close();
//    qDebug() << logMessage(data);
}
