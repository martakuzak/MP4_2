#include "sampleentry.h"

/////////////
SampleEntry::SampleEntry(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int & e,
                         const QList<unsigned int> &res, const unsigned  int& dri):
    Box(s,t,off,e),
    reserved(res),
    dataReferenceIndex(dri)
{}
QString SampleEntry::getInfo() {
    QString tmp("");
    tmp.append("Reserved\t\t");
    int resSize = reserved.size();
    for (int i = 0; i<resSize; ++i) {
        tmp.append(QString::number(reserved.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nData reference index\t");
    tmp.append(QString::number(dataReferenceIndex));
    return tmp;
}

/////////////
VisualSampleEntry::VisualSampleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                     const QList<unsigned int>& res, const unsigned int &dri, const unsigned int &pd, const unsigned int& r2,
                                     const QList<unsigned int> &pd1, const unsigned int& wdth, const unsigned int& hght, const unsigned  int& hr,
                                     const unsigned int& vr, const unsigned int& r3, const unsigned int& fc, const QString & csn,
                                     const unsigned int& dpth, const int &pd2):
    SampleEntry(s,t,off,e, res, dri),
    predefined(pd),
    reserved2(r2),
    predefined1(pd1),
    width(wdth),
    height(hght),
    horizontalResolution(hr),
    verticalResolution(vr),
    reserved3(r3),
    frameCount(fc),
    compressorname(csn),
    depth(dpth),
    predefined2(pd2)
{}
QString VisualSampleEntry::getInfo() {
    QString tmp("");
    tmp.append(SampleEntry::getInfo());
    tmp.append("\nPredefined\t\t");
    tmp.append(QString::number(predefined));
    tmp.append("\nReserved\t\t");
    tmp.append(QString::number(reserved2));
    int p1Size = predefined1.size();
    for (int i = 0; i<p1Size; ++i) {
        tmp.append(QString::number(predefined1.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nWidth\t\t");
    tmp.append(QString::number(width));
    tmp.append("\nHeight\t\t");
    tmp.append(QString::number(height));
    tmp.append("\nHorizontal resolution\t");
    tmp.append(QString::number(horizontalResolution));
    tmp.append("\nVertical resolution\t");
    tmp.append(QString::number(verticalResolution));
    tmp.append("\nReserved2\t\t");
    tmp.append(QString::number(reserved3));
    tmp.append("\nFrame count\t\t");
    tmp.append(QString::number(frameCount));
    tmp.append("\nCompressor name\t\t");
    tmp.append(compressorname);
    tmp.append("\nDepth\t\t");
    tmp.append(QString::number(depth));
    tmp.append("\nPredefined2\t\t");
    tmp.append(QString::number(predefined2));
    return tmp;
}
/////////////
AudioSampleEntry::AudioSampleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                   const QList<unsigned int>& res, const unsigned int &dri, const QList<unsigned int> &res1,
                                   const unsigned int &chc, const unsigned int &ss, const unsigned int &pred, const unsigned int &res2,
                                   const unsigned int &srate):
    SampleEntry(s,t,off,e,res,dri),
    reserved1(res1),
    channelCount(chc),
    sampleSize(ss),
    predefined(pred),
    reserved2(res2),
    sampleRate(srate)
{}
QString AudioSampleEntry::getInfo() {
    QString tmp("");
    tmp.append(SampleEntry::getInfo());
    tmp.append("\nReserved1\t\t");
    int res1Size = reserved1.size();
    for (int i = 0; i<res1Size; ++i) {
        tmp.append(QString::number(reserved1.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nChannel count\t\t");
    tmp.append(QString::number(channelCount));
    tmp.append("\nSample size\t\t");
    tmp.append(QString::number(sampleSize));
    tmp.append("\nPredefined\t\t");
    tmp.append(QString::number(predefined));
    tmp.append("\nReserved2\t\t");
    tmp.append(QString::number(reserved2));
    tmp.append("\nSample rate\t\t");
    tmp.append(QString::number(sampleRate));
    return tmp;
}
/////////////
HintSampleEntry::HintSampleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned int &e,
                                 const QList<unsigned int>& res, const unsigned int &dri):
    SampleEntry(s,t,off,e, res, dri)
{}
/////////////
MP4VisualSampleEntry::MP4VisualSampleEntry(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                           const QList<unsigned int>& res, const unsigned int &dri, const unsigned int &pd,
                                           const unsigned int& r2,const QList<unsigned int>& pd1,const unsigned int& wdth,
                                           const unsigned int& hght, const unsigned  int& hr, const unsigned int& vr, const unsigned int& r3,
                                           const unsigned int& fc, const QString & csn, const unsigned int& dpth, const unsigned int &pd2):
    VisualSampleEntry(s,t,off,e,res, dri,pd,r2,pd1, wdth,hght, hr,vr, r3, fc, csn, dpth, pd2)
{}
///////////////
MP4AudioSampleEntry::MP4AudioSampleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                         const QList<unsigned int>& res, const unsigned int &dri, const QList<unsigned int> &res1,
                                         const unsigned int &chc, const unsigned int &ss, const unsigned int &pred, const unsigned int &res2,
                                         const unsigned int &srate):
    AudioSampleEntry(s,t,off,e,res,dri,res1,chc,ss,pred,res2,srate)
{}
///////////////
MpegSampleEntry::MpegSampleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                 const QList<unsigned int> &res, const unsigned int &dri):
    SampleEntry(s,t,off,e,res,dri) {}
///////////////
/////MP4///////
ObjectDescriptorBox::ObjectDescriptorBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v,const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
///////////////
ESDBox::ESDBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const unsigned  int& v,const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
///////////////
AVCSampleEntry::AVCSampleEntry(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                               const QList<unsigned int>& res, const unsigned int &dri, const unsigned int &pd,
                               const unsigned int& r2,const QList<unsigned int>& pd1,const unsigned int& wdth,
                               const unsigned int& hght, const unsigned  int& hr, const unsigned int& vr, const unsigned int& r3,
                               const unsigned int& fc, const QString & csn, const unsigned int& dpth, const unsigned int &pd2):
    VisualSampleEntry(s,t,off,e,res, dri,pd,r2,pd1, wdth,hght, hr,vr, r3, fc, csn, dpth, pd2)
{}
///////////////
AVCConfigurationBox::AVCConfigurationBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                         const unsigned int& cv, const unsigned int& avcpi, const unsigned int& pc, const unsigned int& avcli,
                                         const unsigned int& r1, const unsigned int& lsmo, const unsigned int& r2, const unsigned int& nosps,
                                         const QList<unsigned int>& spsl, const QList<unsigned long int>& spsnu, const unsigned int& nopps,
                                         const QList<unsigned int>& ppsl, const QList<unsigned long int>& ppsnu):
    Box(s, t, off, e),
    configurationVersion(cv),
    AVCProfileIndication(avcpi),
    profileCompability(pc),
    AVCLevelIndication(avcli),
    reserved1(r1),
    lengthSizeMinusOne(lsmo),
    reserved2(r2),
    numOfSequenceParameterSets(nosps),
    sequenceParameterSetLength(spsl),
    sequenceParameterSetNALUnit(spsnu),
    numOfPictureParameterSets(nopps),
    pictureParameterSetLength(ppsl),
    pictureParameterSetNALUnit(ppsnu)
{}
QString AVCConfigurationBox::getInfo() {
    QString tmp("");
    tmp.append("Configuration version\t\t");
    tmp.append(QString::number(configurationVersion));
    tmp.append("\nAVC Profile Indication\t\t");
    tmp.append(QString::number(AVCProfileIndication));
    tmp.append("\nReserved1\t\t\t");
    tmp.append(QString::number(reserved1, 2));
    tmp.append("b");
    tmp.append("\nlengthSizeMinusOne\t\t");
    tmp.append(QString::number(lengthSizeMinusOne));
    tmp.append("\nReserved2\t\t\t");
    tmp.append(QString::number(reserved2, 2));
    tmp.append("b");
    tmp.append("\nnumOfSequenceParameterSets\t\t");
    tmp.append(QString::number(numOfSequenceParameterSets));
    for(unsigned int i = 0; i < numOfSequenceParameterSets; ++i) {
        tmp.append("\nsequenceParameterSetLength [");
        tmp.append(QString::number(i));
        tmp.append("]\t");
        tmp.append(QString::number(sequenceParameterSetLength.at(i)));
        tmp.append("\nsequenceParameterSetNALUnit [");
        tmp.append(QString::number(i));
        tmp.append("]\t");
        tmp.append(QString::number(sequenceParameterSetNALUnit.at(i)));
    }
    tmp.append("\nnumOfPictureParameterSets\t\t");
    tmp.append(QString::number(numOfPictureParameterSets));
    for(unsigned int i = 0; i < numOfPictureParameterSets; ++i) {
        tmp.append("\npictureParameterSetLength [");
        tmp.append(QString::number(i));
        tmp.append("]\t\t");
        tmp.append(QString::number(pictureParameterSetLength.at(i)));
        tmp.append("\npictureParameterSetNALUnit [");
        tmp.append(QString::number(i));
        tmp.append("]\t\t");
        tmp.append(QString::number(pictureParameterSetNALUnit.at(i)));
    }
    return tmp;
}
///////////////
MPEG4BitRateBox::MPEG4BitRateBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                 const unsigned long int& bsDB, const unsigned long int& maxbr, const unsigned long int& avgBr):
    Box(s, t, off, e),
    bufferSizeDB(bsDB),
    maxBitrate(maxbr),
    avgBitrate(avgBr)
{}
QString MPEG4BitRateBox::getInfo() {
    QString tmp("");
    tmp.append("Buffer size DB\t\t");
    tmp.append(QString::number(bufferSizeDB));
    tmp.append("\nMax bitrate\t\t");
    tmp.append(QString::number(maxBitrate));
    tmp.append("\nAverage bitrate\t\t");
    tmp.append(QString::number(avgBitrate));
    return tmp;
}
