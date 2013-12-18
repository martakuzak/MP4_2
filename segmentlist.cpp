#include "segmentlist.h"

SegmentList::SegmentList() {}
/////////////
SegmentList::SegmentList(const unsigned int &ts, const unsigned long &dur, const Initialization &init, const QList<SegmentURL> surl):
    timescale(ts), duration(dur), initialization(init), segmentURLs(surl)
{
}
/////////////
void SegmentList::write(QXmlStreamWriter *stream) {
    stream->writeStartElement("SegmentList");
    if(timescale != NULL)
        stream->writeAttribute("timescale", QString::number(timescale));
    if(duration != NULL)
        stream->writeAttribute("duration", QString::number(duration));
    initialization.write(stream);
    while(!segmentURLs.empty()) {
        segmentURLs.back().write(stream);
        segmentURLs.pop_back();
    }
    stream->writeEndElement();
}
//////////////////////////////////////////////////////////////////
Initialization::Initialization() {}
/// \brief Initialization::Initialization
/// \param r
/// \param sURL
///
Initialization::Initialization(const QString& r, const QString &sURL): range(r), sourceURL(sURL) {}
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
/// \brief SegmentURL::SegmentURL
/// \param med
/// \param mRange
/// \param iRange
///
SegmentURL::SegmentURL(const QString& med, const QString& mRange, const QString& iRange):
    media(med), mediaRange(mRange), indexRange(iRange) {}
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
