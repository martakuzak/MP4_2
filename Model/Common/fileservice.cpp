#include "fileservice.h"

FileService::FileService(QString name){
    file = new QFile(name);
}


FileService::~FileService(){
    delete file;
}

char* FileService::getBytes(unsigned long offset, unsigned int length) const {
    QByteArray array;
    file->seek(offset);
    array = file->read(length);
    return array.data();
}

char* FileService::getBits(unsigned long offset, unsigned int length)  {
    qDebug()<<"offset:"<<offset<<"length:"<<length;
    if(!length)
        return NULL;
    char* bitData = new char(length);
    int firstByteIdx = offset/BITS_IN_BYTE;
    int lastByteIdx = (offset + length - 1)/BITS_IN_BYTE;
    int byteLength = lastByteIdx - firstByteIdx + 1;

    char* byteData = new char[byteLength];
    memcpy(byteData, this->getBytes(firstByteIdx, byteLength), byteLength);

    int prefix = offset % BITS_IN_BYTE;
    int suffix = - (offset + length) + byteLength* BITS_IN_BYTE;
    qDebug()<<"prefix:"<<prefix<<"suffix:"<<suffix;

    //przekopiowanie bitow z pierwszego byte'u
    qDebug()<<"byte 0, prefix:"<<prefix<<"suffix:"<<((byteLength > 1) ? 0 : suffix)<<"dlugosc:"<<(BITS_IN_BYTE - prefix);
    memcpy(bitData, toBitArray(byteData[0], prefix, (byteLength > 1) ? 0 : suffix), BITS_IN_BYTE - prefix);

    //dolaczenie bitow z kolejnych byte'ów oprocz ostatniego
    for(int byteIdx = 1; byteIdx < (byteLength - 1); ++ byteIdx) {
        qDebug()<<"kolejny byte nr"<<byteIdx<<"przesuniecie:"<<(BITS_IN_BYTE*byteIdx - prefix)<<"dlugosc:"<<BITS_IN_BYTE;
        memmove(bitData + BITS_IN_BYTE*byteIdx - prefix, toBitArray(byteData[byteIdx]), BITS_IN_BYTE);
    }

    //dolaczenie bitow z ostatniego byte'u
    if(byteLength > 1) {
        int przesuniecie = length - BITS_IN_BYTE + suffix;
        qDebug()<<"ostatni byte, przesuniecie:"<<przesuniecie<<"dlugosc:"<<(BITS_IN_BYTE - suffix);
        memmove(bitData + length - BITS_IN_BYTE + suffix, toBitArray(byteData[byteLength - 1]), BITS_IN_BYTE - suffix);
    }

    return bitData;
}

char* FileService::toBitArray(char byte, int prefix, int suffix) {
    int length = BITS_IN_BYTE - prefix - suffix;
    char* bitData = new char(length);

    int bitIdx = length - 1;

    byte = byte >> suffix;
    for(int i = length - 1; i >= 0; -- i) {
        char tmp = byte - ((byte >> 1) << 1 );
        bitData[bitIdx --] = tmp;
        byte = byte >> 1;
    }
    return bitData;
}

