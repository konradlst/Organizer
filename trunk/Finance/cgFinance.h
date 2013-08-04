#ifndef CGFINANCE_H
#define CGFINANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
class QSqlTableModel;
class QTableView;
class QComboBox;
QT_END_NAMESPACE

class cgFinance : public QMainWindow
{
    Q_OBJECT
public:
    cgFinance(QWidget *parent = 0);
    ~cgFinance();

private slots:
    void currentTableChanged(const int &index);
    void submit();
    void addRecord();
    void removeRecord();
    void dbGenerate();

private:
    QWidget          *centralWidget;
    QTabWidget       *m_tabWidget;
    QTableView       *m_view;
    QHash<QString, QSqlTableModel *> *m_models;
    QComboBox        *m_tableComboBox;
    QPushButton      *m_btnOpenDb;
    QPushButton      *m_btnAdd;
    QPushButton      *m_btnSubmit;
    QPushButton      *m_btnRevert;
    QPushButton      *m_btnRemove;
    QWidget          *m_accountTab;
    QStringList       m_tables;
    QString           m_currentTable;
    QString           m_currentPathToDb;

    void initModel();
    void createInterface();
    void createAccountTab();
    QString openDb();
};

#endif // CGFINANCE_H
