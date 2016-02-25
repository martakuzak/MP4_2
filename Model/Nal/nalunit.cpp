#include "nalunit.h"

NalUnit::NalUnit(const unsigned int&  nri, const unsigned long & off, const unsigned short &sl) : nalRefIdc(nri), offset(off), startLength(sl) {}

NalUnit::~NalUnit() {}

unsigned int ExtendedNalUnit::getSVCflag() const {
    return SVCflag;
}

ExtendedNalUnit::ExtendedNalUnit(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl, const unsigned int& rob) :
    NalUnit(nri, off, sl), SVCflag(rob) {}

ExtendedNalUnit::~ExtendedNalUnit() {}

QString ExtendedNalUnit::getHeaderExtension() {
    return "SVC extension flag: " + QString::number(SVCflag);
}

unsigned int SVCNalUnit::getIdrFlag() const {
    return idrFlag;
}

unsigned int SVCNalUnit::getNoInterLayerPredFlag() const {
    return noInterLayerPredFlag;
}

unsigned int SVCNalUnit::getDependencyId() const {
    return dependencyId;
}

unsigned int SVCNalUnit::getQualityId() const {
    return qualityId;
}

unsigned int SVCNalUnit::getTemporaryId() const {
    return temporaryId;
}

unsigned int SVCNalUnit::getUseRefBasePicFlag() const {
    return useRefBasePicFlag;
}

unsigned int SVCNalUnit::getDiscardableFlag() const {
    return discardableFlag;
}

unsigned int SVCNalUnit::getOutputFlag() const {
    return outputFlag;
}

unsigned int SVCNalUnit::getReservedThree2bits() const {
    return reservedThree2bits;
}

SVCNalUnit::SVCNalUnit(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl, const unsigned int& rob,
                       const unsigned int& idr,const unsigned int& pid, const unsigned int& nilp, const unsigned int& did,
                       const unsigned int& qid, const unsigned int& tid, const unsigned int& urbp, const unsigned int& dis,
                       const unsigned int&of, const unsigned int&rt2b) : ExtendedNalUnit(nri, off, sl, rob), idrFlag(idr), priorityId(pid),
    noInterLayerPredFlag(nilp), dependencyId(did), qualityId(qid), temporaryId(tid), useRefBasePicFlag(urbp), discardableFlag(dis),
    outputFlag(of), reservedThree2bits(rt2b){}
SVCNalUnit::~SVCNalUnit() {}

QString SVCNalUnit::getHeaderExtension() {
    return SVCNalUnit::getHeaderExtension() + "\nIDR flag: " + QString::number(idrFlag) +
            "\nPriority ID: " + QString::number(priorityId) + "\nNo Inter Layer Prediction Flag: " + QString::number(noInterLayerPredFlag) +
            "\nDependency ID: " + QString::number(dependencyId) + "\nQuality ID: " + QString::number(qualityId) +
            "\nTemporary ID: " + QString::number(temporaryId) + "\nUse Ref Base Picture Flag: " + QString::number(useRefBasePicFlag)
            + "\nDiscardable Flag: " + QString::number(discardableFlag) + "\nReserved three 2 bits: " + QString::number(reservedThree2bits);
}

Unspecified::Unspecified(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified::~Unspecified() {}

NonIdrSliceLayerWithoutPartitioningRbsp::NonIdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & off,
                                                                                 const unsigned short & sl, unsigned long fmis,
                                                                                 unsigned int st, unsigned long ppsi) :
    NalUnit(nri, off, sl), firstMbInSlice(fmis), sliceType(st), pictureParameterSetId(ppsi) {}
NonIdrSliceLayerWithoutPartitioningRbsp::~NonIdrSliceLayerWithoutPartitioningRbsp() {}

QString NonIdrSliceLayerWithoutPartitioningRbsp::getInfo() {
    QString res("");
    res.append("FirstMbInSlice : " + QString::number(firstMbInSlice) + "\n");
    res.append("SliceType : " + QString::number(sliceType) + "\n");
    res.append("PictureParameterSetId : " + QString::number(pictureParameterSetId));
    return res;
}

SliceDataPartitionALayerRbsp::SliceDataPartitionALayerRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) :
    NalUnit(nri, off, sl) {}
SliceDataPartitionALayerRbsp::~SliceDataPartitionALayerRbsp() {}

SliceDataPartitionBLayerRbsp::SliceDataPartitionBLayerRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) :
    NalUnit(nri, off, sl) {}
SliceDataPartitionBLayerRbsp::~SliceDataPartitionBLayerRbsp() {}

SliceDataPartitionCLayerRbsp::SliceDataPartitionCLayerRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) :
    NalUnit(nri, off, sl) {}
SliceDataPartitionCLayerRbsp::~SliceDataPartitionCLayerRbsp() {}

