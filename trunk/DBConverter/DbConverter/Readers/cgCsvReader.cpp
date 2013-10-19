#include <QFile>
#include <QDebug>
#include <QStringList>
#include "cgCsvReader.h"

namespace
{
    const QString Separator = "\t";
    const QString EndLine = "\n";
}

cgCsvReader::cgCsvReader(QObject *parent)
    : cgReader(parent),
      m_separator(Separator)
{
}

aScheme* cgCsvReader::loadData(const QString &path) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.fileName() + "is not open!";
        return 0;
    }

    aTable dataTable;
    QStringList row = QString(file.readLine()).remove(EndLine).split(m_separator);
    while (file.atEnd())
    {
        aRow dataRow;
        foreach (const QString &field, row)
            dataRow.append(field);
        dataTable.append(dataRow);
        row = QString(file.readLine()).remove(EndLine).split(m_separator);
    }
    aScheme *dataScheme = new aScheme();
    dataScheme->append(dataTable);
    return dataScheme;
}

bool cgCsvReader::saveData(const aScheme &scheme, const QString &path) const
{
    if (scheme.isEmpty())
    {
        qDebug() << "Scheme is empty!";
        return false;
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << file.fileName() + "is not open!";
        return false;
    }
    QByteArray data;
    aTable table = scheme.at(0);
    foreach (const aRow &row, table)
    {
        foreach (const QVariant &field, row)
            data.append(field.toString() + Separator);
        data.append(EndLine);
    }
    file.write(data);
    file.close();
    return true;
}
