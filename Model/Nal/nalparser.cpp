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
    fileService = new FileService(fileName);
}

NALParser::~NALParser() {
    delete bitOperator;
    delete fileService;
}

QList<std::shared_ptr<NalUnit>> NALParser::parseFile() {
    unsigned long int offset= 0;//offset w pliku

    QList<std::shared_ptr<NalUnit>> list;
    NalUnitFactory factory(this, fileService);

    if(fileService->openFile()) {
        while(offset < fileSize) {

            unsigned int pref3Byte = valueOfGroupOfBytes(3, offset); //? sprawdzic to wszystko !!!
            unsigned int pref4Byte = valueOfGroupOfBytes(4, offset);

            if(pref3Byte == 1 || pref4Byte == 1) { //prefix == 0x001 lub 0x0001
                int off = offset;
                offset += (pref3Byte == 1) ? 3 : 4;
                //forbidden_zero_bit
                short int forbiddenZeroBit = valueOfGroupOfBits(1, offset*8); //razem: 1 bit
                //nal_ref_idc
                short int nalRefIdc = valueOfGroupOfBits(2, offset*8 + 1); //razem: 3 bity
                //nal_unit_type;
                int nalUnitType = valueOfGroupOfBits(5, offset*8 + 3); //razem: 8 bitów
                ////qDebug()<<offset;
                offset += 1;
                //qDebug()<<"NALPARSER parse" <<nalRefIdc<<nalUnitType;
                //identifyNalType(nalUnitType, offset);
                std::shared_ptr<NalUnit> nalUnit = factory.getNalUnit(nalUnitType, nalRefIdc, off);
                list.append(nalUnit);

            } else
                offset += 1;
        }
        fileService->close();
    }
    qDebug()<<"NALPARSER parseFile 4";

    return list;

}

int NALParser::sliceLayerWithoutPartitioningRbsp( int offset) {
    //qDebug()<<"sliceLayerWithoutPartitionRbsp";
    int newOffset = sliceHeader(offset);
    /*
    slice_header();
    slice_data( );
    rbsp_slice_trailing_bits( );
    */
    return newOffset;
}

int NALParser::sliceHeader(int offset) {
    int bitOffset = 8*offset;
    //qDebug()<<"SLICE HEADER";
    int* resLength = new int[1];
    unsigned long firstMbInSlice = bitOperator->unsignedExpGolomb(file, bitOffset, resLength);
    bitOffset += resLength[0];
    resLength[0] = 0;
    unsigned int sliceType = bitOperator->unsignedExpGolomb(file, bitOffset, resLength);
    bitOffset += resLength[0];
    resLength[0] = 0;
    unsigned long pictureParameterSetId = bitOperator->unsignedExpGolomb(file, bitOffset, resLength);
    bitOffset += resLength[0];
    resLength[0] = 0;
    ////qDebug()<<firstMbInSlice<<sliceType<<pictureParameterSetId;
    //int frameNum = bitOperator->
    /*first_mb_in_slice 2 ue(v)
    slice_type 2 ue(v)
    pic_parameter_set_id 2 ue(v)
    frame_num*/
    return bitOffset;
}

int NALParser::parseSEI(int offset) {
    ////qDebug()<<"parseSEI";
    int payloadType = 0;
    /* int nextByteValue = bitOperator->valueOfGroupOfBytes(file, 1, offset ++);
    while(nextByteValue == 0xFF) {
        payloadType += 255;
        nextByteValue = bitOperator->valueOfGroupOfBytes(file, 1, offset ++);
    }
    payloadType += nextByteValue;

    int payloadSize = 0;
    nextByteValue = bitOperator->valueOfGroupOfBytes(file, 1, offset ++);
    while(nextByteValue == 0xFF) {
        payloadSize += 255;
        nextByteValue = bitOperator->valueOfGroupOfBytes(file, 1, offset ++);
    }
    payloadSize += nextByteValue;*/


    ////qDebug()<<"payloadType : "<<payloadType<<" payloadSize : "<<payloadSize;
    //parseSEIPayload(payloadType, payloadSize, offset);
    return ++offset;
}

int NALParser::parseSEIPayload(int payloadType, int payloadSize, int offset) {
    ////qDebug()<<"parseSEIpayload";
    switch(payloadType) {
    case 24:
        offset = scalabilityInfo(payloadSize, offset);
        break;
    default:
        break;
    }
    return offset;
}

int NALParser::scalabilityInfo(int payloadSize, int offset) {
    ////qDebug()<<"GOLOMP";
    /*int bitOffset = 8*offset;
    int temporalIdNestingFlag = bitOperator->valueOfGroupOfBits(file, 1, bitOffset ++);
    int priorityLayerInfoPresentFlag = bitOperator->valueOfGroupOfBits(file, 1, bitOffset ++);
    int priorityIdSettingFlag = bitOperator->valueOfGroupOfBits(file, 1, bitOffset ++);

    int* golombOffset = new int[1];
    int numLayersMinus1 = bitOperator->unsignedExpGolomb(file, bitOffset, golombOffset);
    bitOffset += golombOffset[0];

    ////qDebug()<<temporalIdNestingFlag<<priorityLayerInfoPresentFlag<<priorityIdSettingFlag<<numLayersMinus1;

    /*for(int i = 0; i <= numLayersMinus1; ++ i) {
        //qDebug()<<bitOperator->unsignedExpGolomb(file, bitOffset, golombOffset);
    }*/

    return offset;
}

