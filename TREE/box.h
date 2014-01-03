/*!
 * \file Box
 * \details
 * Box
 * FullBox
 * FileTypeBox
 * MovieBox
 * MovieExtendsBox
 * MovieExtendsHeaderBox
 * MovieFragmentBox
 * MovieFragmentHeaderBox
 * MovieFragmentRandomAccessBox
 * MovieFragmentRandomAccessOffsetBox
 * MovieHeaderBox
 * MovieHintInformation
 * MediaBox
 * MediaDataBox
 * MediaHeaderBox
 * MediaInformationBox
 */

#ifndef BOX_H
#define BOX_H

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <qDebug>

class MainWindow;
/*!
 * \brief The Box class
 * is represantion of MP4 Box
 */

class Box
{
protected:
    /*!
     * \brief size size of the box
     */
    unsigned  int size;
    /*!
     * \brief type type of the box
     */
    QString type;
    /*!
     * \brief offset bit offset of the box location
     */
    unsigned long int offset;
    /*!
     * \brief extended_type indicates whether the box has extended type (1) or not (0)
     */
    unsigned  int extended_type;
    /*!
     * \brief otherBoxOffset bit byte distance between begin of box and the begin of boxes from the box
     * (for boxes who are containers)
     */
    unsigned long int otherBoxOffset;
public:
    /*!
     * \brief Box
     * constructor
     * \param s size of box in bytes
     * \param t type of box (created from reading bytes in ASCII code)
     * \param off offset of box in bytes
     * \param e extended_type
     */
    Box(const unsigned  int &s, const QString& t, const unsigned long &off, const unsigned  int &e);
    /*!
     * \brief isContainer
     * \return true when box contains other boxes, false otherwise
     */
    virtual bool isContainer() { return false; }
    /*!
     * \brief getContainetOffset
     * \return offset of child boxes in the box (in bytes)
     */
    virtual unsigned int getContainerOffset() { return 8; }
    /*!
     * \brief getType
     * \return type of the box
     */
    virtual QString getType() { return type; }
    /*!
     * \brief getFullName
     * \return fullName of the box, e.g. "Media Data Box"
     */
    virtual QString getFullName() { return QString(" "); }
    virtual QStandardItemModel* getModel() { return new QStandardItemModel(); }
    /*!
     * \brief getSize
     * \return size in bytes
     */
    virtual unsigned long int getSize() { return size; }
    /*!
     * \brief getOffset
     * \return offset of the box in bytes
     */
    virtual unsigned long int getOffset() const { return offset; }
    /*!
     * \brief getSampleSize
     * This method is overwritten in SampleSizeBox. It should not be used while dealing with other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int SampleSizeBox::getSampleSize(const unsigned long int& id);
     * \param id
     * \return
     */
    virtual unsigned long int getSampleSize(const unsigned long int& id) {
        return id*0;
    }
    /*!
     * \brief getEntryCount
     * This method is overwritten in SampleSizeBox, SyncSampleBox and SampleDescriptionBox. It should not be used while dealing with
     * other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int SampleSizeBox::getEntryCount();
     * \see virtual unsigned long int SyncSampleBox::getEntryCount();
     * \see virtual unsigned long int SampleDescriptionBox::getEntryCount();
     * \param id
     * \return
     */
    virtual unsigned long int getEntryCount() {
        return 0;
    }
    /*!
     * \brief getSyncSample
     * This method is overwritten in SyncSampleBox. It should not be used while dealing with other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int SyncSampleBox::getSyncSample(const unsigned long int& id);
     * \param id
     * \return
     */
    virtual unsigned long int getSyncSample(const int& id) {
        return 0*id;
    }
    /*!
     * \brief getMediaTimeScale()
     * This method is overwritten in MediaHeaderBox. It should not be used while dealing with other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int MediaHeaderBox::getMediaTimeScale();
     * \param id
     * \return
     */
    virtual unsigned long int getMediaTimeScale() {
        return 0;
    }
    /*!
     * \brief getTrackID()
     * This method is overwritten in MediaHeaderBox, TrackHeaderBox, TrackExtendsBox and TrackFragmentHeaderBox.
     * It should not be used while dealing with other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int MediaHeaderBox::getTrackID);
     * \see virtual unsigned long int TrackHeaderBox::getTrackID);
     * \see virtual unsigned long int TrackExtendsBox::getTrackID);
     * \see virtual unsigned long int TrackFragmentHeaderBox::getTrackID);
     * \param id
     * \return
     */
    virtual unsigned int getTrackID() {
        return 0;
    }
    /*!
     * \brief getVersion
     * \return version of the box or 2 if box is not FullBox
     */
    virtual unsigned int getVersion() {
        return 2;
    }
    /*!
     * \brief getDuration
     * This method is overwritten in MovieHeaderBox.
     * It should not be used while dealing with other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int MovieHeaderBox::getDuration()
     * \return
     */
    virtual unsigned long int getDuration() {
        return 0;
    }
    /*!
     * \brief getSampleSize
     * This method is overwritten in SampleSizeBox.
     * It should not be used while dealing with other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int SampelSizeBox::getSampleSize()
     * \return
     */
    virtual unsigned long int getSampleSize() {
        return 0;
    }
    /*!
     * \brief getTimeScale
     * This method is overwritten in MovieHeaderBox.
     * It should not be used while dealing with other boxes.
     * When called on other boxes it returns 0.
     * \see virtual unsigned long int MovieHeaderBox::getTimeScale()
     * \return
     */
    virtual unsigned long int getTimeScale() {
        return 0;
    }
    virtual unsigned int getHeight() {
        return 0;
    }
    virtual unsigned int getWidth() {
        return 0;
    }

