#ifndef NALUNIT_H
#define NALUNIT_H

#include <QString>

/*!
 * \brief The NalUnit class NAL unit representation
 */
class NalUnit {
protected:
    unsigned int nalRefIdc;
    unsigned long offset;
    unsigned long length;
    /*!
     * \brief startLength length in bytes of the start code before NAL (it may be either 0x000001 or 0x00000001)
     */
    unsigned short startLength;
public:
    /*!
     * \brief NalUnit
     * \param nri NAL reference indicator
     * \param off offset in bytes in the file
     * \param sl start code length (it should be either 3 or 4)
     */
    NalUnit(const unsigned int&  nri = 0, const unsigned long & off = 0, const unsigned short & sl = 3);
    ~NalUnit();
    /*!
     * \brief setLength sets length of NAL unit
     * \param endOfNal the last byte index in the file
     * \return
     */
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
    virtual unsigned short getStartCodeLength() { return startLength; }
    /*!
     * \brief getName
     * \return name of the NAL unit regarding its type
     */
    virtual QString getName() { return "NAL Unit"; }
    /*!
     * \brief getTypeCode
     * \return integer value of NAL unit type
     */
    virtual int getTypeCode() { return -1; }
    /*!
     * \brief getInfo
     * \return string value of parameters of NAL unit (without header)
     */
    virtual QString getInfo() { return ""; }
    /*!
     * \brief getHeader
     * \return string value of NAL unit header
     */
    virtual QString getHeader() { return "NalRefIdc: " + QString::number(nalRefIdc);}
};

/*!
 * \brief The ExtendedNalUnit class NAL unit that has extended header
 */
class ExtendedNalUnit : public NalUnit {
protected:
    /*!
     * \brief SVCflag indicater whether the extended NAL unit refers to SVC or not
     */
    unsigned int SVCflag;
public:
    /*!
     * \brief ExtendedNalUnit
     * \param nri NAL reference indicator
     * \param off offset in bytes in the file
     * \param sl start code length (it should be either 3 or 4)
     * \param svcFlag indicater whether the extended NAL unit refers to SVC or not
     */
    ExtendedNalUnit(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3,
                    const unsigned int& svcFlag = 0);
    ~ExtendedNalUnit();
    virtual QString getName() { return "Extended NAL Unit"; }
    virtual int getTypeCode() { return -1; }
    virtual QString getHeaderExtension();
    virtual QString getHeader() {
        return NalUnit::getHeader() + "\n" + getHeaderExtension();
    }
    unsigned int getSVCflag() const;
};

/*!
 * \brief The SVCNalUnit class NAL unit of type 14 or 20
 */
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
    SVCNalUnit(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3, const unsigned int& SVCflag = 0,
               const unsigned int& idrFlag = 0, const unsigned int& priorityId = 0, const unsigned int& noInterLayerPredFlag = 0,
               const unsigned int& dependencyId = 0, const unsigned int& qualityId = 0, const unsigned int& temporaryId = 0,
               const unsigned int& useRefBasePicFlag = 0, const unsigned int& discardableFlag = 0, const unsigned int& outputFlag = 0,
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

/*!
 * \brief The Unspecified class
 */
class Unspecified : public NalUnit {
public:
    Unspecified(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified();
    virtual QString getName() { return "UNSPECIFIED_"; }
    virtual int getTypeCode() { return 0; }
};

/*!
 * \brief The NonIdrSliceLayerWithoutPartitioningRbsp class
 */
class NonIdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
protected:
    unsigned long firstMbInSlice;
    unsigned int sliceType;
    unsigned long pictureParameterSetId;
public:
    NonIdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3,
                                            unsigned long fmis = 0, unsigned int st = 0, unsigned long ppsi = 0);
    ~NonIdrSliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 1; }
    virtual QString getInfo();
};

/*!
 * \brief The SliceDataPartitionALayerRbsp class
 */
class SliceDataPartitionALayerRbsp : public NalUnit {
public:
    SliceDataPartitionALayerRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SliceDataPartitionALayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_A_LAYER_RBSP"; }
    virtual int getTypeCode() { return 2; }
};

/*!
 * \brief The SliceDataPartitionBLayerRbsp class
 */
class SliceDataPartitionBLayerRbsp : public NalUnit {
public:
    SliceDataPartitionBLayerRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SliceDataPartitionBLayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_B_LAYER_RBSP"; }
    virtual int getTypeCode() { return 3; }
};

/*!
 * \brief The SliceDataPartitionCLayerRbsp class
 */
class SliceDataPartitionCLayerRbsp : public NalUnit {
public:
    SliceDataPartitionCLayerRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SliceDataPartitionCLayerRbsp();
    virtual QString getName() { return "SLICE_DATA_PARTITION_C_LAYER_RBSP"; }
    virtual int getTypeCode() { return 4; }
};

