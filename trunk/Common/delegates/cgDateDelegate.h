#ifndef CGDATEDELEGATE_H
#define CGDATEDELEGATE_H

#include <QStyledItemDelegate>

class cgDateDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit cgDateDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &) const;
};

#endif // CGDATEDELEGATE_H
