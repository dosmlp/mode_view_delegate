#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QSettings>
struct Node{
    enum Type{
        Key,
        Value
    };
    Node* parent;
    QList<Node*> children;
    QString text;
    Type t;
    Node(const QString& t)
    {
        text = t;
        parent = Q_NULLPTR;
    }
    ~Node()
    {
        qDeleteAll(children);
        children.clear();
    }
};


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(QObject* p = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QMap<int,QVariant> itemData(const QModelIndex &index) const;
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;


private:
    void loadSet();
    inline Node* getNode(const QModelIndex &index) const;
    Node* rootNode;
};

#endif // TREEMODEL_H
