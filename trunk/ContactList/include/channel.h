#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>

class QLabel;
class QLineEdit;

namespace Channel
{
const QString Phone("Phone");
const QString Email("Email");
const QString Skype("Skype");
const QString Site("Site");

enum Type
{ PhoneType = 0, EmailType, SkypeType, SiteType};

class Data
{
public:
    explicit Data();

private:
    Type m_type;
    QString m_name;
    QString m_value;
};

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);
    bool isEmpty() const;
    void setName(Type _type, QString &_name);
    QString name();

private:
    QLabel *m_icon;
    QLabel *m_name;
    QLineEdit *m_value;
};

}
#endif // CHANNEL_H
