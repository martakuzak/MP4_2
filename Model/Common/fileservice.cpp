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
    char* bitData = new char(length);
    int firstByteIdx = offset/8;
    int lastByteIdx = (length) ? (offset + length - 1)/8 : firstByteIdx;
    int byteLength = lastByteIdx - firstByteIdx + 1;

    char* byteData = new char[byteLength];
    byteData = this->getBytes(firstByteIdx, byteLength);

    int prefix = offset%8;
    int suffix = 8 - (offset + length)%9; // ???? PRZEMYSLEC


    //przekopiowanie bitow z pierwszego byte'u
    memcpy(bitData, toBitArray(byteData[0], prefix, (byteLength > 1) ? 0 : suffix), 9);

    //dolaczenie bitow z kolejnych byte'ów oprocz ostatniego
    for(int byteIdx = 1; byteIdx < (byteLength - 1); ++ byteIdx)
        memmove(bitData + 8*byteIdx - prefix, toBitArray(byteData[byteIdx]), 8);

    //dolaczenie bitow z ostatniego byte'u
    if(byteLength > 1)
        memmove(bitData + length - 8 + suffix - 1, toBitArray(byteData[byteLength - 1]), 8 - suffix + 1);

    return bitData;
}

char* FileService::toBitArray(char byte, int prefix, int suffix) {
    int length = 8 - prefix - suffix;
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

