#ifndef CGTASKDIALOG_H
#define CGTASKDIALOG_H

#include <QDialog>
#include <cgCalendarConst.h>

class QComboBox;
class QLineEdit;
class QDoubleSpinBox;

class cgTaskDialog : public QWidget
{
    Q_OBJECT
public:
    explicit cgTaskDialog(QWidget *parent = 0);
    void init(Calendar::TaskType type, Calendar::Duration frequency, QString description,
              double price, Calendar::Duration deadline);
    QStringList data() const;

private:
    void createInterface();

private:
    QComboBox *m_type;
    QComboBox *m_frequency;
    QLineEdit *m_description;
    QDoubleSpinBox *m_price;
    QComboBox *m_deadline;
    QPushButton *m_ok;
    QPushButton *m_cancel;
};

#endif // CGTASKDIALOG_H