/*!
 * \brief The IdrSliceLayerWithoutPartitioningRbsp class
 */
class IdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
protected:
    unsigned long firstMbInSlice;
    unsigned int sliceType;
    unsigned long pictureParameterSetId;
public:
    IdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3,
                                         unsigned long fmis = 0, unsigned int st = 0, unsigned long ppsi = 0);
    ~IdrSliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 5; }
    virtual QString getInfo();
};

/*!
 * \brief The SeiRbsp class
 */
class SeiRbsp : public NalUnit {
public:
    SeiRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SeiRbsp();
    virtual QString getName() { return "SEI RBSP"; }
    virtual int getTypeCode() { return 6; }
};

/*!
 * \brief The SeqParameterSetRbsp class
 */
class SeqParameterSetRbsp : public NalUnit {
public:
    SeqParameterSetRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SeqParameterSetRbsp();
    virtual QString getName() { return "SEQ_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 7; }
};

/*!
 * \brief The PicParameterSetRbsp class
 */
class PicParameterSetRbsp : public NalUnit {
public:
    PicParameterSetRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~PicParameterSetRbsp();
    virtual QString getName() { return "PIC_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 8; }
};

/*!
 * \brief The AccessUnitDelimiterRbsp class
 */
class AccessUnitDelimiterRbsp : public NalUnit {
public:
    AccessUnitDelimiterRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~AccessUnitDelimiterRbsp();
    virtual QString getName() { return "ACCESS_UNIT_DELIMITER_RBSP"; }
    virtual int getTypeCode() { return 9; }
};

/*!
 * \brief The EndOfSequenceRbsp class
 */
class EndOfSequenceRbsp : public NalUnit {
public:
    EndOfSequenceRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~EndOfSequenceRbsp();
    virtual QString getName() { return "END_OF_SEQUENCE_RBSP"; }
    virtual int getTypeCode() { return 10; }
};

/*!
 * \brief The EndOfStreamRbsp class
 */
class EndOfStreamRbsp : public NalUnit {
public:
    EndOfStreamRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~EndOfStreamRbsp();
    virtual QString getName() { return "END_OF_STREAM_RBSP"; }
    virtual int getTypeCode() { return 11; }
};

/*!
 * \brief The FillerDataRbsp class
 */
class FillerDataRbsp : public NalUnit {
public:
    FillerDataRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~FillerDataRbsp();
    virtual QString getName() { return "FILLER_DATA_RBSP"; }
    virtual int getTypeCode() { return 12; }
};

/*!
 * \brief The SeqParameterSetExtensionRbsp class
 */
class SeqParameterSetExtensionRbsp : public NalUnit {
public:
    SeqParameterSetExtensionRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SeqParameterSetExtensionRbsp();
    virtual QString getName() { return "SEQ_PARAMETER_SET_EXTENSION_RBSP"; }
    virtual int getTypeCode() { return 13; }
};

/*!
 * \brief The PrefixNalUnitRbsp class
 */
class PrefixNalUnitRbsp : public SVCNalUnit {
public:
    PrefixNalUnitRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3, const unsigned int& SVCflag = 0,
                      const unsigned int& idrFlag = 0, const unsigned int& priorityId = 0, const unsigned int& noInterLayerPredFlag = 0,
                      const unsigned int& dependencyId = 0, const unsigned int& qualityId = 0, const unsigned int& temporaryId = 0,
                      const unsigned int& useRefBasePicFlag = 0, const unsigned int& discardableFlag = 0, const unsigned int& outputFlag = 0,
                      const unsigned int& reservedThree2bits = 0);
    ~PrefixNalUnitRbsp();
    virtual QString getName() { return "PREFIX_NAL_UNIT_RBSP"; }
    virtual int getTypeCode() { return 14; }
    virtual QString getHeaderExtension();
    virtual QString getHeader() {
        return NalUnit::getHeader() + "\n" + getHeaderExtension();
    }
};

/*!
 * \brief The SubsetSequenceParameterSetRbsp class
 */
class SubsetSequenceParameterSetRbsp : public NalUnit {
public:
    SubsetSequenceParameterSetRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SubsetSequenceParameterSetRbsp();
    virtual QString getName() { return "SUBSET_SEQUENCE_PARAMETER_SET_RBSP"; }
    virtual int getTypeCode() { return 15; }
};

/*!
 * \brief The Reserved16 class
 */
class Reserved16 : public NalUnit {
public:
    Reserved16(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Reserved16();
    virtual QString getName() { return "RESERVED_16"; }
    virtual int getTypeCode() { return 16; }
};

/*!
 * \brief The Reserved17 class
 */
class Reserved17 : public NalUnit {
public:
    Reserved17(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Reserved17();
    virtual QString getName() { return "RESERVED_17"; }
    virtual int getTypeCode() { return 17; }
};

/*!
 * \brief The Reserved18 class
 */
class Reserved18 : public NalUnit {
public:
    Reserved18(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Reserved18();
    virtual QString getName() { return "RESERVED_18"; }
    virtual int getTypeCode() { return 18; }
};

/*!
 * \brief The SliceLayerWithoutPartitioningRbsp class
 */
class SliceLayerWithoutPartitioningRbsp : public NalUnit {
public:
    SliceLayerWithoutPartitioningRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~SliceLayerWithoutPartitioningRbsp();
    virtual QString getName() { return "SLICE_LAYER_WITHOUT_PARTITIONING_RBSP"; }
    virtual int getTypeCode() { return 19; }
};

/*!
 * \brief The SliceLayerExtensionRbsp class
 */
class SliceLayerExtensionRbsp : public SVCNalUnit {
public:
    SliceLayerExtensionRbsp(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3,
                            const unsigned int& SVCflag = 1, const unsigned int& idrFlag = 0, const unsigned int&priorityId = 0,
                            const unsigned int&noInterLayerPredFlag = 0, const unsigned int&dependencyId = 0, const unsigned int&qualityId = 0,
                            const unsigned int&temporaryId = 0, const unsigned int&useRefBasePicFlag = 0, const unsigned int&discardableFlag = 0,
                            const unsigned int&outputFlag = 0, const unsigned int&rt2b = 0);
    ~SliceLayerExtensionRbsp();
    virtual QString getName() { return "SLICE_LAYER_EXTENSION_RBSP"; }
    virtual int getTypeCode() { return 20; }
    virtual QString getHeaderExtension();
    virtual QString getHeader() {
        return NalUnit::getHeader() + "\n" + getHeaderExtension();
    }
};

/*!
 * \brief The Reserved21 class
 */
class Reserved21 : public NalUnit {
public:
    Reserved21(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Reserved21();
    virtual QString getName() { return "RESERVED_21"; }
    virtual int getTypeCode() { return 21; }
};

/*!
 * \brief The Reserved22 class
 */
class Reserved22 : public NalUnit {
public:
    Reserved22(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Reserved22();
    virtual QString getName() { return "RESERVED_22"; }
    virtual int getTypeCode() { return 22; }
};

/*!
 * \brief The Reserved23 class
 */
class Reserved23 : public NalUnit {
public:
    Reserved23(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Reserved23();
    virtual QString getName() { return "RESERVED_23"; }
    virtual int getTypeCode() { return 23; }
};

/*!
 * \brief The Unspecified24 class
 */
class Unspecified24 : public NalUnit {
public:
    Unspecified24(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified24();
    virtual QString getName() { return "UNSPECIFIED_24"; }
    virtual int getTypeCode() { return 24; }
};

/*!
 * \brief The Unspecified25 class
 */
class Unspecified25 : public NalUnit {
public:
    Unspecified25(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified25();
    virtual QString getName() { return "UNSPECIFIED_25"; }
    virtual int getTypeCode() { return 25; }
};

/*!
 * \brief The Unspecified26 class
 */
class Unspecified26 : public NalUnit {
public:
    Unspecified26(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified26();
    virtual QString getName() { return "UNSPECIFIED_26"; }
    virtual int getTypeCode() { return 26; }
};

/*!
 * \brief The Unspecified27 class
 */
class Unspecified27 : public NalUnit {
public:
    Unspecified27(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified27();
    virtual QString getName() { return "UNSPECIFIED_27"; }
    virtual int getTypeCode() { return 27; }
};

/*!
 * \brief The Unspecified28 class
 */
class Unspecified28 : public NalUnit {
public:
    Unspecified28(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified28();
    virtual QString getName() { return "UNSPECIFIED_28"; }
    virtual int getTypeCode() { return 28; }
};

/*!
 * \brief The Unspecified29 class
 */
class Unspecified29 : public NalUnit {
public:
    Unspecified29(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified29();
    virtual QString getName() { return "UNSPECIFIED_29"; }
    virtual int getTypeCode() { return 29; }
};

/*!
 * \brief The Unspecified30 class
 */
class Unspecified30 : public NalUnit {
public:
    Unspecified30(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified30();
    virtual QString getName() { return "UNSPECIFIED_30"; }
    virtual int getTypeCode() { return 30; }
};

/*!
 * \brief The Unspecified31 class
 */
class Unspecified31 : public NalUnit {
public:
    Unspecified31(const unsigned int&  nri = 0, const unsigned long & offset = 0, const unsigned short & sl = 3);
    ~Unspecified31();
    virtual QString getName() { return "UNSPECIFIED_31"; }
    virtual int getTypeCode() { return 31; }
};

#endif // NALUNIT_H
