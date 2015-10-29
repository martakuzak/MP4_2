#include "fileservice.h"

FileService::FileService(const QString &name) {
    file = new QFile(name);
}

FileService::~FileService(){
    delete file;
}

void FileService::getBytes(char *dst, unsigned int length, unsigned long offset) {
    QByteArray array;
    if(offset + length > file->size())
        dst = NULL;
    file->seek(offset);
    array = file->read(length);
    memmove(dst, array.data(), length);
}

void FileService::getBits(char *dst, unsigned int length, unsigned long offset) {
    //qDebug()<<"FILESERVICE: getBits 1"<<length<<offset;
    if(!length || offset + length > (8*file->size()))
        dst = NULL;
    int firstByteIdx = offset/BITS_IN_BYTE;
    int lastByteIdx = (offset + length - 1)/BITS_IN_BYTE;
    int byteLength = lastByteIdx - firstByteIdx + 1;
    char* byteData = new char[byteLength];
    this->getBytes(byteData, byteLength, firstByteIdx);
    if(byteData == NULL) {
        dst = NULL;
        return;
    }
    //memmove(byteData, this->getBytes(byteLength, firstByteIdx), byteLength);

    int prefix = offset % BITS_IN_BYTE;
    int suffix =(byteLength + firstByteIdx)* BITS_IN_BYTE  - (offset + length) ;

    //przekopiowanie bitow z pierwszego byte'u
    char* bitArray = new char[BITS_IN_BYTE - prefix];
    toBitArray(bitArray, byteData[0], BITS_IN_BYTE - prefix, /*prefix,*/ (byteLength > 1) ? 0 : suffix);
    //memmove(dst, toBitArray(byteData[0], prefix, (byteLength > 1) ? 0 : suffix), BITS_IN_BYTE - prefix);
    delete[] bitArray;

    //dolaczenie bitow z kolejnych byte'ów oprocz ostatniego
    for(int byteIdx = 1; byteIdx < (byteLength - 1); ++ byteIdx) {
        char* bitArray = new char[BITS_IN_BYTE];
        toBitArray(bitArray, byteData[byteIdx], BITS_IN_BYTE);
        memmove(dst + BITS_IN_BYTE*byteIdx - prefix, bitArray, BITS_IN_BYTE);
        delete[] bitArray;
    }

    //dolaczenie bitow z ostatniego byte'u
    if(byteLength > 1) {
        char* bitArray = new char[BITS_IN_BYTE - suffix];
        toBitArray(bitArray, byteData[byteLength - 1], BITS_IN_BYTE - suffix);
        memmove(dst + length - BITS_IN_BYTE + suffix, bitArray, BITS_IN_BYTE - suffix);
        delete[] bitArray;
    }

    delete[] byteData;
    //qDebug()<<"FILESERVICE: getBits 2";

    //return dst;
}

void FileService::toBitArray(char *dst, char byte, int length, /*int prefix,*/ int suffix) {
    //int length = BITS_IN_BYTE - prefix - suffix; - to trzeba podać!
    //char* bitData = new char(length);

    byte = byte >> suffix;
    for(int i = length - 1; i >= 0; -- i) {
        //bitData[i] = byte - ((byte >> 1) << 1 );
        dst[i] = byte - ((byte >> 1) << 1 );
        byte = byte >> 1;
    }
    //return dst;
}
