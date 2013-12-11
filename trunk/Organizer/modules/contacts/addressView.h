#ifndef ADDRESSVIEW_H
#define ADDRESSVIEW_H

#include <QWidget>

class QPushButton;
class QLabel;

class AddressView : public QWidget
{
    Q_OBJECT
public:
    explicit AddressView(const QString &country, const QString &city,
                         const QString &street, const QString &home,
                         const QString &apartment, QWidget *parent = 0);

signals:
    void deleted();

private:
    QPushButton *m_country;
    QPushButton *m_city;
    QLabel *m_street;
    QLabel *m_home;
    QLabel *m_apartment;
    QPushButton *m_detail;
    QPushButton *m_delete;
};

#endif // ADDRESSVIEW_H
