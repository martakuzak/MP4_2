#ifndef PERIOD_H
#define PERIOD_H

#include "segmentlist.h"

class BaseURL {
private:
    QString content;
    //attrs
    QString serviceLocation;
    QString byteRange;
public:
    BaseURL();
    BaseURL(const QString& con, const QString& sl, const QString& br);

    QString getContent() const;
    void setContent(const QString &value);
    QString getServiceLocation() const;
    void setServiceLocation(const QString &value);
    QString getByteRange() const;
    void setByteRange(const QString &value);
    void write(QXmlStreamWriter *stream);
};
///////////////////////////////////////////////////////////////////////////////////
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
    BaseURL baseurl;
    SegmentList segmentList;
public:
    Representation();
    Representation(const unsigned int& i, const QString& mime, const QString& cod, const unsigned int& w, const unsigned int& h,
                   const unsigned int& fr, const QString& sar, const unsigned short int& swSAP, const unsigned int& band,
                   const BaseURL& burl, const SegmentList& slist);
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
    BaseURL getBaseurl() const;
    void setBaseurl(const BaseURL &value);
    SegmentList getSegmentList() const;
    void setSegmentList(const SegmentList &value);
    void write(QXmlStreamWriter *stream);
};
///////////////////////////////////////////////////////////////////////////////////
/// \brief The AdaptationSet class
///
///
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
    QList<Representation> representations;
public:
    AdaptationSet();
    AdaptationSet(const bool& segAlig, const bool& subsegAlig, const bool& bitsSwit, const unsigned int& maxW, const unsigned int& maxH,
                  const unsigned int& maxFR, const unsigned short int& swSAP, const unsigned short int& subsswSAP, const QString& p,
                  const QString& mimeT, const QString& cod, const QString& fr, const QString& lan, const QList<Representation> rep);

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
    QList<Representation> getRepresentations() const;
    void setRepresentations(const QList<Representation> &value);
    void write(QXmlStreamWriter *stream);
};
/////////////////////////////////
class Period
{
private:
    unsigned int id;
    QString duration;
    QString start;
    AdaptationSet* adaptationSet;
public:
    Period();
    Period(const unsigned int& i, const QString& dur, const QString& st);
    unsigned int getId() const;
    void setId(unsigned int value);
    QString getDuration() const;
    void setDuration(const QString &value);
    QString getStart() const;
    void setStart(const QString &value);
    AdaptationSet *getAdaptationSet() const;
    void setAdaptationSet(AdaptationSet *value);
    void write(QXmlStreamWriter *stream);
};
///////////////////////////////////////////////////////////////////////////////////



#endif // PERIOD_H
