#ifndef NALPARSER_H
#define NALPARSER_H

#include <QString>
#include <QFile>
#include <QByteArray>
#include <QList>
#include <memory>

#include "nalunit.h"
#include "nalunitfactory.h"
#include "nalunitsbo.h"
#include "nalunittype.h"
#include "filebitoperator.h"

class Box;

class NALParser {
protected:
    QString fileName;
    unsigned long int fileSize;
    FileBitOperator* fbOperator;
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
    //std::shared_ptr<Box> getHBox(const unsigned int& size = 0, QString type = "", unsigned long int off = 0);
    bool isAUStarter(NalUnitType type);
    bool isVCL(NalUnitType type, bool sync = false);
};

#endif // NALPARSER_H
