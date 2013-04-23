#ifndef CONVERTERSQL_H
#define CONVERTERSQL_H

#include "converter.h"

class ConverterSql : public Converter
{
public:
	explicit ConverterSql(Converter *parent = 0);
	void setData(QStandardItemModel *data, QString &path);
	QStandardItemModel *getData(QString &path);
};

#endif // CONVERTERSQL_H
