#include "box.h"


Box::Box(const unsigned  int &s, const QString &t, const unsigned long &off):
    size(s),type(t),offset(off) {}
/////////////
FullBox::FullBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v,
                 const QList<unsigned int>& f):
    Box(s,t,off),
    version(v),
    flags(f)
{}
/////////////
FileTypeBox::FileTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const QString& mb, const unsigned int &mv,
                         const QList<QString>& cb):
    Box(s,t,off),
    majorBrand(mb),
    minorVersion(mv),
    compatibleBrands(cb) {}

QStandardItemModel *FileTypeBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Major brand");
    model->setData(model->index(0, 1, QModelIndex()), majorBrand);
    model->setData(model->index(1, 0, QModelIndex()), "Minor version");
    model->setData(model->index(1, 1, QModelIndex()), QString::number(minorVersion));
    model->setData(model->index(2, 0, QModelIndex()), "Compatible brands");
    QString tmp("");
    QList<QString>::iterator i;
    for (i = compatibleBrands.begin(); i !=compatibleBrands.end(); ++i) {
        tmp.append(*i);
        tmp.append(" | ");
    }
    model->setData(model->index(2, 1, QModelIndex()), tmp);

    return model;
}

/////////////
SegmentTypeBox::SegmentTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                               const QString& mb, const unsigned int &mv, const QList<QString>& cb):
    Box(s,t,off),
    majorBrand(mb),
    minorVersion(mv),
    compatibleBrands(cb) {}

QStandardItemModel *SegmentTypeBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Major brand");
    model->setData(model->index(0, 1, QModelIndex()), majorBrand);
    model->setData(model->index(1, 0, QModelIndex()), "Minor version");
    model->setData(model->index(1, 1, QModelIndex()), QString::number(minorVersion));
    model->setData(model->index(2, 0, QModelIndex()), "Compatible brands");
    QString tmp("");
    QList<QString>::iterator i;
    for (i = compatibleBrands.begin(); i !=compatibleBrands.end(); ++i) {
        tmp.append(*i);
        tmp.append(" | ");
    }
    model->setData(model->index(2, 1, QModelIndex()), tmp);

    return model;
}
/////////////
MediaBox::MediaBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
/////////////
MediaDataBox::MediaDataBox(const unsigned  int& s, const QString& t, const unsigned long int& off):Box(s,t,off) {}
/////////////
MediaHeaderBox::MediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                               const unsigned  int& v, const QList<unsigned int>& f, const unsigned long &ct, const unsigned long &mt,
                               const unsigned int &ts, const unsigned long &dur, const bool &pd, const QList<unsigned int> &lan,
                               const unsigned int &prd):
    FullBox(s,t,off,v, f) ,


    creationTime(ct),
    modificationTime(mt),
    timescale(ts),
    duration(dur),
    pad(pd),
    language(lan),
    predefined(prd)
{}

QStandardItemModel *MediaHeaderBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(8, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Creation time");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(creationTime));
    model->setData(model->index(3, 0, QModelIndex()), "Modification time");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(modificationTime));
    model->setData(model->index(4, 0, QModelIndex()), "Timescale");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(timescale));
    model->setData(model->index(5, 0, QModelIndex()), "Duration");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(duration));
    model->setData(model->index(6, 0, QModelIndex()), "Pad");
    if(pad)
        model->setData(model->index(6, 1, QModelIndex()), QString::number(1));
    else
        model->setData(model->index(6, 1, QModelIndex()), QString::number(0));
    tmp.clear();
    for(int i = 0; i < language.size(); ++i) {
        tmp.append(QString::number(language.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(7, 0, QModelIndex()), "Language");
    model->setData(model->index(7, 1, QModelIndex()), tmp);
    model->setData(model->index(7, 0, QModelIndex()), "Predefined");
    model->setData(model->index(7, 1, QModelIndex()), QString::number(predefined));
    return model;
}
/////////////
MovieBox::MovieBox(const unsigned  int& s, const QString& t, const unsigned long int& off):Box(s,t,off) {}
/////////////
MovieHeaderBox::MovieHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                               const unsigned  int &v, const QList<unsigned int> &f, const unsigned long &ct, const unsigned long &mt,
                               const unsigned long &ts, const unsigned long &d, const unsigned int &r, const unsigned int &vl,
                               const unsigned int &r16, const QList<unsigned long> &r32, const QList<unsigned long> &mx,
                               const QList<unsigned long> &pr, const unsigned long &nid):
    FullBox(s,t,off,v, f) ,
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

