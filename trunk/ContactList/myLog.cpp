#include "myLog.h"
#include <QFile>
#include <QDateTime>

namespace {
#define CURRENT_DATETIME QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz")

QString logMessage(QString data) {
    return CURRENT_DATETIME + " " + data + "\n";
}
}

myLog::myLog() :
    m_path(new QString(Log::defaultPathToLog)),
    m_logFile(new QFile(*m_path)),
    m_logging(true)
{
}

myLog::~myLog()
{
}

myLog* myLog::m_instance = 0;

myLog *myLog::instance()
{
    if(m_instance == 0)
        m_instance = new myLog();
    return m_instance;
}

void myLog::operator <<(const QString &data)
{
    if(m_logging) {
        m_logFile->open(QIODevice::Append | QIODevice::Text);
        m_logFile->write(logMessage(data).toLatin1());
        m_logFile->close();
    }
}

void myLog::logging(bool flag, const QString &path)
{
    m_logging = flag;
    if(!path.trimmed().isEmpty())
        *m_path = path;
    else
        *m_path = Log::defaultPathToLog;
    m_logFile->setFileName(*m_path);
}
