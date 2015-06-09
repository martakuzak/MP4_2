#ifndef NALPARSER_H
#define NALPARSER_H

#include <QString>
#include <QFile>
#include "bitoperator.h"
#include <QByteArray>
#include "nalunittype.h"
#include <QList>
#include "nalunit.h"
#include <memory>
#include "nalunitfactory.h"

class NALParser {
public:
    NALParser();
    NALParser(const QString& fileName);
    ~NALParser();

    QList<std::shared_ptr<NalUnit> > parseFile();
    void identifyNalType(int nalUnitType, int offset);
    int parseSEI(int offset);
    int parseSEIPayload(int payloadType, int payloadSize, int offset);
    int scalabilityInfo(int payloadSize, int offset);
    int sliceLayerWithoutPartitioningRbsp(int offset);
    int sliceHeader(int offset);

private:
    QString fileName;
    QFile* file;
    unsigned long int fileSize;
    BitOperator* bitOperator;
};

#endif // NALPARSER_H
