#include "cgTimeDelegate.h"
#include <QTimeEdit>

namespace
{
const QString Format("hh:mm:ss");
}

cgTimeDelegate::cgTimeDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *cgTimeDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &,
                                      const QModelIndex &) const
{
    QTimeEdit *time = new QTimeEdit(parent);
    time->setDisplayFormat(Format);
    return time;
}

void cgTimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QTime value = QTime::fromString(index.model()->data(index).toString(), Format);
    QTimeEdit *time = static_cast<QTimeEdit*>(editor);
    time->setTime(value);
}

void cgTimeDelegate::setModelData(QWidget *editor,
                                  QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
    QTimeEdit *time = static_cast<QTimeEdit*>(editor);
    model->setData(index, time->time().toString(Format), Qt::EditRole);
}

void cgTimeDelegate::updateEditorGeometry(QWidget *editor,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
