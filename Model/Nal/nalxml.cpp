#include "nalxml.h"

NALXml::NALXml(const QString &fn, NalUnitsBO *nalunits): fileName(fn), nalUnitsBO(nalunits) {

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

void NALXml::write(QXmlStreamWriter* stream) const {
    int idx = 1;
    stream->writeStartElement("NAL_Stream");
    QList<std::shared_ptr<NalUnit>>::const_iterator it;
    for(it = nalUnitsBO->getNalUnits().constBegin(); it < nalUnitsBO->getNalUnits().constEnd(); ++it) {
        stream->writeStartElement("NAL_unit");
        stream->writeAttribute("idx", QString::number(idx++));
        stream->writeAttribute("name", (*it)->getName());
        stream->writeAttribute("offset", QString::number((*it)->getOffset()));
        stream->writeAttribute("length", QString::number((*it)->getLength()));
        writeHeader(stream, (*it));
        writeExtendedHeader(stream, (*it));
        stream->writeEndElement();
    }
    stream->writeEndElement();
}

void NALXml::writeHeader(QXmlStreamWriter *stream, const std::shared_ptr<NalUnit> nalUnit) const {
    stream->writeStartElement("header");
    stream->writeAttribute("type", QString::number(nalUnit->getTypeCode()));
    stream->writeAttribute("NAL Ref ID", QString::number(nalUnit->getNalRefIdc()));
    stream->writeEndElement();
}

void NALXml::writeExtendedHeader(QXmlStreamWriter *stream, std::shared_ptr<NalUnit> nalUnit) const {
    if(nalUnit->getTypeCode() == 14 || nalUnit->getTypeCode() == 20) {
        stream->writeStartElement("Extended_header");
        try {
            std::shared_ptr<ExtendedNalUnit> unit = std::dynamic_pointer_cast<ExtendedNalUnit>(nalUnit);
            unsigned int SVCflag = unit->getSVCflag();
            stream->writeAttribute("SVCflag", QString::number(SVCflag));

            if(SVCflag) {
                std::shared_ptr<SVCNalUnit> svcUnit = std::dynamic_pointer_cast<SVCNalUnit> (unit);
                stream->writeAttribute("idrFlag", QString::number(svcUnit->getIdrFlag()));
                stream->writeAttribute("priorityId", QString::number(svcUnit->getPriorityId()));
                stream->writeAttribute("noInterLayerPrediction", QString::number(svcUnit->getNoInterLayerPredFlag()));
                stream->writeAttribute("dependencyId", QString::number(svcUnit->getDependencyId()));
                stream->writeAttribute("qualityId", QString::number(svcUnit->getQualityId()));
                stream->writeAttribute("temporaryId", QString::number(svcUnit->getTemporaryId()));
                stream->writeAttribute("useRefBasePicFlag", QString::number(svcUnit->getUseRefBasePicFlag()));
                stream->writeAttribute("discardableFlag", QString::number(svcUnit->getDiscardableFlag()));
                stream->writeAttribute("outputFlag", QString::number(svcUnit->getOutputFlag()));
                stream->writeAttribute("reservedThree2bits", QString::number(svcUnit->getReservedThree2bits()));

            }
        }
        catch (const std::bad_cast& e) {
            qCritical() << "  Exception " << e.what() << " thrown.";
            //std::cerr << "  Exception " << e.what() << " thrown." << std::endl;
            //std::cerr << "  Object is not of type B" << std::endl;
        }
        stream->writeEndElement();
    }
}
