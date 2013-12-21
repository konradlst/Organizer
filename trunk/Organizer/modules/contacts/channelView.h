#ifndef CHANNELVIEW_H
#define CHANNELVIEW_H

#include <QWidget>

class QLabel;
class QPushButton;
struct ChannelData;

class ChannelView : public QWidget
{
    Q_OBJECT
public:
    explicit ChannelView(const QString &type, const QString &subType,
                         const QString &value, QWidget *parent = 0);
    explicit ChannelView(const ChannelData &data);

signals:
    void deleted();

private:
    QPushButton *m_type;
    QLabel *m_subType;
    QLabel *m_value;
    QPushButton *m_detail;
    QPushButton *m_delete;

    void createInterface();
};

#endif // CHANNELVIEW_H
