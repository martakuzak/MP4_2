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
QStandardItemModel* SampleEntry::getModel() {
    QStandardItemModel* model = new QStandardItemModel(2, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Reserved");
    QString tmp("");
    for(int i = 0; i < reserved.size(); ++i) {
        tmp.append(QString::number(reserved.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(0, 1, QModelIndex()), tmp);
    tmp.clear();
    model->setData(model->index(1, 0, QModelIndex()), "Data reference index");
    model->setData(model->index(1, 1, QModelIndex()), QString::number(dataReferenceIndex));

    return model;
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
QStandardItemModel* VisualSampleEntry::getModel() {
    QStandardItemModel* model = new QStandardItemModel(2, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Reserved");
    QString tmp("");
    for(int i = 0; i < reserved.size(); ++i) {
        tmp.append(QString::number(reserved.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(0, 1, QModelIndex()), tmp);
    tmp.clear();
    model->setData(model->index(1, 0, QModelIndex()), "Data reference index");
    model->setData(model->index(1, 1, QModelIndex()), QString::number(dataReferenceIndex));
    model->setData(model->index(2, 0, QModelIndex()), "Predefined");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(predefined));
    model->setData(model->index(3, 0, QModelIndex()), "Reserved2");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(reserved2));
    model->setData(model->index(4, 0, QModelIndex()), "Predefined1");
    tmp.clear();
    int p1Size = predefined1.size();
    for (int i = 0; i<p1Size; ++i) {
        tmp.append(QString::number(predefined1.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(4, 1, QModelIndex()), tmp);
    model->setData(model->index(5, 0, QModelIndex()), "Width");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(width));
    model->setData(model->index(6, 0, QModelIndex()), "Height");
    model->setData(model->index(6, 1, QModelIndex()), QString::number(height));
    model->setData(model->index(7, 0, QModelIndex()), "Hotizontal resolution");
    model->setData(model->index(7, 1, QModelIndex()), QString::number(horizontalResolution));
    model->setData(model->index(8, 0, QModelIndex()), "Vertical resolution");
    model->setData(model->index(8, 1, QModelIndex()), QString::number(verticalResolution));
    model->setData(model->index(9, 0, QModelIndex()), "Reseserved3");
    model->setData(model->index(9, 1, QModelIndex()), QString::number(reserved3));
    model->setData(model->index(10, 0, QModelIndex()), "Frame count");
    model->setData(model->index(10, 1, QModelIndex()), QString::number(frameCount));
    model->setData(model->index(11, 0, QModelIndex()), "Compressor name");
    model->setData(model->index(11, 1, QModelIndex()), compressorname);
    model->setData(model->index(12, 0, QModelIndex()), "Depth");
    model->setData(model->index(12, 1, QModelIndex()), QString::number(depth));
    model->setData(model->index(13, 0, QModelIndex()), "Predefined2");
    model->setData(model->index(13, 1, QModelIndex()), QString::number(predefined2));

    return model;
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
QStandardItemModel* AudioSampleEntry::getModel() {
    QStandardItemModel* model = new QStandardItemModel(8, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Reserved");
    QString tmp("");
    for(int i = 0; i < reserved.size(); ++i) {
        tmp.append(QString::number(reserved.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(0, 1, QModelIndex()), tmp);
    tmp.clear();
    model->setData(model->index(1, 0, QModelIndex()), "Data reference index");
    model->setData(model->index(1, 1, QModelIndex()), QString::number(dataReferenceIndex));
    model->setData(model->index(2, 0, QModelIndex()), "Reserved1");
    tmp.clear();
    int res1Size = reserved1.size();
    for (int i = 0; i<res1Size; ++i) {
        tmp.append(QString::number(reserved1.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(2, 1, QModelIndex()), tmp);
    model->setData(model->index(3, 0, QModelIndex()), "Channel count");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(channelCount));
    model->setData(model->index(4, 0, QModelIndex()), "Sample size");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(sampleSize));
    model->setData(model->index(5, 0, QModelIndex()), "Predefined");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(predefined));
    model->setData(model->index(6, 0, QModelIndex()), "Reserved2");
    model->setData(model->index(6, 1, QModelIndex()), QString::number(reserved2));
    model->setData(model->index(7, 0, QModelIndex()), "Sample rate");
    model->setData(model->index(7, 1, QModelIndex()), QString::number(sampleRate));

    return model;
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
QStandardItemModel* AVCConfigurationBox::getModel() {
    QStandardItemModel* model = new QStandardItemModel(5 + 2*numOfSequenceParameterSets +
                                                       2*numOfPictureParameterSets, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Configuration version");
    model->setData(model->index(0, 1, QModelIndex()), QString::number(configurationVersion));
    model->setData(model->index(1, 0, QModelIndex()), "AVC Profile Indication");
    model->setData(model->index(1, 1, QModelIndex()), QString::number(AVCProfileIndication));
    model->setData(model->index(2, 0, QModelIndex()), "Reserved1");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(reserved1, 2) + "b");
    model->setData(model->index(3, 0, QModelIndex()), "Length size minus one");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(lengthSizeMinusOne));
    model->setData(model->index(4, 0, QModelIndex()), "Reserved2");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(reserved2, 2) + "b");
    model->setData(model->index(5, 0, QModelIndex()), "Num of sequence paramter sets");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(numOfSequenceParameterSets));
    int index = 6;
    for(unsigned int i = 0; i < numOfSequenceParameterSets; ++ i) {
        model->setData(model->index(index, 0, QModelIndex()), "sequenceParameterSetLength[" +
                       QString::number(i) + "]");
        model->setData(model->index(index, 1, QModelIndex()),
                       QString::number(sequenceParameterSetLength.at(i)));
        model->setData(model->index(index, 0, QModelIndex()), "sequenceParameterSetNALUnit[" +
                       QString::number(i) + "]");
        model->setData(model->index(index, 1, QModelIndex()),
                       QString::number(sequenceParameterSetNALUnit.at(i)));
        ++ index;
    }
    model->setData(model->index(5, 0, QModelIndex()), "Num of picture paramter sets");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(numOfPictureParameterSets));
    for(unsigned int i = 0; i < numOfPictureParameterSets; ++ i) {
        model->setData(model->index(index, 0, QModelIndex()), "pictureParameterSetLength[" +
                       QString::number(i) + "]");
        model->setData(model->index(index, 1, QModelIndex()),
                       QString::number(pictureParameterSetLength.at(i)));
        model->setData(model->index(index, 0, QModelIndex()), "pictureParameterSetNALUnit[" +
                       QString::number(i) + "]");
        model->setData(model->index(index, 1, QModelIndex()),
                       QString::number(pictureParameterSetNALUnit.at(i)));
        ++ index;
    }

    return model;
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
QStandardItemModel* MPEG4BitRateBox::getModel() {
    QStandardItemModel* model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Buffer size DB");
    model->setData(model->index(0, 1, QModelIndex()), QString::number(bufferSizeDB));
    model->setData(model->index(1, 0, QModelIndex()), "Max bitrate");
    model->setData(model->index(1, 1, QModelIndex()), QString::number(maxBitrate));
    model->setData(model->index(2, 0, QModelIndex()), "Average bitrate");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(avgBitrate));

    return model;
}