QStandardItemModel *MovieHeaderBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(11, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Creation time");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(creationTime));
    model->setData(model->index(3, 0, QModelIndex()), "Modification time");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(modificationTime));
    model->setData(model->index(4, 0, QModelIndex()), "Timescale");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(timeScale));
    model->setData(model->index(5, 0, QModelIndex()), "Duration");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(duration));
    model->setData(model->index(6, 0, QModelIndex()), "Rate");
    model->setData(model->index(6, 1, QModelIndex()), QString::number(rate));
    model->setData(model->index(7, 0, QModelIndex()), "Volume");
    model->setData(model->index(7, 1, QModelIndex()), QString::number(volume));
    model->setData(model->index(7, 0, QModelIndex()), "Reserved1");
    model->setData(model->index(7, 1, QModelIndex()), QString::number(reserved16));
    tmp.clear();
    for(int i = 0; i < reserved32.size(); ++i) {
        tmp.append(QString::number(reserved32.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(8, 0, QModelIndex()), "Reserved2");
    model->setData(model->index(8, 1, QModelIndex()), tmp);
    tmp.clear();
    for(int i = 0; i < matrix.size(); ++i) {
        tmp.append(QString::number(matrix.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(9, 0, QModelIndex()), "Matrix");
    model->setData(model->index(9, 1, QModelIndex()), tmp);
    tmp.clear();
    for(int i = 0; i < predefined.size(); ++i) {
        tmp.append(QString::number(predefined.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(10, 0, QModelIndex()), "Next track ID");
    model->setData(model->index(10, 1, QModelIndex()), QString::number(nextTrackId));
    return model;
}
/////////////
MediaInformationBox::MediaInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
/////////////
VideoMediaHeaderBox::VideoMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                         const unsigned  int& v, const QList<unsigned int>& f, const unsigned int &gmode,
                                         const QList<unsigned int> &opc):
    FullBox(s,t,off,v, f),


    graphicsmode(gmode),
    opcolor(opc)
{}

QStandardItemModel *VideoMediaHeaderBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(6, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Graphicsmode");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(graphicsmode));
    model->setData(model->index(3, 0, QModelIndex()), "Opcolor");
    tmp.clear();
    for(int i = 0; i < opcolor.size(); ++i) {
        tmp.append(QString::number(opcolor.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(3, 1, QModelIndex()), tmp);

    return model;
}

/////////////
SoundMediaHeaderBox::SoundMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                         const unsigned  int& v, const QList<unsigned int>& f, const unsigned int &bl,
                                         const unsigned int &res):
    FullBox(s,t,off,v, f),


    balance(bl),
    reserved(res)
{}

QStandardItemModel *SoundMediaHeaderBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(6, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Balance");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(balance));
    model->setData(model->index(3, 0, QModelIndex()), "Reserved");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(reserved));

    return model;
}
/////////////
HintMediaHeaderBox::HintMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
/////////////
NullMediaHeaderBox::NullMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
/////////////
DataInformationBox::DataInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off):
    Box(s,t,off)
{}
/////////////
DataEntryUrnBox::DataEntryUrnBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                 const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
/////////////
DataEntryUrlBox::DataEntryUrlBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                 const unsigned  int& v, const QList<unsigned int>& f, const QString &loc):
    FullBox(s,t,off,v, f),
    location(loc)
{}

QStandardItemModel *DataEntryUrlBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Location");
    model->setData(model->index(2, 1, QModelIndex()), location);
    return model;
}
/////////////
DataReferenceBox::DataReferenceBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                   const unsigned  int& v, const QList<unsigned int>& f, const unsigned long int&ec):
    FullBox(s,t,off,v, f),


    entryCount(ec)
{}

