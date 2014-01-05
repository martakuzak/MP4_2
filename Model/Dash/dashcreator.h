#ifndef DASHCREATOR_H
#define DASHCREATOR_H

#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDir>
#include "treemodel.h"

class TreeModel;
/*!
  *\brief The DashCreator class provides several methods that enables writing mp4 dash file. The file may be streamed via internet
  *according to MPEG-DASH standard.
 */
class DashCreator {
private:
    QString dashPath;
    //name of analyzed file
    QString fileName;
    TreeModel *model;
    QFile *initFile;
    QFile *dashFile;
    QFile *file;
public:
    DashCreator(const QString& path, const QString& name, TreeModel *mod);
    bool writeFile(const unsigned int & maxSampleNum);
    bool writeFiles(const unsigned int & maxSampleNum);
//public:
//    /*!
//      *\brief DashCreator manages stream to newly created dash file
//      *\param fn according to file with given fileName dash file is created
//      *\param model model of box tree
//     */
//    DashCreator(const QString& fn, TreeModel *model);
//    ~DashCreator();
//    /*!
//      *\brief closeFileStream closes filename file stream
//     */
//    void closeFileStream();
//    /*!
//      *\brief copyBox
//      *Copies first box (box of smallest offset) of given type in original file and writes it to the dash file.
//      *If dashFile is NULL method only returns size of potentially copied box.
//      *\param type type of the box
//      *\param dashFile
//      *\param maxSize maximum size of copied box
//      *\return number of copied bytes
//     */
    unsigned int copyBox(const QString& type, QFile *dashFile = NULL, const unsigned long int& maxSize = 0);
    /*!
      *\brief copyBox
      *Copies box of given type and parent in original file and writes it to the dash file.
      *If dashFile is NULL method only returns size of potentially copied box.
      *\param type type of the box
      *\param parent box parent of given box
      *\param dashFile
      *\param maxSize maxSize maximum size of copied box
      *\return number of copied bytes
     */
    unsigned int copyBox(const QString &type, std::shared_ptr<Box> parent, QFile *dashFile = NULL, const unsigned long &maxSize = 0);
    /*!
      *\brief mdatSize
      *\param firstSample number of size of meta data
      *\param sampleNumber number of samples of meta data
      *\param stsz Sample Size Box that defines samples size of meta data
      *\return size in bytes of sampleNumber samples from firstSample index
     */
    unsigned long int mdatSize(const unsigned long int& firstSample, const unsigned int& sampleNumber, SampleSizeBox *stsz);
    /*!
      *\brief writeAvc1
      *Writes avc1 box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written avc1 box
     */
    unsigned int writeAvc1(QFile *dashFile = NULL);
    /*!
      *\brief writeAvcC
      *Writes avcC box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written avcC box
     */
    unsigned int writeAvcC(QFile *dashFile = NULL);
    /*!
      *\brief writeBtrt
      *Writes btrt box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written btrt box
     */
    unsigned int writeBtrt(QFile *dashFile = NULL);
    /*!
      *\brief writeMinf
      *Writes minf box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param parent box parent of minf in original file
      *\return size in bytes of written minf box
     */
    unsigned int writeMinf(std::shared_ptr<Box> parent, QFile *dashFile = NULL);
    /*!
      *\brief writeFree
      *Writes free box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written free box
     */
    unsigned int writeFree(QFile *dashFile = NULL);
    /*!
      *\brief writeFtyp
      *Writes ftyp box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written ftyp box
     */
    unsigned int writeFtyp(QFile *dashFile = NULL);
    /*!
      *\brief writeMdat
      *Writes mdat box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param firstSample number of size of meta data
      *\param sampleNumber number of samples of meta data
      *\param stsz Sample Size Box that defines samples size of meta data
      *\param dashFile
      *\return size in bytes of written mdat box
     */
    unsigned int writeMdat(const unsigned long int& firstSample, const unsigned int& sampleNumber, SampleSizeBox *stsz,
                           QFile *dashFile = NULL);
    /*!
      *\brief writeMdhd
      *Writes mdhd box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param parent box parent of minf in original file
      *\return size in bytes of written mdhd box
     */
    unsigned int writeMdhd(std::shared_ptr<Box> parent, QFile *dashFile = NULL);
    /*!
      *\brief writeMdia
      *Writes mdia box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param parent box parent of mdia in original file
      *\return size in bytes of written minfavc1 box
     */
    unsigned int writeMdia(std::shared_ptr<Box> parent, QFile *dashFile = NULL);
    /*!
      *\brief writeMehd
      *Writes mehd box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written mehd box
     */
    unsigned int writeMehd(QFile *dashFile = NULL);
    /*!
      *\brief writeMfhd
      *Writes mfhd box with given sequence number and returns size of it.
      *If dashFile is NULL, method only returns size of potentially written box.
      *\param sequenceNumber
      *\param dashFile
      *\return size in bytes of written mfhd box
     */
    unsigned int writeMfhd(const unsigned long int& sequenceNumber, QFile *dashFile);
    /*!
      *\brief writeMoof
      *Writes moof with given parameters and returns size of it.
      *If dashFile is NULL, method only returns size of potentially written box.
      *\param sequenceNumber
      *\param trackID
      *\param baseMediaDecodeTime
      *\param trunFlag2
      *\param trunFlag3
      *\param sampleCount
      *\param firstSampleFlags
      *\param firstSample
      *\param stsz
      *\param dashFile
      *\return
     */
    unsigned int writeMoof(const unsigned long int& sequenceNumber, const unsigned int& trackID, const unsigned long &baseMediaDecodeTime,
                           const unsigned int& trunFlag2, const unsigned int& trunFlag3, const unsigned int& sampleCount,
                           const unsigned int& firstSampleFlags, const unsigned long int& firstSample, SampleSizeBox *stsz,
                           QFile *dashFile = NULL);
    /*!
      *\brief writeMoov
      *Writes moov box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written moov box
     */
    unsigned int writeMoov(QFile *dashFile = NULL);
    /*!
      *\brief writeMvex
      *Writes mvex box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written mvex box
     */
    unsigned int writeMvex(QFile *dashFile = NULL);
    /*!
      *\brief writeMvhd
      *Writes mvhd box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written mvhd box
     */
    unsigned int writeMvhd(QFile *dashFile = NULL);
    /*!
      *\brief writeSidx
      *Writes sidx with given parameters and returns size of it.
      *If dashFile is NULL, method only returns size of potentially written box.
      *\param version
      *\param referenceID
      *\param timescale
      *\param earliestPresentationTime
      *\param firstOffset
      *\param referenceCount
      *\param referenceType
      *\param referenceSize
      *\param subsegmentDuration
      *\param startsWithSAP
      *\param SAPType
      *\param SAPDeltaTime
      *\param dashFile
      *\return
     */
    unsigned int writeSidx(const unsigned short int& version, const unsigned int& referenceID, const unsigned int& timescale,
                           const unsigned long int& earliestPresentationTime, const unsigned long int& firstOffset,
                           const unsigned int &referenceCount, const QList<unsigned short> &referenceType,
                           const QList<unsigned long int>& referenceSize, const QList<unsigned long int>& subsegmentDuration,
                           const QList <unsigned short int>& startsWithSAP, const QList <unsigned short int>& SAPType,
                           const QList <unsigned long int>& SAPDeltaTime, QFile *dashFile = NULL);
    /*!
      *\brief writeTfdt
      *Writes tfdt with given baseMediaDecodeTime and returns size of it.
      *If dashFile is NULL, method only returns size of potentially written box.
      *\param baseMediaDecodeTime
      *\param dashFile
      *\return
     */
    unsigned int writeTfdt(const unsigned long &baseMediaDecodeTime, QFile *dashFile);
    /*!
      *\brief writeStbl
      *Writes stbl box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param minf box parent of stbl in original file
      *\return size in bytes of written stbl box
     */
    unsigned int writeStbl(std::shared_ptr<Box> minf, QFile *dashFile = NULL);
    /*!
      *\brief writeStsd
      *Writes stsd box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param stbl box parent of stsd in original file
      *\return size in bytes of written stsd box
     */
    unsigned int writeStsd(std::shared_ptr<Box> stbl, QFile *dashFile = NULL);
    /*!
      *\brief writeStsz
      *Writes stsz box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param stbl box parent of stsz in original file
      *\return size in bytes of written stsz box
     */
    unsigned int writeStsz(std::shared_ptr<Box> stbl, QFile *dashFile = NULL);
    //for stts, stco, stsc
    /*!
      *\brief writeStxx
      *Writes stts/stco/stsc box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *The method must not be used with other box types than stts, stco, stsc.
      *\param dashFile
      *\param stbl box parent of stts/stco/stsc in original file
      *\return size in bytes of written stts/stco/stsc box
     */
    unsigned int writeStxx(const QString &type, QFile *dashFile = NULL);
    /*!
      *\brief writeStyp
      *Writes styp box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written styp box
     */
    unsigned int writeStyp(QFile *dashFile = NULL);
    /*!
      *\brief writeTfhd
      *Writes tfhd with given track id and returns size of it.
      *If dashFile is NULL, method only returns size of potentially written box.
      *\param trackID
      *\param dashFile
      *\return
     */
    unsigned int writeTfhd(const unsigned int& trackID, QFile *dashFile = NULL);
    /*!
      *\brief writeTkhd
      *Writes tkhd box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param parent box parent of tkhd in original file
      *\return size in bytes of written minfavc1 box
     */
    unsigned int writeTkhd(std::shared_ptr<Box> parent, QFile *dashFile = NULL);
    /*!
      *\brief writeTraf
      *Writes traf with given parameters and returns size of it.
      *If dashFile is NULL, method only returns size of potentially written box.
      *\param trackID
      *\param baseMediaDecodeTime
      *\param trunFlag2
      *\param trunFlag3
      *\param sampleCount
      *\param dataOffset
      *\param firstSampleFlags
      *\param firstSample
      *\param stsz
      *\param dashFile
      *\return
     */
    unsigned int writeTraf(const unsigned int& trackID, const unsigned long &baseMediaDecodeTime, const unsigned int& trunFlag2,
                           const unsigned int& trunFlag3, const unsigned int& sampleCount, const signed int& dataOffset,
                           const unsigned int& firstSampleFlags, const unsigned long int& firstSample, SampleSizeBox *stsz,
                           QFile *dashFile = NULL);
    /*!
      *\brief writeTrack
      *Writes trak box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param trak Track Box according to what new trak is created
      *\param dashFile
      *\return size in bytes of written mvex box
     */
    unsigned int writeTrak(std::shared_ptr<Box> trak, QFile *dashFile = NULL);
    /*!
      *\brief writeTrun
      *Writes trun with given parameters and returns size of it.
      *If dashFile is NULL, method only returns size of potentially written box.
      *\param flag2
      *\param flag3
      *\param sampleCount
      *\param dataOffset
      *\param firstSampleFlags
      *\param firstSample
      *\param stsz
      *\param dashFile
      *\return
     */
    unsigned int writeTrun(const unsigned int& flag2, const unsigned int& flag3, const unsigned int& sampleCount,
                           const signed int& dataOffset, const unsigned int& firstSampleFlags, const unsigned long int& firstSample,
                           SampleSizeBox *stsz, QFile *dashFile = NULL);
    /*!
      *\brief writeTrex
      *Writes trex box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written trex box
     */
    unsigned int writeTrex(QFile *dashFile = NULL);
    /*!
      *\brief writeVmhd
      *Writes vmhd box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\param parent box parent of vmhd in original file
      *\return size in bytes of written minfavc1 box
     */
    unsigned int writeVmhd(std::shared_ptr<Box> parent, QFile *dashFile = NULL);
    /*!
      *\brief writeSegments
      *Writes segments including all apropiate boxes (like sidx, moof, mdat).
      *\param maxSampleNum maximum number of samples in one mdat
      *\param dashFile
     */
    bool writeSegments(const unsigned int &maxSampleNum, QFile *dashFile, const QString& path = QString(""),
                       const QString& fileName = QString(""));
//    /*!
//      *\brief writeFile
//      *Writes dash file
//      *\param maxSampleNum maximum number of samples in one mdat
//      *\return true, if file was succesfully written
//     */
//    bool writeFile(const QString &date, const QString &fileName, const unsigned int & maxSampleNum);
//    /*!
//      *\brief writeFiles
//      *Writes dash files - each segment has its own file
//      *\param maxSampleNum maximum number of samples in one mdat
//      *\return true, if all files were managed to be written
//     */
//    bool writeFiles(const QString &date, const QString& dashFile, const unsigned int & maxSampleNum);


//private:
//    /*!
//      *\brief fileName name of the mp4 file that is transformed into dash mp4 file
//     */
//    QString fileName;
//    QString date;
//    /*!
//      *\brief model model of boxes mp4 file
//     */
//    TreeModel *model;
//    /*!
//      *\brief file mp4 file that is transformed into dash mp4 file
//     */
//    QFile *file;
//    QFile *dashFile;
//    QFile *initFile;
};

#endif // DASHCREATOR_H
