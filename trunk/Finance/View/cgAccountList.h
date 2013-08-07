#ifndef CGACCOUNTLIST_H
#define CGACCOUNTLIST_H

#include <QObject>
#include <QList>
class QGroupBox;
class QDoubleSpinBox;
class QFormLayout;
class QProgressBar;

struct cgAccount
{
    cgAccount(QString name, qint64 value) :
        m_name(name),
        m_value(value)
    {}
    QString m_name;
    qint64 m_value;
};

class cgAccountList
{
public:
    cgAccountList();
    QWidget *view();
    void addAccount(const cgAccount &account);
    bool removeAccount(const QString &name);
    bool removeAccount(const int &index);
    qint64 total();
    qint64 value(const QString &name);
    qint64 value(const int &index);

private:
    QGroupBox *m_view;
    QFormLayout *m_mainLayout;
    QDoubleSpinBox *m_totalView;
    qint64 m_total;
    QList<cgAccount> *m_accounts;
    QHash<QString, QProgressBar *> *m_accountsView;

    void createView();
};

#endif // CGACCOUNTLIST_H
