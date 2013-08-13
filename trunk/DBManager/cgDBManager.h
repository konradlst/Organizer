#ifndef CGDBMANAGER_H
#define CGDBMANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
class QSqlTableModel;
class QTableView;
class QComboBox;
QT_END_NAMESPACE

class cgDBManager : public QMainWindow
{
    Q_OBJECT
public:
    cgDBManager(QWidget *parent = 0);
    ~cgDBManager();

private slots:
    void currentTableChanged(const int &index);
    void submit();
    void addRecord();
    void removeRecord();
    void revertAll();
    void dbGenerate();

private:
    QWidget          *centralWidget;
    QTableView       *m_view;
    QHash<QString, QSqlTableModel *> *m_models;
    QComboBox        *m_tableComboBox;
    QPushButton      *m_btnOpenDb;
    QPushButton      *m_btnAdd;
    QPushButton      *m_btnSubmit;
    QPushButton      *m_btnRevert;
    QPushButton      *m_btnRemove;
    QStringList       m_tables;
    QString           m_currentTable;
    QString           m_currentPathToDb;

    void initModel();
    void createInterface();
    QString openDb();
    void setDelegates();
};

#endif // CGDBMANAGER_H
