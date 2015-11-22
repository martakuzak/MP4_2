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
public:
    bool writeFile(const QString& name);
protected:
    /*!
      *\brief writeFtyp
      *Writes ftyp box and returns size of it. If dashFile is NULL, method only returns size of potentially written box.
      *\param dashFile
      *\return size in bytes of written ftyp box
     */
    unsigned int writeFtyp();
    unsigned int writeMdat();
    unsigned int writeMoov();
    unsigned int writeMvhd();
    unsigned int writeTkhd();
    unsigned int writeMdia();
    unsigned int writeMdhd();
    unsigned int writeHdlr();
    unsigned int writeMinf();

signals:

public slots:
};

#endif // SVCWRITER_H
