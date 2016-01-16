#ifndef SVCWRITER_H
#define SVCWRITER_H
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QList>
#include <QDateTime>
#include <memory>
#include "nalunit.h"
#include "nalunittype.h"

class NalUnit;

class SvcWriter {
public:
    SvcWriter(const QList<std::shared_ptr<NalUnit> >& nu);
protected:
    //name of analyzed file
    QString fileName;
    QFile *file;
    QList<std::shared_ptr<NalUnit> > nalUnits;
    const int MDHD_SIZE_0 = 32; //version = 0
    const int MDHD_SIZE_1 = 44; //version = 1
    const int MVHD_SIZE_0 = 108; //version = 0
    const int MVHD_SIZE_1 = 120; //version = 1
    const int TKHD_SIZE_0 = 92; //version = 0
    const int TKHD_SIZE_1 = 114; //version = 1
    const unsigned long SEC_1904_1970 = 7171200; //time between 00:00:00 01.01.1904 and 00:00:00 01.01.1970
    const char* UND_LAN_CODE = "und";
    const char* VIDE_TRACK = "vide";
    const char* VIDEO_HANDLER = "VideoHandler";
public:
    bool writeMP4File(const QString& name);
    bool writeBaseLayer(const QString &name, const QString &svcFile);
protected:
    short calculateBytesNumOfNalLenPar();
    /*!
      *\brief writeFtyp
      *Writes ftyp box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written ftyp box
     */
    void writeFtyp(QFile* outputFile);
    void writeMoov(QFile* outputFile, int layerNum);
    unsigned int writeMvhd(QFile* outputFile, bool write, int trackNum);
    unsigned int writeTrak(QFile* outputFile, bool write, int trackID);
    unsigned int writeTkhd(QFile* outputFile, bool write, int trackID);
    unsigned int writeMdia(QFile* outputFile, bool write);
    unsigned int writeMdhd(QFile* outputFile, bool write);
    unsigned int writeHdlr(QFile* outputFile, bool write);
    unsigned int writeMinf(QFile* outputFile, bool write);
    unsigned int writeVmhd(QFile* outputFile, bool write);
    unsigned int writeDinf(QFile* outputFile, bool write);
    unsigned int writeDref(QFile* outputFile, bool write);
    unsigned int writeStbl(QFile* outputFile, bool write);
    unsigned int writeStsd(QFile* outputFile, bool write);
    unsigned int writeStts(QFile* outputFile, bool write);
    unsigned int writeCtts(QFile* outputFile, bool write);
    unsigned int writeStsc(QFile* outputFile, bool write);
    unsigned int writeStsz(QFile* outputFile, bool write); //stz2?
    unsigned int writeStco(QFile* outputFile, bool write);
    unsigned int writeStss(QFile* outputFile, bool write);
    void writeMdat(QFile* outputFile);
    unsigned int getTimeSince1904();

signals:

public slots:
};

#endif // SVCWRITER_H
