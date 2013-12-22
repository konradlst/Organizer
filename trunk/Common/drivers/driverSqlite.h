#ifndef DRIVERSQLITE_H
#define DRIVERSQLITE_H

#include <QObject>
#include <QStringList>
#include <QSqlDatabase>
#include "OrganizerConst.h"

struct ContactData;
struct AddressData;
struct ChannelData;
struct CompanyData;
struct AccountData;
struct DealData;
struct TimeData;
struct TransactionData;

class DriverSqlite : public QObject
{
    Q_OBJECT
public:
    explicit DriverSqlite(QObject *parent = 0);

    //! Запрашивает список контактов.
    QList<ContactData*> *contacts();
    //! Запрашивает контакт по его \alias прозвищу.
    ContactData* contact(const QString &alias);
    //! Запрашивает список счетов.
    QList<AccountData*> *accounts();
    //! Запрашивает список транзакций в указанную дату \param date.
    QList<TransactionData*> *transactions(const QDate &date);
    //! Запрашивает список временных расходов в указанную дату \param date.
    QList<TimeData*> *timeLine(const QDate &/*date*/);
    //! Запрашивает список дел в указанную дату \param date по заданными параметрам \param params.
    QList<DealData*> *deals(const QDate &date, const QStringList params = QStringList());

    //! Добавляет новый счет \param record.
    void addAccount(const AccountData &/*record*/);
    //! Добавляет новую транзакцию \param record.
    void addTransaction(const TransactionData &/*record*/);
    //! Добавляет новую запись о времени \param record.
    void addTimeRecord(const TimeData &/*record*/);
    //! Добавляет новое дело \param record.
    void addDeal(const DealData &/*record*/);
    //! Добавляет новый контакт.
    void addContact(const ContactData &/*record*/);

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
