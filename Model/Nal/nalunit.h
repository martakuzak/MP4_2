#ifndef NALUNIT_H
#define NALUNIT_H

#include <QString>
#include <QDebug>

class NalUnit {
protected:
    unsigned int nalRefIdc;
    unsigned long offset;
    unsigned long length;
public:
    NalUnit(const unsigned int&  nri = 0, const unsigned long & off = 0);
    ~NalUnit();
    bool setLength(const unsigned long endOfNal) {
        if(endOfNal <= offset)
            return false;
        else
            length = endOfNal - offset;
        return true;
    }
    unsigned long getLength() { return length; }
    unsigned int getNalRefIdc() { return nalRefIdc; }
    unsigned int getOffset() {return offset; }
    virtual QString getName() { return "NAL Unit"; }
    virtual int getTypeCode() { return -1; }
    virtual QString getInfo() { return ""; }
    virtual QString getHeader() { return "NalRefIdc: " + QString::number(nalRefIdc);}
};

class ExtendedNalUnit : public NalUnit {
protected:
    unsigned int SVCflag;
public:
    ExtendedNalUnit(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned int& svcFlag = 0);
    ~ExtendedNalUnit();
    virtual QString getName() { return "Extended NAL Unit"; }
    virtual int getTypeCode() { return -1; }
    virtual QString getHeaderExtension();
    virtual QString getHeader() {
        return NalUnit::getHeader() + "\n" + getHeaderExtension();
    }
    unsigned int getSVCflag() const;
};

class SVCNalUnit : public ExtendedNalUnit {
protected:
    unsigned int idrFlag;
    unsigned int priorityId;
    unsigned int noInterLayerPredFlag;
    unsigned int dependencyId;
    unsigned int qualityId;
    unsigned int temporaryId;
    unsigned int useRefBasePicFlag;
    unsigned int discardableFlag;
    unsigned int outputFlag;
    unsigned int reservedThree2bits;
public:
    SVCNalUnit(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned int& SVCflag = 0, const unsigned int& idrFlag = 0,
               const unsigned int& priorityId = 0, const unsigned int& noInterLayerPredFlag = 0, const unsigned int& dependencyId = 0, const unsigned int& qualityId = 0,
               const unsigned int& temporaryId = 0, const unsigned int& useRefBasePicFlag = 0, const unsigned int& discardableFlag = 0, const unsigned int& outputFlag = 0,
               const unsigned int& reservedThree2bits = 0);
    ~SVCNalUnit();
    virtual QString getName() { return "Extended NAL Unit"; }
    virtual int getTypeCode() { return -1; }
    virtual QString getHeaderExtension();
    virtual QString getHeader() {
        return NalUnit::getHeader() + "\n" + getHeaderExtension();
    }
    int getPriorityId() { return priorityId; }
    unsigned int getIdrFlag() const;
    unsigned int getNoInterLayerPredFlag() const;
    unsigned int getDependencyId() const;
    unsigned int getQualityId() const;
    unsigned int getTemporaryId() const;
    unsigned int getUseRefBasePicFlag() const;
    unsigned int getDiscardableFlag() const;
    unsigned int getOutputFlag() const;
    unsigned int getReservedThree2bits() const;
};

class Unspecified : public NalUnit {
public:
    Unspecified(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified();
    virtual QString getName() { return "UNSPECIFIED_"; }
    virtual int getTypeCode() { return 0; }
};

class NonIdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
protected:
    unsigned long firstMbInSlice;
    unsigned int sliceType;
    unsigned long pictureParameterSetId;
public:
    NonIdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & offset, unsigned long fmis, unsigned int st, unsigned long ppsi);
    ~NonIdrSliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 1; }
    virtual QString getInfo();
};

class SliceDataPartitionALayerRbsp : public NalUnit {
public:
    SliceDataPartitionALayerRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SliceDataPartitionALayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_A_LAYER_RBSP"; }
    virtual int getTypeCode() { return 2; }
};

class SliceDataPartitionBLayerRbsp : public NalUnit {
public:
    SliceDataPartitionBLayerRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SliceDataPartitionBLayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_B_LAYER_RBSP"; }
    virtual int getTypeCode() { return 3; }
};

