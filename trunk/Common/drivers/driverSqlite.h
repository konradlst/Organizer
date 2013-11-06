#ifndef DRIVERSQLITE_H
#define DRIVERSQLITE_H

#include <QObject>
#include "OrganizerConst.h"

class QSqlDatabase;

class DriverSqlite : public QObject
{
    Q_OBJECT
public:
    explicit DriverSqlite(QObject *parent = 0);

    //! Запрашивает список контактов.
    Data::Table *contacts() const;
    //! Запрашивает контакт по его \alias прозвищу.
    Data::Record* contact(const QString &alias) const;
    //! Запрашивает список счетов.
    Data::Table *financeAccounts() const;
    //! Запрашивает список транзакций в указанную дату \param date.
    Data::Table *financeTransaction(const QDate &date) const;
    //! Запрашивает список временных расходов в указанную дату \param date.
    Data::Table *timeLine(const QDate &date) const;
    //! Запрашивает список дел в указанную дату \param date.
    Data::Table *deals(const QDate &date) const;
    //! Запрашивает список заметок по заданными параметрам \param params.
    Data::Table *notes(const QStringList &params) const;

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
    //! Добавляет новую заметку.
    void addNote(const Data::Record &record);

private:
    QSqlDatabase *m_db;
};

#endif // DRIVERSQLITE_H
