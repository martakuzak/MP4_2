#include "period.h"

Period::Period() {}
Period::Period(const unsigned int &i, const QString &dur, const QString &st): id(i), duration(dur), start(st)
{
}
void Period::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("Period");
    if(id != NULL) {
        stream->writeAttribute("id", QString::number(id));
    }
    if(duration.size())
        stream->writeAttribute("duration", duration);
    if(start.size())
        stream->writeAttribute("start", start);
    adaptationSet->write(stream);
    stream->writeEndElement();
}

/////////////
unsigned int Period::getId() const
{
    return id;
}
/////////////
void Period::setId(unsigned int value)
{
    id = value;
}
/////////////
QString Period::getStart() const
{
    return start;
}
/////////////
void Period::setStart(const QString &value)
{
    start = value;
}
/////////////
QString Period::getDuration() const
{
    return duration;
}
/////////////
void Period::setDuration(const QString &value)
{
    duration = value;
}

AdaptationSet *Period::getAdaptationSet() const
{
return adaptationSet;
}

void Period::setAdaptationSet(AdaptationSet *value)
{
adaptationSet = value;
}
/////////////////////////////////////////////////////////////////////////////
AdaptationSet::AdaptationSet() {}
/// \brief AdaptationSet::AdaptationSet
/// \param segAlig
/// \param subsegAlig
/// \param bitsSwit
/// \param maxW
/// \param maxH
/// \param maxFR
/// \param swSAP
/// \param subsswSAP
/// \param p
/// \param mimeT
/// \param cod
/// \param fr
/// \param lan
/// \param rep
AdaptationSet::AdaptationSet(const bool& segAlig, const bool& subsegAlig, const bool& bitsSwit, const unsigned int& maxW,
                             const unsigned int& maxH, const unsigned int& maxFR, const unsigned short int& swSAP,
                             const unsigned short int& subsswSAP, const QString& p, const QString& mimeT, const QString& cod,
                             const QString& fr, const QString& lan

                             , const QList<Representation> rep):
    segmentAlignment(segAlig), subsegmentAlignment(subsegAlig), bitstreamSwitching(bitsSwit), maxWidth(maxW), maxHeight(maxH),
    maxFrameRate(maxFR), startsWithSAP(swSAP), subsegmentStartsWithSAP(subsswSAP), par(p), mimeType(mimeT), codecs(cod),
    frameRate(fr), lang(lan), representations(rep)
{}
///////////
void AdaptationSet::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("AdaptationSet");
    if(segmentAlignment != NULL) {
        if(segmentAlignment)
            stream->writeAttribute("segmentAlignment", "true");
        else
            stream->writeAttribute("segmentAlignment", "false");
    }
    if(subsegmentAlignment != NULL){
        if(subsegmentAlignment)
            stream->writeAttribute("subegmentAlignment", "true");
        else
            stream->writeAttribute("subsegmentAlignment", "false");
    }
    if(bitstreamSwitching != NULL){
        if(bitstreamSwitching)
            stream->writeAttribute("bitstreamSwitching", "true");
        else
            stream->writeAttribute("bitstreamSwitching", "false");
    }
    if(maxWidth != NULL)
        stream->writeAttribute("maxWidth", QString::number(maxWidth));
    if(maxHeight != NULL)
        stream->writeAttribute("maxHeight", QString::number(maxHeight));
    if(maxFrameRate != NULL)
        stream->writeAttribute("maxFrameRate", QString::number(maxFrameRate));
    if(maxFrameRate != NULL)
        stream->writeAttribute("maxFrameRate", QString::number(maxFrameRate));
    if(startsWithSAP != NULL)
        stream->writeAttribute("startsWithSAP", QString::number(startsWithSAP));
    if(subsegmentStartsWithSAP != NULL)
        stream->writeAttribute("subsegmentStartsWithSAP", QString::number(subsegmentStartsWithSAP));
    if(par.size())
        stream->writeAttribute("par", par);
    if(mimeType.size())
        stream->writeAttribute("mimeType", mimeType);
    if(codecs.size())
        stream->writeAttribute("codecs", codecs);
    //    frameRate(fr), lang(lan), representations(rep)
    if(frameRate != NULL)
        stream->writeAttribute("frameRate", frameRate);
    if(lang != NULL)
        stream->writeAttribute("lang", lang);
    int size = representations.size();
    for (int i = 0; i < size; ++i) {
        Representation r = representations.at(i);
        r.write(stream);
    }
    stream->writeEndElement();
}

