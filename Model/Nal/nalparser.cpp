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
            qDebug()<<offset;
            offset += 1;
            //qDebug()<<nalRefIdc<<nalUnitType;
            identifyNalType(nalUnitType, offset);

        } else
            offset += 1;
    }

}

int NALParser::parseSEI(int offset) {
    int payloadType = 0;
    int nextByteValue = bitOperator->valueOfGroupOfBytes(file, 1, offset ++);
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
    payloadSize += nextByteValue;


    qDebug()<<"payloadType : "<<payloadType<<" payloadSize : "<<payloadSize;
    return ++offset;
}

int NALParser::parseSEIpayload(int payloadType, int payloadSize, int offset) {
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
    int temporalIdNestingFlag = bitOperator->valueOfGroupOfBits(file, 1, 8*offset);
    int priorityLayerInfoPresentFlag = bitOperator->valueOfGroupOfBits(file, 1, 8*offset + 1);
    int priorityIdSettingFlag = bitOperator->valueOfGroupOfBits(file, 1, 8*offset + 2);
    int numLayersMinus1 = bitOperator->valueOfGroupOfBits(file, 1, 8*offset + 3);
    qDebug()<<temporalIdNestingFlag<<priorityLayerInfoPresentFlag<<priorityIdSettingFlag<<numLayersMinus1;
    for(int i = 0; i <= numLayersMinus1; ++ i) {

    }

    return offset;
}

void NALParser::identifyNalType(int nalUnitType, int offset) {
    switch(nalUnitType) {
    case UNSPECIFIED:
        qDebug()<<"UNSPECIFIED";
        break;
    case NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        qDebug()<<"NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP";
        break;
    case SLICE_DATA_PARTITION_A_LAYER_RBSP:
        qDebug()<<"SLICE_DATA_PARTITION_A_LAYER_RBSP";
        break;
    case SLICE_DATA_PARTITION_B_LAYER_RBSP:
        qDebug()<<"SLICE_DATA_PARTITION_B_LAYER_RBSP";
        break;
    case SLICE_DATA_PARTITION_C_LAYER_RBSP:
        qDebug()<<"SLICE_DATA_PARTITION_C_LAYER_RBSP";
        break;
    case IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        qDebug()<<"IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP";
        break;
    case SEI_RBSP:
        qDebug()<<"SEI_RBSP\n\n";
        parseSEI(offset);
        qDebug()<<"\n\n";
        break;
    case SEQ_PARAMATER_SET_RBSP:
        qDebug()<<"SEQ_PARAMATER_SET_RBSP";
        break;
    case PIC_PARAMATER_SET_RBSP:
        qDebug()<<"PIC_PARAMATER_SET_RBSP";
        break;
    case ACCESS_UNIT_DELIMITER_RBSP:
        qDebug()<<"ACCESS_UNIT_DELIMITER_RBSP";
        break;
    case END_OF_SEQUENCE_RBSP:
        qDebug()<<"END_OF_SEQUENCE_RBSP";
        break;
    case END_OF_STREAM_RBSP:
        qDebug()<<"END_OF_STREAM_RBSP";
        break;
    case FILLER_DATA_RBSP:
        qDebug()<<"FILLER_DATA_RBSP";
        break;
    case RESERVED_13:
        qDebug()<<"RESERVED_13";
        break;
    case RESERVED_14: // NAL unit type 14 is used for prefix NAL unit
        qDebug()<<"RESERVED_14 SVC prefix NAL unit";
        break;
    case RESERVED_15: //NAL unit type 15 is used for subset sequence parameter set
        qDebug()<<"RESERVED_15 SVC subset sequence parameter set";
        break;
    case RESERVED_16:
        qDebug()<<"RESERVED_16";
        break;
    case RESERVED_17:
        qDebug()<<"RESERVED_17";
        break;
    case RESERVED_18:
        qDebug()<<"RESERVED_18";
        break;
    case RESERVED_19:
        qDebug()<<"RESERVED_19";
        break;
    case RESERVED_20: // NAL unit type 20 is used for coded slice in scalable extension
        qDebug()<<"RESERVED_20 SVC coded slice in scalable extension";
        break;
    case RESERVED_21:
        qDebug()<<"RESERVED_21";
        break;
    case RESERVED_22:
        qDebug()<<"RESERVED_22";
        break;
    case RESERVED_23:
        qDebug()<<"RESERVED_23";
        break;
    case UNSPECIFIED_24:
        qDebug()<<"RESERVED_24";
        break;
    case UNSPECIFIED_25:
        qDebug()<<"RESERVED_25";
        break;
    case UNSPECIFIED_26:
        qDebug()<<"RESERVED_26";
        break;
    case UNSPECIFIED_27:
        qDebug()<<"RESERVED_27";
        break;
    case UNSPECIFIED_28:
        qDebug()<<"RESERVED_28";
        break;
    case UNSPECIFIED_29:
        qDebug()<<"RESERVED_29";
        break;
    case UNSPECIFIED_30:
        qDebug()<<"RESERVED_30";
        break;
    case UNSPECIFIED_31:
        qDebug()<<"RESERVED_31";
        break;
    default:
        break;

    }
}
