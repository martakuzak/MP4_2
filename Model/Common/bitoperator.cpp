#include "bitoperator.h"

BitOperator::BitOperator() {}

BitOperator::~BitOperator() {
}

unsigned long BitOperator::valueOfGroupOfBytes(QFile* file, const int &length, const unsigned long &offset)
{
    /*if (!file->open(QIODevice::ReadOnly)) {
        return 0;
    }*/

    QByteArray array;
    unsigned long int num = 0;
    file->seek(offset);
    array = file->read(length);
    for(int i = 0; i< length; ++i) {
        num |= static_cast<unsigned int>(array[i]) & 0xFF; //suma bit po bicie
        if(0!=length && i!=(length-1)) {
            num=(num<<8); //przesuniecie o 8 bitow w lewo
        }
    }
    return num;
}

signed long BitOperator::signedValueOfGroupOfBytes(QFile *file, const int &length, const unsigned long &offset)
{
    if (!file->open(QIODevice::ReadOnly)) {
        return 0;
    }

}

unsigned long BitOperator::valueOfGroupOfBits(QFile *file, const int &length, const unsigned long &offset)
{
    if (!file->open(QIODevice::ReadOnly)) {
        return 0;
    }
}

QString BitOperator::qstringValue(QFile *file, const unsigned int &length, const unsigned int &offset)
{
    if (!file->open(QIODevice::ReadOnly)) {
        return 0;
    }
}
