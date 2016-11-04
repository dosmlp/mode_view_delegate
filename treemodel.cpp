#include "treemodel.h"

TreeModel::TreeModel(QObject *p):
    QAbstractItemModel(p)
{
    loadSet();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();
    Node* p = getNode(parent);
    Node* c = p->children.value(row);
    if(c)
        return createIndex(row,column,c);
    return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    Node* n = getNode(child);
    if(!n)
        return QModelIndex();
    Node* p = n->parent;
    if(!p)
        return QModelIndex();
    Node* gp = p->parent;
    if(!gp)
        return QModelIndex();

    int row = gp->children.indexOf(p);
    return createIndex(row,0,p);
}
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
        return 0;
    Node* p = getNode(parent);
    if(!p)
        return 0;

    return p->children.size();
}
int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(index.column() > 0)
        return QVariant();
    Node* n = getNode(index);
    if(!n)
        return QVariant();

    if(index.column() == 0)
    {
        switch (role) {
        case Qt::DisplayRole:
            return n->text;
        case Qt::ToolTipRole:
            return n->text;
        case Qt::EditRole:
            return n->text;
        default:
            return QVariant();
            break;
        }
    }
    return QVariant();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column() > 0)
        return false;
    Node* n = getNode(index);
    if(!n)
        return false;
    if(role == Qt::EditRole)
    {
        n->text = value.toString();
        QSettings set("set.ini",QSettings::IniFormat);
        set.setIniCodec("UTF-8");
        set.setValue(n->parent->text,n->text);
        emit dataChanged(index,index,QVector<int>()<<role);
    }
    return true;
}

QMap<int, QVariant> TreeModel::itemData(const QModelIndex &index) const
{
    QMap<int, QVariant> roles;
    for (int i = 0; i < Qt::UserRole; ++i) {
        QVariant variantData = data(index, i);
        if (variantData.isValid())
            roles.insert(i, variantData);
    }
    return roles;

}

bool TreeModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    bool b = true;
    for (QMap<int, QVariant>::ConstIterator it = roles.begin(); it != roles.end(); ++it)
        b = b && setData(index, it.value(), it.key());
    return b;
}
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags f = QAbstractItemModel::flags(index);
    if(index.isValid())
    {
        if(getNode(index)->t == Node::Value)
        {
            //让model可编辑,model必须得让delegate知道它的数据项是可编辑的.
            f |= Qt::ItemIsEditable;
            return f;
        }
    }
    return f;

}
void TreeModel::loadSet()
{
    rootNode = new Node("root");
    QSettings set("set.ini",QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    QStringList keylist = set.allKeys();

    for(int i = 0;i < keylist.size();++i)
    {
        Node* n = new Node(keylist.at(i));
        n->t = Node::Key;
        QString v = set.value(keylist.at(i)).toString();
        Node* nc = new Node(v);
        nc->t = Node::Value;
        nc->parent = n;
        n->children.append(nc);

        rootNode->children.append(n);
        n->parent = rootNode;
    }

}

Node* TreeModel::getNode(const QModelIndex &index) const
{
    if(index.isValid())
    {
        return static_cast<Node*>(index.internalPointer());
    }
    else
    {
        return rootNode;
    }
}
