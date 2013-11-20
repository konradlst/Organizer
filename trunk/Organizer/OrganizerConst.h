#ifndef ORGANIZERCONST_H
#define ORGANIZERCONST_H

#include <QList>
#include <QVariant>

namespace Data
{
    typedef QList<QVariant> Record;
    typedef QList<Record> Table;
    typedef QList<Table> Scheme;
}

#endif // ORGANIZERCONST_H
