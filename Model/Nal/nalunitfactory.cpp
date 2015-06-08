#include "nalunitfactory.h"

NalUnitFactory::NalUnitFactory()
{

}

NalUnitFactory::~NalUnitFactory()
{

}

std::shared_ptr<NalUnit> NalUnitFactory::getNalUnit(int typeCode) {
    switch(typeCode) {

    case UNSPECIFIED:
        return std::shared_ptr<NalUnit>(new Unspecified());
        break;

    case NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        return std::shared_ptr<NalUnit>(new NonIdrSliceLayerWithoutPartitioningRbsp());
        break;

    case SLICE_DATA_PARTITION_A_LAYER_RBSP:
        return std::shared_ptr<NalUnit>(new SliceDataPartitionALayerRbsp());
        break;

    case SLICE_DATA_PARTITION_B_LAYER_RBSP:
        return std::shared_ptr<NalUnit>(new SliceDataPartitionBLayerRbsp());
        break;

    case SLICE_DATA_PARTITION_C_LAYER_RBSP:
        return std::shared_ptr<NalUnit>(new SliceDataPartitionCLayerRbsp());
        break;

    case IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        return std::shared_ptr<NalUnit>(new IdrSliceLayerWithoutPartitioningRbsp());
        break;

    case SEI_RBSP:
        return std::shared_ptr<NalUnit>(new SeiRbsp());
        break;

    case SEQ_PARAMATER_SET_RBSP:
        return std::shared_ptr<NalUnit>(new SeqParamaterSetRbsp());
        break;

    case PIC_PARAMATER_SET_RBSP:
        return std::shared_ptr<NalUnit>(new PicParamaterSetRbsp());
        break;

    case ACCESS_UNIT_DELIMITER_RBSP:
        return std::shared_ptr<NalUnit>(new AccessUnitDelimiterRbsp());
        break;

    case END_OF_SEQUENCE_RBSP:
        return std::shared_ptr<NalUnit>(new EndOfSequenceRbsp());
        break;

    case END_OF_STREAM_RBSP:
        return std::shared_ptr<NalUnit>(new EndOfStreamRbsp());
        break;

    case FILLER_DATA_RBSP:
        return std::shared_ptr<NalUnit>(new FillerDataRbsp());
        break;

    case SEQ_PARAMETER_SET_EXTENSION_RBSP:
        return std::shared_ptr<NalUnit>(new SeqParameterSetExtensionRbsp());
        break;

    case PREFIX_NAL_UNIT_RBSP:
        return std::shared_ptr<NalUnit>(new PrefixNalUnitRbsp());
        break;

    case SUBSET_SEQUENCE_PARAMETER_SET_RBSP:
        return std::shared_ptr<NalUnit>(new SubsetSequenceParameterSetRbsp());
        break;

    case RESERVED_16:
        return std::shared_ptr<NalUnit>(new Reserved16());
        break;

    case RESERVED_17:
        return std::shared_ptr<NalUnit>(new Reserved17());
        break;

    case RESERVED_18:
        return std::shared_ptr<NalUnit>(new Reserved18());
        break;

    case SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
        return std::shared_ptr<NalUnit>(new SliceLayerWithoutPartitioningRbsp());
        break;

    case SLICE_LAYER_EXTENSION_RBSP:
        return std::shared_ptr<NalUnit>(new SliceLayerExtensionRbsp());
        break;

    case RESERVED_21:
        return std::shared_ptr<NalUnit>(new Reserved21());
        break;

    case RESERVED_22:
        return std::shared_ptr<NalUnit>(new Reserved22());
        break;

    case RESERVED_23:
        return std::shared_ptr<NalUnit>(new Reserved23());
        break;

    case UNSPECIFIED_24:
        return std::shared_ptr<NalUnit>(new Unspecified24());
        break;

    case UNSPECIFIED_25:
        return std::shared_ptr<NalUnit>(new Unspecified25());
        break;

    case UNSPECIFIED_26:
        return std::shared_ptr<NalUnit>(new Unspecified26());
        break;

    case UNSPECIFIED_27:
        return std::shared_ptr<NalUnit>(new Unspecified27());
        break;

    case UNSPECIFIED_28:
        return std::shared_ptr<NalUnit>(new Unspecified28());
        break;

    case UNSPECIFIED_29:
        return std::shared_ptr<NalUnit>(new Unspecified29());
        break;

    case UNSPECIFIED_30:
        return std::shared_ptr<NalUnit>(new Unspecified30());
        break;

    case UNSPECIFIED_31:
        return std::shared_ptr<NalUnit>(new Unspecified31());
        break;

    default:
        break;
    }
    return std::shared_ptr<NalUnit>(new NalUnit());
}

