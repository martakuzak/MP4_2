#ifndef PERIOD_H
#define PERIOD_H

#include <qDebug>
#include "segmentlist.h"
/*!
  *\brief The BaseURL class represents BaseURL element of Media Presentation Description xml file.
  *\see ISO/IEC 23009-1:2012 Information technology – Dynamic adaptive streaming over HTTP (DASH) – Part 1: Media presentation description and segment formats
 */
class BaseURL {
private:
    QString content;
    //attrs
    QString serviceLocation;
    QString byteRange;
public:
    BaseURL();
    /*!
      *\brief write
      * Writes BaseURL vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    QString getContent() const;
    void setContent(const QString &value);
    QString getServiceLocation() const;
    void setServiceLocation(const QString &value);
    QString getByteRange() const;
    void setByteRange(const QString &value);
};
///////////////////////////////////////////////////////////////////////////////////
/*!
  *\brief The Representation class represents AdaptationSet element of Media Presentation Description xml file.
  *\see ISO/IEC 23009-1:2012 Information technology – Dynamic adaptive streaming over HTTP (DASH) – Part 1: Media presentation description and segment formats
 */
class Representation {
private:
    unsigned int id;
    QString mimeType;
    QString codecs;
    unsigned int width;
    unsigned int height;
    unsigned int frameRate;
    QString sar;
    unsigned short int startWithSAP;
    unsigned int bandwidth;
    //
    BaseURL *baseurl;
    SegmentList *segmentList;
    SegmentBase *segmentBase;
public:
    Representation();
    /*!
      *\brief write
      *Writes Representation vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    unsigned int getId() const;
    void setId(unsigned int value);
    QString getMimeType() const;
    void setMimeType(const QString &value);
    QString getCodecs() const;
    void setCodecs(const QString &value);
    unsigned int getWidth() const;
    void setWidth(unsigned int value);
    unsigned int getHeight() const;
    void setHeight(unsigned int value);
    unsigned int getFrameRate() const;
    void setFrameRate(unsigned int value);
    QString getSar() const;
    void setSar(const QString &value);
    unsigned short getStartWithSAP() const;
    void setStartWithSAP(unsigned short value);
    unsigned int getBandwidth() const;
    void setBandwidth(unsigned int value);
    BaseURL *getBaseurl() const;
    void setBaseurl(BaseURL *value);
    SegmentList *getSegmentList() const;
    void setSegmentList(SegmentList *value);
    void setSegmentBase(SegmentBase *value);
};
///////////////////////////////////////////////////////////////////////////////////
/*!
  *\brief The AdaptationSet class represents AdaptationSet element of Media Presentation Description xml file.
  *\see ISO/IEC 23009-1:2012 Information technology – Dynamic adaptive streaming over HTTP (DASH) – Part 1: Media presentation description and segment formats
 */

class AdaptationSet {
private:
    //attrs
    bool segmentAlignment;
    bool subsegmentAlignment;
    bool bitstreamSwitching;
    unsigned int maxWidth;
    unsigned int maxHeight;
    unsigned int maxFrameRate;
    unsigned short int startsWithSAP;
    unsigned short int subsegmentStartsWithSAP;
    QString par;
    QString mimeType;
    QString codecs;
    QString frameRate;
    QString lang;
    //
    QList<Representation*> representations;
public:
    AdaptationSet();
    /*!
      *\brief write
      *Writes AdaptationSet vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    void addRepresentations(const QList<Representation*>& repr);
    void addRepresentation(Representation *repr);
    bool getSegmentAlignment() const;
    void setSegmentAlignment(bool value);
    bool getSubsegmentAlignment() const;
    void setSubsegmentAlignment(bool value);
    bool getBitstreamSwitching() const;
    void setBitstreamSwitching(bool value);
    unsigned int getMaxWidth() const;
    void setMaxWidth(unsigned int value);
    unsigned int getMaxHeight() const;
    void setMaxHeight(unsigned int value);
    unsigned int getMaxFrameRate() const;
    void setMaxFrameRate(unsigned int value);
    unsigned short getStartsWithSAP() const;
    void setStartsWithSAP(unsigned short value);
    unsigned short getSubsegmentStartsWithSAP() const;
    void setSubsegmentStartsWithSAP(unsigned short value);
    QString getPar() const;
    void setPar(const QString &value);
    QString getMimeType() const;
    void setMimeType(const QString &value);
    QString getCodecs() const;
    void setCodecs(const QString &value);
    QString getFrameRate() const;
    void setFrameRate(const QString &value);
    QString getLang() const;
    void setLang(const QString &value);
};
/////////////////////////////////
/*!
  *\brief The Period class represents Period element of Media Presentation Description xml file.
  *\see ISO/IEC 23009-1:2012 Information technology – Dynamic adaptive streaming over HTTP (DASH) – Part 1: Media presentation description and segment formats
 */

class Period {
private:
    unsigned int id;
    QString duration;
    QString start;
    QList<AdaptationSet*> adaptationSets;
public:
    Period();
    /*!
      *\brief write
      *Writes Period vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    unsigned int getId() const;
    void setId(unsigned int value);
    QString getDuration() const;
    void setDuration(const QString &value);
    QString getStart() const;
    void setStart(const QString &value);
    void addAdaptationSet();
    void addAdaptationSet(AdaptationSet *adaptSet);
};
///////////////////////////////////////////////////////////////////////////////////



#endif // PERIOD_H
