/*!
  *\file SampleTableBox
  *\details
  *ChunkLargeOffsetBox
  *ChunkOffsetBox
  *CompactSampleSizeBox
  *CompositionOffsetBox
  *DegradationPriorityBox
  *SampleDescriptionBox
  *SampleScaleBox
  *SampleSizeBox
  *SampleTableBox
  *SampleToChunkBox
  *ShadowSyncSampleBox
  *SyncSampleBox
  *TimeToSampleBox
  *PaddingBitsBox
 */
#ifndef SAMPLETABLEBOX_H
#define SAMPLETABLEBOX_H

#include "box.h"
class MainWindow;

/*!
 * \brief The SampleTableBox class represents 'stbl' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SampleTableBox : public Box {
public:
    SampleTableBox(const unsigned long int& s=0, const QString& t="", const unsigned long int& off=0);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Sample Table Box "); }
    virtual QStandardItemModel *getModel() {
        QStandardItemModel *model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Sample Table Box is a container for all the time and data indexing of the media samples in the track.");
        return model;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TimeToSampleBox class represents 'stts' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TimeToSampleBox : public FullBox {
private:
    unsigned int entryCount;
    QList<unsigned int> sampleCount;
    QList<unsigned int> sampleDelta;
public:
    TimeToSampleBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                    const QList<unsigned int>& f, unsigned int ec, QList<unsigned int> sc, QList<unsigned int> sd);
    virtual QString getFullName() { return QString("Time To Sample Box"); }  
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The CompositionOffsetBox class represents 'ctts' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class CompositionOffsetBox : public FullBox {
private:
    unsigned int entryCount;
    QList<unsigned int> sampleCount;
    QList<unsigned int> sampleOffset;
public:
    CompositionOffsetBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                         const QList<unsigned int>& f,unsigned int ec, QList<unsigned int> sc, QList<unsigned int> sd);
    virtual QString getFullName() { return QString("Composition Offset Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
  *\brief The SampleDescriptionBox class represents 'stsd' box
  * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
*/
class SampleDescriptionBox : public FullBox {
private:
    unsigned int entryCount;
public:
    SampleDescriptionBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                         const QList<unsigned int>& f, const unsigned int &ec);
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return (16); }
    virtual QString getFullName() { return QString("Sample Description Box"); }
    /*!
      *\brief getEntryCount
      *\return entry_count
     */
    unsigned long int getEntryCount() { return entryCount; }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleSizeBox class represents 'stsz' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SampleSizeBox : public FullBox {
private:
    unsigned long int sampleSize;
    unsigned long int sampleCount;
    QList<unsigned int> entrySize;
public:
    SampleSizeBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                  const QList<unsigned int>& f, const unsigned long int &sz, const unsigned long int & sc,
                  const QList<unsigned int> & es);
    virtual QString getFullName() { return QString("Sample Size Box"); }
    virtual QStandardItemModel *getModel();
    unsigned long int getSampleSize(const unsigned long int& id) {
        return entrySize.at(id);
    }
    unsigned long int getEntryCount() {
        return sampleCount;
    }
    unsigned long int getSampleSize() {
        return sampleSize;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The CompactSampleSizeBox class represents 'stz2' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class CompactSampleSizeBox : public FullBox {
    unsigned int reserved;
    unsigned int fieldSize;
    unsigned int sampleCount;
    QList <unsigned int> entrySize;
public:
    CompactSampleSizeBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                         const QList<unsigned int>& f, const unsigned int& res, const unsigned int& fs, const unsigned long int& sc,
                         const QList<unsigned int>& es);
    virtual QString getFullName() { return QString("Compact Sample Size Box"); }
    virtual QStandardItemModel *getModel();
    unsigned long int getSampleSize(const unsigned long int& id) {
        return entrySize.at(id);
    }
    unsigned long int getEntryCount() {
        return sampleCount;
    }
    unsigned long int getSampleSize() {
        return fieldSize;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleToChunkBox class represents 'stsc' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SampleToChunkBox : public FullBox {
private:
    unsigned long int entryCount;
    QList<unsigned long int> firstChunk;
    QList<unsigned long int> samplesPerChunk;
    QList<unsigned long int> sampleDescriptionIndex;
public:
    SampleToChunkBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                     const QList<unsigned int>& f, const unsigned long int &entryCount, const QList<unsigned long int>& fc,
                     const QList<unsigned long int>& spc, const QList<unsigned long int>& sdi);
    virtual QString getFullName() { return QString("Sample To Chunk Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ChunkOffsetBox class represents 'stco' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ChunkOffsetBox : public FullBox {
private:
     unsigned long int entryCount;
    QList<unsigned long int> chunkOffset;
public:
    ChunkOffsetBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                   const QList<unsigned int>& f, const unsigned long int& ec, const QList<unsigned long int>& co);
    virtual QString getFullName() { return QString("Chunk Offset Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ChunkLargeOffsetBox class represents 'co64' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ChunkLargeOffsetBox : public FullBox {
private:
    unsigned long int entryCount;
    QList<unsigned long int> chunkOffset;
public:
    ChunkLargeOffsetBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                        const QList<unsigned int>& f, const unsigned long int& ec, const QList<unsigned long int>& co);
    virtual QString getFullName() { return QString("Chunk Large Offset Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SyncSampleBox class represents 'stss' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SyncSampleBox : public FullBox {
private:
    unsigned long int entryCount;
    QList<unsigned long int> sampleNumber;
public:
    SyncSampleBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v,
                  const QList<unsigned int>& f, const unsigned long int&ec, const QList<unsigned long int> sn);
    virtual QString getFullName() { return QString("Sync Sample Box"); }
    virtual QStandardItemModel *getModel();
    unsigned long int getEntryCount() {
        return entryCount;
    }
    unsigned long int getSyncSample(const int& id) {
        return sampleNumber.at(id);
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ShadowSyncSampleBox class represents 'stsh' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ShadowSyncSampleBox : public FullBox{
public:
    ShadowSyncSampleBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Shadow Sync Sample Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The DegradationPriorityBox class represents 'stdp' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class DegradationPriorityBox : public FullBox {
public:
    DegradationPriorityBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Degradation Priority Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The PaddingBitsBox class represents 'padb' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class PaddingBitsBox : public FullBox {
public:
    PaddingBitsBox(const unsigned long int& s, const QString& t, const unsigned long int& off,const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Padding Bits Box"); }
};
#endif // SAMPLETABLEBOX_H
