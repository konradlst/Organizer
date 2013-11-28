#include <QPushButton>
#include <QSpacerItem>
#include <QBoxLayout>
#include <QDateEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include "dialogConst.h"
#include "dealView.h"

namespace
{
const QStringList Labels = QObject::trUtf8("Created :;Duration :;Type :;Price :;DeadLine :;Humans :;").split(Separator);

const QString Created = QObject::trUtf8("Created");
const QString Duration = QObject::trUtf8("Duration");
const QString DealType = QObject::trUtf8("Deal type");
const QString Price = QObject::trUtf8("Price");
const QString DeadLine = QObject::trUtf8("DeadLine");
const QString Humans = QObject::trUtf8("Humans");
const QString Description = QObject::trUtf8("Description");
const QString DescriptionPlaceholder = QObject::trUtf8("Deal description (comment)");
const QString DeleteThisDeal = QObject::trUtf8("Delete this deal");
}

DealView::DealView(const int type, const QDate &created, const int price,
                   const QTime &duration, const QDate &deadline,
                   const QString &humans, const QString &description,
                   QGroupBox *parent)
    : QGroupBox(parent),
      m_created(new QDateEdit(created)),
      m_duration(new QTimeEdit(duration)),
      m_type(new QComboBox),
      m_price(new QSpinBox),
      m_deadline(new QDateEdit(deadline)),
      m_humans(new QLineEdit(humans)),
      m_description(new QLineEdit(description)),
      m_delete(new QPushButton)
{
    setTitle(DealTypes.at(type));
    m_type->addItems(DealTypes);
    m_type->setCurrentIndex(type);
    m_price->setSuffix(" rub.");
    m_price->setValue(price);
    m_humans->setPlaceholderText(HumansPlaceholder);
    m_description->setPlaceholderText(DescriptionPlaceholder);
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/delete"));

    m_created->setToolTip(Created);
    m_duration->setToolTip(Duration);
    m_type->setToolTip(DealType);
    m_price->setToolTip(Price);
    m_deadline->setToolTip(DeadLine);
    m_humans->setToolTip(Humans);
    m_description->setToolTip(Description);
    m_delete->setToolTip(DeleteThisDeal);

    QGridLayout *lay = new QGridLayout();
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setVerticalSpacing(0);
    for (int i = 0; i < 6; ++i)
        lay->addWidget(new QLabel(Labels[i]), 0, i);

    lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding), 0, 5);
    lay->addWidget(m_created, 1, 0);
    lay->addWidget(m_duration, 1, 1);
    lay->addWidget(m_type, 1, 2);
    lay->addWidget(m_price, 1, 3);
    lay->addWidget(m_deadline, 1, 4);
    lay->addWidget(m_humans, 1, 5, 1, 3);
    lay->addWidget(m_delete, 0, 7);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    descriptionLayout->addWidget(new QLabel(LblDescription));
    descriptionLayout->addWidget(m_description);

    QVBoxLayout *mLay = new QVBoxLayout();
    mLay->setContentsMargins(6, 0, 6, 6);
    mLay->addLayout(lay);
    mLay->addLayout(descriptionLayout);
    setLayout(mLay);

    connect(m_delete, SIGNAL(clicked()), SIGNAL(deleted()));
}
