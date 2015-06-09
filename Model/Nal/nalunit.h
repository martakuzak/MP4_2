#ifndef NALUNIT_H
#define NALUNIT_H

#include <QString>

class NalUnit {
protected:
    unsigned int nalRefIdc;
    unsigned long offset;
public:
    NalUnit(unsigned int nri, unsigned long offset);
    ~NalUnit();
    virtual QString getName() { return "NAL Unit"; }
    virtual int getTypeCode() { return -1; }
    unsigned int getNalRefIdc() { return nalRefIdc; }
    unsigned int getOffset() { return offset; }
};


class Unspecified : public NalUnit {
public:
    Unspecified(unsigned int nri, unsigned long offset);
    ~Unspecified();
    virtual QString getName() { return "UNSPECIFIED_"; }
    virtual int getTypeCode() { return 0; }
};

class NonIdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
public:

    NonIdrSliceLayerWithoutPartitioningRbsp(unsigned int nri, unsigned long offset);
    ~NonIdrSliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 1; }
};

class SliceDataPartitionALayerRbsp : public NalUnit {
public:
    SliceDataPartitionALayerRbsp(unsigned int nri, unsigned long offset);
    ~SliceDataPartitionALayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_A_LAYER_RBSP"; }
    virtual int getTypeCode() { return 2; }
};

class SliceDataPartitionBLayerRbsp : public NalUnit {
public:
    SliceDataPartitionBLayerRbsp(unsigned int nri, unsigned long offset);
    ~SliceDataPartitionBLayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_B_LAYER_RBSP"; }
    virtual int getTypeCode() { return 3; }
};

class SliceDataPartitionCLayerRbsp : public NalUnit {
public:
    SliceDataPartitionCLayerRbsp(unsigned int nri, unsigned long offset);
    ~SliceDataPartitionCLayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_C_LAYER_RBSP"; }
    virtual int getTypeCode() { return 4; }
};

class IdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
public:
    IdrSliceLayerWithoutPartitioningRbsp(unsigned int nri, unsigned long offset);
    ~IdrSliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 5; }
};

class SeiRbsp : public NalUnit {
public:
    SeiRbsp(unsigned int nri, unsigned long offset);
    ~SeiRbsp();
    virtual QString getName() { return "SEI RBSP"; }
    virtual int getTypeCode() { return 6; }
};

