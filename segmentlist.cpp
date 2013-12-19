#include "segmentlist.h"

SegmentList::SegmentList() {}
/////////////
//SegmentList::SegmentList(const unsigned int &ts, const unsigned long &dur, const Initialization &init, const QList<SegmentURL> surl):
//    timescale(ts), duration(dur), initialization(init), segmentURLs(surl)
//{
//}
/////////////
void SegmentList::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("SegmentList");
    if(timescale != NULL)
        stream->writeAttribute("timescale", QString::number(timescale));
    if(duration != NULL)
        stream->writeAttribute("duration", QString::number(duration));
    initialization->write(stream);
    while(!segmentURLs.empty()) {
        segmentURLs.front()->write(stream);
        segmentURLs.pop_front();
    }
    stream->writeEndElement();
}
//////
void SegmentList::addSegmentURL(const QString& mediaRange, const QString& indexRange) {
    SegmentURL* surl = new SegmentURL();
    surl->setMediaRange(mediaRange);
    surl->setIndexRange(indexRange);
    segmentURLs.append(surl);
}
///////
Initialization *SegmentList::getInitialization() const {
    return initialization;
}
//////////
void SegmentList::setInitialization(Initialization *value) {
    initialization = value;
}
//////////////////////////////////////////////////////////////////
Initialization::Initialization() {}
/////
QString Initialization::getRange() const{
    return range;
}
//////
void Initialization::setRange(const QString &value){
    range = value;
}

//Initialization::Initialization(const QString& r, const QString &sURL): range(r), sourceURL(sURL) {}
/////////////
void Initialization::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("Initialization");
    if(range.size())
        stream->writeAttribute("range", range);
    if(sourceURL.size())
        stream->writeAttribute("sourceURL", sourceURL);
    stream->writeEndElement();
}
//////////////////////////////////////////////////////////////////
SegmentURL::SegmentURL() {}
//SegmentURL::SegmentURL(const QString& med, const QString& mRange, const QString& iRange):
//    media(med), mediaRange(mRange), indexRange(iRange) {}
////////
QString SegmentURL::getMediaRange() const {
    return mediaRange;
}
////////
void SegmentURL::setMediaRange(const QString &value) {
    mediaRange = value;
}
////////
QString SegmentURL::getIndexRange() const {
    return indexRange;
}
////////
void SegmentURL::setIndexRange(const QString &value) {
    indexRange = value;
}
///////////
void SegmentURL::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("SegmentURL");
    if(media.size())
        stream->writeAttribute("media", media);
    if(mediaRange.size())
        stream->writeAttribute("mediaRange", mediaRange);
    if(indexRange.size())
        stream->writeAttribute("indexRange", indexRange);
    stream->writeEndElement();
}
///////////


