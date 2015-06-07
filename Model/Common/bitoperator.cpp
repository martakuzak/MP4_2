#include "bitoperator.h"

BitOperator::BitOperator() {}

BitOperator::~BitOperator() {
}

unsigned long BitOperator::valueOfGroupOfBytes(QFile* file, const int &length, const unsigned long &offset) {
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

signed long BitOperator::signedValueOfGroupOfBytes(QFile *file, const int &length, const unsigned long &offset) {
    QByteArray array;
    signed long int num = 0;
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

unsigned long BitOperator::valueOfGroupOfBits(QFile *file, const int &length, const unsigned long &offset) {
    int firstByteNum = offset/8;
    int lastByteNum = (offset + length)/8;

    //unsigned long int byteValue = this->valueOfGroupOfBytes(lastByteNum - firstByteNum + 1, firstByteNum);
    BitOperator* bitOperator = new BitOperator();
    unsigned long int byteValue = bitOperator->valueOfGroupOfBytes(file, lastByteNum - firstByteNum + 1, firstByteNum);
    //koniec zmian

    int suffix = 8 - (offset + length)%8;

    unsigned long int bitValue = 0;
    int pattern = 0;

    for(int i = 0; i < length; ++i) { //utworzenie wzoru: liczby, ktora w reprezentacji binarnej ma jedynki tam, ktory fragment mamy wyciac
        //i zera w pozostalych przypadkach: wygenerowanie ciagu 1
        pattern |= 1;
        pattern = pattern << 1;
    }
    for(int i = 0; i < suffix; ++i) {//dodanie odpowiedniej ilosci zer
        pattern |= 0;
        if (!(i== suffix - 1))
            pattern = pattern << 1;
    }

    bitValue = (byteValue & pattern) >> suffix; //iloczyn logiczny bit po bicie i przesuniecie bitowe w prawo

    return bitValue;
}

QString BitOperator::qstringValue(QFile *file, const unsigned int &length, const unsigned int &offset) {
    QByteArray array;
    file->seek(offset);
    array = file->read(length);
    return QString(array);
}

unsigned long int BitOperator::unsignedExpGolomb(QFile *file, const unsigned long int& offset, int *resLength) {
    QByteArray array;
    int leadingZeroNum = 0;
    int i = 0;
    while(!valueOfGroupOfBits(file, 1, offset + i)) {
        ++ leadingZeroNum;
        ++ i;
    }
    qDebug()<<"GOLOMB zeros : "<<leadingZeroNum;
    resLength[0] = leadingZeroNum*2 + 1;
    return valueOfGroupOfBits(file, leadingZeroNum + 1, offset + i) - 1;

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