IdrSliceLayerWithoutPartitioningRbsp::IdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & off,
                                                                           const unsigned short & sl, unsigned long fmis,
                                                                           unsigned int st, unsigned long ppsi) : NalUnit(nri, off, sl) ,
    firstMbInSlice(fmis), sliceType(st), pictureParameterSetId(ppsi)  {}
IdrSliceLayerWithoutPartitioningRbsp::~IdrSliceLayerWithoutPartitioningRbsp() {}

QString IdrSliceLayerWithoutPartitioningRbsp::getInfo() {
    QString res("");
    res.append("FirstMbInSlice : " + QString::number(firstMbInSlice) + "\n");
    res.append("SliceType : " + QString::number(sliceType) + "\n");
    res.append("PictureParameterSetId : " + QString::number(pictureParameterSetId));
    return res;
}

SeiRbsp::SeiRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
SeiRbsp::~SeiRbsp() {}

SeqParameterSetRbsp::SeqParameterSetRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl,
                                         const unsigned short &pidc, const bool &f0, const bool &f1, const bool &f2, const bool &f3,
                                         const bool &f4, const bool &f5, const unsigned short &lidc, const unsigned int &spsid) :
    NalUnit(nri, off, sl), profileIdc(pidc), constraintSet0Flag(f0), constraintSet1Flag(f1), constraintSet2Flag(f2),
    constraintSet3Flag(f3), constraintSet4Flag(f4), constraintSet5Flag(f5), levelIdc(lidc), seqParSetId(spsid) {}
SeqParameterSetRbsp::~SeqParameterSetRbsp() {}

QString SeqParameterSetRbsp::getInfo() {
    return "Profile_idc = " + QString::number(profileIdc) + "\nConstraint_set0_flag = " +
            QString::number(constraintSet0Flag) + "\nConstraint_set1_flag = " +
            QString::number(constraintSet1Flag) +"\nConstraint_set2_flag = " +
            QString::number(constraintSet2Flag) +"\nConstraint_set3_flag = " +
            QString::number(constraintSet3Flag) +"\nConstraint_set4_flag = " +
            QString::number(constraintSet4Flag) +"\nConstraint_set5_flag = " +
            QString::number(constraintSet5Flag) + "\nLevel_idc = " + QString::number(levelIdc) +
            "\nSeq_par_set_id = " + QString::number(seqParSetId);
}


unsigned short SeqParameterSetRbsp::getProfileIdc() const {
    return profileIdc;
}

bool SeqParameterSetRbsp::getConstraintSet0Flag() const {
    return constraintSet0Flag;
}

bool SeqParameterSetRbsp::getConstraintSet1Flag() const {
    return constraintSet1Flag;
}

bool SeqParameterSetRbsp::getConstraintSet2Flag() const {
    return constraintSet2Flag;
}

bool SeqParameterSetRbsp::getConstraintSet3Flag() const {
    return constraintSet3Flag;
}

bool SeqParameterSetRbsp::getConstraintSet4Flag() const {
    return constraintSet4Flag;
}

bool SeqParameterSetRbsp::getConstraintSet5Flag() const {
    return constraintSet5Flag;
}

unsigned short SeqParameterSetRbsp::getLevelIdc() const {
    return levelIdc;
}

unsigned int SeqParameterSetRbsp::getSeqParSetId() const {
    return seqParSetId;
}

PicParameterSetRbsp::PicParameterSetRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl,
                                         const unsigned int &pid, const unsigned int &sid) : NalUnit(nri, off, sl),
    ppsId(pid), spsId(sid){}
PicParameterSetRbsp::~PicParameterSetRbsp() {}

unsigned int PicParameterSetRbsp::getPpsId() const {
    return ppsId;
}

unsigned int PicParameterSetRbsp::getSpsId() const {
    return spsId;
}

QString PicParameterSetRbsp::getInfo() {
    return "Picture_parameter_set_id = " + QString::number(ppsId) + "\nSequence_parameter_set_id = " +
            QString::number(spsId);
}

AccessUnitDelimiterRbsp::AccessUnitDelimiterRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) :
    NalUnit(nri, off, sl) {}
AccessUnitDelimiterRbsp::~AccessUnitDelimiterRbsp() {}

EndOfSequenceRbsp::EndOfSequenceRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
EndOfSequenceRbsp::~EndOfSequenceRbsp() {}

EndOfStreamRbsp::EndOfStreamRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
EndOfStreamRbsp::~EndOfStreamRbsp() {}

FillerDataRbsp::FillerDataRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
FillerDataRbsp::~FillerDataRbsp() {}

SeqParameterSetExtensionRbsp::SeqParameterSetExtensionRbsp(const unsigned int&  nri, const unsigned long & off,
                                                           const unsigned short & sl) : NalUnit(nri, off, sl) {}
