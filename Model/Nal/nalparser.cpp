#include "nalparser.h"

NALParser::NALParser() {

}

NALParser::NALParser(const QString &fileName) {
    this->fileName=fileName;
    this->fileSize = 0;
    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        return ;
    }
    fileSize = file->size();
    bitOperator = new BitOperator();
}

NALParser::~NALParser() {

}

void NALParser::parseFile() {
    //QByteArray byteArray;
    unsigned long int offset= 0;//offset w pliku

    int* tab = new int[116];

    for(int i = 0; i < 116; ++i)
        tab[i] = 0;

    while(offset < fileSize) {

        unsigned int pref3Byte = bitOperator->valueOfGroupOfBytes(file, 3, offset);
        unsigned int pref4Byte = bitOperator->valueOfGroupOfBytes(file, 4, offset);


        if(pref3Byte == 1 || pref4Byte == 1) {
            offset += (pref3Byte == 1) ? 3 : 4;
            //forbidden_zero_bit
            short int forbiddenZeroBit = bitOperator->valueOfGroupOfBits(file, 1, offset*8);
            //nal_ref_idc
            short int nalRefIdc = bitOperator->valueOfGroupOfBits(file, 2, offset*8 + 1);
            //nal_unit_type;
            int nalUnitType = bitOperator->valueOfGroupOfBits(file, 5, offset*8 + 3);
            offset += 1;
            qDebug()<<nalRefIdc<<nalUnitType;
        } else
            offset += 1;
    }

}
