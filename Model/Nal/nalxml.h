#ifndef NALXML_H
#define NALXML_H

#include <QFile>
#include <QXmlStreamWriter>
#include <QList>
#include <memory>

#include "nalunit.h"
#include "nalunittype.h"

class NALXml {
public:
    NALXml(const QString& fileName, const QList<std::shared_ptr<NalUnit> >& nu);
    bool writeXML();
protected:
    QString fileName;
    QList<std::shared_ptr<NalUnit> > nalUnits;
    void write(QXmlStreamWriter *stream);

signals:

public slots:
};

#endif // NALXML_H
