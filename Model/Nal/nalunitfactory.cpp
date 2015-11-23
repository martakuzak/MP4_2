#include "nalunitfactory.h"

NalUnitFactory::NalUnitFactory(NALParser *par, FileService* fs) : parser(par), fileService(fs){
    bitOperator = new BitOperator();
}

NalUnitFactory::~NalUnitFactory() {
    //delete parser; //NALParser wola obiekt factory - niech factory go nie kasuje!!!!!!!
    //TO-DO przemyselec, jak to lepiej zrobic
    //delete fileService;
    delete bitOperator;
}

std::shared_ptr<NalUnit> NalUnitFactory::getNalUnit(int typeCode, unsigned int nalRefIdc, unsigned long offset) {
    switch(typeCode) {
    case UNSPECIFIED:
        return std::shared_ptr<NalUnit>(new Unspecified(nalRefIdc, offset));
        break;

    case NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        return std::shared_ptr<NalUnit>(new NonIdrSliceLayerWithoutPartitioningRbsp(nalRefIdc, offset, 0, 0, 0));
        break;

    case SLICE_DATA_PARTITION_A_LAYER_RBSP:
        return std::shared_ptr<NalUnit>(new SliceDataPartitionALayerRbsp(nalRefIdc, offset));
        break;

    case SLICE_DATA_PARTITION_B_LAYER_RBSP:
        return std::shared_ptr<NalUnit>(new SliceDataPartitionBLayerRbsp(nalRefIdc, offset));
        break;

    case SLICE_DATA_PARTITION_C_LAYER_RBSP:
        return std::shared_ptr<NalUnit>(new SliceDataPartitionCLayerRbsp(nalRefIdc, offset));
        break;

    case IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        return std::shared_ptr<NalUnit>(new IdrSliceLayerWithoutPartitioningRbsp(nalRefIdc, offset, 0, 0, 0));
        break;

    case SEI_RBSP:
        return std::shared_ptr<NalUnit>(new SeiRbsp(nalRefIdc, offset));
        break;

    case SEQ_PARAMETER_SET_RBSP:
        return std::shared_ptr<NalUnit>(new SeqParameterSetRbsp(nalRefIdc, offset));
        break;

    case PIC_PARAMETER_SET_RBSP:
        return std::shared_ptr<NalUnit>(new PicParameterSetRbsp(nalRefIdc, offset));
        break;

    case ACCESS_UNIT_DELIMITER_RBSP:
        return std::shared_ptr<NalUnit>(new AccessUnitDelimiterRbsp(nalRefIdc, offset));
        break;

    case END_OF_SEQUENCE_RBSP:
        return std::shared_ptr<NalUnit>(new EndOfSequenceRbsp(nalRefIdc, offset));
        break;

    case END_OF_STREAM_RBSP:
        return std::shared_ptr<NalUnit>(new EndOfStreamRbsp(nalRefIdc, offset));
        break;

    case FILLER_DATA_RBSP:
        return std::shared_ptr<NalUnit>(new FillerDataRbsp(nalRefIdc, offset));
        break;

    case SEQ_PARAMETER_SET_EXTENSION_RBSP:
        return std::shared_ptr<NalUnit>(new SeqParameterSetExtensionRbsp(nalRefIdc, offset));
        break;

    case PREFIX_NAL_UNIT_RBSP: //14
    {
        unsigned int off = offset;
        off += 5;
        unsigned int svcExtensionFlag = valueOfGroupOfBits(1, off*8);
        if(svcExtensionFlag) {
            unsigned int reservedOneBit = valueOfGroupOfBits(1, off*8);
            unsigned int idrFlag = valueOfGroupOfBits(1, off*8 + 1);
            unsigned int priorityId = valueOfGroupOfBits(6, off*8 + 2);
            off += 1;
            unsigned int noInterLayerPredFlag = valueOfGroupOfBits(1, off*8);
            unsigned int dependencyId = valueOfGroupOfBits(3, off*8 + 1);
            unsigned int qualityId = valueOfGroupOfBits(4, off*8 + 4);
            unsigned int temporaryId = valueOfGroupOfBits(3, off*8 + 7);
            unsigned int useRefBasePicFlag = valueOfGroupOfBits(1, off*8 + 10);
            unsigned int discardableFlag = valueOfGroupOfBits(1, off*8 + 11);
            unsigned int outputFlag = valueOfGroupOfBits(1, off*8 + 12);
            unsigned int reservedThree2bits = valueOfGroupOfBits(2, off*8 + 13);
            return std::shared_ptr<NalUnit>(new PrefixNalUnitRbsp(nalRefIdc, offset, reservedOneBit, idrFlag, priorityId, noInterLayerPredFlag,
                                                                        dependencyId, qualityId, temporaryId, useRefBasePicFlag, discardableFlag, outputFlag,
                                                                        reservedThree2bits));
        }
        else return std::shared_ptr<NalUnit>(new NalUnit(nalRefIdc, off));
    }
    case SUBSET_SEQUENCE_PARAMETER_SET_RBSP:
        return std::shared_ptr<NalUnit>(new SubsetSequenceParameterSetRbsp(nalRefIdc, offset));
        break;

    case RESERVED_16:
        return std::shared_ptr<NalUnit>(new Reserved16(nalRefIdc, offset));
        break;

    case RESERVED_17:
        return std::shared_ptr<NalUnit>(new Reserved17(nalRefIdc, offset));
        break;

    case RESERVED_18:
        return std::shared_ptr<NalUnit>(new Reserved18(nalRefIdc, offset));
        break;

    case SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        return std::shared_ptr<NalUnit>(new SliceLayerWithoutPartitioningRbsp(nalRefIdc, offset));
        break;

    case SLICE_LAYER_EXTENSION_RBSP: //20
    {
        unsigned int off = offset;
        off += 5;
        unsigned int svcExtensionFlag = valueOfGroupOfBits(1, off*8);
        if(svcExtensionFlag) {
            unsigned int reservedOneBit = valueOfGroupOfBits(1, off*8);
            unsigned int idrFlag = valueOfGroupOfBits(1, off*8 + 1);
            unsigned int priorityId = valueOfGroupOfBits(6, off*8 + 2);
            off += 1;
            unsigned int noInterLayerPredFlag = valueOfGroupOfBits(1, off*8);
            unsigned int dependencyId = valueOfGroupOfBits(3, off*8 + 1);
            unsigned int qualityId = valueOfGroupOfBits(4, off*8 + 4);
            unsigned int temporaryId = valueOfGroupOfBits(3, off*8 + 7);
            unsigned int useRefBasePicFlag = valueOfGroupOfBits(1, off*8 + 10);
            unsigned int discardableFlag = valueOfGroupOfBits(1, off*8 + 11);
            unsigned int outputFlag = valueOfGroupOfBits(1, off*8 + 12);
            unsigned int reservedThree2bits = valueOfGroupOfBits(2, off*8 + 13);

            return std::shared_ptr<NalUnit>(new SliceLayerExtensionRbsp(nalRefIdc, offset, reservedOneBit, idrFlag, priorityId, noInterLayerPredFlag,
                                                                        dependencyId, qualityId, temporaryId, useRefBasePicFlag, discardableFlag, outputFlag,
                                                                        reservedThree2bits));
        }
        else return std::shared_ptr<NalUnit>(new NalUnit(nalRefIdc, off));
        break;
    }
    case RESERVED_21:
        return std::shared_ptr<NalUnit>(new Reserved21(nalRefIdc, offset));
        break;

    case RESERVED_22:
        return std::shared_ptr<NalUnit>(new Reserved22(nalRefIdc, offset));
        break;

    case RESERVED_23:
        return std::shared_ptr<NalUnit>(new Reserved23(nalRefIdc, offset));
        break;

    case UNSPECIFIED_24:
        return std::shared_ptr<NalUnit>(new Unspecified24(nalRefIdc, offset));
        break;

    case UNSPECIFIED_25:
        return std::shared_ptr<NalUnit>(new Unspecified25(nalRefIdc, offset));
        break;

    case UNSPECIFIED_26:
        return std::shared_ptr<NalUnit>(new Unspecified26(nalRefIdc, offset));
        break;

    case UNSPECIFIED_27:
        return std::shared_ptr<NalUnit>(new Unspecified27(nalRefIdc, offset));
        break;

    case UNSPECIFIED_28:
        return std::shared_ptr<NalUnit>(new Unspecified28(nalRefIdc, offset));
        break;

    case UNSPECIFIED_29:
        return std::shared_ptr<NalUnit>(new Unspecified29(nalRefIdc, offset));
        break;

    case UNSPECIFIED_30:
        return std::shared_ptr<NalUnit>(new Unspecified30(nalRefIdc, offset));
        break;

    case UNSPECIFIED_31:
        return std::shared_ptr<NalUnit>(new Unspecified31(nalRefIdc, offset));
        break;
    default:
        break;
    }
    return std::shared_ptr<NalUnit>(new NalUnit(nalRefIdc, offset));
}

unsigned long int NalUnitFactory::valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}
signed long int NalUnitFactory::signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    long int ret = bitOperator->signedValueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}
unsigned long int NalUnitFactory::valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBits(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBits(ptr, length);
    delete[] ptr;
    return ret;
}
QString NalUnitFactory::stringValue(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    QString ret = bitOperator->stringValue(ptr, length);
    delete[] ptr;
    return ret;
}
