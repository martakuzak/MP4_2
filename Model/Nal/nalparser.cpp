#include "nalparser.h"

#include <QDateTime>

NALParser::NALParser() {}

NALParser::NALParser(const QString &fileName) {
    this->fileName=fileName;
    this->fileSize = 0;
    fbOperator = new FileBitOperator(fileName);
    fileSize = fbOperator->getSize();
}

NALParser::~NALParser() {
    delete fbOperator;
}

NalUnitsBO *NALParser::parseFile() {
    long start = QDateTime::currentMSecsSinceEpoch();
    QList<std::shared_ptr<NalUnit>> nalUnits;
    unsigned long int offset = 0;//offset w pliku
    unsigned short sizeFieldLength = -1; //rozmiar pola rozmiaru przed jednostka NAL - 1, 2 lub 4
    unsigned int allPrefLength = 0; //długość sumy wszystkich prefiksów przed NALami
    bool previousVCL = false; //do szukania jednostek dostępu, czy poprzednia jednostka była NALem
    QHash<unsigned int, QList<unsigned int>> seqParSetsIdx;
    QHash<unsigned int, QList<unsigned int>> picParSetsIdx;
    QList<unsigned int> syncSampleIdx; //offsety kolejnych jednostek dostępu
    QList<unsigned int> sampleIdx; //numery NALi, które rozpoczynają kolejne ramki

    NalUnitFactory factory(fbOperator);
    if(!fbOperator->openFile()) {
    } else {
        unsigned int maxLength = 0;
        while(offset < fileSize) {
            unsigned int pref3Byte = fbOperator->valueOfGroupOfBytes(3, offset);
            unsigned int pref4Byte = fbOperator->valueOfGroupOfBytes(4, offset);

            if(pref3Byte == 1 || pref4Byte == 1) { //prefix == 0x001 lub 0x0001
                int off = offset;
                offset += (pref3Byte == 1) ? 3 : 4;
                allPrefLength += (pref3Byte == 1) ? 3 : 4;
                //forbidden_zero_bit
                short int forbiddenZeroBit = fbOperator->valueOfGroupOfBits(1, offset*8); //razem: 1 bit
                //nal_ref_idc
                short int nalRefIdc = fbOperator->valueOfGroupOfBits(2, offset*8 + 1); //razem: 3 bity
                //nal_unit_type;
                int nalUnitType = fbOperator->valueOfGroupOfBits(5, offset*8 + 3); //razem: 8 bitów
                std::shared_ptr<NalUnit> nalUnit = factory.getNalUnit(nalUnitType, nalRefIdc, off, (pref3Byte == 1) ? 3 : 4);
                //rozmiary - start
                unsigned int size = nalUnits.size();
                if(size) {
                    nalUnits.at(size - 1)->setLength(off);
                    unsigned int nalUnitLength= nalUnits.at(size - 1)->getLength();
                    if(nalUnitLength > maxLength)
                        maxLength = nalUnitLength;
                }
                //rozmiary - koniec
                //zliczanie zestawów parametrów - start
                if(nalUnitType == 7) {
                    unsigned int id = dynamic_cast<SeqParameterSetRbsp*>(nalUnit.get())->getSeqParSetId();
                    seqParSetsIdx[id].append(size);
                }
                else if(nalUnitType == 8) {
                    unsigned int id = dynamic_cast<PicParameterSetRbsp*>(nalUnit.get())->getPpsId();
                    picParSetsIdx[id].append(size);
                }
                //zliczanie zestawów parametrów  - koniec

                //jednostki dostepu + ramki - start
                NalUnitType nalType = (NalUnitType)nalUnitType;
                if(!size) {
                    sampleIdx.append(size);
                    syncSampleIdx.append(sampleIdx.size());
                }
                else if (isVCL(nalType, false)) //jesli jest to VCL, ale nie IDR, to dodaj ramke
                    sampleIdx.append(size);
                else if((previousVCL && //jesli poprzednia to VCL, a obecna to NAL, ktory moze zaczynac jednostke dostepu
                         this->isAUStarter(nalType))) {
                    if(nalUnits.back()->getTypeCode() == 14 && //nal 14 moze byc prefiksem
                            this->isAUStarter(nalType)) {
                        sampleIdx.append(size - 1);
                        syncSampleIdx.append(sampleIdx.size());
                    }
                    else {
                        sampleIdx.append(size);
                        syncSampleIdx.append(sampleIdx.size());
                    }
                }
                if(nalUnit->getTypeCode() != 14)
                    previousVCL = this->isVCL(nalType, true);
                //jednostki dostepu + ramki - koniec
                nalUnits.append(nalUnit);

                //offset += 1;
                //NumBytesInRBSP = 0
                //nalUnitHeaderBytes = 1
                if(nalUnitType == 14 || nalUnitType == 20)
                    offset += 4; //normalny naglowek (1)+ naglowek rozszerzony (3)
                else
                    offset += 1; //normalny naglowek

            } else {
                unsigned int* bytes = new unsigned int[4];
                for(int i = 0; i < 4; ++ i) {//ostatni byte ma numer 0
                    bytes[i] = (pref4Byte >> (8*i)) & 0xff;
                }
                if(bytes[0] > 1 || (bytes[0] == 1 && (bytes[1] || bytes[2])))
                    offset += 4;
                else if(bytes[1] ) //ostatni = 0 i przedostatni > 0
                    offset += 3;
                else if(bytes[2]) //ostatni = 0, przedostatni = 0, przedprzedostatni > 0
                    offset += 2;
                else //JESZCZE POMYŚL
                    offset += 1;
            }
        }
        int size = nalUnits.size();
        if(size) {
            nalUnits.at(size - 1)->setLength(fbOperator->getSize());
            unsigned int nalUnitLength= nalUnits.at(size - 1)->getLength();
            if(nalUnitLength > maxLength)
                maxLength = nalUnitLength;
        }

        //okresl na ilu bajtach trzeba to zapisac: do wybory 1, 2, 4
        if(maxLength < 0xFF)
            sizeFieldLength = 1;
        else if(maxLength < 0xFFFF)
            sizeFieldLength = 2;
        else if(maxLength < 0xFFFFFFFF)
            sizeFieldLength = 4;
        //koniec
        fbOperator->close();
    }
    long end = QDateTime::currentMSecsSinceEpoch();
    qDebug()<<"Czas : "<<QString::number(end - start) + " ms";

    return new NalUnitsBO(fileName, nalUnits, sizeFieldLength, allPrefLength, sampleIdx, syncSampleIdx, seqParSetsIdx,
                          picParSetsIdx);

}

