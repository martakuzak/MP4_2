#include "bitoperator.h"

BitOperator::BitOperator() {}

BitOperator::~BitOperator() {
}

unsigned long BitOperator::valueOfGroupOfBytes(const unsigned int array[], const unsigned int & length) const {
    unsigned long int num = 0;
    for (int i = 0; i < length; ++ i) {
        num |= array[i] & 0xFF; //suma bit po bicie
        qDebug()<<"num przed if"<<num<<i;
        if(0 != length && i != (length - 1))
            num = (num << 8); //przesuniecie o 8 bitow w lewo
        qDebug()<<"num po if"<<num<<i;
    }
    return num;
}

signed long BitOperator::signedValueOfGroupOfBytes(const unsigned int array[], const unsigned int &length) const{
    signed long num = 0;
    for(int i = 0; i< length; ++i) {
        num |= array[i] & 0xFF; //suma bit po bicie
        if(0 != length && i != (length-1)) {
            num = (num << 8); //przesuniecie o 8 bitow w lewo
        }
    }
    return num;
}

unsigned long BitOperator::valueOfGroupOfBits(const bool array[], const unsigned int &length) const {
    unsigned long num = 0;

    for(int i = 0; i < length; ++ i) {
        num |= array[i] & 0xFF; //suma bit po bicie
        if(0 != length && i != (length-1)) {
            num = (num << 1); //przesuniecie o 8 bitow w lewo
        }
    }

    return num;
}

QString BitOperator::qstringValue(const char entry[], const unsigned int &length) const {
    QByteArray array(entry, length);
    return QString(array);
}

//DO WYWALENIA

unsigned long int BitOperator::unsignedExpGolomb(QFile *file, const unsigned long int& offset, int *resLength) const {
    QByteArray array;
    int leadingZeroNum = 0;
    int i = 0;
    while(0/*!valueOfGroupOfBits(file, 1, offset + i)*/) {
        ++ leadingZeroNum;
        ++ i;
    }
    //qDebug()<<"GOLOMB zeros : "<<leadingZeroNum;
    resLength[0] = leadingZeroNum*2 + 1;
    return 0; //valueOfGroupOfBits(file, leadingZeroNum + 1, offset + i) - 1;

    /*unsigned long int num = 0;
    file->seek(offset);
    array = file->read(length);
    for(int i = 0; i< length; ++i) {
        num |= static_cast<unsigned int>(array[i]) & 0xFF; //suma bit po bicie
        if(0!=length && i!=(length-1)) {
            num=(num<<8); //przesuniecie o 8 bitow w lewo
        }
    }*/
    //return num;
}
