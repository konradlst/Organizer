#ifndef DRIVERSQLITE_H
#define DRIVERSQLITE_H

#include <QObject>
#include <QStringList>
#include <QSqlDatabase>
#include "OrganizerConst.h"

class DriverSqlite : public QObject
{
    Q_OBJECT
public:
    explicit DriverSqlite(QObject *parent = 0);

    //! Запрашивает список контактов.
    Data::Table *contacts();
    //! Запрашивает контакт по его \alias прозвищу.
    Data::Record* contact(const QString &alias);
    //! Запрашивает список счетов.
    Data::Table *accounts();
    //! Запрашивает список транзакций в указанную дату \param date.
    Data::Table *transactions(const QDate &date);
    //! Запрашивает список временных расходов в указанную дату \param date.
    Data::Table *timeLine(const QDate &/*date*/);
    //! Запрашивает список дел в указанную дату \param date по заданными параметрам \param params.
    Data::Table *deals(const QDate &date, const QStringList params = QStringList());

    //! Добавляет новый счет \param record.
    void addAccount(const Data::Record &record);
    //! Добавляет новую транзакцию \param record.
    void addTransaction(const Data::Record &record);
    //! Добавляет новую запись о времени \param record.
    void addTimeRecord(const Data::Record &record);
    //! Добавляет новое дело \param record.
    void addDeal(const Data::Record &record);
    //! Добавляет новый контакт.
    void addContact(const Data::Record &record);

private:
    QSqlDatabase m_db;
    QString m_pathToDb;

private:
    bool openDb();
};

class SqliteTableDriver
{
public:
    explicit SqliteTableDriver(const QString &/*tableName*/, const QSqlDatabase &/*db*/) {};
    void submit() {};
    void openTransaction() {};
    void closeTransaction() {};
    void insertQuery() {};
    void deleteQuery() {};
    void updateQuery() {};

private:
    struct Mapper{};
    Mapper m_mapper;
    QString m_table;
};

#endif // DRIVERSQLITE_H