/////////////
QList<Representation> AdaptationSet::getRepresentations() const
{
    return representations;
}
/////////////
void AdaptationSet::setRepresentations(const QList<Representation> &value)
{
    representations = value;
}
/////////////
QString AdaptationSet::getLang() const
{
    return lang;
}
/////////////
void AdaptationSet::setLang(const QString &value)
{
    lang = value;
}
/////////////
QString AdaptationSet::getFrameRate() const
{
    return frameRate;
}
/////////////
void AdaptationSet::setFrameRate(const QString &value)
{
    frameRate = value;
}
/////////////
QString AdaptationSet::getCodecs() const
{
    return codecs;
}
/////////////
void AdaptationSet::setCodecs(const QString &value)
{
    codecs = value;
}
/////////////
QString AdaptationSet::getMimeType() const
{
    return mimeType;
}
/////////////
void AdaptationSet::setMimeType(const QString &value)
{
    mimeType = value;
}
/////////////
QString AdaptationSet::getPar() const
{
    return par;
}
/////////////
void AdaptationSet::setPar(const QString &value)
{
    par = value;
}
/////////////
unsigned short AdaptationSet::getSubsegmentStartsWithSAP() const
{
    return subsegmentStartsWithSAP;
}
/////////////
void AdaptationSet::setSubsegmentStartsWithSAP(unsigned short value)
{
    subsegmentStartsWithSAP = value;
}
/////////////
unsigned short AdaptationSet::getStartsWithSAP() const
{
    return startsWithSAP;
}
/////////////
void AdaptationSet::setStartsWithSAP(unsigned short value)
{
    startsWithSAP = value;
}
/////////////
unsigned int AdaptationSet::getMaxFrameRate() const
{
    return maxFrameRate;
}
/////////////
void AdaptationSet::setMaxFrameRate(unsigned int value)
{
    maxFrameRate = value;
}
/////////////
unsigned int AdaptationSet::getMaxHeight() const
{
    return maxHeight;
}
/////////////
void AdaptationSet::setMaxHeight(unsigned int value)
{
    maxHeight = value;
}
/////////////
unsigned int AdaptationSet::getMaxWidth() const
{
    return maxWidth;
}
/////////////
void AdaptationSet::setMaxWidth(unsigned int value)
{
    maxWidth = value;
}
/////////////
bool AdaptationSet::getBitstreamSwitching() const
{
    return bitstreamSwitching;
}
/////////////
void AdaptationSet::setBitstreamSwitching(bool value)
{
    bitstreamSwitching = value;
}
/////////////
bool AdaptationSet::getSubsegmentAlignment() const
{
    return subsegmentAlignment;
}
/////////////
void AdaptationSet::setSubsegmentAlignment(bool value)
{
    subsegmentAlignment = value;
}
/////////////
bool AdaptationSet::getSegmentAlignment() const
{
    return segmentAlignment;
}
/////////////
void AdaptationSet::setSegmentAlignment(bool value)
{
    segmentAlignment = value;
}

