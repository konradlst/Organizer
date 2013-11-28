#include <QPlainTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include "dialog.h"
#include "dialogConst.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent),
      m_ok(new QPushButton(LblOk)),
      m_lay(new QFormLayout()),
      m_type(new QComboBox()),
      m_description(new QPlainTextEdit())
{
    m_ok->setFixedSize(90, 25);
    setLayout(m_lay);
    setModal(true);

    connect(m_ok, SIGNAL(clicked()), SLOT(accept()));
}
