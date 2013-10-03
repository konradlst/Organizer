#include "cgDateTimeDelegate.h"
#include <QDateTimeEdit>

namespace
{
const QString FORMAT("dd.MM.yyyy hh:mm:ss.zzz");
}

cgDateTimeDelegate::cgDateTimeDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *cgDateTimeDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &) const
{
    QDateTimeEdit *dateTime = new QDateTimeEdit(parent);
    dateTime->setDateTime(QDateTime::currentDateTime());
    dateTime->setCalendarPopup(true);
    dateTime->setDisplayFormat(FORMAT);
    return dateTime;
}

void cgDateTimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QDateTime value = index.model()->data(index, Qt::EditRole).toDateTime();
    QDateTimeEdit *dateTime = static_cast<QDateTimeEdit*>(editor);
    dateTime->setDateTime(value);
}

void cgDateTimeDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
    QDateTimeEdit *dateTime = static_cast<QDateTimeEdit*>(editor);
    model->setData(index, dateTime->dateTime().toString(FORMAT), Qt::EditRole);
}

void cgDateTimeDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}