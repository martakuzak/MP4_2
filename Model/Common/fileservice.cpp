#include "fileservice.h"

FileService::FileService(QString name){
    file = new QFile(name);
}


FileService::~FileService(){
    delete file;
}

char* FileService::getBytes(unsigned long offset, unsigned int length) const {
    qDebug()<<"getByte"<<offset<<length;
    QByteArray array;
    file->seek(offset);
    array = file->read(length);
    qDebug()<<"getBytes"<<array.data();
    return array.data();
}

char* FileService::getBits(unsigned long offset, unsigned int length) const {
    int firstByteIdx = offset/8;
    int lastByteIdx = (offset + length)/8;

    char* byteData = this->getBytes(firstByteIdx, lastByteIdx - firstByteIdx);

    qDebug()<<"getBits"<<byteData;
    return byteData;
}

