#include "nalunit.h"

NalUnit::NalUnit(const unsigned int&  nri, const unsigned long & off) : nalRefIdc(nri), offset(off) {}

NalUnit::~NalUnit() {}

unsigned int ExtendedNalUnit::getSVCflag() const
{
    return SVCflag;
}

ExtendedNalUnit::ExtendedNalUnit(const unsigned int&  nri, const unsigned long & off, const unsigned int& rob) : NalUnit(nri, off),
    SVCflag(rob) {}

ExtendedNalUnit::~ExtendedNalUnit() {}

QString ExtendedNalUnit::getHeaderExtension() {
    return "SVC extension flag: " + QString::number(SVCflag);
}

unsigned int noInterLayerPredFlag;
unsigned int dependencyId;
unsigned int qualityId;
unsigned int temporaryId;
unsigned int useRefBasePicFlag;
unsigned int discardableFlag;
unsigned int outputFlag;
unsigned int reservedThree2bits;

unsigned int SVCNalUnit::getIdrFlag() const
{
    return idrFlag;
}

unsigned int SVCNalUnit::getNoInterLayerPredFlag() const
{
    return noInterLayerPredFlag;
}

unsigned int SVCNalUnit::getDependencyId() const
{
    return dependencyId;
}

unsigned int SVCNalUnit::getQualityId() const
{
    return qualityId;
}

unsigned int SVCNalUnit::getTemporaryId() const
{
    return temporaryId;
}

unsigned int SVCNalUnit::getUseRefBasePicFlag() const
{
    return useRefBasePicFlag;
}

unsigned int SVCNalUnit::getDiscardableFlag() const
{
    return discardableFlag;
}

unsigned int SVCNalUnit::getOutputFlag() const
{
    return outputFlag;
}

unsigned int SVCNalUnit::getReservedThree2bits() const
{
    return reservedThree2bits;
}

SVCNalUnit::SVCNalUnit(const unsigned int&  nri, const unsigned long & off, const unsigned int& rob, const unsigned int& idr,
                                     const unsigned int& pid, const unsigned int& nilp, const unsigned int& did, const unsigned int& qid,
                                     const unsigned int& tid, const unsigned int& urbp, const unsigned int& dis, const unsigned int&of,
                                     const unsigned int&rt2b) : ExtendedNalUnit(nri, off, rob), idrFlag(idr), priorityId(pid),
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

Unspecified::Unspecified(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified::~Unspecified() {}

NonIdrSliceLayerWithoutPartitioningRbsp::NonIdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & off, unsigned long fmis,
                                                                                 unsigned int st, unsigned long ppsi) : NalUnit(nri, off) ,
    firstMbInSlice(fmis), sliceType(st), pictureParameterSetId(ppsi) {}
NonIdrSliceLayerWithoutPartitioningRbsp::~NonIdrSliceLayerWithoutPartitioningRbsp() {}

QString NonIdrSliceLayerWithoutPartitioningRbsp::getInfo() {
    QString res("");
    res.append("FirstMbInSlice : " + QString::number(firstMbInSlice) + "\n");
    res.append("SliceType : " + QString::number(sliceType) + "\n");
    res.append("PictureParameterSetId : " + QString::number(pictureParameterSetId));
    return res;
}

SliceDataPartitionALayerRbsp::SliceDataPartitionALayerRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SliceDataPartitionALayerRbsp::~SliceDataPartitionALayerRbsp() {}

SliceDataPartitionBLayerRbsp::SliceDataPartitionBLayerRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SliceDataPartitionBLayerRbsp::~SliceDataPartitionBLayerRbsp() {}

SliceDataPartitionCLayerRbsp::SliceDataPartitionCLayerRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SliceDataPartitionCLayerRbsp::~SliceDataPartitionCLayerRbsp() {}

IdrSliceLayerWithoutPartitioningRbsp::IdrSliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & off, unsigned long fmis,
                                                                           unsigned int st, unsigned long ppsi) : NalUnit(nri, off) ,
    firstMbInSlice(fmis), sliceType(st), pictureParameterSetId(ppsi)  {}
IdrSliceLayerWithoutPartitioningRbsp::~IdrSliceLayerWithoutPartitioningRbsp() {}

QString IdrSliceLayerWithoutPartitioningRbsp::getInfo() {
    QString res("");
    res.append("FirstMbInSlice : " + QString::number(firstMbInSlice) + "\n");
    res.append("SliceType : " + QString::number(sliceType) + "\n");
    res.append("PictureParameterSetId : " + QString::number(pictureParameterSetId));
    return res;
}

SeiRbsp::SeiRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SeiRbsp::~SeiRbsp() {}

SeqParameterSetRbsp::SeqParameterSetRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SeqParameterSetRbsp::~SeqParameterSetRbsp() {}

PicParameterSetRbsp::PicParameterSetRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
PicParameterSetRbsp::~PicParameterSetRbsp() {}

