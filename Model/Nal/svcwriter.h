#ifndef SVCWRITER_H
#define SVCWRITER_H
#include <QFile>
#include <QDataStream>

class SvcWriter {
public:
    SvcWriter(const QString& name);
protected:
    //name of analyzed file
    QString fileName;
    QFile *file;
    const int MVHD_SIZE_0 = 108; //version = 0
    const int MVHD_SIZE_1 = 120; //version = 1
public:
    bool writeFile(const QString& name);
protected:
    /*!
      *\brief writeFtyp
      *Writes ftyp box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written ftyp box
     */
    void writeFtyp();
    void writeMoov();
    unsigned int writeMvhd(bool write);
    unsigned int writeTrak(bool write);
    unsigned int writeTkhd(bool write);
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