class SliceDataPartitionCLayerRbsp : public NalUnit {
public:
    SliceDataPartitionCLayerRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SliceDataPartitionCLayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_C_LAYER_RBSP"; }
    virtual int getTypeCode() { return 4; }
};

class IdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
protected:
    unsigned long firstMbInSlice;
    unsigned int sliceType;
    unsigned long pictureParameterSetId;
public:
    IdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & offset, unsigned long fmis, unsigned int st, unsigned long ppsi);
    ~IdrSliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 5; }
    virtual QString getInfo();
};

class SeiRbsp : public NalUnit {
public:
    SeiRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SeiRbsp();
    virtual QString getName() { return "SEI RBSP"; }
    virtual int getTypeCode() { return 6; }
};

class SeqParameterSetRbsp : public NalUnit {
public:
    SeqParameterSetRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SeqParameterSetRbsp();
    virtual QString getName() { return "SEQ_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 7; }
};

class PicParameterSetRbsp : public NalUnit {
public:
    PicParameterSetRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~PicParameterSetRbsp();
    virtual QString getName() { return "PIC_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 8; }
};

class AccessUnitDelimiterRbsp : public NalUnit {
public:
    AccessUnitDelimiterRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~AccessUnitDelimiterRbsp();
    virtual QString getName() { return "ACCESS_UNIT_DELIMITER_RBSP"; }
    virtual int getTypeCode() { return 9; }
};

class EndOfSequenceRbsp : public NalUnit {
public:
    EndOfSequenceRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~EndOfSequenceRbsp();
    virtual QString getName() { return "END_OF_SEQUENCE_RBSP"; }
    virtual int getTypeCode() { return 10; }
};

class EndOfStreamRbsp : public NalUnit {
public:
    EndOfStreamRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~EndOfStreamRbsp();
    virtual QString getName() { return "END_OF_STREAM_RBSP"; }
    virtual int getTypeCode() { return 11; }
};

class FillerDataRbsp : public NalUnit {
public:
    FillerDataRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~FillerDataRbsp();
    virtual QString getName() { return "FILLER_DATA_RBSP"; }
    virtual int getTypeCode() { return 12; }
};

class SeqParameterSetExtensionRbsp : public NalUnit {
public:
    SeqParameterSetExtensionRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SeqParameterSetExtensionRbsp();
    virtual QString getName() { return "SEQ_PARAMETER_SET_EXTENSION_RBSP"; }
    virtual int getTypeCode() { return 13; }
};

class PrefixNalUnitRbsp : public SVCNalUnit {
public:
    PrefixNalUnitRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned int& SVCflag = 0, const unsigned int& idrFlag = 0,
                      const unsigned int& priorityId = 0, const unsigned int& noInterLayerPredFlag = 0, const unsigned int& dependencyId = 0, const unsigned int& qualityId = 0,
                      const unsigned int& temporaryId = 0, const unsigned int& useRefBasePicFlag = 0, const unsigned int& discardableFlag = 0, const unsigned int& outputFlag = 0,
                      const unsigned int& reservedThree2bits = 0);
    ~PrefixNalUnitRbsp();
    virtual QString getName() { return "PREFIX_NAL_UNIT_RBSP"; }
    virtual int getTypeCode() { return 14; }
    virtual QString getHeaderExtension();
    virtual QString getHeader() {
        return NalUnit::getHeader() + "\n" + getHeaderExtension();
    }
};

class SubsetSequenceParameterSetRbsp : public NalUnit {
public:
    SubsetSequenceParameterSetRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SubsetSequenceParameterSetRbsp();
    virtual QString getName() { return "SUBSET_SEQUENCE_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 15; }
};

class Reserved16 : public NalUnit {
public:
    Reserved16(const unsigned int&  nri, const unsigned long & offset);
    ~Reserved16();
    virtual QString getName() { return "RESERVED_16"; }
    virtual int getTypeCode() { return 16; }
};

class Reserved17 : public NalUnit {
public:
    Reserved17(const unsigned int&  nri, const unsigned long & offset);
    ~Reserved17();
    virtual QString getName() { return "RESERVED_17"; }
    virtual int getTypeCode() { return 17; }
};

class Reserved18 : public NalUnit {
public:
    Reserved18(const unsigned int&  nri, const unsigned long & offset);
    ~Reserved18();
    virtual QString getName() { return "RESERVED_18"; }
    virtual int getTypeCode() { return 18; }
};

class SliceLayerWithoutPartitioningRbsp : public NalUnit {
public:
    SliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & offset);
    ~SliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 19; }
};

