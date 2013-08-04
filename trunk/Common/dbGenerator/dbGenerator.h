#ifndef DBGENERATOR_H
#define DBGENERATOR_H

class QString;
class QDomElement;
class QStringList;

class dbGenerator
{
public:
    dbGenerator(QString &metascheme, QString &pathToDb);
    bool generate();

private:
    QString &m_metascheme;
    QString &m_pathToDb;

    bool loadScheme(QDomElement &scheme);
    void parseField(const QDomElement &field, QString &data);
    bool createTable(QStringList &queryText);
};

#endif // DBGENERATOR_H
