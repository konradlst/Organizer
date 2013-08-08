#ifndef DBGENERATOR_H
#define DBGENERATOR_H

#include <QSqlDatabase>
class QString;
class QDomElement;
class QStringList;

namespace Db
{
const QString SQLITE("QSQLITE");
}

class dbGenerator
{
public:
    dbGenerator(const QString &metascheme, const QString &pathToDb);
    bool generate(const bool fillTable = false);

private:
    const QString &m_metascheme;
    const QString &m_pathToDb;
    QSqlDatabase m_db;

    bool loadScheme(QDomElement &scheme);
    void parseField(const QDomElement &field, QString &data);
    bool execQueries(const QStringList &list);
};

#endif // DBGENERATOR_H
