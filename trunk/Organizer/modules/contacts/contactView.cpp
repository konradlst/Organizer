#include <QGridLayout>
#include <QSizePolicy>
#include <QPushButton>
#include <QLabel>
#include "contactView.h"

ContactView::ContactView(QWidget *parent)
    : QWidget(parent),
      m_name(new QLabel()),
      m_surName(new QLabel()),
      m_otherName(new QLabel()),
      m_nickName(new QLabel()),
      m_birthday(new QLabel()),
      m_userPic(new QLabel()),
      m_editUserPic(new QPushButton())
{
    QGridLayout *layout = new QGridLayout();
    layout->setHorizontalSpacing(5);
    layout->setVerticalSpacing(0);
    layout->setContentsMargins(5, 3, 5, 3);

    QFont font;
    font.setPointSize(8);
    font.setBold(true);
    font.setWeight(75);
    m_name->setFont(font);

    layout->addWidget(m_name, 0, 1, 1, 1);

    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(m_userPic->sizePolicy().hasHeightForWidth());
    m_userPic->setSizePolicy(sizePolicy1);
    m_userPic->setFixedSize(120, 120);
    m_userPic->setPixmap(QPixmap(QString::fromUtf8(":/logo")));
    m_userPic->setScaledContents(true);
    m_userPic->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    layout->addWidget(m_userPic, 0, 0, 5, 1);

    sizePolicy1.setHeightForWidth(m_editUserPic->sizePolicy().hasHeightForWidth());
    m_editUserPic->setSizePolicy(sizePolicy1);
    m_editUserPic->setFixedSize(25, 25);
    m_editUserPic->setIcon(QIcon(":/editingMode"));
    m_editUserPic->setFlat(true);

    layout->addWidget(m_editUserPic, 0, 0, 1, 1);

    m_birthday->setFont(font);
    layout->addWidget(m_birthday, 4, 1, 1, 1);

    QFont font1;
    font1.setBold(true);
    font1.setWeight(75);
    m_surName->setFont(font1);

    layout->addWidget(m_surName, 1, 1, 1, 1);

    m_otherName->setFont(font1);

    layout->addWidget(m_otherName, 2, 1, 1, 1);

    QFont font2;
    font2.setPointSize(8);
    font2.setItalic(true);
    m_nickName->setFont(font2);

    layout->addWidget(m_nickName, 3, 1, 1, 1);

    setLayout(layout);

    //TEST
    m_name->setText("Ivan");
    m_surName->setText("Ivanov");
    m_otherName->setText("Ivanovich");
    m_nickName->setText("( venik )");
    m_birthday->setText("20.15.1981");
}

void ContactView::setName(const QString &name)
{
    m_name->setText(name);
}

void ContactView::setSurName(const QString &surName)
{
    m_surName->setText(surName);
}

void ContactView::setOtherName(const QString &otherName)
{
    m_otherName->setText(otherName);
}

void ContactView::setNickName(const QString &nickName)
{
    m_nickName->setText(nickName);
}

void ContactView::setBirthday(const QString &birthday)
{
    m_birthday->setText(birthday);
}

void ContactView::setUserPic(const QPixmap &userPic)
{
    m_userPic->setPixmap(userPic);
}

QString ContactView::name() const
{
    return m_name->text();
}

QString ContactView::surName() const
{
    return m_surName->text();
}

QString ContactView::otherName() const
{
    return m_otherName->text();
}

QString ContactView::nickName() const
{
    return m_nickName->text();
}

QString ContactView::birthday() const
{
    return m_birthday->text();
}

QString ContactView::userPic() const
{
    return m_userPic->text();
}
