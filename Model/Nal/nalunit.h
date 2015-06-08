#ifndef NALUNIT_H
#define NALUNIT_H

#include <QString>

class NalUnit {
public:
    NalUnit();
    ~NalUnit();
    QString getName() { return "NAL Unit"; }
    int getTypeCode() { return -1; }
};


class Unspecified : public NalUnit {
public:
    Unspecified();
    ~Unspecified();
    QString getName() { return "Unspecified"; }
    int getTypeCode() { return 0; }
};

class NonIdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
public:

    NonIdrSliceLayerWithoutPartitioningRbsp();
    ~NonIdrSliceLayerWithoutPartitioningRbsp();
    QString getName() { return "NonIdrSliceLayerWithoutPartitioningRbsp"; }
    int getTypeCode() { return 1; }
};

class SliceDataPartitionALayerRbsp : public NalUnit {
public:
    SliceDataPartitionALayerRbsp();
    ~SliceDataPartitionALayerRbsp();
    QString getName() { return "SliceDataPartitionALayerRbsp"; }
    int getTypeCode() { return 2; }
};

class SliceDataPartitionBLayerRbsp : public NalUnit {
public:
    SliceDataPartitionBLayerRbsp();
    ~SliceDataPartitionBLayerRbsp();
    QString getName() { return "SliceDataPartitionBLayerRbsp"; }
    int getTypeCode() { return 3; }
};

class SliceDataPartitionCLayerRbsp : public NalUnit {
public:
    SliceDataPartitionCLayerRbsp();
    ~SliceDataPartitionCLayerRbsp();
    QString getName() { return "SliceDataPartitionCLayerRbsp"; }
    int getTypeCode() { return 4; }
};

class IdrSliceLayerWithoutPartitioningRbsp : public NalUnit {
public:
    IdrSliceLayerWithoutPartitioningRbsp();
    ~IdrSliceLayerWithoutPartitioningRbsp();
    QString getName() { return "IdrSliceLayerWithoutPartitioningRbsp"; }
    int getTypeCode() { return 5; }
};

class SeiRbsp : public NalUnit {
public:
    SeiRbsp();
    ~SeiRbsp();
    QString getName() { return "SeiRbsp"; }
    int getTypeCode() { return 6; }
};

class SeqParamaterSetRbsp : public NalUnit {
public:
    SeqParamaterSetRbsp();
    ~SeqParamaterSetRbsp();
    QString getName() { return "SeqParamaterSetRbsp"; }
    int getTypeCode() { return 7; }
};

class PicParamaterSetRbsp : public NalUnit {
public:
    PicParamaterSetRbsp();
    ~PicParamaterSetRbsp();
    QString getName() { return "PicParamaterSetRbsp"; }
    int getTypeCode() { return 8; }
};

class AccessUnitDelimiterRbsp : public NalUnit {
public:
    AccessUnitDelimiterRbsp();
    ~AccessUnitDelimiterRbsp();
    QString getName() { return "AccessUnitDelimiterRbsp"; }
    int getTypeCode() { return 9; }
};

class EndOfSequenceRbsp : public NalUnit {
public:
    EndOfSequenceRbsp();
    ~EndOfSequenceRbsp();
    QString getName() { return "EndOfSequenceRbsp"; }
    int getTypeCode() { return 10; }
};

class EndOfStreamRbsp : public NalUnit {
public:
    EndOfStreamRbsp();
    ~EndOfStreamRbsp();
    QString getName() { return "EndOfStreamRbsp"; }
    int getTypeCode() { return 11; }
};

class FillerDataRbsp : public NalUnit {
public:
    FillerDataRbsp();
    ~FillerDataRbsp();
    QString getName() { return "FillerDataRbsp"; }
    int getTypeCode() { return 12; }
};

class SeqParameterSetExtensionRbsp : public NalUnit {
public:
    SeqParameterSetExtensionRbsp();
    ~SeqParameterSetExtensionRbsp();
    QString getName() { return "SeqParameterSetExtensionRbsp"; }
    int getTypeCode() { return 13; }
};

