#include "fileservice.h"

FileService::FileService(const QString &name) {
    file = new QFile(name);
}

FileService::~FileService(){
    delete file;
}

void FileService::getBytes(char *dst, unsigned int length, unsigned long offset) {
    QByteArray array;
    if(offset + length > file->size()) {
        dst = NULL;
        return;
    }
    file->seek(offset);
    array = file->read(length);
    memmove(dst, array.data(), length);
}

void FileService::getBits(char *dst, unsigned int length, unsigned long offset) {
    if(!length || offset + length > (8*file->size())) {
        dst = NULL;
        return;
    }
    int firstByteIdx = offset/BITS_IN_BYTE;
    int lastByteIdx = (offset + length - 1)/BITS_IN_BYTE;
    int byteLength = lastByteIdx - firstByteIdx + 1;
    char* byteData = new char[byteLength];
    this->getBytes(byteData, byteLength, firstByteIdx);
    if(byteData == NULL) {
        dst = NULL;
        return;
    }
    int prefix = offset % BITS_IN_BYTE;
    int suffix =(byteLength + firstByteIdx)* BITS_IN_BYTE  - (offset + length) ;

    //przekopiowanie bitow z pierwszego byte'u
    toBitArray(dst, byteData[0], (byteLength > 1) ? (BITS_IN_BYTE - prefix) : (BITS_IN_BYTE - prefix - suffix), /*prefix,*/ (byteLength > 1) ? 0 : suffix);

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
}

void FileService::toBitArray(char *dst, char byte, int length, int suffix) {//TO-DO co z tym prefixem??
    byte = byte >> suffix;
    for(int i = length - 1; i >= 0; -- i) {
        dst[i] = byte - ((byte >> 1) << 1 );
        byte = byte >> 1;
    }
}
