#include "box.h"


Box::Box(const unsigned  int &s, const QString &t, const unsigned long &off, const unsigned  int & e):
    size(s),type(t),offset(off), extended_type(e) {}
/////////////
FullBox::FullBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v,
                 const QList<unsigned int>& f):
    Box(s,t,off,e),
    version(v),
    flags(f)
{}
QString FullBox::getInfo() {
    QString tmp("");
    tmp.append("Version\t\t");
    tmp.append(QString::number(version));
    tmp.append("\nFlags\t\t");
    tmp.append(QString::number(flags.at(0), 16));
    tmp.append(" | ");
    tmp.append(QString::number(flags.at(1), 16));
    tmp.append(" | ");
    tmp.append(QString::number(flags.at(2), 16));
    tmp.append(" | ");
    return tmp;
}
/////////////
FileTypeBox::FileTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int & e, const QString& mb, const unsigned int &mv,
                         const QList<QString>& cb):
    Box(s,t,off,e),
    majorBrand(mb),
    minorVersion(mv),
    compatibleBrands(cb) {}

QString FileTypeBox::getInfo() {
    QString tmp("");
    tmp.append("Major brand\t\t");
    tmp.append(majorBrand);
    tmp.append("\nMinor version\t\t");
    tmp.append(QString::number(minorVersion));
    tmp.append("\nCompatible brands\t");
    QList<QString>::iterator i;
    for (i = compatibleBrands.begin(); i !=compatibleBrands.end(); ++i) {
        tmp.append(*i);
        tmp.append(" | ");
    }
    return tmp;
}
/////////////
SegmentTypeBox::SegmentTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int & e,
                               const QString& mb, const unsigned int &mv, const QList<QString>& cb):
    Box(s,t,off,e),
    majorBrand(mb),
    minorVersion(mv),
    compatibleBrands(cb) {}

QString SegmentTypeBox::getInfo() {
    QString tmp("");
    tmp.append("Major brand\t\t");
    tmp.append(majorBrand);
    tmp.append("\nMinor version\t\t");
    tmp.append(QString::number(minorVersion));
    tmp.append("\nCompatible brands\t");
    QList<QString>::iterator i;
    for (i = compatibleBrands.begin(); i !=compatibleBrands.end(); ++i) {
        tmp.append(*i);
        tmp.append(" | ");
    }
    return tmp;
}
/////////////
MediaBox::MediaBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
/////////////
MediaDataBox::MediaDataBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e):Box(s,t,off,e) {}
/////////////
MediaHeaderBox::MediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                               const unsigned  int& v, const QList<unsigned int>& f, const unsigned long &ct, const unsigned long &mt,
                               const unsigned int &ts, const unsigned long &dur, const bool &pd, const QList<unsigned int> &lan,
                               const unsigned int &prd):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    creationTime(ct),
    modificationTime(mt),
    timescale(ts),
    duration(dur),
    pad(pd),
    language(lan),
    predefined(prd)
{}
QString MediaHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nCreation time\t\t");
    tmp.append(QString::number(creationTime));
    tmp.append("\nModification time\t");
    tmp.append(QString::number(modificationTime));
    tmp.append("\nTimescale\t\t");
    tmp.append(QString::number(timescale));
    tmp.append("\nDuration\t\t");
    tmp.append(QString::number(duration));
    tmp.append("\nPad\t\t");
    if(pad)
        tmp.append("1");
    else
        tmp.append("0");
    int lanSize = language.size();
    tmp.append("\nLanguage\t\t");
    for(int i = 0; i < lanSize; ++i) {
        tmp.append(QString::number(language.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nPredefined\t\t");
    tmp.append(QString::number(predefined));
    return tmp;
}
/////////////
MovieBox::MovieBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e):Box(s,t,off,e) {}
/////////////
MovieHeaderBox::MovieHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                               const unsigned  int &v, const QList<unsigned int> &f, const unsigned long &ct, const unsigned long &mt,
                               const unsigned long &ts, const unsigned long &d, const unsigned int &r, const unsigned int &vl,
                               const unsigned int &r16, const QList<unsigned long> &r32, const QList<unsigned long> &mx,
                               const QList<unsigned long> &pr, const unsigned long &nid):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    creationTime(ct),
    modificationTime(mt),
    timeScale(ts),
    duration(d),
    rate(r),
    volume(vl),
    reserved16(r16),
    reserved32(r32),
    nextTrackId(nid),
    matrix(mx),
    predefined(pr)
{}
QString MovieHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nCreation time\t\t");
    tmp.append(QString::number(creationTime));
    tmp.append("\nModification time\t");
    tmp.append(QString::number(modificationTime));
    tmp.append("\nTimescale\t\t");
    tmp.append(QString::number(timeScale));
    tmp.append("\nDuration\t\t");
    tmp.append(QString::number(duration));
    tmp.append("\nRate\t\t");
    tmp.append(QString::number(rate));
    tmp.append("\nVolume\t\t");
    tmp.append(QString::number(volume));
    tmp.append("\nReserved16\t\t");
    tmp.append(QString::number(reserved16));
    tmp.append("\nReserved32\t\t");
    QList<unsigned long int>::iterator p;
    for (p = reserved32.begin(); p !=reserved32.end(); ++p) {
        tmp.append(QString::number(*p));
        tmp.append(" | ");
    }
    tmp.append("\nMatrix\t\t");
    QList<unsigned long int>::iterator i;
    for (i = matrix.begin(); i !=matrix.end(); ++i) {
        tmp.append(QString::number(*i));
        tmp.append(" | ");
    }
    tmp.append("\nPredefined\t\t");
    QList<unsigned long int>::iterator k;
    for (k = predefined.begin(); k !=predefined.end(); ++k) {
        tmp.append(QString::number(*k));
        tmp.append(" | ");
    }
    tmp.append("\nNext track id\t\t");
    tmp.append(QString::number(nextTrackId));
    return tmp;
}
/////////////
MediaInformationBox::MediaInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
/////////////
VideoMediaHeaderBox::VideoMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                         const unsigned  int& v, const QList<unsigned int>& f, const unsigned int &gmode,
                                         const QList<unsigned int> &opc):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f),
    graphicsmode(gmode),
    opcolor(opc)
{}
QString VideoMediaHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nGraphicsmode\t\t");
    tmp.append(QString::number(graphicsmode));
    int ocSize = opcolor.size();
    tmp.append("\nOpcolor\t\t");
    for (int i = 0; i<ocSize; ++i) {
        tmp.append(QString::number(opcolor.at(i)));
        tmp.append(" | ");
    }
    return tmp;
}
/////////////
SoundMediaHeaderBox::SoundMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                         const unsigned  int& v, const QList<unsigned int>& f, const unsigned int &bl,
                                         const unsigned int &res):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f),
    balance(bl),
    reserved(res)
{}
QString SoundMediaHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nBalance\t\t");
    tmp.append(QString::number(balance));
    tmp.append("\nReserved\t\t");
    tmp.append(QString::number(reserved));
    return tmp;
}

