#include "cgLineEditDelegate.h"
#include <QLineEdit>

cgLineEditDelegate::cgLineEditDelegate(int maxLength, QString mask,
                                       QObject *parent) :
    QStyledItemDelegate(parent),
    m_mask(mask),
    m_maxLength(maxLength)
{
}

QWidget *cgLineEditDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &,
                                         const QModelIndex &) const
{
    QLineEdit *delegate = new QLineEdit(parent);
    delegate->setInputMask(m_mask);
    delegate->setMaxLength(m_maxLength);
    return delegate;
}

void cgLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *delegate = static_cast<QLineEdit*>(editor);
    delegate->setText(value);
}

void cgLineEditDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    QLineEdit *delegate = static_cast<QLineEdit*>(editor);
    model->setData(index, delegate->text(), Qt::EditRole);
}

void cgLineEditDelegate::updateEditorGeometry(QWidget *editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
