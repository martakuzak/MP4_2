#ifndef SVCWRITER_H
#define SVCWRITER_H
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QList>
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
    void writeMdat();

signals:

public slots:
};

#endif // SVCWRITER_H
