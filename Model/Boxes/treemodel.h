#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QHash>
#include <qDebug>
#include "fileservice.h"
#include "treeitem.h"

class Analyzer;
class TreeItem;
class MainWindow;
class DashWrapper;
/*!
  *\brief The TreeModel class
  * represents tree model for TreeView
 */

const QString SIZE = "Size";
const QString OFFSET = "Offset";

class TreeModel : public QAbstractItemModel {
    Q_OBJECT
private:
    //void setupModelData(const QStringList &lines, TreeItem *parent);
    /*!
      *\brief rootItem root of the tree model
     */
    TreeItem *rootItem;
    /*!
      *\brief treeItems QHash of all TreeItem's
      *key: offset in file
      *value: TreeItem
     */
    QHash<long,TreeItem*> *treeItems;
public:

    explicit TreeModel(FileService *fs, QObject *parent = 0);
    explicit TreeModel(QObject *parent = 0);
    //!Destructor
    ~TreeModel();
    /*!
      *\brief data
      *\param index
      *\param role
      *\return the data stored under the given role for the item referred to by the index.
     */
    QVariant data(const QModelIndex &index, int role) const;
    /*!
      *\brief flags
      *\param index
      *\return the item flags for the given index.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    /*!
      *\brief headerData
      *\param section
      *\param orientation
      *\param role
      *\return the data for the given role and section in the header with the specified orientation.
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    /*!
      *\brief index
      *\param row
      *\param column
      *\param parent
      *\return the index of the item in the model specified by the given row, column and parent index.
     */
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    /*!
      *\brief parent
      *\param index
      *\return the parent of the model item with the given index. If the item has no parent, an invalid QModelIndex is returned.
     */
    QModelIndex parent(const QModelIndex &index) const;
    /*!
      *\brief rowCount
      *\param parent
      *\return the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /*!
      *\brief columnCount
      *\param parent
      *\return the number of columns for the children of the given parent.
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    /*!
      *\brief getRootItem
      *\return rootItem
     */
    TreeItem *getRootItem() { return rootItem; }
    /*!
      *\brief getChild
      *\param parent parent TreeItem
      *\param type box type
      *\return child item of given parent and box type
     */
    TreeItem *getChild(TreeItem *parent, QString type);
    /*!
      *\brief getChild
      *\param offset offset of box in bytes in the file
      *\return child that has given offset
     */
    TreeItem *getChild(int offset);
    /*!
      *\brief getBoxes
      *\param type box type
      *\return list of pointers to boxes that has given type
     */
    QList <std::shared_ptr <Box>> getBoxes(const QString& type);
};

#endif // TREEMODEL_H
