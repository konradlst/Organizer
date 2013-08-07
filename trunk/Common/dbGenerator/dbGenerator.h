#ifndef DBGENERATOR_H
#define DBGENERATOR_H

class QString;
class QDomElement;
class QStringList;

class dbGenerator
{
public:
    dbGenerator(const QString &metascheme, const QString &pathToDb);
    bool generate(const bool fillTable = false);

private:
    const QString &m_metascheme;
    const QString &m_pathToDb;

    bool loadScheme(QDomElement &scheme);
    void parseField(const QDomElement &field, QString &data);
    bool createTable(QStringList &queryText);
};

#endif // DBGENERATOR_H
