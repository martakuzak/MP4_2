#include "fileservice.h"

FileService::FileService(QString name){
    file = new QFile(name);
}


FileService::~FileService(){
    delete file;
}

char* FileService::getBytes(unsigned long offset, unsigned int length) const {
    //qDebug()<<"getByte"<<offset<<length;
    QByteArray array;
    file->seek(offset);
    array = file->read(length);
    //qDebug()<<"getBytes"<<array.data();
    char* tmp = array.data();
    //qDebug()<<QString(tmp[0])<<tmp[1];
    return array.data();
}

char* FileService::getBits(unsigned long offset, unsigned int length)  {
    char* bitData = new char(length);
    int firstByteIdx = offset/8;
    int lastByteIdx = (offset + length)/8;
    int byteLength = lastByteIdx - firstByteIdx;
    qDebug()<<"getBits"<<firstByteIdx<<lastByteIdx<<byteLength;

    char* byteData = this->getBytes(firstByteIdx, byteLength);

    int prefix = offset%8;
    int suffix = 8 - (offset + length)%9; // ???? PRZEMYSLEC

    char byte = byteData[0];
    qDebug()<<"getbits"<<(int)byte;
    //przekopiowanie bitow z pierwszego byte'u
    strcpy(bitData, toBitArray(byte, prefix, (byteLength > 1) ? 0 : suffix));

    //dolaczenie bitow z kolejnych byte'ów oprocz ostatniego
    for(int byteIdx = 1; byteIdx < (byteLength - 1); ++ byteIdx)
        strcat(bitData, toBitArray(byteData[byteIdx]));

    //dolaczenie bitow z ostatniego byte'u
    if(byteLength > 1)
        strcat(bitData, toBitArray(byteData[length - 1], 0, suffix));

    return bitData;
}

char* FileService::toBitArray(char byte, int prefix, int suffix) {
    qDebug()<<"toBitArray"<<(int)byte<<prefix<<suffix;
    int length = 8 - prefix - suffix;
    char* bitData = new char(length);

    int bitIdx = length;

    byte = byte >> suffix;
    qDebug()<<"pierwszy byte"<<(int)byte;
    for(int i = 7 - suffix; i >= prefix; -- i) {
        char tmp = byte - ((byte >> 1) << 1 );
        qDebug()<<"alala"<<(int)tmp;
        bitData[bitIdx --] = tmp;
        byte = byte >> 1;
    }

    return bitData;
}