class SliceLayerExtensionRbsp : public SVCNalUnit {
public:
    SliceLayerExtensionRbsp(const unsigned int&  nri, const unsigned long & offset, const unsigned int& SVCflag,
                            const unsigned int& idrFlag, const unsigned int&priorityId, const unsigned int&noInterLayerPredFlag,
                            const unsigned int&dependencyId, const unsigned int&qualityId, const unsigned int&temporaryId,
                            const unsigned int&useRefBasePicFlag, const unsigned int&discardableFlag, const unsigned int&outputFlag,
                            const unsigned int&rt2b);
    ~SliceLayerExtensionRbsp();
    virtual QString getName() { return "SLICE_LAYER_EXTENSION_RBSP"; }
    virtual int getTypeCode() { return 20; }
    virtual QString getHeaderExtension();
    virtual QString getHeader() {
        return NalUnit::getHeader() + "\n" + getHeaderExtension();
    }
};

class Reserved21 : public NalUnit {
public:
    Reserved21(const unsigned int&  nri, const unsigned long & offset);
    ~Reserved21();
    virtual QString getName() { return "RESERVED_21"; }
    virtual int getTypeCode() { return 21; }
};

class Reserved22 : public NalUnit {
public:
    Reserved22(const unsigned int&  nri, const unsigned long & offset);
    ~Reserved22();
    virtual QString getName() { return "RESERVED_22"; }
    virtual int getTypeCode() { return 22; }
};

class Reserved23 : public NalUnit {
public:
    Reserved23(const unsigned int&  nri, const unsigned long & offset);
    ~Reserved23();
    virtual QString getName() { return "RESERVED_23"; }
    virtual int getTypeCode() { return 23; }
};

class Unspecified24 : public NalUnit {
public:
    Unspecified24(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified24();
    virtual QString getName() { return "UNSPECIFIED_24"; }
    virtual int getTypeCode() { return 24; }
};

class Unspecified25 : public NalUnit {
public:
    Unspecified25(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified25();
    virtual QString getName() { return "UNSPECIFIED_25"; }
    virtual int getTypeCode() { return 25; }
};

class Unspecified26 : public NalUnit {
public:
    Unspecified26(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified26();
    virtual QString getName() { return "UNSPECIFIED_26"; }
    virtual int getTypeCode() { return 26; }
};

class Unspecified27 : public NalUnit {
public:
    Unspecified27(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified27();
    virtual QString getName() { return "UNSPECIFIED_27"; }
    virtual int getTypeCode() { return 27; }
};

class Unspecified28 : public NalUnit {
public:
    Unspecified28(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified28();
    virtual QString getName() { return "UNSPECIFIED_28"; }
    virtual int getTypeCode() { return 28; }
};

class Unspecified29 : public NalUnit {
public:
    Unspecified29(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified29();
    virtual QString getName() { return "UNSPECIFIED_29"; }
    virtual int getTypeCode() { return 29; }
};

class Unspecified30 : public NalUnit {
public:
    Unspecified30(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified30();
    virtual QString getName() { return "UNSPECIFIED_30"; }
    virtual int getTypeCode() { return 30; }
};

class Unspecified31 : public NalUnit {
public:
    Unspecified31(const unsigned int&  nri, const unsigned long & offset);
    ~Unspecified31();
    virtual QString getName() { return "UNSPECIFIED_31"; }
    virtual int getTypeCode() { return 31; }
};


#endif // NALUNIT_H
