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
    stream->writeStartElement("NAL_Stream");
    for(int i = 0; i < nalUnits.size(); ++ i) {
        std::shared_ptr<NalUnit> nalUnit = nalUnits.at(i);
        stream->writeStartElement("NAL_unit");
        stream->writeAttribute("name", nalUnit->getName());
        stream->writeAttribute("offset", QString::number(nalUnit->getOffset()));
        stream->writeAttribute("length", QString::number(nalUnit->getLength()));
        writeHeader(stream, nalUnit);
        writeExtendedHeader(stream, nalUnit);
        stream->writeEndElement();
    }
    stream->writeEndElement();
}

void NALXml::writeHeader(QXmlStreamWriter *stream, std::shared_ptr<NalUnit> nalUnit) {
    stream->writeStartElement("header");
    stream->writeAttribute("type", QString::number(nalUnit->getTypeCode()));
    stream->writeAttribute("NAL Ref ID", QString::number(nalUnit->getNalRefIdc()));
    stream->writeEndElement();
}

void NALXml::writeExtendedHeader(QXmlStreamWriter *stream, std::shared_ptr<NalUnit> nalUnit) {
    if(nalUnit->getTypeCode() == 14 || nalUnit->getTypeCode() == 20) {
        stream->writeStartElement("Extended_header");
        std::shared_ptr<ExtendedNalUnit> unit = std::dynamic_pointer_cast<ExtendedNalUnit>(nalUnit);
        unsigned int SVCflag = unit->getSVCflag();
        stream->writeAttribute("SVCflag", QString::number(SVCflag));

        if(SVCflag) {
            try {
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

            } catch (const std::bad_cast& e) {
                //std::cerr << "  Exception " << e.what() << " thrown." << std::endl;
                //std::cerr << "  Object is not of type B" << std::endl;
            }
        }
        stream->writeEndElement();
    }
}
