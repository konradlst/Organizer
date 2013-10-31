#ifndef CGCOMBOBOXDELEGATE_H
#define CGCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class cgComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit cgComboBoxDelegate(const QStringList &list, bool editable, QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &) const;

private:
    QStringList m_list;
    bool m_editable;
};

#endif // CGCOMBOBOXDELEGATE_H
