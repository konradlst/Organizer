#ifndef CONVERTERMODEL_H
#define CONVERTERMODEL_H

#include <QWidget>

class QDomDocument;

class ConverterModel : public QWidget
{
    Q_OBJECT
public:
    explicit ConverterModel(QWidget *parent = 0);

public slots:
    void setPathToLoad(const QString &path);
    void setPathToSave(const QString &path);
    bool convert();

private:
    QDomDocument *m_data;
    QString *m_pathToLoad;
    QString *m_pathToSave;
};

#endif // CONVERTERMODEL_H
