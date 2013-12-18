#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QHash>
#include <qDebug>
#include "analyzer.h"
#include "treeitem.h"

class Analyzer;
class TreeItem;
class MainWindow;
class DashProxy;
/*!
 * \brief The TreeModel class
 * represents tree model for TreeView
 */
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    //void setupModelData(const QStringList &lines, TreeItem *parent);
    /*!
     * \brief rootItem root of the tree model
     */
    TreeItem *rootItem;
    /*!
     * \brief treeItems QHash of all TreeItem's
     * key: offset in file
     * value: TreeItem
     */
    QHash<long,TreeItem*>* treeItems;

public:
    /*!
     * \brief TreeModel constructor
     * \param fileName  name of the analyzed file
     * \param parent
     */
    explicit TreeModel(Analyzer* analyzer, QObject *parent = 0);
    //!Destructor
    ~TreeModel();
    /*!
     * \brief data
     * \param index
     * \param role
     * \return the data stored under the given role for the item referred to by the index.
     */
    QVariant data(const QModelIndex &index, int role) const;
    /*!
     * \brief flags
     * \param index
     * \return the item flags for the given index.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    /*!
     * \brief headerData
     * \param section
     * \param orientation
     * \param role
     * \return the data for the given role and section in the header with the specified orientation.
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    /*!
     * \brief index
     * \param row
     * \param column
     * \param parent
     * \return the index of the item in the model specified by the given row, column and parent index.
     */
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    /*!
     * \brief parent
     * \param index
     * \return the parent of the model item with the given index. If the item has no parent, an invalid QModelIndex is returned.
     */
    QModelIndex parent(const QModelIndex &index) const;
    /*!
     * \brief rowCount
     * \param parent
     * \return the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /*!
     * \brief columnCount
     * \param parent
     * \return the number of columns for the children of the given parent.
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    TreeItem* getRootItem() { return rootItem; }
    TreeItem *getChild(TreeItem *parent, QString type);
    TreeItem *getChild(int offset);
    QList <std::shared_ptr <Box>> getBoxes(const QString& type);
    //    unsigned long int mdatSize(const unsigned long int& firstSample, const unsigned int& sampleNumber, std::shared_ptr<Box>& stsz,
    //                               Analyzer* an);
    //    unsigned int writeMdat(const unsigned long int& firstSample, const unsigned int& sampleNumber, std::shared_ptr<Box>& stsz, QFile* dashFile,
    //                   Analyzer* an);
    //    unsigned int writeMoof(const unsigned long int& sequenceNumber, const unsigned int& trackID, const unsigned long &baseMediaDecodeTime,
    //                          const unsigned int& trunFlag2, const unsigned int& trunFlag3, const unsigned int& sampleCount,
    //                          const signed int& dataOffset, const unsigned int& firstSampleFlags, const unsigned long int& firstSample, std::shared_ptr<Box>& stsz, QFile* dashFile, Analyzer* an);
    //    unsigned int writeMfhd(const unsigned long int& sn, QFile* dashFile, Analyzer* an);
    //    unsigned int writeTfhd(const unsigned int& trackID, QFile* dashFile, Analyzer* an);
    //    unsigned int writeTfdt(const unsigned long &baseMediaDecodeTime, QFile* dashFile, Analyzer* an);
    //    unsigned int writeTrun(const unsigned int& flag2, const unsigned int& flag3, const unsigned int& sampleCount,
    //                           const signed int& dataOffset, const unsigned int& firstSampleFlags, const unsigned long int& firstSample, std::shared_ptr<Box>& stsz, QFile* dashFile, Analyzer* an);
    //    unsigned int writeTraf(const unsigned int& trackID, const unsigned long &baseMediaDecodeTime, const unsigned int& trunFlag2,
    //                           const unsigned int& trunFlag3, const unsigned int& sampleCount, const signed int& dataOffset,
    //                           const unsigned int& firstSampleFlags, const unsigned long int& firstSample, std::shared_ptr<Box>& stsz, QFile* dashFile, Analyzer* an);
};

#endif // TREEMODEL_H