//int NALParser::sliceLayerWithoutPartitioningRbsp( int offset) {
//    //qDebug()<<"sliceLayerWithoutPartitionRbsp";
//    int newOffset = sliceHeader(offset);
//    /*
//    slice_header();
//    slice_data( );
//    rbsp_slice_trailing_bits( );
//    */
//    return newOffset;
//}

//int NALParser::sliceHeader(int offset) {
//    int bitOffset = 8*offset;
//    //qDebug()<<"SLICE HEADER";
//    int* resLength = new int[1];
//    unsigned long firstMbInSlice = bitOperator->unsignedExpGolomb(file, bitOffset, resLength);
//    bitOffset += resLength[0];
//    resLength[0] = 0;
//    unsigned int sliceType = bitOperator->unsignedExpGolomb(file, bitOffset, resLength);
//    bitOffset += resLength[0];
//    resLength[0] = 0;
//    unsigned long pictureParameterSetId = bitOperator->unsignedExpGolomb(file, bitOffset, resLength);
//    bitOffset += resLength[0];
//    resLength[0] = 0;
//    ////qDebug()<<firstMbInSlice<<sliceType<<pictureParameterSetId;
//    //int frameNum = bitOperator->
//    /*first_mb_in_slice 2 ue(v)
//    slice_type 2 ue(v)
//    pic_parameter_set_id 2 ue(v)
//    frame_num*/
//    return bitOffset;
//}

//int NALParser::parseSEI(int offset) {
//    ////qDebug()<<"parseSEI";
//    int payloadType = 0;
//    /* int nextByteValue = bitOperator->fbOperator->valueOfGroupOfBytes(file, 1, offset ++);
//    while(nextByteValue == 0xFF) {
//        payloadType += 255;
//        nextByteValue = bitOperator->fbOperator->valueOfGroupOfBytes(file, 1, offset ++);
//    }
//    payloadType += nextByteValue;

//    int payloadSize = 0;
//    nextByteValue = bitOperator->fbOperator->valueOfGroupOfBytes(file, 1, offset ++);
//    while(nextByteValue == 0xFF) {
//        payloadSize += 255;
//        nextByteValue = bitOperator->fbOperator->valueOfGroupOfBytes(file, 1, offset ++);
//    }
//    payloadSize += nextByteValue;*/


//    ////qDebug()<<"payloadType : "<<payloadType<<" payloadSize : "<<payloadSize;
//    //parseSEIPayload(payloadType, payloadSize, offset);
//    return ++offset;
//}

//int NALParser::parseSEIPayload(int payloadType, int payloadSize, int offset) {
//    ////qDebug()<<"parseSEIpayload";
//    switch(payloadType) {
//    case 24:
//        offset = scalabilityInfo(payloadSize, offset);
//        break;
//    default:
//        break;
//    }
//    return offset;
//}

//int NALParser::scalabilityInfo(int payloadSize, int offset) {
//    ////qDebug()<<"GOLOMP";
//    /*int bitOffset = 8*offset;
//    int temporalIdNestingFlag = bitOperator->fbOperator->valueOfGroupOfBits(file, 1, bitOffset ++);
//    int priorityLayerInfoPresentFlag = bitOperator->fbOperator->valueOfGroupOfBits(file, 1, bitOffset ++);
//    int priorityIdSettingFlag = bitOperator->fbOperator->valueOfGroupOfBits(file, 1, bitOffset ++);

//    int* golombOffset = new int[1];
//    int numLayersMinus1 = bitOperator->unsignedExpGolomb(file, bitOffset, golombOffset);
//    bitOffset += golombOffset[0];

//    ////qDebug()<<temporalIdNestingFlag<<priorityLayerInfoPresentFlag<<priorityIdSettingFlag<<numLayersMinus1;

//    /*for(int i = 0; i <= numLayersMinus1; ++ i) {
//        //qDebug()<<bitOperator->unsignedExpGolomb(file, bitOffset, golombOffset);
//    }*/

//    return offset;
//}

bool NALParser::isAUStarter(NalUnitType type) {
    return ( (type >= 5 && type <= 9) /*IDR, SEI, sequence par set, pic par set, access unit delimeter*/ ||
             (type >= 14 && type <= 18));
}

bool NALParser::isVCL(NalUnitType type, bool sync){
    if(sync)
        return ( type >= 1 && type <= 5) || type == 20;
    return ( type >= 1 && type <= 4) || type == 20;
}
