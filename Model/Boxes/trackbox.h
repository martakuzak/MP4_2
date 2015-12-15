/*!
  *\file TrackBox
  *\details
  *TrackBox
  *TrackExtendsBox
  *TrackFragmentBaseMediaDecodeTimeBox
  *TrackFragmentBox
  *TrackFragmentHeaderBox
  *TrackFragmentRandomAccessBox
  *TrackHeaderBox
  *TrackReferenceBox
  *TrackRunBox
  *HandlerBox
 */
#ifndef TRACKBOX_H
#define TRACKBOX_H

#include "box.h"
class MainWindow;

/*!
 * \brief The TrackBox class
 * represents 'trak' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackBox : public Box {
public:
    TrackBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Track Box"); }
    virtual QStandardItemModel *getModel() {
        QStandardItemModel *model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Track Box is a box container for a single track of presentation.");
        return model;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackHeaderBox class
 * represents 'tkhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackHeaderBox : public FullBox {
protected:
    unsigned long int creationTime;
    unsigned long int modificationTime;
    unsigned int trackID;
    unsigned int reserved1;
    unsigned long duration;
    QList<unsigned int> reserved2;
    unsigned int layer;
    unsigned int alternateGroup;
    unsigned int volume;
    unsigned int reserved3;
    QList<unsigned int> matrix;
    unsigned int width;
    unsigned int height;
public:
    TrackHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                   const QList<unsigned int>& f, const unsigned long int& ct, const unsigned long int & mt, const unsigned int & tid,
                   const unsigned int & r1, const unsigned long int & dur, const QList<unsigned int> & r2, const unsigned int & lay,
                   const unsigned int & ag, const unsigned int & vol, const unsigned int & r3, const QList<unsigned int> mx,
                   const unsigned int & wdth, const unsigned int & hght);
    virtual QString getFullName() { return QString("Track Header Box"); }
    virtual QStandardItemModel *getModel();
    unsigned int getTrackID() {
        return trackID;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackReferenceBox class
 * represents 'tref' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackReferenceBox : public Box {
public:
    TrackReferenceBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Track Reference Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackExtendsBox class
 * represents 'trex' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackExtendsBox : public FullBox {
protected:
    unsigned int getTrackID;
    unsigned int defaultSampleDescriptionIndex;
    unsigned int defaultSampleDuration;
    unsigned int defaultSampleSize;
    unsigned int defaultSampleFlags;
public:
    TrackExtendsBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                    const QList<unsigned int>& f, const unsigned int& tid, const unsigned int& dsdi, const unsigned int& dsd,
                    const unsigned int& dss, const unsigned int& dsf);
    virtual QString getFullName() { return QString("Track Extends Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackFragmentBox class
 * represents 'traf' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackFragmentBox : public Box {
public:
    TrackFragmentBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Track Fragment Box"); }
    virtual QStandardItemModel *getModel() {
        QStandardItemModel *model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Track Fragment Box is usefull for defaulting many fields within track fragments structure, it can store the space and complexity of movie fragments default values");
        return model;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackFragmentHeaderBox class
 * represents 'tfhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackFragmentHeaderBox : public FullBox {
protected:
    unsigned int getTrackID;
    unsigned long int baseDataOffset;
    unsigned int sampleDescriptionIndex;
    unsigned int defaultSampleDuration;
    unsigned int defaultSampleSize;
    unsigned int defaultSampleFlags;
public:
    TrackFragmentHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                           const unsigned int& v, const QList<unsigned int>& f, const unsigned int& tid, const unsigned long int& bdo,
                           const unsigned int& dsdi, const unsigned int& dsd, const unsigned int& dss,
                           const unsigned int& dsf);
    virtual QString getFullName() { return QString("Track Fragment Header Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackRunBox class
 * represents 'trun' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackRunBox : public FullBox {
protected:
    unsigned int sampleCount;
    long int dataOffset;
    unsigned int firstSampleFlags;
    QList<unsigned int> sampleDuration;
    QList<unsigned int> sampleSize;
    QList<unsigned int> sampleFlags;
    QList<unsigned int> sampleCompositionTimeOffset;

public:
    TrackRunBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                const QList<unsigned int>& f, const unsigned int& sc, const long int& dof, const unsigned int& fsf,
                const QList<unsigned  int>& sd, const QList<unsigned int>& ss, const QList<unsigned int>& sf,
                const QList<unsigned int>& scto);
    virtual QString getFullName() { return QString("Track Run Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackFragmentRandomAccessBox class
 * represents 'tfra' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TrackFragmentRandomAccessBox : public FullBox {
public:
    TrackFragmentRandomAccessBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Track Fragment Random Access Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TrackFragmentBaseMediaDecodeTimeBox class
 * represents 'tfdt' box
 * \see ISO/IEC 14496-12:2008/FDAM 3:2011 – Information technology – Coding of audio-visual objects – Part 12: ISO base media file format, AMENDMENT 3: DASH support and RTP reception hint track processing
 */
class TrackFragmentBaseMediaDecodeTimeBox : public FullBox {
protected:
    unsigned long int baseMediaDecodeTime;
public:
    TrackFragmentBaseMediaDecodeTimeBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                                        const unsigned int& v, const QList<unsigned int>& f, const unsigned long int& bmdt);
    virtual QString getFullName() { return QString("Track Fragment Base Media Decode Time Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The HandlerBox class
 * represents 'hdlr' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class HandlerBox : public FullBox {
protected:
    unsigned int predefined;
    unsigned int handlerType;
    QList<unsigned int> reserved;
    QString name;
public:
    HandlerBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned  int& v,
               const QList<unsigned int>& f, const unsigned int & pred, const unsigned int & hand, const QList<unsigned int> & res,
               const QString & nam);
    virtual QString getFullName() { return QString("Handler Box"); }
    virtual QStandardItemModel *getModel();
};

#endif // TRACKBOX_H
