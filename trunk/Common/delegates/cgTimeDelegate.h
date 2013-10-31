#ifndef CGTIMEDELEGATE_H
#define CGTIMEDELEGATE_H

#include <QStyledItemDelegate>

class cgTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit cgTimeDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &) const;
};

#endif // CGTIMEDELEGATE_H
