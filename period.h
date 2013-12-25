#ifndef PERIOD_H
#define PERIOD_H

#include "segmentlist.h"

/*!
 * \brief The BaseURL class describes URL
 *  - atrributes:
 *      -# serviceLocation(optional)
 *      -# byteRange (optional)
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
     * \brief write
     * Writes BaseURL vertex into Media Presentation Description file
     * \param stream stream of the MPD file
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
 * \brief The Representation class contains a description of a Representation.
 *  - atrributes:
 *      -# id (optional)
 *      -# bandwidith (optional)
 *      -# qualityRanking (optional)
 *      -# dependencyId (optional)
 *      -# mediaStreamStructureId (optional)
 *      -# CommonAttributesElements
 *  - elements:
 *      -# BaseURL (0..N)
 *      -# SubRepresentation (0..N)
 *      -# SegmentBase (0..1)
 *      -# SegmentList (0..1)
 *      -# SegmentTemplate (0..1)
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
    unsigned short int startsWithSAP;
    unsigned int bandwidth;
    //
    BaseURL* baseurl;
    SegmentList* segmentList;
public:
    Representation();
    /*!
     * \brief write
     * Writes Representation vertex into Media Presentation Description file
     * \param stream stream of the MPD file
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
    unsigned short getStartsWithSAP() const;
    void setStartsWithSAP(unsigned short value);
    unsigned int getBandwidth() const;
    void setBandwidth(unsigned int value);
    BaseURL* getBaseurl() const;
    void setBaseurl(BaseURL* value);
    SegmentList* getSegmentList() const;
    void setSegmentList(SegmentList* value);
};
///////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief The AdaptationSet class specifies the information of a AdaptationSet.
 *  - atrributes:
 *      -# id (optional)
 *      -# group (optional)
 *      -# CommonAttributesElements
 *      -# lang (optional)
 *      -# contentType (optional)
 *      -# par (optional)
 *      -# minBandwidth (optional)
 *      -# maxBandwidth (optional)
 *      -# minWidth (optional)
 *      -# maxWidth (optional)
 *      -# minHeight (optional)
 *      -# maxHeight (optional)
 *      -# minFrameRate (optional)
 *      -# maxFrameRate (optional)
 *      -# SegmentAlignment (optional with default value: false)
 *      -# bitstreamSwitching (optional)
 *      -# subsegmentAlignment (optional with default value: false)
 *      -# subsegmentStartsWithSAP (optional with default value: 0)
 *  - elements:
 *      -# Accessibility (0..N)
 *      -# Role (0..N)
 *      -# Rating (0..N)
 *      -# Viewpoint (0..N)
 *      -# ContentComponent (0..N)
 *      -# BaseURL (0..N)
 *      -# SegmentBase (0..1)
 *      -# SegmentList (0..1)
 *      -# SegmentTemplate (0..1)
 *      -# Representation (0..N)
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
     * \brief write
     * Writes AdaptationSet vertex into Media Presentation Description file
     * \param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);void addRepresentation();
    void addRepresentation(Representation* repr);
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
 * \brief The Period class specifies the information of a Period.
 *  - atrributes:
 *      -# id (optional)
 *      -# start (optional)
 *      -# duration (optional)
 *      -# bitstreamswitching (optional with default value: false)
 *  - elements:
 *      -# BaseURL (0..N)
 *      -# SegmentBase (0..1)
 *      -# SegmentList (0..1)
 *      -# SegmentTemplate (0..1)
 *      -# AdaptationSet (0..N)
 *      -# Subset (0..N)
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
     * \brief write
     * Writes Period vertex into Media Presentation Description file
     * \param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    unsigned int getId() const;
    void setId(unsigned int value);
    QString getDuration() const;
    void setDuration(const QString &value);
    QString getStart() const;
    void setStart(const QString &value);
    void addAdaptationSet();
    void addAdaptationSet(AdaptationSet* adaptSet);
};
///////////////////////////////////////////////////////////////////////////////////



#endif // PERIOD_H
