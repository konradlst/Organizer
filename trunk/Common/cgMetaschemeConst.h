#ifndef CGMETASCHEMECONST_H
#define CGMETASCHEMECONST_H

#include <QString>
class QDomElement;

namespace Scheme
{
const QString metaschemeFile("./metascheme.xml");
const QString SPLITTER(";");
const QString VERSION("0.1.1");
const QString tagRoot("cg_db_scheme");
const QString tagTables("tables");
const QString tagValues("values");
const QString tagTable("table");
const QString tagDelegates("delegates");
const QString tagDelegate("delegate");
const QString attrVersion("version");
const QString attrName("name");
const QString attrValue("value");
const QString attrType("type");
const QString attrPk("pk");
const QString attrFk("fk");
const QString attrFkField("fkField");
const QString attrNullable("nullable");
const QString attrUnq("unq");
const QString attrDefault("default");
const QString attrDelegate("delegate");
const QString attrParam("param");

bool loadScheme(QDomElement &scheme, const QString &path = metaschemeFile);
}

namespace delegateName
{
const QString line("lineEdit");
const QString comboBox("comboBoxEdit");
const QString checkBox("checkBoxEdit");
const QString spinBox("spinBoxEdit");
const QString date("dateEdit");
const QString time("timeEdit");
const QString dateTime("dateTimeEdit");
const QString dSpinBox("doubleSpinBoxEdit");
}

namespace SQL
{
const QString SQLITE("QSQLITE");
const QString COMMA(", ");
const QString INSERT("INSERT INTO %1(%2) VALUES(%3);");
const QString INSERT_DEFAULT("INSERT INTO %1 DEFAULT VALUES;");
const QString DELETE_WHERE("DELETE FROM %1 WHERE id=%2;");
const QString CREATE("CREATE TABLE %1 (%2);");
const QString SELECT_SHORT("SELECT * FROM %1");
const QString SELECT("SELECT * FROM %1 WHERE ownerId = '%2'");
const QString SELECT_WHERE("SELECT * FROM %1 WHERE type = '%2' AND ownerId = '%3'");

const QString PRIMARY_KEY("PRIMARY KEY");
const QString FOREIGN_KEY("FOREIGN KEY (%1) REFERENCES %2(%3) ON UPDATE CASCADE ON DELETE CASCADE");
const QString NOT_NULL("NOT NULL");
const QString DEFAULT("DEFAULT %1");
const QString UNIQUE("UNIQUE");
}

#endif // CGMETASCHEMECONST_H