/////////////
HintMediaHeaderBox::HintMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
/////////////
NullMediaHeaderBox::NullMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
/////////////
DataInformationBox::DataInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e):
    Box(s,t,off,e)
{}
/////////////
DataEntryUrnBox::DataEntryUrnBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                 const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
/////////////
DataEntryUrlBox::DataEntryUrlBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                 const unsigned  int& v, const QList<unsigned int>& f, const QString &loc):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f),
    location(loc)
{}
QString DataEntryUrlBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nLocation\t\t");
    tmp.append(location);
    return tmp;
}

/////////////
DataReferenceBox::DataReferenceBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                   const unsigned  int& v, const QList<unsigned int>& f, const unsigned long int&ec):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f),
    entryCount(ec)
{}
QString DataReferenceBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    return tmp;
}

///////////////
FreeSpaceBox::FreeSpaceBox(bool c,const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int & e): Box(s,t,off,e), container(c) {}
///////////////
EditBox::EditBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
EditListBox::EditListBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                         const unsigned int& v, const QList<unsigned int>& f, const unsigned int & eCount,
                         const QList<unsigned long int>& segmD, const QList<unsigned long int>&medT, const QList<unsigned int>& mri,
                         const QList<unsigned int>& mrf):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f),
    entryCount(eCount),
    segmentDuration(segmD),
    mediaTime(medT),
    mediaRateInteger(mri),
    mediaRateFraction(mrf)
{}
QString EditListBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    tmp.append("\nSegment duration\t");
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(segmentDuration.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nMedia time\t\t");
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(mediaTime.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nMedia rate integer\t");
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(mediaRateInteger.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nMedia rate fraction\t");
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(mediaRateFraction.at(i)));
        tmp.append(" | ");
    }
    return tmp;
}
///////////////
UserDataBox::UserDataBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
CopyRightBox::CopyRightBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                           const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
///////////////
MovieExtendsBox::MovieExtendsBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
MovieExtendsHeaderBox::MovieExtendsHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                             const unsigned  int& v, const QList<unsigned int>& f, const unsigned long &fd):
    FullBox(s,t,off,e, v, f),
    fragmentDuration(fd)
{}
QString MovieExtendsHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nFragment duration\t");
    tmp.append(QString::number(fragmentDuration));
    return tmp;
}
///////////////
MovieFragmentBox::MovieFragmentBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
MovieFragmentHeaderBox::MovieFragmentHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const long &sn, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    sequenceNumber(sn){}
QString MovieFragmentHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nSequence number\t");
    tmp.append(QString::number(sequenceNumber));
    return tmp;
}
///////////////
MovieFragmentRandomAccessBox::MovieFragmentRandomAccessBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}

