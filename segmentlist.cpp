#include "segmentlist.h"

Initialization::Initialization() {}
/////
QString Initialization::getRange() const{
    return range;
}
//////
void Initialization::setRange(const QString &value){
    range = value;
}
/////////////////
QString Initialization::getSourceURL() const {
    return sourceURL;
}
///////////////
void Initialization::setSourceURL(const QString &value) {
    sourceURL = value;
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
QString SegmentURL::getMedia() const {
    return media;
}
///////////
void SegmentURL::setMedia(const QString &value) {
    media = value;
}
///////
SegmentURL::SegmentURL() {}
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
SegmentList::SegmentList() {
    timescale = NULL;
    duration = NULL;
}
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
////////
void SegmentList::addSegmentURL(const QString &media) {
    SegmentURL* surl = new SegmentURL();
    surl->setMedia(media);
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