class SeqParameterSetRbsp : public NalUnit {
public:
    SeqParameterSetRbsp(unsigned int nri, unsigned long offset);
    ~SeqParameterSetRbsp();
    virtual QString getName() { return "SEQ_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 7; }
};

class PicParameterSetRbsp : public NalUnit {
public:
    PicParameterSetRbsp(unsigned int nri, unsigned long offset);
    ~PicParameterSetRbsp();
    virtual QString getName() { return "PIC_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 8; }
};

class AccessUnitDelimiterRbsp : public NalUnit {
public:
    AccessUnitDelimiterRbsp(unsigned int nri, unsigned long offset);
    ~AccessUnitDelimiterRbsp();
    virtual QString getName() { return "ACCESS_UNIT_DELIMITER_RBSP"; }
    virtual int getTypeCode() { return 9; }
};

class EndOfSequenceRbsp : public NalUnit {
public:
    EndOfSequenceRbsp(unsigned int nri, unsigned long offset);
    ~EndOfSequenceRbsp();
    virtual QString getName() { return "END_OF_SEQUENCE_RBSP"; }
    virtual int getTypeCode() { return 10; }
};

class EndOfStreamRbsp : public NalUnit {
public:
    EndOfStreamRbsp(unsigned int nri, unsigned long offset);
    ~EndOfStreamRbsp();
    virtual QString getName() { return "END_OF_STREAM_RBSP"; }
    virtual int getTypeCode() { return 11; }
};

class FillerDataRbsp : public NalUnit {
public:
    FillerDataRbsp(unsigned int nri, unsigned long offset);
    ~FillerDataRbsp();
    virtual QString getName() { return "FILLER_DATA_RBSP"; }
    virtual int getTypeCode() { return 12; }
};

class SeqParameterSetExtensionRbsp : public NalUnit {
public:
    SeqParameterSetExtensionRbsp(unsigned int nri, unsigned long offset);
    ~SeqParameterSetExtensionRbsp();
    virtual QString getName() { return "SEQ_PARAMETER_SET_EXTENSION_RBSP"; }
    virtual int getTypeCode() { return 13; }
};

class PrefixNalUnitRbsp : public NalUnit {
public:
    PrefixNalUnitRbsp(unsigned int nri, unsigned long offset);
    ~PrefixNalUnitRbsp();
    virtual QString getName() { return "PREFIX_NAL_UNIT_RBSP"; }
    virtual int getTypeCode() { return 14; }
};

class SubsetSequenceParameterSetRbsp : public NalUnit {
public:
    SubsetSequenceParameterSetRbsp(unsigned int nri, unsigned long offset);
    ~SubsetSequenceParameterSetRbsp();
    virtual QString getName() { return "SUBSET_SEQUENCE_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 15; }
};

class Reserved16 : public NalUnit {
public:
    Reserved16(unsigned int nri, unsigned long offset);
    ~Reserved16();
    virtual QString getName() { return "RESERVED_16"; }
    virtual int getTypeCode() { return 16; }
};

class Reserved17 : public NalUnit {
public:
    Reserved17(unsigned int nri, unsigned long offset);
    ~Reserved17();
    virtual QString getName() { return "RESERVED_17"; }
    virtual int getTypeCode() { return 17; }
};

class Reserved18 : public NalUnit {
public:
    Reserved18(unsigned int nri, unsigned long offset);
    ~Reserved18();
    virtual QString getName() { return "RESERVED_18"; }
    virtual int getTypeCode() { return 18; }
};

class SliceLayerWithoutPartitioningRbsp : public NalUnit {
public:
    SliceLayerWithoutPartitioningRbsp(unsigned int nri, unsigned long offset);
    ~SliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 19; }
};

class SliceLayerExtensionRbsp : public NalUnit {
public:
    SliceLayerExtensionRbsp(unsigned int nri, unsigned long offset);
    ~SliceLayerExtensionRbsp();
    virtual QString getName() { return "SLICE_LAYER_EXTENSION_RBSP"; }
    virtual int getTypeCode() { return 20; }
};

class Reserved21 : public NalUnit {
public:
    Reserved21(unsigned int nri, unsigned long offset);
    ~Reserved21();
    virtual QString getName() { return "RESERVED_21"; }
    virtual int getTypeCode() { return 21; }
};

class Reserved22 : public NalUnit {
public:
    Reserved22(unsigned int nri, unsigned long offset);
    ~Reserved22();
    virtual QString getName() { return "RESERVED_22"; }
    virtual int getTypeCode() { return 22; }
};

class Reserved23 : public NalUnit {
public:
    Reserved23(unsigned int nri, unsigned long offset);
    ~Reserved23();
    virtual QString getName() { return "RESERVED_23"; }
    virtual int getTypeCode() { return 23; }
};

class Unspecified24 : public NalUnit {
public:
    Unspecified24(unsigned int nri, unsigned long offset);
    ~Unspecified24();
    virtual QString getName() { return "UNSPECIFIED_24"; }
    virtual int getTypeCode() { return 24; }
};

class Unspecified25 : public NalUnit {
public:
    Unspecified25(unsigned int nri, unsigned long offset);
    ~Unspecified25();
    virtual QString getName() { return "UNSPECIFIED_25"; }
    virtual int getTypeCode() { return 25; }
};

class Unspecified26 : public NalUnit {
public:
    Unspecified26(unsigned int nri, unsigned long offset);
    ~Unspecified26();
    virtual QString getName() { return "UNSPECIFIED_26"; }
    virtual int getTypeCode() { return 26; }
};

class Unspecified27 : public NalUnit {
public:
    Unspecified27(unsigned int nri, unsigned long offset);
    ~Unspecified27();
    virtual QString getName() { return "UNSPECIFIED_27"; }
    virtual int getTypeCode() { return 27; }
};

class Unspecified28 : public NalUnit {
public:
    Unspecified28(unsigned int nri, unsigned long offset);
    ~Unspecified28();
    virtual QString getName() { return "UNSPECIFIED_28"; }
    virtual int getTypeCode() { return 28; }
};

class Unspecified29 : public NalUnit {
public:
    Unspecified29(unsigned int nri, unsigned long offset);
    ~Unspecified29();
    virtual QString getName() { return "UNSPECIFIED_29"; }
    virtual int getTypeCode() { return 29; }
};

class Unspecified30 : public NalUnit {
public:
    Unspecified30(unsigned int nri, unsigned long offset);
    ~Unspecified30();
    virtual QString getName() { return "UNSPECIFIED_30"; }
    virtual int getTypeCode() { return 30; }
};

class Unspecified31 : public NalUnit {
public:
    Unspecified31(unsigned int nri, unsigned long offset);
    ~Unspecified31();
    virtual QString getName() { return "UNSPECIFIED_31"; }
    virtual int getTypeCode() { return 31; }
};


#endif // NALUNIT_H
