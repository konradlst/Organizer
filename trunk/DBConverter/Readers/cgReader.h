#ifndef CGREADER_H
#define CGREADER_H

#include <QObject>

typedef QList<QVariant> aRow;
typedef QList<aRow> aTable;
typedef QList<aTable> aScheme;

//! \class cgReader
//! \brief Абстрактный класс для чтения данных в определенном формате.
class cgReader : public QObject
{
    Q_OBJECT
public:
    explicit cgReader(QObject *parent = 0)
        : QObject(parent)
    {};

    //! Загружает данные по указанному \param path пути.
    //! Простейшая реализация паттерна шаблонный метод
    aScheme* load(const QString &path)
    {
        m_lastPath = path;
        return loadData(path);
    };
    virtual aScheme* loadData(const QString &path) const = 0;
    //! Сохраняет данные \param scheme по указанному \param path пути.
    //! Простейшая реализация паттерна шаблонный метод
    bool save(const aScheme &scheme, const QString &path)
    {
        m_lastPath = path;
        return saveData(scheme, path);
    };
    virtual bool saveData(const aScheme &scheme, const QString &path) const = 0;
    //! Возвращает последний используемый путь
    QString lastPath() { return m_lastPath; };

private:
    QString m_lastPath;
};

#endif // CGREADER_H
