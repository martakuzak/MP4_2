
#ifndef ANALYZER_H
#define ANALYZER_H
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QVariant>
#include <QTextStream>
#include <qDebug>
#include "treemodel.h"
#include "treeitem.h"
#include "sampletablebox.h"
#include "mainwindow.h"
#include "filebitoperator.h"

class TreeItem;
class TreeModel;
/*!
  *\brief The Analyzer class
  * provides tools to analyze MP4 file.
 */
class Analyzer {
private:
    FileBitOperator* fbOperator;
    /*!
      *\brief mdatOffset
      *offset in bytes of mdat box
     */
    unsigned long int mdatOffset;
public:
    Analyzer();
    /*!
      *\brief Analyzer - constructor
      *\param fileName name of the file to be analyzed
     */
    Analyzer(FileBitOperator *fs);
    ~Analyzer();
    /*!
      *\brief setData adds children to the parent.
      *\param parent parent of the tree fragment that children are to be analyzed.
     */
    void setData(TreeItem *parent, QHash<long,TreeItem*> *items);
private:
    /*!
      *\brief setData the method is calls inside public setData method. It analyzes mp4 file by finding boxes, creating TreeItem objects
      *for each box and adding them to their parents.
      *\param parent parent of the tree fragment that children are to be analyzed
      *\param items hashmap of TreeItem pointers
      *\param off offset of the analyzed box
      *\param maxOff max offset possible of the parent analyzed box
     */
    void setData(TreeItem *&parent, QHash<long,TreeItem*> *items, const unsigned long int &off, unsigned long int maxOff = 0L);
    /*!
     * @brief decToHex
     * @param offset
     * @return QString that contains hex representation of given decimal number
     */
    QString decToHex(const unsigned long& offset);

};

#endif // ANALYZER_H
