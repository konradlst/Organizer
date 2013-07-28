#ifndef CGFINANCE_H
#define CGFINANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
class QTableView;
QT_END_NAMESPACE

class cgFinance : public QMainWindow
{
    Q_OBJECT
public:
    cgFinance(QWidget *parent = 0);
    ~cgFinance();

private slots:
    void submit();
    void addRecord();
    void removeRecord();

private:
    QWidget             *centralWidget;
    QTabWidget          *m_tabWidget;
    QTableView          *m_logView;
    QTableView          *m_accountView;
    QTableView          *m_timeView;
    QHash<QString, QSqlTableModel *> *m_models;
    QPushButton         *m_btnAdd;
    QPushButton         *m_btnSubmit;
    QPushButton         *m_btnRevert;
    QPushButton         *m_btnRemove;
    QDialogButtonBox    *m_btnBox;

    void initModel();
    void createInterface();
    bool dbGenerate();
};

#endif // CGFINANCE_H
