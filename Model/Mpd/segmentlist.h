/*!
  *\file SegmentList
  *\details
  *Initialization
  *SegmentURL
  *SegmentList
 */

#ifndef SEGMENTLIST_H
#define SEGMENTLIST_H

#include <QString>
#include <QList>
#include <QXmlStreamWriter>
#include <QDebug>

/*!
  *\brief The Initialization class specifies the URL including a possible byte range for the Initialization Segment.
  * - atrributes:
  *     -# sourceURL
  *     -# range
 */
class Initialization {
private:
    //attrs
    QString range;
    QString sourceURL;
public:
    Initialization();
    /*!
      *\brief write
      *Writes Initialization vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    QString getRange() const;
    void setRange(const QString &value);
    QString getSourceURL() const;
    void setSourceURL(const QString &value);
};
///////////////////////////////////////////////////////////////////////////
class SegmentBase {
private:
    Initialization *init;
public:
    SegmentBase();
    void write(QXmlStreamWriter *stream);
    void setInitialization(Initialization *ini);
};
///////////////////////////////////////////////////////////////////////////
/*!
  *\brief The SegmentURL class specifies a Media Segment URL and a possibly present Index Segment URL.
  * - atrributes:
  *     -# media (optional)
  *     -# mediaRange (optional)
  *     -# index (optional)
  *     -# indexRange (optional)
 */
class SegmentURL {
private:
    //attrs
    QString media;
    QString mediaRange;
    QString indexRange;
    //QString index;
public:
    SegmentURL();
    /*!
      *\brief write
      *Writes SegmentURL vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    QString getMediaRange() const;
    void setMediaRange(const QString &value);
    QString getIndexRange() const;
    void setIndexRange(const QString &value);
    QString getMedia() const;
    void setMedia(const QString &value);
};
///////////////////////////////////////////////////////////////////////////
/*!
  *\brief The SegmentList class defines SegmentList vertex in the Media Presentation Description file.
  *SegmentList vertex:
  * - atrributes:
  *     -# MultipleSegmentBaseInformation
  * - elements:
  *     -# Initialization: 0 or 1 occurance
  *     -# SegmentURL 0 or more occurances
 */
class SegmentList {
private:
    //attrs
    unsigned int timescale;
    unsigned long int duration;
    //elements
    Initialization *initialization;
    QList<SegmentURL*> segmentURLs;
public:
    SegmentList();
    /*!
      *\brief write
      *Writes SegmentList vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    /*!
      *\brief addSegmentURL
      *Creates SegmentURL with given mediaRange and indexRange and adds it to SegmentList
      *\param mediaRange defines byte range of the segment like this: 'first_byte-last_byte', for example '841-693308'
      *\param indexRange defines byte range of segment index like this: 'first_byte-last_byte', for example '841-897'
     */
    void addSegmentURL(const QString &mediaRange, const QString &indexRange, const QString &media="");
    void addSegmentURL(const QString &media);
   // void addSegmentsURL();
    Initialization *getInitialization() const;
    void setInitialization(Initialization *value);
};


#endif // SEGMENTLIST_H