AccessUnitDelimiterRbsp::AccessUnitDelimiterRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
AccessUnitDelimiterRbsp::~AccessUnitDelimiterRbsp() {}

EndOfSequenceRbsp::EndOfSequenceRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
EndOfSequenceRbsp::~EndOfSequenceRbsp() {}

EndOfStreamRbsp::EndOfStreamRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
EndOfStreamRbsp::~EndOfStreamRbsp() {}

FillerDataRbsp::FillerDataRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
FillerDataRbsp::~FillerDataRbsp() {}

SeqParameterSetExtensionRbsp::SeqParameterSetExtensionRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SeqParameterSetExtensionRbsp::~SeqParameterSetExtensionRbsp() {}

PrefixNalUnitRbsp::PrefixNalUnitRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned int& rob, const unsigned int& idr,
                                     const unsigned int& pid, const unsigned int& nilp, const unsigned int& did, const unsigned int& qid,
                                     const unsigned int& tid, const unsigned int& urbp, const unsigned int& dis, const unsigned int&of,
                                     const unsigned int&rt2b) : SVCNalUnit(nri, off, rob, idr, pid, nilp, did, qid, tid, urbp,
                                                                                                   dis, of, rt2b) {}
PrefixNalUnitRbsp::~PrefixNalUnitRbsp() {}

QString PrefixNalUnitRbsp::getHeaderExtension() {
    return ExtendedNalUnit::getHeaderExtension() + "\nIDR flag: " + QString::number(idrFlag) +
            "\nPriority ID: " + QString::number(priorityId) + "\nNo Inter Layer Prediction Flag: " + QString::number(noInterLayerPredFlag) +
            "\nDependency ID: " + QString::number(dependencyId) + "\nQuality ID: " + QString::number(qualityId) +
            "\nTemporary ID: " + QString::number(temporaryId) + "\nUse Ref Base Picture Flag: " + QString::number(useRefBasePicFlag)
            + "\nDiscardable Flag: " + QString::number(discardableFlag) + "\nReserved three 2 bits: " + QString::number(reservedThree2bits);
}

SubsetSequenceParameterSetRbsp::SubsetSequenceParameterSetRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SubsetSequenceParameterSetRbsp::~SubsetSequenceParameterSetRbsp() {}

Reserved16::Reserved16(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Reserved16::~Reserved16() {}

Reserved17::Reserved17(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Reserved17::~Reserved17() {}

Reserved18::Reserved18(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Reserved18::~Reserved18() {}

SliceLayerWithoutPartitioningRbsp::SliceLayerWithoutPartitioningRbsp(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
SliceLayerWithoutPartitioningRbsp::~SliceLayerWithoutPartitioningRbsp() {}

SliceLayerExtensionRbsp::SliceLayerExtensionRbsp(const unsigned int&  nri, const unsigned long & off, const unsigned int& rob, const unsigned int& idr,
                                                 const unsigned int& pid, const unsigned int& nilp, const unsigned int& did, const unsigned int& qid,
                                                 const unsigned int& tid, const unsigned int& urbp, const unsigned int& dis, const unsigned int&of,
                                                 const unsigned int&rt2b) : SVCNalUnit(nri, off, rob, idr, pid, nilp, did, qid, tid, urbp,
                                                                                                               dis, of, rt2b) {}
SliceLayerExtensionRbsp::~SliceLayerExtensionRbsp() {}

QString SliceLayerExtensionRbsp::getHeaderExtension() {
    return ExtendedNalUnit::getHeaderExtension() + "\nIDR flag: " + QString::number(idrFlag) +
            "\nPriority ID: " + QString::number(priorityId) + "\nNo Inter Layer Prediction Flag: " + QString::number(noInterLayerPredFlag) +
            "\nDependency ID: " + QString::number(dependencyId) + "\nQuality ID: " + QString::number(qualityId) +
            "\nTemporary ID: " + QString::number(temporaryId) + "\nUse Ref Base Picture Flag: " + QString::number(useRefBasePicFlag)
            + "\nDiscardable Flag: " + QString::number(discardableFlag) + "\nReserved three 2 bits: " + QString::number(reservedThree2bits);
}

Reserved21::Reserved21(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Reserved21::~Reserved21() {}

Reserved22::Reserved22(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Reserved22::~Reserved22() {}

Reserved23::Reserved23(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Reserved23::~Reserved23() {}

Unspecified24::Unspecified24(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified24::~Unspecified24() {}

Unspecified25::Unspecified25(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified25::~Unspecified25() {}

Unspecified26::Unspecified26(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified26::~Unspecified26() {}

Unspecified27::Unspecified27(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified27::~Unspecified27() {}

Unspecified28::Unspecified28(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified28::~Unspecified28() {}

Unspecified29::Unspecified29(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified29::~Unspecified29() {}

Unspecified30::Unspecified30(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified30::~Unspecified30() {}

Unspecified31::Unspecified31(const unsigned int&  nri, const unsigned long & off) : NalUnit(nri, off) {}
Unspecified31::~Unspecified31() {}
