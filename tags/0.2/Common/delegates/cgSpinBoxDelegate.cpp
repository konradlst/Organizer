#include "cgSpinBoxDelegate.h"
#include <QDoubleSpinBox>

cgSpinBoxDelegate::cgSpinBoxDelegate(int decimals, QObject *parent) :
    QStyledItemDelegate(parent),
    m_decimals(decimals)
{
}

QWidget *cgSpinBoxDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &,
                                         const QModelIndex &) const
{
    QDoubleSpinBox *box = new QDoubleSpinBox(parent);
    box->setMaximum(9999999);
    box->setMinimum(-9999999);
    box->setDecimals(m_decimals);
    return box;
}

void cgSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *box = static_cast<QDoubleSpinBox*>(editor);
    box->setValue(value);
}

void cgSpinBoxDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    QDoubleSpinBox *box = static_cast<QDoubleSpinBox*>(editor);
    model->setData(index, box->value(), Qt::EditRole);
}

void cgSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
