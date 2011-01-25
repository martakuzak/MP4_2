/*!
  *\file Box
  *\details
  *Box
  *FullBox
  *FileTypeBox
  *MovieBox
  *MovieExtendsBox
  *MovieExtendsHeaderBox
  *MovieFragmentBox
  *MovieFragmentHeaderBox
  *MovieFragmentRandomAccessBox
  *MovieFragmentRandomAccessOffsetBox
  *MovieHeaderBox
  *MovieHintInformation
  *MediaBox
  *MediaDataBox
  *MediaHeaderBox
  *MediaInformationBox
 */

#ifndef BOX_H
#define BOX_H

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <qDebug>

/*!
  *\brief The Box class
  * is representation of MP4 box. It contains parameters that all the classes should have.
  *\see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class Box {
protected:
    /*!
      *\brief size size of the box
     */
    unsigned long int size;
    /*!
      *\brief type type of the box
     */
    QString type;
    /*!
      *\brief offset byte offset of the box location
     */
    unsigned long int offset;
public:
    /*!
      *\brief Box
      *constructor
      *\param s size of box in bytes
      *\param t type of box (created from reading bytes in ASCII code)
      *\param off offset of box in bytes
     */
    Box(const unsigned long int &s, const QString& t, const unsigned long &off);
    /*!
      *\brief getType
      *\return type of the box
     */
    virtual QString getType() { return type; }
    /*!
      *\brief getSize
      *\return size in bytes
     */
    virtual unsigned int getSize() { return size; }
    /*!
      *\brief getOffset
      *\return offset of the box in bytes
     */
    virtual unsigned long int getOffset() const { return offset; }
    /*!
      *\brief isContainer
      *\return true when box contains other boxes, false otherwise
     */
    virtual bool isContainer() { return false; }
    /*!
      *\brief getContainetOffset
      *\return offset of child boxes in the box (in bytes)
     */
    virtual unsigned int getContainerOffset() { return 8; }
    /*!
      *\brief getFullName
      *\return fullName of the box, e.g. "Media Data Box"
     */
    virtual QString getFullName() { return QString(" "); }
    /*!
     * \brief getModel
     * Constructs and return QStandardItemModel object that is appropriate for graphical representation
     * (for elements like QTreeView, QTableView etc.). Returned model contains names of the box attributes
     * and their value. Each pair it's in its own row. Name of the attribute is in column 0, value - column 1.
     * \return model of Box attributes
     */
    virtual QStandardItemModel *getModel() { return new QStandardItemModel(); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The FullBox class represents Full Box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class FullBox : public Box {
protected:
    /*!
      *\brief version indicates version of FullBox. When set to 1, some of the paramaters can have bigger
      * size (64-bit instead of 32-bit)
     */
    unsigned int version;
    /*!
     * \brief flags 3 unsigned int numbers that can determine forward content of the box or meaning of
     * the other attributes.
     */
    QList<unsigned int> flags;

public:
    FullBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
            const QList<unsigned int>& f);
    virtual QString getFullName() { return QString(" "); }
    unsigned int getVersion() { return version; }
    QList<unsigned int> getFlags() { return flags; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The FileTypeBox class represents 'ftyp' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class FileTypeBox : public Box {
protected:
    QString majorBrand;
    unsigned int minorVersion;
    QList<QString> compatibleBrands;
public:
    FileTypeBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const QString& mb,
                const unsigned int& mv, const QList<QString>& cb);
    virtual QString getFullName() { return QString("File Type Box"); }
    virtual QStandardItemModel *getModel();
};
//////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SegmentTypeBox class represents 'styp' box
 */
class SegmentTypeBox : public Box {
protected:
    QString majorBrand;
    unsigned int minorVersion;
    QList<QString> compatibleBrands;
public:
    SegmentTypeBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const QString& mb,
                   const unsigned int& mv, const QList<QString>& cb);
    virtual QString getFullName() { return QString("Segment Type Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
/* \brief The MediaBox class represents 'mdia' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
*/
class MediaBox : public Box {
public:
    MediaBox(const unsigned long int& s, const QString& t, const unsigned long &off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Media Box"); }
    virtual QStandardItemModel *getModel() {
         QStandardItemModel *model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Media Box is a container for all objects that declare information about the media data within a track.");
        return model;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
/*! * \brief The MediaDataBox class represents 'mdat' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
/*! */
class MediaDataBox : public Box {
public:
    MediaDataBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Media Data Box"); }
    virtual QStandardItemModel *getModel() {
         QStandardItemModel *model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Media Box contains the media data.");
        return model;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MediaHeaderBox class represents 'mdhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MediaHeaderBox : public FullBox {
protected:
    unsigned long int creationTime;
    unsigned long int modificationTime;
    unsigned int timescale;
    unsigned long int duration;
    bool pad;
    QList<unsigned int> language;
    unsigned int predefined;
public:
    MediaHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                   const QList<unsigned int>& f, const unsigned long int& ct, const unsigned long int& mt, const unsigned int & ts,
                   const unsigned long int & dur, const bool & pad, const QList<unsigned int> & lan, const unsigned int & pd);
    virtual QString getFullName() { return QString("Media Header Box"); }
    virtual QStandardItemModel *getModel();
    unsigned int getMediaTimeScale() {
        return timescale;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieBox class represents 'moov' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieBox : public Box {
public:
    MovieBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Box"); }
    virtual QStandardItemModel *getModel() {
         QStandardItemModel *model = new QStandardItemModel(1,1,0);
        model->setData(model->index(0, 0, QModelIndex()), "Movie Box is container box for all meta-data.");
        return model;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieHeaderBox class represents 'mvhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieHeaderBox : public FullBox {
protected:
    unsigned long int creationTime; //in seconds since midnight, Jan. 1, 1904, in UTC time
    unsigned long int modificationTime;
    unsigned long int timeScale; //ilosc jednostek w sekundzie
    unsigned long int duration; //liczba jednostek czasu wynikajacych ze skali czasu
    unsigned int rate;
    unsigned int volume;
    unsigned int reserved16;
    QList<unsigned int> reserved32;
    QList<unsigned int> matrix;
    QList<unsigned int> predefined;
    unsigned int nextTrackId;
public:
    MovieHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                   const QList<unsigned int>& f, const unsigned long int &creationTime, const unsigned long int& modificationTime,
                   const unsigned long int &timeScale, const unsigned long int& duration, const unsigned int& rate, const unsigned int& volume,
                   const unsigned int& reserved16, const QList<unsigned int>& reserved32, const QList<unsigned int>& mx,
                   const QList<unsigned int>& pr, const unsigned int& nextTrackId);
    virtual QString getFullName() { return QString("Movie Header Box "); }
    virtual QStandardItemModel *getModel();
    unsigned long int getDuration() {
        return duration;
    }
    unsigned int getTimeScale() {
        return timeScale;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MediaInformationBox class represents 'minf' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MediaInformationBox : public Box {
public:
    MediaInformationBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Media Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The VideoMediaHeaderBox class represents 'vmhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class VideoMediaHeaderBox : public FullBox {
protected:
    unsigned int graphicsmode;
    QList <unsigned int> opcolor;
public:
    VideoMediaHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                        const unsigned int& v, const QList<unsigned int>& f, const unsigned int & graphicsmode,
                        const QList <unsigned int> & opcolor);
    virtual QString getFullName() { return QString("Video Media Header Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SoundMediaHeaderBox class represents 'smhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SoundMediaHeaderBox : public FullBox {
protected:
    unsigned int balance;
    unsigned int reserved;
public:
    SoundMediaHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                        const unsigned int& v, const QList<unsigned int>& f, const unsigned int& bl, const unsigned int&res);
    virtual QString getFullName() { return QString("Sound Media Header Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The HintMediaHeaderBox class represents 'hmhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class HintMediaHeaderBox : public FullBox {
public:
    HintMediaHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Hint Media Header Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The NullMediaHeaderBox class represents 'nmhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class NullMediaHeaderBox : public FullBox{
public:
    NullMediaHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Null Media Header Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The DataInformationBox class represents 'dinf' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class DataInformationBox : public Box {
public:
    DataInformationBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Data Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The DataEntryUrnBox class represents 'urn ' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class DataEntryUrnBox : public FullBox {
public:
    DataEntryUrnBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Data Entry URN Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The DataEntryUrlBox class represents 'url ' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class DataEntryUrlBox : public FullBox {
protected:
    QString location;
public:
    DataEntryUrlBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                    const QList<unsigned int>& f, const QString& location);
    virtual QString getFullName() { return QString("Data Entry URL Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The DataReferenceBox class represents 'dref' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class DataReferenceBox : public FullBox {
protected:
    unsigned int entryCount;
public:
    DataReferenceBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                     const QList<unsigned int>& f, const unsigned int& ec);
    virtual QString getFullName() { return QString("Data Reference Box"); }
    virtual QStandardItemModel *getModel();
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 16; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The FreeSpaceBox class represents 'free' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class FreeSpaceBox : public Box {
protected:
    bool container;
public:
    FreeSpaceBox(bool container,const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return container; }
    virtual QString getFullName() { return QString("Free Space Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The EditBox class represents 'edts' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class EditBox : public Box {
public:
    EditBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Edit Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The EditListBox class represents 'elst' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class EditListBox : public FullBox {
protected:
     unsigned int entryCount;
    QList <unsigned long int> segmentDuration;
    QList <unsigned long int> mediaTime;
    QList <unsigned int> mediaRateInteger;
    QList <unsigned int> mediaRateFraction;
public:
    EditListBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                const unsigned int& v, const QList<unsigned int>& f, const unsigned int & entryCount, const QList<unsigned long int>& segmD,
                const QList<unsigned long int>&medT, const QList<unsigned int>& mri, const QList<unsigned int>& mrf);
    virtual QString getFullName() { return QString("Edit List Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The UserDataBox class represents 'udta' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class UserDataBox : public Box {
public:
    UserDataBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("User Data Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The CopyRightBox class represents 'cprt' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class CopyRightBox : public FullBox {
public:
    CopyRightBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("CopyRight Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieExtendsBox class represents 'mvex' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieExtendsBox : public Box {
public:
    MovieExtendsBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Extends Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieExtendsHeaderBox class represents 'mehd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieExtendsHeaderBox : public FullBox {
protected:
    unsigned long int fragmentDuration;
public:
    MovieExtendsHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                          const unsigned int& v, const QList<unsigned int>& f, const unsigned long int& fd);
    virtual QString getFullName() { return QString("Movie Extends Header Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieFragmentBox class represents 'moof' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieFragmentBox : public Box {
public:
    MovieFragmentBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Fragment Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieFragmentHeaderBox class represents 'mfhd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieFragmentHeaderBox : public FullBox {
protected:
    unsigned int sequenceNumber;
public:
    MovieFragmentHeaderBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const long& sn, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Movie Fragment Header Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieFragmentRandomAccessBox class represents 'mfra' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieFragmentRandomAccessBox : public Box {
public:
    MovieFragmentRandomAccessBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Movie Fragment Access Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieFragmentRandomAccessOffsetBox class represents 'mfro' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieFragmentRandomAccessOffsetBox : public FullBox {
public:
    MovieFragmentRandomAccessOffsetBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Movie Fragment Random Access Offset Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleDependencyTypeBox class represents 'sdtp' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SampleDependencyTypeBox : public FullBox {
public:
    SampleDependencyTypeBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Dependency Type Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleToGroupBox class represents 'sbgp' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SampleToGroupBox : public FullBox {
public:
    SampleToGroupBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample To Group Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleGroupDescriptionBox class represents 'sgpd' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SampleGroupDescriptionBox : public FullBox {
public:
    SampleGroupDescriptionBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Group Description Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleScaleBox class represents 'stsl' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SampleScaleBox : public FullBox {
public:
    SampleScaleBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Scale Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SubSampleInformationBox class represents 'subs' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SubSampleInformationBox : public FullBox {
public:
    SubSampleInformationBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sub Sample Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ProgressiveDownloadInfoBox class represents 'pdin' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ProgressiveDownloadInfoBox : public FullBox {
public:
    ProgressiveDownloadInfoBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Pogressive Donwload Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MetaBox class represents 'meta' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MetaBox : public FullBox {
public:
    MetaBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual bool isContainer() { return true; }
    virtual unsigned int getContainerOffset() { return 12;}
    virtual QString getFullName() { return QString("Meta Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
* \brief The XMLBox class represents 'xml ' box
* \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
*/
class XMLBox : public FullBox {
public:
    XMLBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("XML Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The BinaryXMLBox class represents 'bxml' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class BinaryXMLBox : public FullBox {
public:
    BinaryXMLBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Binary XML Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ItemLocationBox class represents 'iloc' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ItemLocationBox : public FullBox {
public:
    ItemLocationBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Item Location Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The PrimaryItemBox class represents 'pitm' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class PrimaryItemBox : public FullBox {
public:
    PrimaryItemBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Primary Item Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ItemProtectionBox class represents 'ipro' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ItemProtectionBox : public FullBox {
public:
    ItemProtectionBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Item Protection Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ItemInfoEntry class represents 'infe' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ItemInfoEntry : public FullBox {
public:
    ItemInfoEntry(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Item unsigned intfo Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ItemInfoBox class represents 'iinf' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ItemInfoBox : public FullBox {
public:
    ItemInfoBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Item Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ProtectionSchemeInfoBox class represents 'sinf' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class ProtectionSchemeInfoBox : public Box {
public:
    ProtectionSchemeInfoBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual bool isContainer() { return true; }
    virtual QString getFullName() { return QString("Protection Scheme Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The OriginalFormatBox class represents 'frma' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class OriginalFormatBox : public Box {
public:
    OriginalFormatBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Original Format Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The IPMPInfoBox class represents 'imif' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class IPMPInfoBox : public FullBox {
public:
    IPMPInfoBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("IPMP Info Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The IPMPControlBox class represents 'ipmc' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class IPMPControlBox : public FullBox {
public:
    IPMPControlBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("IPMP Control Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SchemeTypeBox class represents 'schm' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SchemeTypeBox : public FullBox {
public:
    SchemeTypeBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Scheme Type Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SchemeInformationBox class represents 'schi' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SchemeInformationBox : public Box {
public:
    SchemeInformationBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Scheme Information Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TimeScaleEntry class represents 'tims' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TimeScaleEntry : public Box {
public:
    TimeScaleEntry(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Time Scale Entry"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The TimeOffset class represents 'tsro' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class TimeOffset : public Box {
public:
    TimeOffset(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Time Offset"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SequenceOffset class represents 'snro' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SequenceOffset : public Box {
public:
    SequenceOffset(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Sequence Offset"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SRTPProcessBox class represents 'srtp' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class SRTPProcessBox : public FullBox {
public:
    SRTPProcessBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("SRTP Process Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The MovieHintInformation class represents 'hnti' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class MovieHintInformation : public Box {
public:
    MovieHintInformation(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Movie Hint Information"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The RTPMovieHintInformation class represents 'rtp ' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class RTPMovieHintInformation : public Box {
public:
    RTPMovieHintInformation(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("RTP Movie Hint Information"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The RTPTrackSDPHintInformation class represents 'sdp ' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class RTPTrackSDPHintInformation : public Box {
public:
    RTPTrackSDPHintInformation(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("RTP Track SDP Hint Information"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The HintStatisticsBox class represents 'hinf' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class HintStatisticsBox : public Box {
public:
    HintStatisticsBox(const unsigned long int& s, const QString& t, const unsigned long int& off);
    virtual QString getFullName() { return QString("Hint Statistics Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///mpeg dash
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
* \brief The SampleAuxiliaryInformationSizesBox class represents 'saiz' box
* \see ISO/IEC 14496-12:2008/FDAM 3:2011 – Information technology – Coding of audio-visual objects – Part 12: ISO base media file format, AMENDMENT 3: DASH support and RTP reception hint track processing
*/
class SampleAuxiliaryInformationSizesBox : public FullBox {
public:
    SampleAuxiliaryInformationSizesBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Auxiliary Information Sizes Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SampleAuxiliaryInformationOffsetsBox class represents 'saio' box
 * \see ISO/IEC 14496-12:2008/FDAM 3:2011 – Information technology – Coding of audio-visual objects – Part 12: ISO base media file format, AMENDMENT 3: DASH support and RTP reception hint track processing
 */
class SampleAuxiliaryInformationOffsetsBox : public FullBox {
public:
    SampleAuxiliaryInformationOffsetsBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Sample Auxiliary Information Offsets Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The LevelAssignmentBox class represents 'leva' box
 * \see ISO/IEC 14496-12:2008/FDAM 3:2011 – Information technology – Coding of audio-visual objects – Part 12: ISO base media file format, AMENDMENT 3: DASH support and RTP reception hint track processing
 */
class LevelAssignmentBox : public FullBox {
public:
    LevelAssignmentBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Level Assignment Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SegmentIndexBox class represents 'sidx' box
 * \see ISO/IEC 14496-12:2008/FDAM 3:2011 – Information technology – Coding of audio-visual objects – Part 12: ISO base media file format, AMENDMENT 3: DASH support and RTP reception hint track processing
 */
class SegmentIndexBox : public FullBox {
protected:
    unsigned int referenceId;
    unsigned int timescale;
    unsigned long int earliestPresentationTime;
    unsigned int long firstOffset;
    unsigned int reserved;
    QList<bool> referenceType;
    QList<unsigned int> referenceSize;
    QList<unsigned int> subsegmentDuration;
    QList<bool> startsWithSAP;
    QList <unsigned int> SAPType;
    QList <unsigned int> SAPDeltaTime;

public:
    SegmentIndexBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f, const unsigned int& referenceId,
                    const unsigned int& timescale,const unsigned long int& myEarliestPresentationTime, const unsigned long int& myFirstOffset, const unsigned int& myReserved,
                    const QList<bool>& referenceType, const QList<unsigned int> referenceSize, const QList<unsigned int> & subsegmentDuration,
                    const QList<bool> & startsWithSAP, const QList<unsigned int>& SAPType, const QList<unsigned int>& SAPDeltaTime);
    virtual QString getFullName() { return QString("Segment Index Box"); }
    virtual QStandardItemModel *getModel();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The SubsegmentIndexBox class represents 'ssix' box
 * \see ISO/IEC 14496-12:2008/FDAM 3:2011 – Information technology – Coding of audio-visual objects – Part 12: ISO base media file format, AMENDMENT 3: DASH support and RTP reception hint track processing
 */
class SubsegmentIndexBox : public FullBox {
public:
    SubsegmentIndexBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Subsegment Index Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The ProducerReferenceTimeBox class represents 'pfrt' box
 * \see ISO/IEC 14496-12:2008/FDAM 3:2011 – Information technology – Coding of audio-visual objects – Part 12: ISO base media file format, AMENDMENT 3: DASH support and RTP reception hint track processing
 */
class ProducerReferenceTimeBox : public FullBox {
public:
    ProducerReferenceTimeBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f);
    virtual QString getFullName() { return QString("Producer Reference Time Box"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The UniversalUniqueIdentifier class represents 'uuid' box
 * \see ISO/IEC 14496-12 Information technology – Coding of audio-visual objects – Part 12: ISO base media file format
 */
class UniversalUniqueIdentifier : public Box {
private:
    QString extendedType;
public:
    UniversalUniqueIdentifier(const unsigned long int& s, const QString& t, const unsigned long int& off, const QString& eType);
    virtual QString getFullName() { return QString("Universal Unique Identifier"); }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // BOX_H

