#include <QStandardItemModel>
#include <QtSql>

namespace {
#define Fields_name "name"
#define Fields_number "number"
#define Fields_type "type"

#define QSQLITE "QSQLITE"
const QString QUERY_CREATE("CREATE TABLE phoneList ("
						   "name VARCHAR(255), "
						   "number VARCHAR(255) PRIMARY KEY NOT NULL, "
						   "type VARCHAR(255)"
						   ");");
const QString QUERY_INSERT("INSERT INTO phoneList(name, number, type) "
						   "VALUES ('%1', '%2', '%3');");
#define QUERY_SELECT "SELECT * FROM phoneList"
}

void setData(QStandardItemModel *data, QString &path)
{
	QSqlDatabase sdb = QSqlDatabase::addDatabase(QSQLITE);
	sdb.setDatabaseName(path);
	sdb.open();

	QSqlQuery a_query;
	a_query.exec(QUERY_CREATE);

	for(int i=0; i<data->rowCount(); ++i) {
		QString str_insert = QUERY_INSERT.arg(
								 data->data(data->index(i,0)).toString(),
								 data->data(data->index(i,1)).toString(),
								 data->data(data->index(i,2)).toString());
		a_query.exec(str_insert);
	}
}

QStandardItemModel *getData(QString &path)
{
	QSqlDatabase sdb = QSqlDatabase::addDatabase(QSQLITE);
	sdb.setDatabaseName(path);
	sdb.open();

	QSqlQuery a_query;
	a_query.exec(QUERY_SELECT);

	QSqlRecord rec = a_query.record();
	while (a_query.next()) {
		QList<QStandardItem*> record;
		record.append(new QStandardItem(
						  a_query.value(rec.indexOf(Fields_name)).toString()));
		record.append(new QStandardItem(
						  a_query.value(rec.indexOf(Fields_number)).toString()));
		record.append(new QStandardItem(
						  a_query.value(rec.indexOf(Fields_type)).toString()));
		m_model->appendRow(record);
	}
	return setHeader(m_model);
}
