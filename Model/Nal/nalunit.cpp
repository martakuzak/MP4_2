#include "nalunit.h"

NalUnit::NalUnit(unsigned int nri, unsigned long off) : nalRefIdc(nri), offset(off) {

}

NalUnit::~NalUnit() {

}

Unspecified::Unspecified(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified::~Unspecified() {}

NonIdrSliceLayerWithoutPartitioningRbsp::NonIdrSliceLayerWithoutPartitioningRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
NonIdrSliceLayerWithoutPartitioningRbsp::~NonIdrSliceLayerWithoutPartitioningRbsp() {}

SliceDataPartitionALayerRbsp::SliceDataPartitionALayerRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SliceDataPartitionALayerRbsp::~SliceDataPartitionALayerRbsp() {}

SliceDataPartitionBLayerRbsp::SliceDataPartitionBLayerRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SliceDataPartitionBLayerRbsp::~SliceDataPartitionBLayerRbsp() {}

SliceDataPartitionCLayerRbsp::SliceDataPartitionCLayerRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SliceDataPartitionCLayerRbsp::~SliceDataPartitionCLayerRbsp() {}

IdrSliceLayerWithoutPartitioningRbsp::IdrSliceLayerWithoutPartitioningRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
IdrSliceLayerWithoutPartitioningRbsp::~IdrSliceLayerWithoutPartitioningRbsp() {}

SeiRbsp::SeiRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SeiRbsp::~SeiRbsp() {}

SeqParameterSetRbsp::SeqParameterSetRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SeqParameterSetRbsp::~SeqParameterSetRbsp() {}

PicParameterSetRbsp::PicParameterSetRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
PicParameterSetRbsp::~PicParameterSetRbsp() {}

AccessUnitDelimiterRbsp::AccessUnitDelimiterRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
AccessUnitDelimiterRbsp::~AccessUnitDelimiterRbsp() {}

EndOfSequenceRbsp::EndOfSequenceRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
EndOfSequenceRbsp::~EndOfSequenceRbsp() {}

EndOfStreamRbsp::EndOfStreamRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
EndOfStreamRbsp::~EndOfStreamRbsp() {}

FillerDataRbsp::FillerDataRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
FillerDataRbsp::~FillerDataRbsp() {}

SeqParameterSetExtensionRbsp::SeqParameterSetExtensionRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SeqParameterSetExtensionRbsp::~SeqParameterSetExtensionRbsp() {}

PrefixNalUnitRbsp::PrefixNalUnitRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
PrefixNalUnitRbsp::~PrefixNalUnitRbsp() {}

SubsetSequenceParameterSetRbsp::SubsetSequenceParameterSetRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SubsetSequenceParameterSetRbsp::~SubsetSequenceParameterSetRbsp() {}

Reserved16::Reserved16(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Reserved16::~Reserved16() {}

Reserved17::Reserved17(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Reserved17::~Reserved17() {}

Reserved18::Reserved18(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Reserved18::~Reserved18() {}

SliceLayerWithoutPartitioningRbsp::SliceLayerWithoutPartitioningRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SliceLayerWithoutPartitioningRbsp::~SliceLayerWithoutPartitioningRbsp() {}

SliceLayerExtensionRbsp::SliceLayerExtensionRbsp(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
SliceLayerExtensionRbsp::~SliceLayerExtensionRbsp() {}

Reserved21::Reserved21(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Reserved21::~Reserved21() {}

Reserved22::Reserved22(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Reserved22::~Reserved22() {}

Reserved23::Reserved23(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Reserved23::~Reserved23() {}

Unspecified24::Unspecified24(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified24::~Unspecified24() {}

Unspecified25::Unspecified25(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified25::~Unspecified25() {}

Unspecified26::Unspecified26(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified26::~Unspecified26() {}

Unspecified27::Unspecified27(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified27::~Unspecified27() {}

Unspecified28::Unspecified28(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified28::~Unspecified28() {}

Unspecified29::Unspecified29(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified29::~Unspecified29() {}

Unspecified30::Unspecified30(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified30::~Unspecified30() {}

Unspecified31::Unspecified31(unsigned int nri, unsigned long off) : NalUnit(nri, off) {}
Unspecified31::~Unspecified31() {}
