#include "cgComboBoxDelegate.h"
#include <QComboBox>

cgComboBoxDelegate::cgComboBoxDelegate(const QStringList &list, bool editable, QObject *parent) :
    QStyledItemDelegate(parent),
    m_list(list),
    m_editable(editable)
{
}

QWidget *cgComboBoxDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &) const
{
    QComboBox *box = new QComboBox(parent);
    box->addItems(m_list);
    box->setEnabled(m_editable);
    return box;
}

void cgComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QString value = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *box = static_cast<QComboBox*>(editor);
    box->setCurrentText(value);
}

void cgComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    model->setData(index, box->currentText(), Qt::EditRole);
}

void cgComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
