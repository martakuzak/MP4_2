#ifndef DASHCREATOR_H
#define DASHCREATOR_H

#include <QFile>
#include <QByteArray>
#include <QString>
#include "treemodel.h"

class TreeModel;

class DashCreator
{
public:
    /*!
     * \brief DashCreator manages stream to newly created dash file
     * \param fileName according to file with given fileName dash file is created
     * \param model model of box tree
     */
    DashCreator(const QString& fileName, TreeModel* model);
    /*!
     * \brief closeFileStream closes filename file stream
     */
    void closeFileStream();
    /*!
     * \brief mdatSize
     * \param firstSample
     * \param sampleNumber
     * \param stsz
     * \return
     */
    unsigned int copyBox(const QString& type, QFile *dashFile = NULL, const unsigned long int& maxSize = 0);
    unsigned int copyBox(const QString &type, std::shared_ptr<Box> parent, QFile *dashFile = NULL, const unsigned long &maxSize = 0);
    unsigned long int mdatSize(const unsigned long int& firstSample, const unsigned int& sampleNumber, std::shared_ptr<Box>& stsz);
    unsigned int writeAvc1(QFile* dashFile = NULL);
    unsigned int writeAvcC(QFile* dashFile = NULL);
    unsigned int writeBtrt(QFile* dashFile = NULL);
    unsigned int writeMinf(std::shared_ptr<Box> parent, QFile* dashFile = NULL);
    unsigned int writeFree(QFile* dashFile = NULL);
    unsigned int writeFtyp(QFile* dashFile = NULL);
    unsigned int writeMdat(const unsigned long int& firstSample, const unsigned int& sampleNumber, std::shared_ptr<Box>& stsz,
                           QFile* dashFile = NULL);
    unsigned int writeMdhd(std::shared_ptr<Box> parent, QFile* dashFile = NULL);
    unsigned int writeMdia(std::shared_ptr<Box> parent, QFile* dashFile = NULL);
    unsigned int writeMehd(QFile* dashFile = NULL);
    unsigned int writeMfhd(const unsigned long int& sequenceNumber, QFile* dashFile);
    unsigned int writeMoof(const unsigned long int& sequenceNumber, const unsigned int& trackID, const unsigned long &baseMediaDecodeTime,
                           const unsigned int& trunFlag2,const unsigned int& trunFlag3, const unsigned int& sampleCount,
                           const signed int& dataOffset,const unsigned int& firstSampleFlags, const unsigned long int& firstSample,
                           std::shared_ptr<Box>& stsz, QFile* dashFile = NULL);
    unsigned int writeMoov(QFile* dashFile = NULL);
    unsigned int writeMvex(QFile* dashFile = NULL);
    unsigned int writeMvhd(QFile* dashFile = NULL);
    unsigned int writeSidx(const unsigned short int& version, const unsigned int& referenceID, const unsigned int& timescale,
                           const unsigned long int& earliestPresentationTime, const unsigned long int& firstOffset,
                           const unsigned int &referenceCount, const QList<unsigned short> &referenceType,
                           const QList<unsigned long int>& referenceSize, const QList<unsigned long int>& subsegmentDuration,
                           const QList <unsigned short int>& startsWithSAP, const QList <unsigned short int>& SAPType,
                           const QList <unsigned long int>& SAPDeltaTime, QFile* dashFile = NULL);unsigned int writeTfdt(const unsigned long &baseMediaDecodeTime, QFile* dashFile);
    unsigned int writeStbl(QFile* dashFile = NULL);
    unsigned int writeStsd(QFile* dashFile = NULL);
    unsigned int writeStsz(QFile* dashFile = NULL);
    //for stts, stco, stsc
    unsigned int writeStxx(const QString &type, QFile* dashFile = NULL);
    unsigned int writeTfhd(const unsigned int& trackID, QFile* dashFile = NULL);
    unsigned int writeTkhd(std::shared_ptr<Box> parent, QFile* dashFile = NULL);
    unsigned int writeTraf(const unsigned int& trackID, const unsigned long &baseMediaDecodeTime, const unsigned int& trunFlag2,
                           const unsigned int& trunFlag3, const unsigned int& sampleCount, const signed int& dataOffset,
                           const unsigned int& firstSampleFlags, const unsigned long int& firstSample, std::shared_ptr<Box>& stsz,
                           QFile* dashFile = NULL);
    unsigned int writeTrak(std::shared_ptr<Box> trak, QFile* dashFile = NULL);
    unsigned int writeTrun(const unsigned int& flag2, const unsigned int& flag3, const unsigned int& sampleCount,
                           const signed int& dataOffset, const unsigned int& firstSampleFlags, const unsigned long int& firstSample,
                           std::shared_ptr<Box>& stsz, QFile* dashFile = NULL);
    unsigned int writeTrex(QFile* dashFile = NULL);
    unsigned int writeVmhd(std::shared_ptr<Box> parent, QFile* dashFile = NULL);

    void writeSegments(const unsigned int &maxSampleNum, QFile* dashFile = NULL);
    void writeFile(const unsigned int & maxSampleNum, QFile* dashFile = NULL);


private:
    QString fileName;
    TreeModel* model;
    QFile* file;
};

#endif // DASHCREATOR_H