class PrefixNalUnitRbsp : public NalUnit {
public:
    PrefixNalUnitRbsp();
    ~PrefixNalUnitRbsp();
    QString getName() { return "PrefixNalUnitRbsp"; }
    int getTypeCode() { return 14; }
};

class SubsetSequenceParameterSetRbsp : public NalUnit {
public:
    SubsetSequenceParameterSetRbsp();
    ~SubsetSequenceParameterSetRbsp();
    QString getName() { return "SubsetSequenceParameterSetRbsp"; }
    int getTypeCode() { return 15; }
};

class Reserved16 : public NalUnit {
public:
    Reserved16();
    ~Reserved16();
    QString getName() { return "Reserved16"; }
    int getTypeCode() { return 16; }
};

class Reserved17 : public NalUnit {
public:
    Reserved17();
    ~Reserved17();
    QString getName() { return "Reserved17"; }
    int getTypeCode() { return 17; }
};

class Reserved18 : public NalUnit {
public:
    Reserved18();
    ~Reserved18();
    QString getName() { return "Reserved18"; }
    int getTypeCode() { return 18; }
};

class SliceLayerWithoutPartitioningRbsp : public NalUnit {
public:
    SliceLayerWithoutPartitioningRbsp();
    ~SliceLayerWithoutPartitioningRbsp();
    QString getName() { return "SliceLayerWithoutPartitioningRbsp"; }
    int getTypeCode() { return 19; }
};

class SliceLayerExtensionRbsp : public NalUnit {
public:
    SliceLayerExtensionRbsp();
    ~SliceLayerExtensionRbsp();
    QString getName() { return "SliceLayerExtensionRbsp"; }
    int getTypeCode() { return 20; }
};

class Reserved21 : public NalUnit {
public:
    Reserved21();
    ~Reserved21();
    QString getName() { return "Reserved21"; }
    int getTypeCode() { return 21; }
};

class Reserved22 : public NalUnit {
public:
    Reserved22();
    ~Reserved22();
    QString getName() { return "Reserved22"; }
    int getTypeCode() { return 22; }
};

class Reserved23 : public NalUnit {
public:
    Reserved23();
    ~Reserved23();
    QString getName() { return "Reserved23"; }
    int getTypeCode() { return 23; }
};

class Unspecified24 : public NalUnit {
public:
    Unspecified24();
    ~Unspecified24();
    QString getName() { return "Unspecified24"; }
    int getTypeCode() { return 24; }
};

class Unspecified25 : public NalUnit {
public:
    Unspecified25();
    ~Unspecified25();
    QString getName() { return "Unspecified25"; }
    int getTypeCode() { return 25; }
};

class Unspecified26 : public NalUnit {
public:
    Unspecified26();
    ~Unspecified26();
    QString getName() { return "Unspecified26"; }
    int getTypeCode() { return 26; }
};

class Unspecified27 : public NalUnit {
public:
    Unspecified27();
    ~Unspecified27();
    QString getName() { return "Unspecified27"; }
    int getTypeCode() { return 27; }
};

class Unspecified28 : public NalUnit {
public:
    Unspecified28();
    ~Unspecified28();
    QString getName() { return "Unspecified28"; }
    int getTypeCode() { return 28; }
};

class Unspecified29 : public NalUnit {
public:
    Unspecified29();
    ~Unspecified29();
    QString getName() { return "Unspecified29"; }
    int getTypeCode() { return 29; }
};

class Unspecified30 : public NalUnit {
public:
    Unspecified30();
    ~Unspecified30();
    QString getName() { return "Unspecified30"; }
    int getTypeCode() { return 30; }
};

class Unspecified31 : public NalUnit {
public:
    Unspecified31();
    ~Unspecified31();
    QString getName() { return "Unspecified31"; }
    int getTypeCode() { return 31; }
};


#endif // NALUNIT_H
