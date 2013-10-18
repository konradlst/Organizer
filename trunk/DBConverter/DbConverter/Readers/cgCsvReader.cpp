#include "cgCsvReader.h"

cgCsvReader::cgCsvReader(QObject *parent)
    : cgReader(parent)
{
}

aScheme *cgCsvReader::loadData(const QString &path) const
{
    //FIXME
    return new aScheme;
}

bool cgCsvReader::saveData(const aScheme &scheme, const QString &path) const
{
    //FIXME
    return true;
}
