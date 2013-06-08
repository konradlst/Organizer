#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "channel.h"

namespace Channel {

Data::Data()
{
}

View::View(QWidget *parent) :
    QWidget(parent),
    m_icon(new QLabel),
    m_name(new QLabel),
    m_value(new QLineEdit)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_icon);
    layout->addWidget(m_name);
    layout->addWidget(m_value);
    setLayout(layout);
}

bool View::isEmpty() const
{
    return m_value->text().isEmpty();
}

void View::setName(Type _type, QString &_name)
{
    QString type;
    switch (_type)
    {
    case PhoneType:
        type = Phone;
        break;
    case EmailType:
        type = Email;
        break;
    case SkypeType:
        type = Skype;
        break;
    case SiteType:
        type = Site;
        break;
    default:
        break;
    }
    m_name->setText(QString("%1 ( % 2)").arg(type, _name));
}

QString View::name()
{
    //FIXME
    return m_name->text();
}

}
