#ifndef CGDATETIMEDELEGATE_H
#define CGDATETIMEDELEGATE_H

#include <QStyledItemDelegate>

class cgDateTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit cgDateTimeDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &) const;

    
};

#endif // CGDATETIMEDELEGATE_H
