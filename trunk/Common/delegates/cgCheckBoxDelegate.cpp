#include "cgCheckBoxDelegate.h"
#include <QCheckBox>

cgCheckBoxDelegate::cgCheckBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *cgCheckBoxDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &) const
{
    QCheckBox *box = new QCheckBox(parent);
    return box;
}

void cgCheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const int value = index.model()->data(index, Qt::EditRole).toInt();
    QCheckBox *box = static_cast<QCheckBox*>(editor);
    switch (value)
    {
    case Qt::Checked:
        box->setChecked(true);
        break;
    case Qt::Unchecked:
        box->setChecked(false);
    default:
        break;
    }
}

void cgCheckBoxDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
    QCheckBox *box = static_cast<QCheckBox*>(editor);
    model->setData(index, box->checkState(), Qt::EditRole);
}

void cgCheckBoxDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
