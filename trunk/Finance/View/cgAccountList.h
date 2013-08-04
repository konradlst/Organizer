#ifndef CGACCOUNTLIST_H
#define CGACCOUNTLIST_H

#include <QObject>
#include <QList>
class QGroupBox;
class QDoubleSpinBox;
class QFormLayout;

class cgAccount
{
public:
    cgAccount(QString &name, qint64 &value);
    QString name() const;
    qint64 value() const;
private:
    QString m_name;
    qint64 m_value;
};

class cgAccountList
{
public:
    cgAccountList();
    QWidget *view();
    void addAccount(cgAccount &account);
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

    void createView();
};

#endif // CGACCOUNTLIST_H
