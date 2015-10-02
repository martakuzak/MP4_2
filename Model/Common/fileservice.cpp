#include "fileservice.h"

FileService::FileService(const QString &name) {
    qDebug()<<"FILESERVICE: constructor"<<name;
    file = new QFile(name);
}

FileService::~FileService(){
    qDebug()<<"FILESERVICE: destructor";
    delete file;
}

char* FileService::getBytes(unsigned int length, unsigned long offset) {
    QByteArray array;
    if(offset + length > file->size()) {
        qDebug()<<"FILESERVICE: getBytes NULL offset = "<<offset<<"length ="<<length<<"filesize = "<<file->size();
        return NULL;
    }
    file->seek(offset);
    array = file->read(length);
    return array.data();
}

char* FileService::getBits(unsigned int length, unsigned long offset) {
    qDebug()<<"FILESERVICE: getBits";
    if(!length || offset + length > (8*file->size())) {
        qDebug()<<"FILESERVICE: getBits NULL"<<length<<(offset + length)<<file->size();
        return NULL;
    }
    qDebug()<<"FILESERVICE: getBits po ifie";
    char* bitData = new char(length);
    int firstByteIdx = offset/BITS_IN_BYTE;
    int lastByteIdx = (offset + length - 1)/BITS_IN_BYTE;
    int byteLength = lastByteIdx - firstByteIdx + 1;

    char* byteData = new char[byteLength];
    qDebug()<<"FILESERVICE: getBits 1"<<firstByteIdx<<lastByteIdx<<byteLength;

    memcpy(byteData, this->getBytes(byteLength, firstByteIdx), byteLength);

    int prefix = offset % BITS_IN_BYTE;
    int suffix =(byteLength + firstByteIdx)* BITS_IN_BYTE  - (offset + length) ;

    //przekopiowanie bitow z pierwszego byte'u
    memcpy(bitData, toBitArray(byteData[0], prefix, (byteLength > 1) ? 0 : suffix), BITS_IN_BYTE - prefix);

    //dolaczenie bitow z kolejnych byte'ów oprocz ostatniego
    for(int byteIdx = 1; byteIdx < (byteLength - 1); ++ byteIdx)
        memmove(bitData + BITS_IN_BYTE*byteIdx - prefix, toBitArray(byteData[byteIdx]), BITS_IN_BYTE);

    //dolaczenie bitow z ostatniego byte'u
    if(byteLength > 1)
        memmove(bitData + length - BITS_IN_BYTE + suffix, toBitArray(byteData[byteLength - 1]), BITS_IN_BYTE - suffix);

    delete byteData;

    qDebug()<<"FILESERVICE: getBits end";
    return bitData;
}

char* FileService::toBitArray(char byte, int prefix, int suffix) {
    int length = BITS_IN_BYTE - prefix - suffix;
    char* bitData = new char(length);

    byte = byte >> suffix;
    for(int i = length - 1; i >= 0; -- i) {
        bitData[i] = byte - ((byte >> 1) << 1 );
        byte = byte >> 1;
    }
    return bitData;
}
