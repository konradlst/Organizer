#ifndef DRIVERSQLITE_H
#define DRIVERSQLITE_H

#include <QObject>
class QSqlDatabase;

class DriverSqlite : public QObject
{
    Q_OBJECT
public:
    typedef QList<QString> cgRecord;
    typedef QList<cgRecord> cgTable;
    typedef QList<cgTable> cgScheme;
    explicit DriverSqlite(QObject *parent = 0);
    //! Запрашивает список финансовых операций в заданную дату \param date.
    cgTable* getFinanceLog(const QDate &date) const;
    //! Запрашивает на что было затраченно время в заданную дату \param date.
    cgTable* getTimeLog(const QDate &date) const;
    //! Запрашивает данные о физических тренировках в заданную дату \param date.
    cgRecord* getSportLog(const QDate &date) const;
    //! Запрашивает список дел на заданную дату \param date.
    cgTable* getToDoList(const QDate &date) const;
    //! Запрашивает список контактов.
    cgTable* getContactList();

    //! Добавляет новую финансовую операцию \param record.
    void addTransaction(const cgRecord &record);
    //! Добавляет новую запись о потраченном времени \param record.
    void addTimeRecord(const cgRecord &record);
    //! Добавляет новую запись о физических тренировках \param record.
    void addSportRecord(const cgRecord &record);
    //! Добавляет запись о новом деле \param record.
    void addDeal(const cgRecord &record);
    //! Добавляет запись о новом контакте.
    void addContact();

private:
    QSqlDatabase *m_db;
};

#endif // DRIVERSQLITE_H
