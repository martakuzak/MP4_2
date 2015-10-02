#include "treeitem.h"

TreeItem::TreeItem(FileService *fileService, const QList<QVariant> &data, TreeItem *parent, const long int &off){
    qDebug()<<"TREEITEM: constructor";
    parentItem = parent;
    itemData = data;
    BoxFactory *bf = new BoxFactory(fileService);
    if(!(data.value(0).toString() == NAME)) {
        try {
            box= bf->getBox( data.value(1).toUInt(),data.value(0).toString(),off ) ;
        }
        catch(QException) {qDebug()<<"TREEITEM: exception while creating Box";}
    } else
        qDebug()<<"TREEITEM: data.value(0).toString() == NAME";
    delete bf;
}
////////////////////////////////////////////////////////////////////////////////////////////
TreeItem::TreeItem() {
}
////////////////////////////////////////////////////////////////////////////////////////////
TreeItem::~TreeItem(){
    qDebug()<<"TREEITEM: destructor";
    qDeleteAll(childItems);
    delete parentItem;
}
////////////////////////////////////////////////////////////////////////////////////////////
void TreeItem::appendChild(TreeItem *item){
    childItems.append(item);
}
////////////////////////////////////////////////////////////////////////////////////////////
TreeItem *TreeItem::child(int row){
    return childItems.value(row);
}
////////////////////////////////////////////////////////////////////////////////////////////
int TreeItem::childCount() const{
    return childItems.count();
}
////////////////////////////////////////////////////////////////////////////////////////////
int TreeItem::columnCount() const{
    return itemData.count();
}
////////////////////////////////////////////////////////////////////////////////////////////
QVariant TreeItem::data(int column) const{
    return itemData.value(column);
}
////////////////////////////////////////////////////////////////////////////////////////////
TreeItem *TreeItem::parent(){
    return parentItem;
}
////////////////////////////////////////////////////////////////////////////////////////////
int TreeItem::row() const {
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
    return 0;
}