QStandardItemModel *DataReferenceBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));
    return model;
}

///////////////
FreeSpaceBox::FreeSpaceBox(bool c, const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off), container(c) {}
///////////////
EditBox::EditBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
EditListBox::EditListBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                         const unsigned int& v, const QList<unsigned int>& f, const unsigned int & eCount,
                         const QList<unsigned long int>& segmD, const QList<unsigned long int>&medT, const QList<unsigned int>& mri,
                         const QList<unsigned int>& mrf):
    FullBox(s,t,off,v, f),
    entryCount(eCount),
    segmentDuration(segmD),
    mediaTime(medT),
    mediaRateInteger(mri),
    mediaRateFraction(mrf)
{}

QStandardItemModel *EditListBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(6, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));
    tmp.clear();
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(segmentDuration.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(3, 0, QModelIndex()), "Segment duration");
    model->setData(model->index(3, 1, QModelIndex()), tmp);
    tmp.clear();
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(mediaTime.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(3, 0, QModelIndex()), "Media Time");
    model->setData(model->index(3, 1, QModelIndex()), tmp);
    tmp.clear();
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(mediaRateInteger.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(4, 0, QModelIndex()), "Media rate integer");
    model->setData(model->index(4, 1, QModelIndex()), tmp);
    tmp.clear();
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(mediaRateFraction.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(5, 0, QModelIndex()), "Media rate fraction");
    model->setData(model->index(5, 1, QModelIndex()), tmp);
    return model;
}
///////////////
UserDataBox::UserDataBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
CopyRightBox::CopyRightBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                           const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
MovieExtendsBox::MovieExtendsBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
MovieExtendsHeaderBox::MovieExtendsHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                             const unsigned  int& v, const QList<unsigned int>& f, const unsigned long &fd):
    FullBox(s,t,off,v, f),
    fragmentDuration(fd)
{}

QStandardItemModel *MovieExtendsHeaderBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Fragment duration");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(fragmentDuration));
    return model;
}
///////////////
MovieFragmentBox::MovieFragmentBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
MovieFragmentHeaderBox::MovieFragmentHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const long &sn, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f),
    sequenceNumber(sn){}

QStandardItemModel *MovieFragmentHeaderBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Sequence number");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(sequenceNumber));

    return model;
}
///////////////
MovieFragmentRandomAccessBox::MovieFragmentRandomAccessBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}

