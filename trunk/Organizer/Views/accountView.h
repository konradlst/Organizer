#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;
class QProgressBar;

//! \class AccountView
//! \brief Класс-представление счета.
class AccountView : public QWidget
{
    Q_OBJECT
public:
    explicit AccountView(int type = 0, const QString &name = QString(),
                         const qint64 &value = 0, const qint64 &maxValue = 0,
                         const QString &comment = QString(), QWidget *parent = 0);
    void rename(const QString &name);
    void setValue(qint64 value);

signals:
    void deleted();

private:
    QLabel *m_name;
    QComboBox *m_type;
    QPushButton *m_delete;
    QProgressBar *m_value;
};

#endif // ACCOUNTVIEW_H