    /*!
     * \brief operator <
     * \param b
     * \return true if offset of the box is smaller than offset of box b
     */
    bool operator < (const Box &b) const {
        return offset < b.getOffset();
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////
class FullBox : public Box
{
protected:
    /*!
     * \brief version
     */
    unsigned int version;
    QList<unsigned int> flags;

public:
    FullBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString(" "); }

    unsigned int getVersion() { return version; }
    QList<unsigned int> getFlags() { return flags; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////
class FileTypeBox : public Box
{
protected:
    QString majorBrand;
    unsigned int minorVersion;
    QList<QString> compatibleBrands;
public:
    FileTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const QString& mb,
                const unsigned int& mv, const QList<QString>& cb);
    virtual QString getFullName() { return QString("File Type Box"); }

    virtual QStandardItemModel* getModel();
};
//////////////////////////////////////////////////////////////////////////////////////////////////
class SegmentTypeBox : public Box
{
protected:
    QString majorBrand;
    unsigned int minorVersion;
    QList<QString> compatibleBrands;
public:
    SegmentTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const QString& mb,
                   const unsigned int& mv, const QList<QString>& cb);
    virtual QString getFullName() { return QString("Segment Type Box"); }

    virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
class MediaBox : public Box
{
public:
    MediaBox(const unsigned  int &s, const QString& t, const unsigned long &off, const unsigned  int &e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Media Box"); }
    virtual QStandardItemModel* getModel() {
         QStandardItemModel* model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Media Box is a container for all objects that declare information about the media data within a track.");
        return model;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
class MediaDataBox : public Box
{
public:
    MediaDataBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Media Data Box"); }
    virtual QStandardItemModel* getModel() {
         QStandardItemModel* model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Media Box contains the media data.");
        return model;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
class MediaHeaderBox : public FullBox
{
protected:
    unsigned long int creationTime;
    unsigned long int modificationTime;
    unsigned int timescale;
    unsigned long int duration;
    bool pad;
    QList<unsigned int> language;
    unsigned int predefined;
public:
    MediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v,
                   const QList<unsigned int>& f, const unsigned long int& ct, const unsigned long int& mt, const unsigned int & ts,
                   const unsigned long int & dur, const bool & pad, const QList<unsigned int> & lan, const unsigned int & pd);
    virtual QString getFullName() { return QString("Media Header Box"); }
     virtual QStandardItemModel* getModel();
    virtual unsigned long int getMediaTimeScale() {
        return timescale;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieBox : public Box
{
public:
    MovieBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Box"); }
    virtual QStandardItemModel* getModel() {
         QStandardItemModel* model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Movie Box is container box for all meta-data.");
        return model;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieHeaderBox : public FullBox
{
protected:


    unsigned long int creationTime; //in seconds since midnight, Jan. 1, 1904, in UTC time
    unsigned long int modificationTime;
    unsigned long int timeScale; //ilosc jednostek w sekundzie
    unsigned long int duration; //liczba jednostek czasu wynikajacych ze skali czasu
    unsigned int rate;
    unsigned int volume;
    unsigned int reserved16;
    QList<unsigned long int> reserved32;
    QList<unsigned long int> matrix;
    QList<unsigned long int> predefined;
    unsigned int long nextTrackId;
public:
    MovieHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v,
                   const QList<unsigned int>& f, const unsigned long int &creationTime, const unsigned long int& modificationTime,
                   const unsigned long int &timeScale, const unsigned long int& duration, const unsigned int& rate, const unsigned int& volume,
                   const unsigned int& reserved16, const QList<unsigned long int>& reserved32, const QList<unsigned long int>& mx,
                   const QList<unsigned long int>& pr, const unsigned long int& nextTrackId);
    virtual QString getFullName() { return QString("Movie Header Box "); }

    virtual QStandardItemModel* getModel();
    virtual unsigned long int getDuration() {
        return duration;
    }
    virtual unsigned long int getTimeScale() {
        return timeScale;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MediaInformationBox : public Box
{
public:
    MediaInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Media Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class VideoMediaHeaderBox : public FullBox
{
protected:


    unsigned int graphicsmode;
    QList <unsigned int> opcolor;
public:
    VideoMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e,
                        const unsigned  int& v, const QList<unsigned int>& f, const unsigned int & graphicsmode,
                        const QList <unsigned int> & opcolor);
    virtual QString getFullName() { return QString("Video Media Header Box"); }

    virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SoundMediaHeaderBox : public FullBox
{
protected:


    unsigned int balance;
    unsigned int reserved;
public:
    SoundMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e,
                        const unsigned  int& v, const QList<unsigned int>& f, const unsigned int& bl, const unsigned int&res);
    virtual QString getFullName() { return QString("Sound Media Header Box"); }
     virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class HintMediaHeaderBox : public FullBox
{
protected:


public:
    HintMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Hint Media Header Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class NullMediaHeaderBox : public FullBox
{
protected:


public:
    NullMediaHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Null Media Header Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class DataInformationBox : public Box
{
protected:


public:
    DataInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Data Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class DataEntryUrnBox : public FullBox
{
protected:


public:
    DataEntryUrnBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Data Entry URN Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class DataEntryUrlBox : public FullBox
{
protected:


    QString location;
public:
    DataEntryUrlBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v,
                    const QList<unsigned int>& f, const QString& location);
    virtual QString getFullName() { return QString("Data Entry URL Box"); }

    virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class DataReferenceBox : public FullBox
{
protected:


    unsigned long int entryCount;
public:
    DataReferenceBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v,
                     const QList<unsigned int>& f, const unsigned long int& ec);
    virtual QString getFullName() { return QString("Data Reference Box"); }

    virtual QStandardItemModel* getModel();
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 16; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
class FreeSpaceBox : public Box
{
protected:
    bool container;
public:
    FreeSpaceBox(bool container,const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return container; }
    virtual QString getFullName() { return QString("Free Space Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditBox : public Box
{
public:
    EditBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Edit Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditListBox : public FullBox
{
protected:
     unsigned int entryCount;
    QList <unsigned long int> segmentDuration;
    QList <unsigned long int> mediaTime;
    QList <unsigned int> mediaRateInteger;
    QList <unsigned int> mediaRateFraction;
public:
    EditListBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                const unsigned  int& v, const QList<unsigned int>& f, const unsigned int & entryCount, const QList<unsigned long int>& segmD,
                const QList<unsigned long int>&medT, const QList<unsigned int>& mri, const QList<unsigned int>& mrf);
    virtual QString getFullName() { return QString("Edit List Box"); }

    virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class UserDataBox : public Box
{
public:
    UserDataBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("User Data Box"); }
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 8;}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class CopyRightBox : public FullBox
{
protected:


public:
    CopyRightBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("CopyRight Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieExtendsBox : public Box
{
public:
    MovieExtendsBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Extends Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieExtendsHeaderBox : public FullBox
{
protected:


    unsigned long int fragmentDuration;
public:
    MovieExtendsHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e,
                          const unsigned  int& v, const QList<unsigned int>& f, const unsigned long int& fd);
    virtual QString getFullName() { return QString("Movie Extends Header Box"); }

    virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieFragmentBox : public Box
{
public:
    MovieFragmentBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Fragment Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieFragmentHeaderBox : public FullBox
{
protected:
    unsigned int sequenceNumber;


public:
    MovieFragmentHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e, const long& sn, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Movie Fragment Header Box"); }

    virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieFragmentRandomAccessBox : public Box
{
public:
    MovieFragmentRandomAccessBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Fragment Access Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieFragmentRandomAccessOffsetBox : public FullBox
{
protected:


public:
    MovieFragmentRandomAccessOffsetBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Movie Fragment Random Access Offset Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleDependencyTypeBox : public FullBox
{
protected:


public:
    SampleDependencyTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Dependency Type Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleToGroupBox : public FullBox
{
protected:


public:
    SampleToGroupBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample To Group Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleGroupDescriptionBox : public FullBox
{
protected:


public:
    SampleGroupDescriptionBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Group Description Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleScaleBox : public FullBox
{
protected:


public:
    SampleScaleBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("sample Scale Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SubSampleInformationBox : public FullBox
{
protected:


public:
    SubSampleInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sub Sample Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ProgressiveDownloadInfoBox : public FullBox
{
protected:


public:
    ProgressiveDownloadInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Pogressive Donwload Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MetaBox : public FullBox
{
protected:


public:
    MetaBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 12;}
    virtual QString getFullName() { return QString("Meta Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class XMLBox : public FullBox
{
protected:


public:
    XMLBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("XML Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class BinaryXMLBox : public FullBox
{
protected:


public:
    BinaryXMLBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Binary XML Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ItemLocationBox : public FullBox
{
protected:


public:
    ItemLocationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Item Location Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class PrimaryItemBox : public FullBox
{
protected:


public:
    PrimaryItemBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Primary Item Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ItemProtectionBox : public FullBox
{
protected:


public:
    ItemProtectionBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Item Protection Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ItemInfoEntry : public FullBox
{
protected:


public:
    ItemInfoEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Item unsigned intfo Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ItemInfoBox : public FullBox
{
protected:


public:
    ItemInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Item Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ProtectionSchemeInfoBox : public Box
{
public:
    ProtectionSchemeInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Protection Scheme Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class OriginalFormatBox : public Box
{
public:
    OriginalFormatBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Original Format Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class IPMPInfoBox : public FullBox
{
protected:


public:
    IPMPInfoBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("IPMP Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class IPMPControlBox : public FullBox
{
protected:


public:
    IPMPControlBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("IPMP Control Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SchemeTypeBox : public FullBox
{
protected:


public:
    SchemeTypeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Scheme Type Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SchemeInformationBox : public Box
{
public:
    SchemeInformationBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Scheme Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TimeScaleEntry : public Box
{
public:
    TimeScaleEntry(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Time Scale Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class TimeOffset : public Box
{
public:
    TimeOffset(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Time Offset"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SequenceOffset : public Box
{
public:
    SequenceOffset(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Sequence Offset"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SRTPProcessBox : public FullBox
{
protected:


public:
    SRTPProcessBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("SRTP Process Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieHintInformation : public Box
{
public:
    MovieHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Movie Hint Information"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class RTPMovieHintInformation : public Box
{
public:
    RTPMovieHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("RTP Movie Hint Information"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class RTPTrackSDPHintInformation : public Box
{
public:
    RTPTrackSDPHintInformation(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("RTP Track SDP Hint Information"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class HintStatisticsBox : public Box
{
public:
    HintStatisticsBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e);
    virtual QString getFullName() { return QString("Hint Statistics Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///mpeg dash
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleAuxiliaryInformationSizesBox : public FullBox
{
protected:


public:
    SampleAuxiliaryInformationSizesBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Auxiliary Information Sizes Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SampleAuxiliaryInformationOffsetsBox : public FullBox
{
protected:


public:
    SampleAuxiliaryInformationOffsetsBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Auxiliary Information Offsets Box"); }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class LevelAssignmentBox : public FullBox
{
protected:


public:
    LevelAssignmentBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Level Assignment Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SegmentIndexBox : public FullBox
{
protected:


    unsigned  int referenceId;
    unsigned  int timescale;
    unsigned  int earliestPresentationTime;
    unsigned  int firstOffset;
    unsigned  int reserved;
    QList<bool> referenceType;
    QList<unsigned  int> referenceSize;
    QList<unsigned  int> subsegmentDuration;
    QList<bool> startsWithSAP;
    QList <unsigned  int> SAPType;
    QList <unsigned  int> SAPDeltaTime;

public:
    SegmentIndexBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f, const unsigned int& referenceId,
                    const unsigned int& timescale,const unsigned int& myEarliestPresentationTime, const unsigned int& myFirstOffset, const unsigned int& myReserved,
                    const QList<bool>& referenceType, const QList<unsigned  int> referenceSize, const QList<unsigned  int> & subsegmentDuration,
                    const QList<bool> & startsWithSAP, const QList<unsigned  int>& SAPType, const QList<unsigned  int>& SAPDeltaTime);
    virtual QString getFullName() { return QString("Segment Index Box"); }

    virtual QStandardItemModel* getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SubsegmentIndexBox : public FullBox
{
protected:


public:
    SubsegmentIndexBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Subsegment Index Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ProducerReferenceTimeBox : public FullBox
{
protected:


public:
    ProducerReferenceTimeBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int& e, const unsigned  int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Producer Reference Time Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // BOX_H
