#ifndef CGSQLITEREADER_H
#define CGSQLITEREADER_H

#include "cgReader.h"

class cgSqliteReader : public cgReader
{
    Q_OBJECT
public:
    explicit cgSqliteReader(QObject *parent = 0);
    virtual aScheme* loadData(const QString &path) const;
    virtual bool saveData(const aScheme &scheme, const QString &path) const;
};

#endif // CGSQLITEREADER_H
