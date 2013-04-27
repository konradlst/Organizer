#ifndef MYLOG_H
#define MYLOG_H

#include <QObject>
#include <QPair>

class QFile;

namespace Log {
const QString StartApp = QObject::trUtf8("Start Application");
const QString StopApp = QObject::trUtf8("Stop Application");

const QString NewContact = QObject::trUtf8("Create new Contact");
const QString LoadContact = QObject::trUtf8("Load Contact from %1");
const QString SaveContact = QObject::trUtf8("Save Contact to %1");
const QString CopyContact = QObject::trUtf8("Copy Contact %1");
const QString DeleteContact = QObject::trUtf8("Delete Contact %1");

const QString NewContactList = QObject::trUtf8("New Contact List");
const QString LoadContactList = QObject::trUtf8("Load Contact List from %1");
const QString SaveContactList = QObject::trUtf8("Save Contact List to %1");

const QString defaultPathToLog("ContactList.log");
}

class myLog
{
public:
    ~myLog();
    static myLog* instance();
    void operator <<(const QString &data);
    void logging(bool flag, const QString &path = Log::defaultPathToLog);
    QPair<bool,QString> *loggingStatus();

private:
    myLog();
    myLog(const myLog& root);
    myLog& operator=(const myLog&);
    static myLog* m_instance;
    QString *m_path;
    QFile *m_logFile;
    bool m_logging;
};

#define MYLOG *myLog::instance()

#endif // MYLOG_H
