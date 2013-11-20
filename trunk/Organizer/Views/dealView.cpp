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
#include "dealView.h"

namespace
{
const QChar Separator = ';';

const QStringList Labels = QObject::trUtf8("Created :;Duration :;Type :;Price :;DeadLine :;Humans :;").split(Separator);
const QString LblDescription = QObject::trUtf8("Description :");

const QString Created = QObject::trUtf8("Created");
const QString Duration = QObject::trUtf8("Duration");
const QString DealType = QObject::trUtf8("Deal type");
const QString Price = QObject::trUtf8("Price");
const QString DeadLine = QObject::trUtf8("DeadLine");
const QString Humans = QObject::trUtf8("Humans");
const QString Description = QObject::trUtf8("Description");
const QString DescriptionPlaceholder = QObject::trUtf8("Deal description (comment)");
const QString HumansPlaceholder = QObject::trUtf8("Associated users separated by commas");
const QString DeleteThisDeal = QObject::trUtf8("Delete this deal");

//test
const QString DealName = QObject::trUtf8("New Deal");
const QStringList DealTypes = QObject::trUtf8("Type1;Type2").split(Separator);
//end test
}

DealView::DealView(QGroupBox *parent)
    : QGroupBox(parent),
      m_created(new QDateEdit),
      m_duration(new QTimeEdit),
      m_type(new QComboBox),
      m_price(new QSpinBox),
      m_deadline(new QDateEdit),
      m_humans(new QLineEdit),
      m_description(new QLineEdit),
      m_delete(new QPushButton)
{
    //test
    setTitle(DealName);
    m_type->addItems(DealTypes);
    //end test
    m_price->setSuffix(" rub.");
    m_humans->setPlaceholderText(HumansPlaceholder);
    m_description->setPlaceholderText(DescriptionPlaceholder);
    m_delete->setFlat(true);
    m_delete->setFixedSize(25, 25);
    m_delete->setIcon(QIcon(":/deleteContact"));

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
