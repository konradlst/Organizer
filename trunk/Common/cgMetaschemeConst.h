#ifndef CGMETASCHEMECONST_H
#define CGMETASCHEMECONST_H

#include <QString>

class QDomElement;

namespace Scheme
{
const QString Splitter = ";";
bool load(QDomElement &scheme, const QString &path = QString());
}

namespace SchemeTag
{
const QString Root = "cg_db_scheme";
const QString Tables = "tables";
const QString Values = "values";
const QString Table = "table";
const QString Delegates = "delegates";
const QString Delegate = "delegate";
}

namespace SchemeAttr
{
const QString Version = "version";
const QString Name = "name";
const QString Value = "value";
const QString Type = "type";
const QString Pk = "pk";
const QString Fk = "fk";
const QString FkField = "fkField";
const QString Nullable = "nullable";
const QString Unq = "unq";
const QString Default = "default";
const QString Delegate = "delegate";
const QString Param = "param";
}

namespace delegateName
{
const QString line = "lineEdit";
const QString comboBox = "comboBoxEdit";
const QString checkBox = "checkBoxEdit";
const QString spinBox = "spinBoxEdit";
const QString date = "dateEdit";
const QString time = "timeEdit";
const QString dateTime = "dateTimeEdit";
const QString dSpinBox = "doubleSpinBoxEdit";
}

namespace SQL
{
const QString Sqlite("QSQLITE");
const QString Comma(", ");
const QString Insert("INSERT INTO %1(%2) VALUES(%3);");
const QString InsertDefault("INSERT INTO %1 DEFAULT VALUES;");
const QString DeleteWhere("DELETE FROM %1 WHERE id=%2;");
const QString Create("CREATE TABLE %1 (%2);");
const QString SelectShort("SELECT * FROM %1");
const QString Select("SELECT * FROM %1 WHERE ownerId = '%2'");
const QString SelectWhere("SELECT * FROM %1 WHERE type = '%2' AND ownerId = '%3'");

const QString PrimaryKey("PRIMARY KEY");
const QString ForeignKey("FOREIGN KEY (%1) REFERENCES %2(%3) ON UPDATE CASCADE ON DELETE CASCADE");
const QString NotNull("NOT NULL");
const QString Default("DEFAULT %1");
const QString Unique("UNIQUE");
}

#endif // CGMETASCHEMECONST_H
