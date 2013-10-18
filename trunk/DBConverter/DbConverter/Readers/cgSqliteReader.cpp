#include "cgSqliteReader.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>

namespace SQL
{
const QString Select = "SELECT %1 FROM %2";
const QString Insert = "SELECT %1 FROM %2";
const QString CreateTable = "CREATE TABLE %1 (%2)";
}

cgSqliteReader::cgSqliteReader(QObject *parent)
    : cgReader(parent)
{
}

aScheme *cgSqliteReader::loadData(const QString &path) const
{
    //FIXME
    QSqlDatabase db("QSQLITE");
    db.open();
    QStringList fieldNames;
    QString tableName;
    QString query = SQL::Select.arg(fieldNames.join(","), tableName);
    QSqlQuery qry(query, db);

    aScheme *scheme = new aScheme();
    while (qry.next())
    {
        aRow row;
        for (int i = 0; i < fieldNames.count(); ++i)
            row.append(qry.value(fieldNames.at(i)));
        scheme->append(row);
    }
    db.close();
    return scheme;
}

bool cgSqliteReader::saveData(const aScheme &scheme, const QString &path) const
{
    //FIXME
    return true;
}
