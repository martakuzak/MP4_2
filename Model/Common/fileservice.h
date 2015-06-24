#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <cstring>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDebug>

class FileService {
public:
    FileService(QString name);
    ~FileService();

    bool openFile(QIODevice::OpenMode openMode = QIODevice::ReadOnly) { return file->open(openMode); }
    qint64 getSize() { return file->size(); }
    void close() { file->close(); }
    //offset i number w byte'ach
    char* getBytes(unsigned long offset, unsigned int length);
    //offset i number w bitach
    char* getBits(unsigned long offset, unsigned int length);
protected:
    char* toBitArray(char byte, int prefix = 0, int suffix = 0);
    QFile* file;
    const int BITS_IN_BYTE = 8;
};

#endif // FILESERVICE_H
