#include "widget.h"
#include <QApplication>
#include <QTableView>
#include "treemodel.h"
#include "itemdelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    TreeModel* model = new TreeModel();
    //QStringListModel* model = new QStringListModel();
    ItemDelegate* delegate = new ItemDelegate();
    //QStringList list;
    //list<<"4"<<"5";
    //model->setStringList(list);
    w.setModel(model);
    w.setItemDelegate(delegate);
    w.show();
    QTableView tw;
    tw.setModel(model);
    tw.setItemDelegate(delegate);
    tw.setSelectionModel(w.selectionModel());
    tw.show();

    return a.exec();
}
