#include "cgDateDelegate.h"
#include <QDateEdit>

namespace
{
const QString Format("dd.MM.yyyy");
}

cgDateDelegate::cgDateDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *cgDateDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &,
                                      const QModelIndex &) const
{
    QDateEdit *date = new QDateEdit(parent);
    date->setDisplayFormat(Format);
    date->setCalendarPopup(true);
    return date;
}

void cgDateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QDate value = QDate::fromString(index.model()->data(index).toString(), Format);
    QDateEdit *date = static_cast<QDateEdit*>(editor);
    date->setDate(value);
}

void cgDateDelegate::setModelData(QWidget *editor,
                                  QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
    QDateEdit *date = static_cast<QDateEdit*>(editor);
    model->setData(index, date->date().toString(Format), Qt::EditRole);
}

void cgDateDelegate::updateEditorGeometry(QWidget *editor,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
