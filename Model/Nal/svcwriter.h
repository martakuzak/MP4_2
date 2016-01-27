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
#include "nalunitsbo.h"

class NalUnit;

class SvcWriter {
protected:
    //name of analyzed file
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
    QFile* outputFile;
    NalUnitsBO* nalUnitsBO;
public:
    SvcWriter(NalUnitsBO* nalInfo);
    bool writeMP4File(const QString& name);
    bool writeBaseLayer(const QString &name);
protected:
    //short calculateBytesNumOfNalLenPar();
    void writeNAL(std::shared_ptr<NalUnit> nalUnit, QFile *file, unsigned short length, bool size = true);
    /*!
      *\brief writeFtyp
      *Writes ftyp box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written ftyp box
     */
    void writeFtyp();
    void writeMoov(int layerNum);
    unsigned int writeMvhd(bool write, int trackNum);
    unsigned int writeTrak(bool write, int trackID);
    unsigned int writeTkhd(bool write, int trackID);
    unsigned int writeMdia(bool write);
    unsigned int writeMdhd(bool write);
    unsigned int writeHdlr(bool write);
    unsigned int writeMinf(bool write);
    unsigned int writeVmhd(bool write);
    unsigned int writeDinf(bool write);
    unsigned int writeDref(bool write);
    unsigned int writeStbl(bool write);
    unsigned int writeStsd(bool write);
    unsigned int writeStts(bool write);
    unsigned int writeCtts(bool write);
    unsigned int writeStsc(bool write);
    unsigned int writeStsz(bool write); //stz2?
    unsigned int writeStco(bool write);
    unsigned int writeStss(bool write);
    unsigned int writeAvc1(bool write);
    unsigned int writeAvcC(bool write);
    void writeMdat();
    unsigned int getTimeSince1904();
};

#endif // SVCWRITER_H
