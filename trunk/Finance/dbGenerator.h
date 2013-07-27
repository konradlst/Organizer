#ifndef DBGENERATOR_H
#define DBGENERATOR_H

class QString;
class QDomElement;

class dbGenerator
{
public:
    dbGenerator(QString &metascheme, QString &pathToDb);
    bool generate();

private:
    QString &m_metascheme;
    QString &m_pathToDb;

    bool loadScheme(QDomElement &scheme);
    void parseField(const QDomElement &fieldElement, QString &data);
    bool createTable(QString &tableName, QString &fieldsData);
};

#endif // DBGENERATOR_H
