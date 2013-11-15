#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include <QWidget>

class QComboBox;
class QTimeEdit;
class QLineEdit;
class QPushButton;

//! \class TimeView
//! \brief Класс-представление записи о времени.
class TimeView : public QWidget
{
    Q_OBJECT
public:
    explicit TimeView(QWidget *parent = 0);

signals:
    void deleted();

private:
    QComboBox *m_type;
    QTimeEdit *m_start;
    QTimeEdit *m_stop;
    QTimeEdit *m_duration;
    QLineEdit *m_comment;
    QPushButton *m_delete;
};

#endif // TIMEVIEW_H
