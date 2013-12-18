/*!
 * \file SampleEntry
 * \details
 * SampleEntry
 * HintSampleEntry
 * VisualSampleEntry
 * AudioSampleEntry
 * MP4AudioSampleEntry
 * MP4VisualSampleEntry
 * MpegSampleEntry
 * ObjectDescriptorBox
 * ESDBox
 */
#ifndef SAMPLEENTRY_H
#define SAMPLEENTRY_H

#include "box.h"
class MainWindow;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleEntry: public Box {
private:
    QList<unsigned int> reserved;
    unsigned int dataReferenceIndex;
public:
    SampleEntry(const unsigned int &s, const QString &t, const unsigned long int &off, const unsigned int &e, const QList<unsigned int>& res,
                const unsigned int &dri);
    virtual QString getFullName() { return QString("Sample Entry"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class HintSampleEntry: public SampleEntry {
public:
    HintSampleEntry(const unsigned int &s, const QString &t, const unsigned long int &off, const unsigned int & e,
                    const QList<unsigned int>& res, const unsigned int &dri);
    virtual QString getFullName() { return QString("Hint Sample Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class VisualSampleEntry: public SampleEntry {
private:
    unsigned int predefined;
    unsigned int reserved2;
    QList<unsigned int> predefined1;
    unsigned int width;
    unsigned int height;
    unsigned int horizontalResolution; // 72 dpi
    unsigned int verticalResolution; // 72 dpi
    unsigned int reserved3;
    unsigned int frameCount;
    QString compressorname;
    unsigned int depth;
    int predefined2;
public:
    VisualSampleEntry(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                      const QList<unsigned int>& res, const unsigned int &dri, const unsigned int &pd, const unsigned int& r2,
                      const QList<unsigned int>& pd1,const unsigned int& wdth, const unsigned int& hght, const unsigned  int& hr,
                      const unsigned int& vr, const unsigned int& r3, const unsigned int& fc, const QString & csn,
                      const unsigned int& dpth, const int &pd2);
    virtual bool isContainer() { return true; }
    unsigned int getWidth() { return width; }
    QString getQStringWidth() { return QString::number(width); }
    unsigned int getHeight() { return height; }
    unsigned int hResolution() { return horizontalResolution; }
    unsigned int vResolution() { return verticalResolution; }
    virtual QString getFullName() { return QString("Visual Sample Entry"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class AudioSampleEntry: public SampleEntry{
private:
    QList<unsigned int> reserved1;
    unsigned int channelCount;
    unsigned int sampleSize;
    unsigned int predefined;
    unsigned int reserved2;
    unsigned int sampleRate;
public:
    AudioSampleEntry(const unsigned int &s, const QString &t, const unsigned long int &off, const unsigned int & e,
                     const QList<unsigned int>& res, const unsigned int &dri, const QList <unsigned int> & res1,
                     const unsigned int & chc, const unsigned int & ss, const unsigned int & pred, const unsigned int & res2,
                     const unsigned int & srate);
    virtual QString getFullName() { return QString("Audio Sample Entry"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MP4VisualSampleEntry : public VisualSampleEntry
{
public:
    MP4VisualSampleEntry(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                         const QList<unsigned int>& res, const unsigned int &dri, const unsigned int &pd, const unsigned int& r2,
                         const QList<unsigned int>& pd1,const unsigned int& wdth, const unsigned int& hght, const unsigned  int& hr,
                         const unsigned int& vr, const unsigned int& r3, const unsigned int& fc, const QString & csn,
                         const unsigned int& dpth, const unsigned int &pd2);
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 86; }
    virtual QString getFullName() { return QString("MP4 Visual Sample Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MP4AudioSampleEntry : public AudioSampleEntry
{
public:
    MP4AudioSampleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                        const QList<unsigned int>& res, const unsigned int &dri, const QList<unsigned int> &res1,
                        const unsigned int &chc, const unsigned int &ss, const unsigned int &pred, const unsigned int &res2,
                        const unsigned int &srate);
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 36; }
    virtual QString getFullName() { return QString("MP4 Audio Sample Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MpegSampleEntry : public SampleEntry
{
public:
    MpegSampleEntry(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int & e,
                    const QList<unsigned int> &res, const unsigned  int& dri);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Mpeg Sample Entry"); }
};
//////////////MP4//////
class ObjectDescriptorBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
public:
    ObjectDescriptorBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Object Descriptor Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ESDBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
public:
    ESDBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,const QList<unsigned int>& f);
    virtual unsigned int getContainerOffset() { return 8; }
    virtual QString getFullName() { return QString("ESD Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class AVCSampleEntry: public VisualSampleEntry
{
public:
    AVCSampleEntry(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                   const QList<unsigned int>& res, const unsigned int &dri, const unsigned int &pd, const unsigned int& r2,
                   const QList<unsigned int>& pd1,const unsigned int& wdth, const unsigned int& hght, const unsigned  int& hr,
                   const unsigned int& vr, const unsigned int& r3, const unsigned int& fc, const QString & csn,
                   const unsigned int& dpth, const unsigned int &pd2);
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 86; }
    virtual QString getFullName() { return QString("AVC Sample Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class AVCConfigurationBox: public Box
{
    unsigned int configurationVersion;
    unsigned int AVCProfileIndication;
    unsigned int profileCompability;
    unsigned int AVCLevelIndication;
    unsigned int reserved1;
    unsigned int lengthSizeMinusOne;
    unsigned int reserved2;
    unsigned int numOfSequenceParameterSets;
    QList<unsigned int> sequenceParameterSetLength;
    QList<unsigned long int> sequenceParameterSetNALUnit;
    unsigned int numOfPictureParameterSets;
    QList<unsigned int> pictureParameterSetLength;
    QList<unsigned long int> pictureParameterSetNALUnit;
public:
    AVCConfigurationBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                        const unsigned int& cv, const unsigned int& avcpi, const unsigned int& pc, const unsigned int& avcli,
                        const unsigned int& r1, const unsigned int& lsmo, const unsigned int& r2, const unsigned int& nosps,
                        const QList<unsigned int>& spsl, const QList<unsigned long int>& spsnu, const unsigned int& nopps,
                        const QList<unsigned int>& ppsl, const QList<unsigned long int>& ppsnu);
    virtual bool isContainer() { return false; }
    virtual QString getFullName() { return QString("AVC Configuration box"); }
    virtual QString getInfo();

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MPEG4BitRateBox: public Box {
    unsigned long int bufferSizeDB;
    unsigned long int maxBitrate;
    unsigned long int avgBitrate;
public:
    MPEG4BitRateBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                        const unsigned long int& bsDB, const unsigned long int& maxbr, const unsigned long int& avgBr);
    virtual bool isContainer() { return false; }
    virtual QString getFullName() { return QString("MPEG4 Bitrate Box"); }
    virtual QString getInfo();
};
#endif // SAMPLEENTRY_H