///////////////
MovieFragmentRandomAccessOffsetBox::MovieFragmentRandomAccessOffsetBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
SampleDependencyTypeBox::SampleDependencyTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
SampleToGroupBox::SampleToGroupBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
SampleGroupDescriptionBox::SampleGroupDescriptionBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
SampleScaleBox::SampleScaleBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
SubSampleInformationBox::SubSampleInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
ProgressiveDownloadInfoBox::ProgressiveDownloadInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
MetaBox::MetaBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
XMLBox::XMLBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
BinaryXMLBox::BinaryXMLBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
ItemLocationBox::ItemLocationBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
PrimaryItemBox::PrimaryItemBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
ItemProtectionBox::ItemProtectionBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
ItemInfoEntry::ItemInfoEntry(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
ItemInfoBox::ItemInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
ProtectionSchemeInfoBox::ProtectionSchemeInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
OriginalFormatBox::OriginalFormatBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
IPMPInfoBox::IPMPInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
IPMPControlBox::IPMPControlBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
SchemeTypeBox::SchemeTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
SchemeInformationBox::SchemeInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
TimeScaleEntry::TimeScaleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
TimeOffset::TimeOffset(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
SequenceOffset::SequenceOffset(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
SRTPProcessBox::SRTPProcessBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
///////////////
MovieHintInformation::MovieHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
RTPMovieHintInformation::RTPMovieHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
RTPTrackSDPHintInformation::RTPTrackSDPHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
HintStatisticsBox::HintStatisticsBox(const unsigned  int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
///////////////
///mpeg dash
//////////////
SampleAuxiliaryInformationSizesBox::SampleAuxiliaryInformationSizesBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
SampleAuxiliaryInformationOffsetsBox::SampleAuxiliaryInformationOffsetsBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
LevelAssignmentBox::LevelAssignmentBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
SegmentIndexBox::SegmentIndexBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f,
                                 const unsigned int &ri, const unsigned int &ts, const unsigned int& myEarliestPresentationTime, const unsigned int& myFirstOffset,
                                 const unsigned int &myReserved, const QList<bool>& myReferenceType, const QList<unsigned  int> myReferenceSize,
                                 const QList<unsigned  int> &mySubsegmentDuration, const QList<bool> & myStartsWithSAP, const QList<unsigned  int> &mySAPType,
                                 const QList<unsigned  int> &mySAPDeltaTime):
    FullBox(s,t,off,v, f),
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

QStandardItemModel *SegmentIndexBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(5 + (SAPDeltaTime.size()>0)*6, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Reference ID");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(referenceId));
    model->setData(model->index(3, 0, QModelIndex()), "Timescale");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(timescale));
    model->setData(model->index(4, 0, QModelIndex()), "Earliest presentation time");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(earliestPresentationTime));
    model->setData(model->index(3, 0, QModelIndex()), "First offset");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(firstOffset));
    model->setData(model->index(4, 0, QModelIndex()), "Reserved");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(reserved));
    unsigned int size = referenceType.size();
    if(size>0) {
        model->setData(model->index(5, 0, QModelIndex()), "Reference type");
        tmp.clear();
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(referenceType.at(i)));
            tmp.append(" |");
        }
        model->setData(model->index(6, 0, QModelIndex()), "Reference size");
        tmp.clear();
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(referenceSize.at(i)));
            tmp.append(" |");
        }
        model->setData(model->index(6, 1, QModelIndex()), tmp);
        model->setData(model->index(7, 0, QModelIndex()), "Subsegment duration");
        tmp.clear();
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(subsegmentDuration.at(i)));
            tmp.append(" |");
        }
        model->setData(model->index(7, 1, QModelIndex()), tmp);
        model->setData(model->index(8, 0, QModelIndex()), "Starts with SAP");
        tmp.clear();
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(startsWithSAP.at(i)));
            tmp.append(" |");
        }
        model->setData(model->index(8, 1, QModelIndex()), tmp);
        model->setData(model->index(9, 0, QModelIndex()), "SAP Type");
        tmp.clear();
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(SAPType.at(i)));
            tmp.append(" |");
        }
        model->setData(model->index(9, 1, QModelIndex()), tmp);
        model->setData(model->index(10, 0, QModelIndex()), "SAP Delta Time");
        for(unsigned int i=0; i<size; i++) {
            tmp.append(QString::number(SAPDeltaTime.at(i)));
            tmp.append(" |");
        }
        model->setData(model->index(10, 1, QModelIndex()), tmp);
    }
    return model;
}
///////////////
SubsegmentIndexBox::SubsegmentIndexBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int& v, const QList<unsigned int>& f): FullBox(s,t,off,v, f) {}
///////////////
ProducerReferenceTimeBox::ProducerReferenceTimeBox(const unsigned  int& s, const QString& t, const unsigned long int& off,  const unsigned  int &v, const QList<unsigned int> &f): FullBox(s,t,off,v, f) {}
///////////////
