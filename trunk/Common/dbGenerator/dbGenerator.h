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
    //! Генерирует БД на основании дефолтной схемы
    //! и при необходимости \param fillTable заполняет таблицы данными.
    bool generate(const bool fillTable = false);

private:
    const QString &m_pathToDb;
    QSqlDatabase m_db;

    //! Генерирует таблицы на основании структуры указанной в схеме \param scheme.
    bool generateTables(const QDomElement &scheme);
    //! Заполняет таблицы данными из схемы \param scheme.
    bool fillTables(const QDomElement &scheme);
    //! Обрабатывает одно поле \param field таблицы и пишет получивщуюся строку в \param data.
    void parseField(const QDomElement &field, QString &data) const;
    //! Выполняет заданный \param list список запросов.
    bool execQueries(const QStringList &list);
};

#endif // DBGENERATOR_H
