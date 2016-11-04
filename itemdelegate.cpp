#include "itemdelegate.h"

ItemDelegate::ItemDelegate(QObject *p):
    QStyledItemDelegate(p)
{

}
void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);
}
QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(50,30);
}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* edit = new QLineEdit(parent);
    return edit;
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit* edit = static_cast<QLineEdit*>(editor);
    edit->setText(index.data().toString());
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* edit = static_cast<QLineEdit*>(editor);
    model->setData(index,edit->text());
}

void ItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

