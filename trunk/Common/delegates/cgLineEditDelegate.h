#ifndef CGLINEEDITDELEGATE_H
#define CGLINEEDITDELEGATE_H

#include <QStyledItemDelegate>

class cgLineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit cgLineEditDelegate(int maxLength, QString mask, bool readOnly,
                                QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

private:
    QString m_mask;
    bool m_readOnly;
    int m_maxLength;
};

#endif // CGLINEEDITDELEGATE_H
