/*!
 * \file TrackBox
 * \details
 * TrackBox
 * TrackExtendsBox
 * TrackFragmentBaseMediaDecodeTimeBox
 * TrackFragmentBox
 * TrackFragmentHeaderBox
 * TrackFragmentRandomAccessBox
 * TrackHeaderBox
 * TrackReferenceBox
 * TrackRunBox
 * HandlerBox
 */
#ifndef TRACKBOX_H
#define TRACKBOX_H

#include "box.h"
class MainWindow;

class TrackBox : public Box
{
public:
    TrackBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Track Box"); }
    virtual QString getInfo() {
        return QString("Track Box is a box container for a single track of presentation.");
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackHeaderBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int creationTime;
    unsigned long int modificationTime;
    unsigned int trackID;
    unsigned int reserved1;
    unsigned int long duration;
    QList<unsigned int> reserved2;
    unsigned int layer;
    unsigned int alternateGroup;
    unsigned int volume;
    unsigned int reserved3;
    QList<unsigned long int> matrix;
    unsigned int width;
    unsigned int height;
public:
    TrackHeaderBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v,
                   const QList<unsigned int>& f, const unsigned long int& ct, const unsigned long int & mt, const unsigned int & tid,
                   const unsigned int & r1, const unsigned long int & dur, const QList<unsigned int> & r2, const unsigned int & lay,
                   const unsigned int & ag, const unsigned int & vol, const unsigned int & r3, const QList<unsigned long int> mx,
                   const unsigned int & wdth, const unsigned int & hght);
    virtual QString getFullName() { return QString("Track Header Box"); }
    virtual QString getInfo();
    virtual unsigned int getTrackID() {
        return trackID;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackReferenceBox : public Box
{
public:
    TrackReferenceBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e);
    virtual QString getFullName() { return QString("Track Reference Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackExtendsBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned int getTrackID;
    unsigned int defaultSampleDescriptionIndex;
    unsigned int defaultSampleDuration;
    unsigned int defaultSampleSize;
    unsigned int defaultSampleFlags;
public:
    TrackExtendsBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v,
                    const QList<unsigned int>& f, const unsigned int& tid, const unsigned int& dsdi, const unsigned int& dsd,
                    const unsigned int& dss, const unsigned int& dsf);
    virtual QString getFullName() { return QString("Track Extends Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackFragmentBox : public Box
{
public:
    TrackFragmentBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Track Fragment Box"); }
    virtual QString getInfo() {
        return QString("Track Fragment Box is usefull for defaulting many fields within track fragments structure, it can store the space and complexity of movie fragments default values");
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackFragmentHeaderBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int getTrackID;
    unsigned long int baseDataOffset;
    unsigned long int sampleDescriptionIndex;
    unsigned long int defaultSampleDuration;
    unsigned long int defaultSampleSize;
    unsigned long int defaultSampleFlags;
public:
    TrackFragmentHeaderBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                           const unsigned int& v, const QList<unsigned int>& f, const unsigned long int& tid, const unsigned long int& bdo,
                           const unsigned long int& dsdi, const unsigned long int& dsd, const unsigned long int& dss,
                           const unsigned long int& dsf);
    virtual QString getFullName() { return QString("Track Fragment Header Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackRunBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int sampleCount;
    long int dataOffset;
    unsigned int firstSampleFlags;
    QList<unsigned long int> sampleDuration;
    QList<unsigned long int> sampleSize;
    QList<unsigned int> sampleFlags;
    QList<unsigned long int> sampleCompositionTimeOffset;

public:
    TrackRunBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v,
                const QList<unsigned int>& f, const unsigned long int& sc, const long int& dof, const unsigned int& fsf,
                const QList<unsigned long int>& sd, const QList<unsigned long int>& ss, const QList<unsigned int>& sf,
                const QList<unsigned long int>& scto);
    virtual QString getFullName() { return QString("Track Run Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackFragmentRandomAccessBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
public:
    TrackFragmentRandomAccessBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Track Fragment Random Access Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrackFragmentBaseMediaDecodeTimeBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int baseMediaDecodeTime;
public:
    TrackFragmentBaseMediaDecodeTimeBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                        const unsigned int& v, const QList<unsigned int>& f, const unsigned long int& bmdt);
    virtual QString getFullName() { return QString("Track Fragment Base Media Decode Time Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class HandlerBox : public FullBox
{
private:
    unsigned  int version;
    QList<unsigned int> flags;
    unsigned int predefined;
    unsigned long int handlerType;
    QList<unsigned int> reserved;
    QString name;
public:
    HandlerBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v,
               const QList<unsigned int>& f, const unsigned int & pred, const unsigned int & hand, const QList<unsigned int> & res,
               const QString & nam);
    virtual QString getFullName() { return QString("Handler Box"); }
    virtual QString getInfo();
};

#endif // TRACKBOX_H