void NALParser::identifyNalType(int nalUnitType, int offset) {
    switch(nalUnitType) {
    case UNSPECIFIED:
        //qDebug()<<"UNSPECIFIED"<<QString::number(offset,16);
        break;
    case NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        //qDebug()<<"NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"<<QString::number(offset,16);
        sliceLayerWithoutPartitioningRbsp(offset);
        break;
    case SLICE_DATA_PARTITION_A_LAYER_RBSP:
        //qDebug()<<"SLICE_DATA_PARTITION_A_LAYER_RBSP"<<QString::number(offset,16);
        break;
    case SLICE_DATA_PARTITION_B_LAYER_RBSP:
        //qDebug()<<"SLICE_DATA_PARTITION_B_LAYER_RBSP"<<QString::number(offset,16);
        break;
    case SLICE_DATA_PARTITION_C_LAYER_RBSP:
        //qDebug()<<"SLICE_DATA_PARTITION_C_LAYER_RBSP"<<QString::number(offset,16);
        break;
    case IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        //qDebug()<<"\nIDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"<<QString::number(offset,16)<<"\n";
        sliceLayerWithoutPartitioningRbsp(offset);
        break;
    case SEI_RBSP:
        //qDebug()<<"SEI_RBSP"<<QString::number(offset,16);
        parseSEI(offset);
        break;
    case SEQ_PARAMETER_SET_RBSP:
        //qDebug()<<"SEQ_PARAMATER_SET_RBSP"<<QString::number(offset,16);
        break;
    case PIC_PARAMETER_SET_RBSP:
        //qDebug()<<"PIC_PARAMATER_SET_RBSP"<<QString::number(offset,16);
        break;
    case ACCESS_UNIT_DELIMITER_RBSP:
        //qDebug()<<"ACCESS_UNIT_DELIMITER_RBSP"<<QString::number(offset,16);
        break;
    case END_OF_SEQUENCE_RBSP:
        //qDebug()<<"END_OF_SEQUENCE_RBSP"<<QString::number(offset,16);
        break;
    case END_OF_STREAM_RBSP:
        //qDebug()<<"END_OF_STREAM_RBSP"<<QString::number(offset,16);
        break;
    case FILLER_DATA_RBSP:
        //qDebug()<<"FILLER_DATA_RBSP"<<QString::number(offset,16);
        break;
        /*case RESERVED_13:
        //qDebug()<<"RESERVED_13"<<QString::number(offset,16);
        break;
    case RESERVED_14: // NAL unit type 14 is used for prefix NAL unit
        //qDebug()<<"RESERVED_14 SVC prefix NAL unit"<<QString::number(offset,16);
        break;
    case RESERVED_15: //NAL unit type 15 is used for subset sequence parameter set
        //qDebug()<<"RESERVED_15 SVC subset sequence parameter set"<<QString::number(offset,16);
        break;*/
    case RESERVED_16:
        //qDebug()<<"RESERVED_16"<<QString::number(offset,16);
        break;
    case RESERVED_17:
        //qDebug()<<"RESERVED_17"<<QString::number(offset,16);
        break;
    case RESERVED_18:
        //qDebug()<<"RESERVED_18"<<QString::number(offset,16);
        break;
        /*case RESERVED_19:
        //qDebug()<<"RESERVED_19"<<QString::number(offset,16);
        break;
    case RESERVED_20: // NAL unit type 20 is used for coded slice in scalable extension
        //qDebug()<<"RESERVED_20 SVC coded slice in scalable extension"<<QString::number(offset,16);
        break;*/
    case RESERVED_21:
        //qDebug()<<"RESERVED_21"<<QString::number(offset,16);
        break;
    case RESERVED_22:
        //qDebug()<<"RESERVED_22"<<QString::number(offset,16);
        break;
    case RESERVED_23:
        //qDebug()<<"RESERVED_23"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_24:
        //qDebug()<<"RESERVED_24"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_25:
        //qDebug()<<"RESERVED_25"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_26:
        //qDebug()<<"RESERVED_26"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_27:
        //qDebug()<<"RESERVED_27"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_28:
        //qDebug()<<"RESERVED_28"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_29:
        //qDebug()<<"RESERVED_29"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_30:
        //qDebug()<<"RESERVED_30"<<QString::number(offset,16);
        break;
    case UNSPECIFIED_31:
        //qDebug()<<"RESERVED_31"<<QString::number(offset,16);
        break;
    default:
        break;

    }    
}


unsigned long int NALParser::valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    if(length == 55808)
        return 0;
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}
signed long int NALParser::signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    long int ret = bitOperator->signedValueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}
unsigned long int NALParser::valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBits(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBits(ptr, length);
    delete[] ptr;
    return ret;
}
QString NALParser::stringValue(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    QString ret = bitOperator->stringValue(ptr, length);
    delete[] ptr;
    return ret;
}
