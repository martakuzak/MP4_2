
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
#include "bitoperator.h"
#include "fileservice.h"

class BitOperator;
class TreeItem;
class TreeModel;
/*!
  *\brief The Analyzer class
  * provides tools to analyze MP4 file.
 */
class Analyzer {
public:
    Analyzer();
    /*!
      *\brief Analyzer - constructor
      *\param fileName name of the file to be analyzed
     */
    Analyzer(FileService *fs);
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
    QString decToHex(const unsigned long& offset);
    //ZMIANY - START
    /*!
      *\brief fileName
      * name of the analyzed file
     */
    //QString fileName;
    /*!
      *\brief file
      *analyzed file
     */
    //QFile *file;
    /*!
      *\brief fileSize
      *number of bytes of analyzed file
     */
    //unsigned long int fileSize;
    FileService *fileService;
    //ZMIANY - KONIEC
    /*!
      *\brief mdatOffset
      *offset in bytes of mdat box
     */
    unsigned long int mdatOffset;
    BitOperator* bitOperator;

};


#endif // ANALYZER_H
