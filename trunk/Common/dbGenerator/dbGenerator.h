#ifndef DBGENERATOR_H
#define DBGENERATOR_H

#include <QSqlDatabase>
class QString;
class QDomElement;
class QStringList;

class dbGenerator
{
public:
    dbGenerator(const QString &pathToDb);
    bool generate(const bool fillTable = false);

private:
    const QString &m_pathToDb;
    QSqlDatabase m_db;

    void parseField(const QDomElement &field, QString &data);
    bool execQueries(const QStringList &list);
};

#endif // DBGENERATOR_H
