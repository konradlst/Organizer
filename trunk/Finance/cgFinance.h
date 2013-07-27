#ifndef CGFINANCE_H
#define CGFINANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QHBoxLayout;
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
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabLog;
    QWidget *m_tabMain;
    QTableView *logView;
    QTableView *m_mainView;
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *m_btnRemove;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *logModel;
    QSqlTableModel *m_accountModel;

    void initModel();
    void createInterface();
    bool dbGenerate();
};

#endif // CGFINANCE_H
