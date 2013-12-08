#ifndef CHANNELVIEW_H
#define CHANNELVIEW_H

#include <QWidget>

class QLabel;
class QPushButton;

class ChannelView : public QWidget
{
    Q_OBJECT
public:
    explicit ChannelView(QWidget *parent = 0);

signals:
    void deleted();

private:
    QPushButton *m_type;
    QLabel *m_subType;
    QLabel *m_value;
    QPushButton *m_detail;
    QPushButton *m_delete;
};

#endif // CHANNELVIEW_H
