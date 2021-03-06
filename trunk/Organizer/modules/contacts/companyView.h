#ifndef COMPANYVIEW_H
#define COMPANYVIEW_H

#include <QWidget>

class QPushButton;
class QLabel;
struct CompanyData;

class CompanyView : public QWidget
{
    Q_OBJECT
public:
    explicit CompanyView(const QString &company, const QString &post,
                         const QString &dateIn, const QString &dateOut = QString(),
                         QWidget *parent = 0);
    explicit CompanyView(const CompanyData &data);

signals:
    void deleted();

private:
    QPushButton *m_company;
    QPushButton *m_post;
    QLabel *m_dateIn;
    QLabel *m_dateOut;
    QPushButton *m_detail;
    QPushButton *m_delete;

    void createInterface();
};

#endif // COMPANYVIEW_H
