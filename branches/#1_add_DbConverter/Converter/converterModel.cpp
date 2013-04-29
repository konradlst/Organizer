#include <QDomDocument>
#include "converterModel.h"

ConverterModel::ConverterModel(QWidget *parent) :
    QWidget(parent),
    m_data(new QDomDocument),
    m_pathToLoad(new QString),
    m_pathToSave(new QString)
{
}

void ConverterModel::setPathToLoad(const QString &path)
{
    *m_pathToLoad = path;
}

void ConverterModel::setPathToSave(const QString &path)
{
    *m_pathToSave = path;
}

bool ConverterModel::convert()
{
    return true;
}
