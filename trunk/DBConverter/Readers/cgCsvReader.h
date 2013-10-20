#ifndef CGCSVREADER_H
#define CGCSVREADER_H

#include "cgReader.h"

class cgCsvReader : public cgReader
{
    Q_OBJECT
public:
    explicit cgCsvReader(QObject *parent = 0);
    virtual aScheme* loadData(const QString &path) const;
    virtual bool saveData(const aScheme &scheme, const QString &path) const;

private:
    QString m_separator;
};

#endif // CGCSVREADER_H