SeqParameterSetExtensionRbsp::~SeqParameterSetExtensionRbsp() {}

PrefixNalUnitRbsp::PrefixNalUnitRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl, const unsigned int& rob,
                                     const unsigned int& idr, const unsigned int& pid, const unsigned int& nilp, const unsigned int& did,
                                     const unsigned int& qid, const unsigned int& tid, const unsigned int& urbp, const unsigned int& dis,
                                     const unsigned int&of, const unsigned int&rt2b) :
    SVCNalUnit(nri, off, sl, rob, idr, pid, nilp, did, qid, tid, urbp, dis, of, rt2b) {}
PrefixNalUnitRbsp::~PrefixNalUnitRbsp() {}

QString PrefixNalUnitRbsp::getHeaderExtension() {
    return ExtendedNalUnit::getHeaderExtension() + "\nIDR flag: " + QString::number(idrFlag) +
            "\nPriority ID: " + QString::number(priorityId) + "\nNo Inter Layer Prediction Flag: " + QString::number(noInterLayerPredFlag) +
            "\nDependency ID: " + QString::number(dependencyId) + "\nQuality ID: " + QString::number(qualityId) +
            "\nTemporary ID: " + QString::number(temporaryId) + "\nUse Ref Base Picture Flag: " + QString::number(useRefBasePicFlag)
            + "\nDiscardable Flag: " + QString::number(discardableFlag) + "\nReserved three 2 bits: " + QString::number(reservedThree2bits);
}

SubsetSequenceParameterSetRbsp::SubsetSequenceParameterSetRbsp(const unsigned int&  nri, const unsigned long & off,
                                                               const unsigned short & sl) :
    NalUnit(nri, off, sl){}
SubsetSequenceParameterSetRbsp::~SubsetSequenceParameterSetRbsp() {}

Reserved16::Reserved16(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Reserved16::~Reserved16() {}

Reserved17::Reserved17(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Reserved17::~Reserved17() {}

Reserved18::Reserved18(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Reserved18::~Reserved18() {}

SliceLayerWithoutPartitioningRbsp::SliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & off,
                                                                     const unsigned short & sl) : NalUnit(nri, off, sl) {}
SliceLayerWithoutPartitioningRbsp::~SliceLayerWithoutPartitioningRbsp() {}

SliceLayerExtensionRbsp::SliceLayerExtensionRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl,
                                                 const unsigned int& rob, const unsigned int& idr, const unsigned int& pid,
                                                 const unsigned int& nilp, const unsigned int& did, const unsigned int& qid,
                                                 const unsigned int& tid, const unsigned int& urbp, const unsigned int& dis,
                                                 const unsigned int&of, const unsigned int&rt2b) :
    SVCNalUnit(nri, off, sl, rob, idr, pid, nilp, did, qid, tid, urbp, dis, of, rt2b) {}
SliceLayerExtensionRbsp::~SliceLayerExtensionRbsp() {}

QString SliceLayerExtensionRbsp::getHeaderExtension() {
    return ExtendedNalUnit::getHeaderExtension() + "\nIDR flag: " + QString::number(idrFlag) +
            "\nPriority ID: " + QString::number(priorityId) + "\nNo Inter Layer Prediction Flag: " + QString::number(noInterLayerPredFlag) +
            "\nDependency ID: " + QString::number(dependencyId) + "\nQuality ID: " + QString::number(qualityId) +
            "\nTemporary ID: " + QString::number(temporaryId) + "\nUse Ref Base Picture Flag: " + QString::number(useRefBasePicFlag)
            + "\nDiscardable Flag: " + QString::number(discardableFlag) + "\nReserved three 2 bits: " + QString::number(reservedThree2bits);
}

Reserved21::Reserved21(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Reserved21::~Reserved21() {}

Reserved22::Reserved22(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Reserved22::~Reserved22() {}

Reserved23::Reserved23(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Reserved23::~Reserved23() {}

Unspecified24::Unspecified24(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified24::~Unspecified24() {}

Unspecified25::Unspecified25(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified25::~Unspecified25() {}

Unspecified26::Unspecified26(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified26::~Unspecified26() {}

Unspecified27::Unspecified27(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified27::~Unspecified27() {}

Unspecified28::Unspecified28(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified28::~Unspecified28() {}

Unspecified29::Unspecified29(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified29::~Unspecified29() {}

Unspecified30::Unspecified30(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified30::~Unspecified30() {}

Unspecified31::Unspecified31(const unsigned int&  nri, const unsigned long & off, const unsigned short & sl) : NalUnit(nri, off, sl) {}
Unspecified31::~Unspecified31() {}