/////////////////////////////////////////////////////////////////////////////
BaseURL::BaseURL() {}
/// \brief BaseURL::BaseURL
/// \param con
/// \param sl
/// \param br
///
BaseURL::BaseURL(const QString& con, const QString &sl, const QString &br):
    content(con), serviceLocation(sl), byteRange(br) {

}
/////////////
void BaseURL::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("BaseURL");
    if(serviceLocation.size()) {
        stream->writeAttribute("serviceLocation", serviceLocation);
    }
    if(byteRange.size())
        stream->writeAttribute("byteRange", byteRange);
    stream->writeCharacters(content);
    stream->writeEndElement();
}
/////////////
QString BaseURL::getByteRange() const
{
    return byteRange;
}
/////////////
void BaseURL::setByteRange(const QString &value)
{
    byteRange = value;
}
/////////////
QString BaseURL::getServiceLocation() const
{
    return serviceLocation;
}
/////////////
void BaseURL::setServiceLocation(const QString &value)
{
    serviceLocation = value;
}
/////////////
QString BaseURL::getContent() const
{
    return content;
}
/////////////
void BaseURL::setContent(const QString &value)
{
    content = value;
}
/////////////////////////////////////////////////////////////////////////////
Representation::Representation() {}
/// \brief Representation::Representation
/// \param i
/// \param mime
/// \param cod
/// \param w
/// \param h
/// \param fr
/// \param sa
/// \param swSAP
/// \param band
/// \param burl
/// \param slist
///
Representation::Representation(const unsigned int& i, const QString& mime, const QString& cod, const unsigned int& w, const unsigned int& h,
                               const unsigned int& fr, const QString& sa, const unsigned short int& swSAP,
                               const unsigned int& band,const BaseURL &burl, const SegmentList &slist):
    id(i), mimeType(mime), codecs(cod), width(w), height(h), frameRate(fr), sar(sa), startsWithSAP(swSAP), bandwidth(band), baseurl(burl),
    segmentList(slist)
{}
void Representation::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("AdaptationSet");
    if(id != NULL)
        stream->writeAttribute("id", QString::number(id));
    if(mimeType.size())
        stream->writeAttribute("mimeType", mimeType);
    if(codecs.size())
        stream->writeAttribute("codecs", codecs);
    if(width != NULL)
        stream->writeAttribute("width", QString::number(width));
    if(height != NULL)
        stream->writeAttribute("height", QString::number(height));
    if(sar.size())
        stream->writeAttribute("sar", sar);
    if(startsWithSAP != NULL)
        stream->writeAttribute("startsWithSAP", QString::number(startsWithSAP));
    if(bandwidth != NULL)
        stream->writeAttribute("bandwidth", QString::number(bandwidth));
    baseurl.write(stream);
    segmentList.write(stream);
    stream->writeEndElement();
}

/////////////
SegmentList Representation::getSegmentList() const
{
    return segmentList;
}
/////////////
void Representation::setSegmentList(const SegmentList &value)
{
    segmentList = value;
}
/////////////
BaseURL Representation::getBaseurl() const
{
    return baseurl;
}
/////////////
void Representation::setBaseurl(const BaseURL &value)
{
    baseurl = value;
}
/////////////
unsigned int Representation::getBandwidth() const
{
    return bandwidth;
}
/////////////
void Representation::setBandwidth(unsigned int value)
{
    bandwidth = value;
}
/////////////
unsigned short Representation::getStartsWithSAP() const
{
    return startsWithSAP;
}
/////////////
void Representation::setStartsWithSAP(unsigned short value)
{
    startsWithSAP = value;
}
/////////////
QString Representation::getSar() const
{
    return sar;
}
/////////////
void Representation::setSar(const QString &value)
{
    sar = value;
}
/////////////
unsigned int Representation::getFrameRate() const
{
    return frameRate;
}
/////////////
void Representation::setFrameRate(unsigned int value)
{
    frameRate = value;
}
/////////////
unsigned int Representation::getHeight() const
{
    return height;
}
/////////////
void Representation::setHeight(unsigned int value)
{
    height = value;
}
/////////////
unsigned int Representation::getWidth() const
{
    return width;
}
/////////////
void Representation::setWidth(unsigned int value)
{
    width = value;
}
/////////////
QString Representation::getCodecs() const
{
    return codecs;
}
/////////////
void Representation::setCodecs(const QString &value)
{
    codecs = value;
}
/////////////
QString Representation::getMimeType() const
{
    return mimeType;
}
/////////////
void Representation::setMimeType(const QString &value)
{
    mimeType = value;
}
/////////////
unsigned int Representation::getId() const
{
    return id;
}
/////////////
void Representation::setId(unsigned int value)
{
    id = value;
}
