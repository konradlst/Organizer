#ifndef CGCHECKBOXDELEGATE_H
#define CGCHECKBOXDELEGATE_H

#include <QStyledItemDelegate>

class cgCheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit cgCheckBoxDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &) const;
};

#endif // CGCHECKBOXDELEGATE_H
