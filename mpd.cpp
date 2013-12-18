#include "mpd.h"

MPD::MPD()
{}
/////////////
QString MPD::getProfiles() const
{
    return profiles;
}
/////////////
void MPD::setProfiles(const QString &value)
{
    profiles = value;
}
/////////////
QString MPD::getMediaPresentationDuration() const
{
    return mediaPresentationDuration;
}
/////////////
void MPD::setMediaPresentationDuration(const QString &value)
{
    mediaPresentationDuration = value;
}
/////////////
QString MPD::getMinBufferTime() const
{
    return minBufferTime;
}
/////////////
void MPD::setMinBufferTime(const QString &value)
{
    minBufferTime = value;
}
/////////////
QString MPD::getXmlns() const
{
    return xmlns;
}
/////////////
void MPD::setXmlns(const QString &value)
{
    xmlns = value;
}
/////////////
QString MPD::getType() const
{
    return type;
}
/////////////
void MPD::setType(const QString &value)
{
    type = value;
}
/////////////
/// \brief MPD::write
/// \param stream
///
void MPD::write(QXmlStreamWriter* stream ) {
    stream->writeStartElement("MPD");
    if(type.size())
        stream->writeAttribute("type", type);
    if(xmlns.size())
        stream->writeAttribute("xmlns", xmlns);
    if(minBufferTime.size())
        stream->writeAttribute("minBufferTime", minBufferTime);
    if(mediaPresentationDuration.size())
        stream->writeAttribute("mediaPresentationDuration", mediaPresentationDuration);
    if(profiles.size())
        stream->writeAttribute("profiles", profiles);
    stream->writeEndElement();
}
/////////////////////////////////////////////////////////////////////////////////////////
MPDWriter::MPDWriter(const QString& fn): filename(fn) {}

void MPDWriter::writeMPD(QFile* file) {
    mpd = new MPD();
    mpd->setType("static");
    mpd->setMinBufferTime("10229");

    BaseURL b;
    b.setByteRange("100-200");
    b.setServiceLocation("u marty");
    b.setContent("zawartosc");

    QList<Representation> repr;
    Representation r;
    r.setBandwidth(200);
    r.setMimeType("mime");
    r.setStartsWithSAP(1);
    r.setBaseurl(b);
    repr.append(r);


    AdaptationSet* adapt = new AdaptationSet();
    adapt->setBitstreamSwitching(false);
    adapt->setLang("polish");
    adapt->setMaxWidth(14);
    adapt->setRepresentations(repr);

    period = new Period();
    period->setDuration("dnufs");
    period->setId(3);
    period->setAdaptationSet(adapt);

    file->open(QIODevice::WriteOnly | QIODevice::Text);
    stream = new QXmlStreamWriter(file);
    stream->setAutoFormatting(true);
    stream->writeStartDocument();
    mpd->write(stream);
    period->write(stream);
    stream->writeEndDocument();
    file->close();
}
