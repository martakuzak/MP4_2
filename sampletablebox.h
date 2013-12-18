/*!
 * \file SampleTableBox
 * \details
 * ChunkLargeOffsetBox
 * ChunkOffsetBox
 * CompactSampleSizeBox
 * CompositionOffsetBox
 * DegradationPriorityBox
 * SampleDescriptionBox
 * SampleScaleBox
 * SampleSizeBox
 * SampleTableBox
 * SampleToChunkBox
 * ShadowSyncSampleBox
 * SyncSampleBox
 * TimeToSampleBox
 * PaddingBitsBox
 */
#ifndef SAMPLETABLEBOX_H
#define SAMPLETABLEBOX_H

#include "box.h"
class MainWindow;

class SampleTableBox : public Box
{
public:
    SampleTableBox(const unsigned int& s=0, const QString& t="", const unsigned long int& off=0, const unsigned int& e=0);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Sample Table Box "); }
    virtual QString getInfo(){
        return QString("Sample Table Box is a container for all the time and data indexing of the media samples in the track.");
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TimeToSampleBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned int entryCount;
    QList<unsigned int> sampleCount;
    QList<unsigned int> sampleDelta;
public:
    TimeToSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,
                    const QList<unsigned int>& f, unsigned int ec, QList<unsigned int> sc, QList<unsigned int> sd);
    virtual QString getFullName() { return QString("Time To Sample Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class CompositionOffsetBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned int entryCount;
    QList<unsigned int> sampleCount;
    QList<unsigned int> sampleOffset;
public:
    CompositionOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,
                         const QList<unsigned int>& f,unsigned int ec, QList<unsigned int> sc, QList<unsigned int> sd);
    virtual QString getFullName() { return QString("Composition Offset Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleDescriptionBox class
 *
 *    -
 *    - Box Types: 'stsd'
 *    - Container: Sample Table Box('stbl')
 *    - Mandatory: Yes
 *    - Quantity: Exactly one
*/
class SampleDescriptionBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned int entryCount;
public:
    SampleDescriptionBox(const unsigned int &s, const QString& t, const unsigned long int& off, const unsigned int &e, const unsigned int& v,
                         const QList<unsigned int>& f, const unsigned int &ec);
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return (16); }
    virtual QString getFullName() { return QString("Sample Description Box"); }
    /*!
     * \brief getEntryCount
     * \return entry_count
     */
    unsigned long int getEntryCount() { return entryCount; }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleSizeBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int sampleSize;
    unsigned long int sampleCount;
    QList<unsigned long int> entrySize;
public:
    SampleSizeBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,
                  const QList<unsigned int>& f, const unsigned long int &sz, const unsigned long int & sc,
                  const QList<unsigned long int> & es);
    virtual QString getFullName() { return QString("Sample Size Box"); }
    virtual QString getInfo();
    virtual unsigned long int getSampleSize(const unsigned long int& id) {
        return entrySize.at(id);
    }
    virtual unsigned long int getEntryCount() {
        return sampleCount;
    }
    virtual unsigned long int getSampleSize() {
        return sampleSize;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class CompactSampleSizeBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
public:
    CompactSampleSizeBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Compact Sample Size Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleToChunkBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int entryCount;
    QList<unsigned long int> firstChunk;
    QList<unsigned long int> samplesPerChunk;
    QList<unsigned long int> sampleDescriptionIndex;
public:
    SampleToChunkBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,
                     const QList<unsigned int>& f, const unsigned long int &entryCount, const QList<unsigned long int>& fc,
                     const QList<unsigned long int>& spc, const QList<unsigned long int>& sdi);
    virtual QString getFullName() { return QString("Sample To Chunk Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ChunkOffsetBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int entryCount;
    QList<unsigned long int> chunkOffset;
public:
    ChunkOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,
                   const QList<unsigned int>& f, const unsigned long int& ec, const QList<unsigned long int>& co);
    virtual QString getFullName() { return QString("Chunk Offset Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ChunkLargeOffsetBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int entryCount;
    QList<unsigned long int> chunkOffset;
public:
    ChunkLargeOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,
                        const QList<unsigned int>& f, const unsigned long int& ec, const QList<unsigned long int>& co);
    virtual QString getFullName() { return QString("Chunk Large Offset Box"); }
    virtual QString getInfo();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SyncSampleBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
    unsigned long int entryCount;
    QList<unsigned long int> sampleNumber;
public:
    SyncSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v,
                  const QList<unsigned int>& f, const unsigned long int&ec, const QList<unsigned long int> sn);
    virtual QString getFullName() { return QString("Sync Sample Box"); }
    virtual QString getInfo();
    virtual unsigned long int getEntryCount() {
        return entryCount;
    }
    virtual unsigned long int getSyncSample(const int& id) {
        return sampleNumber.at(id);
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ShadowSyncSampleBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
public:
    ShadowSyncSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Shadow Sync Sample Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class DegradationPriorityBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
public:
    DegradationPriorityBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Degradation Priority Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class PaddingBitsBox : public FullBox
{
private:
    unsigned int version;
    QList<unsigned int> flags;
public:
    PaddingBitsBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& e, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Padding Bits Box"); }
};
#endif // SAMPLETABLEBOX_H
