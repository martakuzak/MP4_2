#ifndef NALPARSER_H
#define NALPARSER_H

#include <QString>
#include <QFile>
#include <QByteArray>
#include <QList>
#include <memory>

#include "nalunit.h"
#include "nalunitfactory.h"
#include "fileservice.h"
#include "nalunitsbo.h"
#include "nalunittype.h"
#include "bitoperator.h"

class Box;

class NALParser {
protected:
    QString fileName;
    QFile* file;
    unsigned long int fileSize;
    BitOperator* bitOperator;
    FileService* fileService;
    QList<std::shared_ptr<NalUnit>> nalUnits;
public:
    NALParser();
    NALParser(const QString& fileName);
    ~NALParser();

    NalUnitsBO* parseFile();
//    int parseSEI(int offset);
//    int parseSEIPayload(int payloadType, int payloadSize, int offset);
//    int scalabilityInfo(int payloadSize, int offset);
//    int sliceLayerWithoutPartitioningRbsp(int offset);
//    int sliceHeader(int offset);

protected:
    std::shared_ptr<Box> getHBox(const unsigned int& size = 0, QString type = "", unsigned long int off = 0);
    unsigned long int valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    signed long int signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    unsigned long int valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const;
    QString stringValue(const unsigned int & length, const unsigned long& offset) const;
};

#endif // NALPARSER_H
