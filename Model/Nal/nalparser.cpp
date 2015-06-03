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

        unsigned int pref_3_byte = bitOperator->valueOfGroupOfBytes(file, 3, offset);
        unsigned int pref_4_byte = bitOperator->valueOfGroupOfBytes(file, 4, offset);


        if(pref_3_byte == 1 || pref_4_byte == 1) {
            offset += (pref_3_byte == 1) ? 3 : 4;
            //forbidden_zero_bit
            short int forbiddenZeroBit = bitOperator->valueOfGroupOfBits(file, 1, offset*8);
            //nal_ref_idc
            short int nalRefIdc = bitOperator->valueOfGroupOfBits(file, 2, offset*8 + 1);
            //nal_unit_type;
            int nalUnitType = bitOperator->valueOfGroupOfBits(file, 5, offset*8 + 3);
            offset += 1;
            qDebug()<<nalRefIdc<<nalUnitType;
        } else {
            //qDebug()<<"NoNAL";
            offset += 1;
        }

        /*//zero byte 0x00
        unsigned int zeroByte = bitOperator->valueOfGroupOfBytes(file, 1, offset);
        if(zeroByte != 0)
            return; //cos jest nie tak
        offset += 1;
        //start code prefix  0x000001
        unsigned int pref = bitOperator->valueOfGroupOfBytes(file, 3, offset);
        if(pref != 1)
            return; //cos jest nie tak
        offset += 3;
        //forbidden_zero_bit
        short int forbiddenZeroBit = bitOperator->valueOfGroupOfBits(file, 1, offset*8);
        //nal_ref_idc
        short int nalRefIdc = bitOperator->valueOfGroupOfBits(file, 2, offset*8 + 1);
        //nal_unit_type;
        int nalUnitType = bitOperator->valueOfGroupOfBits(file, 5, offset*8 + 3);
        offset += 1;

        qDebug()<<"zeroByte "<<zeroByte<<" prefix "<<pref<<" fzb "<<forbiddenZeroBit<<" nri "<<nalRefIdc<<" nut "<<nalUnitType;*/
        //return;
    }

}
