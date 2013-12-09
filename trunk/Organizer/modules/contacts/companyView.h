#ifndef COMPANYVIEW_H
#define COMPANYVIEW_H

#include <QWidget>

class QPushButton;
class QLabel;

class CompanyView : public QWidget
{
    Q_OBJECT
public:
    explicit CompanyView(QWidget *parent = 0);

signals:
    void deleted();

private:
    QPushButton *m_company;
    QPushButton *m_post;
    QLabel *m_dateIn;
    QLabel *m_dateOut;
    QPushButton *m_detail;
    QPushButton *m_delete;
};

#endif // COMPANYVIEW_H
