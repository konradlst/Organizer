#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include "contactsConst.h"
#include "companyData.h"
#include "companyDialog.h"

CompanyDialog::CompanyDialog(QWidget *parent)
    : Dialog(parent),
      m_name(new QLineEdit()),
      m_phone(new QLineEdit()),
      m_department(new QLineEdit()),
      m_post(new QLineEdit()),
      m_address(new QLineEdit()),
      m_dateIn(new QDateEdit()),
      m_dateOut(new QDateEdit())
{
    setWindowTitle(Title::company);

    m_name->setPlaceholderText(Placeholder::name);
    m_phone->setPlaceholderText(Placeholder::phone);
    m_department->setPlaceholderText(Placeholder::department);
    m_post->setPlaceholderText(Placeholder::post);
    m_address->setPlaceholderText(Placeholder::address);

    m_dateIn->setCalendarPopup(true);
    m_dateOut->setCalendarPopup(true);

    m_lay->addRow(Label::name, m_name);
    m_lay->addRow(Label::phone, m_phone);
    m_lay->addRow(Label::department, m_department);
    m_lay->addRow(Label::post, m_post);
    m_lay->addRow(Label::dateIn, m_dateIn);
    m_lay->addRow(Label::dateOut, m_dateOut);
    m_lay->addWidget(m_ok);
}

QStringList *CompanyDialog::data()
{
    QStringList *data = new QStringList();
    *data << m_name->text()
          << m_phone->text()
          << m_department->text()
          << m_post->text()
          << m_address->text()
          << m_dateIn->date().toString(DateFormat)
          << ((m_dateOut->date() == QDateEdit().date())
                ? ""
                : m_dateOut->date().toString(DateFormat));
    return data;
}

CompanyData CompanyDialog::data2() const
{
    CompanyData data;
    data.company = m_name->text();
    data.post = m_post->text();
    data.dateIn = m_dateIn->text();
    data.dateOut = m_dateOut->text();
    return data;
}
