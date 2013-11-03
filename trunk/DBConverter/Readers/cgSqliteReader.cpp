#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QVariant>
#include "cgSqliteReader.h"

namespace
{
    const QString Separator = ", ";
    const QString Qsqlite = "QSQLITE";
    const QString ConnectionName = "ReaderConnection";
    const QString Select = "SELECT %1 FROM %2";
    const QString Insert = "INSERT INTO %1(%2) VALUES %3";
}

cgSqliteReader::cgSqliteReader(QObject *parent)
    : cgReader(parent)
{
}

aScheme *cgSqliteReader::loadData(const QString &path) const
{
    //FIXME
    QSqlDatabase db = QSqlDatabase::addDatabase(Qsqlite, ConnectionName);
    db.setDatabaseName(path);
    db.open();
    QStringList fieldNames;
    QString tableName;
    QString query = Select.arg(fieldNames.join(","), tableName);
    QSqlQuery qry(query, db);

    aTable table;
    while (qry.next())
    {
        aRow row;
        for (int i = 0; i < fieldNames.count(); ++i)
            row.append(qry.value(fieldNames.at(i)));
        table.append(row);
    }
    aScheme *scheme = new aScheme();
    scheme->append(table);
    db.close();
    return scheme;
}

bool cgSqliteReader::saveData(const aScheme &scheme, const QString &path) const
{
    //FIXME
    QSqlDatabase db = QSqlDatabase::addDatabase(Qsqlite, ConnectionName);
    db.setDatabaseName(path);
    db.open();
    foreach (const aTable &table, scheme)
    {
        foreach (const aRow &row, table)
        {
            QStringList values;
            QStringList fields;
            QString tableName;
            foreach (const QVariant &data, row)
                values << data.toString();
//            QString query = Insert.arg(tableName, fields.join(Separator), values.join(Separator));
//            QSqlQuery(query, db);
        }
    }
    db.close();
    return true;
}
