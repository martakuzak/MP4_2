#include "nalxml.h"

NALXml::NALXml(const QString &fn, const QList<std::shared_ptr<NalUnit> > &nu): fileName(fn), nalUnits(nu) {

}

bool NALXml::writeXML() {
    QFile *file = new QFile(fileName);
    if(file->open(QIODevice::ReadWrite)) {
        QXmlStreamWriter *stream = new QXmlStreamWriter(file);
        stream->setAutoFormatting(true);
        stream->writeStartDocument();
        write(stream);
        stream->writeEndDocument();
        file->close();
        return true;
    } else
        return false;
}

void NALXml::write(QXmlStreamWriter* stream) {
    stream->writeStartElement("NalStream");
    for(int i = 0; i < nalUnits.size(); ++ i) {
        //stream->writeAttribute();
    }
  /*  if(type.size())
        stream->writeAttribute("type", type);
    if(xmlns.size())
        stream->writeAttribute("xmlns", xmlns);
    if(minBufferTime.size())
        stream->writeAttribute("minBufferTime", minBufferTime);
    if(profiles.size())
        stream->writeAttribute("profiles", profiles);
    if(mediaPresentationDuration.size())
        stream->writeAttribute("mediaPresentationDuration", mediaPresentationDuration);
    if(baseURL != NULL)
        baseURL->write(stream);
    if(periods.size()) {
        int size = periods.size();
        for(int i = 0; i < size; ++i) {
            periods.at(i)->write(stream);
        }
    }*/
    stream->writeEndElement();
}
