#ifndef CONTACTVIEW_H
#define CONTACTVIEW_H

#include <QWidget>

class QLabel;
class QPushButton;
struct ContactData;

class ContactView : public QWidget
{
    Q_OBJECT
public:
    explicit ContactView(QWidget *parent = 0);
    void setData(const ContactData &data);
    void setName(const QString &name);
    void setSurName(const QString &surName);
    void setOtherName(const QString &otherName);
    void setNickName(const QString &nickName);
    void setBirthday(const QString &birthday);
    void setUserPic(const QPixmap &userPic);
    void setVisibleEditUserPic(bool flag);
    QString name() const;
    QString surName() const;
    QString otherName() const;
    QString nickName() const;
    QString birthday() const;
    QString userPic() const;

private:
    QLabel *m_name;
    QLabel *m_surName;
    QLabel *m_otherName;
    QLabel *m_nickName;
    QLabel *m_birthday;
    QLabel *m_userPic;
    QPushButton *m_editUserPic;
};

#endif // CONTACTVIEW_H
