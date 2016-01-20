#ifndef NALXML_H
#define NALXML_H

#include <QFile>
#include <QXmlStreamWriter>
#include <QList>
#include <memory>
#include <QDebug>
#include "nalunit.h"
#include "nalunittype.h"
#include "nalunitsbo.h"

class NALXml {
protected:
    QString fileName;
    NalUnitsBO* nalUnitsBO;
public:
    NALXml(const QString& fileName, NalUnitsBO* nalunits);
    bool writeXML();
protected:
    void write(QXmlStreamWriter *stream) const;
    void writeHeader(QXmlStreamWriter *stream, const std::shared_ptr<NalUnit> nalUnit) const;
    void writeExtendedHeader(QXmlStreamWriter *stream, std::shared_ptr<NalUnit> nalUnit) const;

signals:

public slots:
};

#endif // NALXML_H