///////////////
MovieFragmentRandomAccessOffsetBox::MovieFragmentRandomAccessOffsetBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
SampleDependencyTypeBox::SampleDependencyTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
SampleToGroupBox::SampleToGroupBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
SampleGroupDescriptionBox::SampleGroupDescriptionBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
SampleScaleBox::SampleScaleBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
SubSampleInformationBox::SubSampleInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
ProgressiveDownloadInfoBox::ProgressiveDownloadInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
MetaBox::MetaBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
XMLBox::XMLBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
BinaryXMLBox::BinaryXMLBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
ItemLocationBox::ItemLocationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
PrimaryItemBox::PrimaryItemBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
ItemProtectionBox::ItemProtectionBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
ItemInfoEntry::ItemInfoEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
///////////////
ItemInfoBox::ItemInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
///////////////
ProtectionSchemeInfoBox::ProtectionSchemeInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
OriginalFormatBox::OriginalFormatBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
IPMPInfoBox::IPMPInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
///////////////
IPMPControlBox::IPMPControlBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
SchemeTypeBox::SchemeTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
SchemeInformationBox::SchemeInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
TimeScaleEntry::TimeScaleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
TimeOffset::TimeOffset(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
SequenceOffset::SequenceOffset(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
SRTPProcessBox::SRTPProcessBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f)
{}
///////////////
MovieHintInformation::MovieHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
RTPMovieHintInformation::RTPMovieHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
RTPTrackSDPHintInformation::RTPTrackSDPHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
HintStatisticsBox::HintStatisticsBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
///mpeg dash
//////////////
SampleAuxiliaryInformationSizesBox::SampleAuxiliaryInformationSizesBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
SampleAuxiliaryInformationOffsetsBox::SampleAuxiliaryInformationOffsetsBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
LevelAssignmentBox::LevelAssignmentBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
SegmentIndexBox::SegmentIndexBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f,
                                 const unsigned int &ri, const unsigned int &ts, const unsigned int& myEarliestPresentationTime, const unsigned int& myFirstOffset,
                                 const unsigned int &myReserved, const QList<bool>& myReferenceType, const QList<unsigned  int> myReferenceSize,
                                 const QList<unsigned  int> &mySubsegmentDuration, const QList<bool> & myStartsWithSAP, const QList<unsigned  int> &mySAPType,
                                 const QList<unsigned  int> &mySAPDeltaTime):
    FullBox(s,t,off,e, v, f),
    version(v),
    flags(f),
    referenceId(ri),
    timescale(ts),
    earliestPresentationTime(myEarliestPresentationTime),
    firstOffset(myFirstOffset),
    reserved(myReserved),
    referenceType(myReferenceType),
    referenceSize(myReferenceSize),
    subsegmentDuration(mySubsegmentDuration),
    startsWithSAP(myStartsWithSAP),
    SAPType(mySAPType),
    SAPDeltaTime(mySAPDeltaTime)
{}
QString SegmentIndexBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nReference ID\t\t");
    tmp.append(QString::number(referenceId));
    tmp.append("\nTimescale\t\t");
    tmp.append(QString::number(timescale));
    tmp.append("\nEarliest presentation time\t");
    tmp.append(QString::number(earliestPresentationTime));
    tmp.append("\nFirst offset\t\t");
    tmp.append(QString::number(firstOffset));
    tmp.append("\nReserved\t\t");
    tmp.append(QString::number(reserved));
    unsigned int size = referenceType.size();
    if(size>0) {
        tmp.append("\nReference type\t\t");
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(referenceType.at(i)));
            tmp.append(" |");
        }
        tmp.append("\nReference size\t\t");
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(referenceSize.at(i)));
            tmp.append(" |");
        }
        tmp.append("\nSubsegment duration\t");
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(subsegmentDuration.at(i)));
            tmp.append(" |");
        }
        tmp.append("\nStarts with SAP\t\t");
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(startsWithSAP.at(i)));
            tmp.append(" |");
        }
        tmp.append("\nSAP type\t\t");
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(SAPType.at(i)));
            tmp.append(" |");
        }
        tmp.append("\nSAP delta time\t\t");
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(SAPDeltaTime.at(i)));
            tmp.append(" |");
        }
    }
    return tmp;
}

///////////////
SubsegmentIndexBox::SubsegmentIndexBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,e, v, f) {}
///////////////
ProducerReferenceTimeBox::ProducerReferenceTimeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int &v, const QList<unsigned int> &f): FullBox(s,t,off,e, v, f) {}
///////////////
