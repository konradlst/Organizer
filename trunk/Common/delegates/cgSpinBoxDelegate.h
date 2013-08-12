#ifndef CGSPINBOXDELEGATE_H
#define CGSPINBOXDELEGATE_H

#include <QStyledItemDelegate>

class cgSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit cgSpinBoxDelegate(int decimals, QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &) const;

private:
    int m_decimals;
};

#endif // CGSPINBOXDELEGATE_H
