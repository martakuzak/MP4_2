#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <cstring>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDebug>

class FileService {
public:
    FileService(const QString &name);
    ~FileService();

    bool openFile(QIODevice::OpenMode openMode = QIODevice::ReadOnly) {
        if(file == NULL)
            qDebug()<<"FILESERVICE: openFile file is null";
        bool tmp = file->open(openMode);
        qDebug()<<"FILESERVICE: openFile file open? : "<<tmp;
        return tmp;
    }
    qint64 getSize() { return file->size(); }
    void close() { file->close(); }
    //offset i number w byte'ach
    char* getBytes(unsigned int length, unsigned long offset);
    //offset i number w bitach
    char* getBits(unsigned int length, unsigned long offset);
protected:
    char* toBitArray(char byte, int prefix = 0, int suffix = 0);
    QFile* file;
    const int BITS_IN_BYTE = 8;
};

#endif // FILESERVICE_H
