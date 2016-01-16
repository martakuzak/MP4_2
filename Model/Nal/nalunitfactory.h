#ifndef NALUNITFACTORY_H
#define NALUNITFACTORY_H

#include "nalunit.h"
#include "nalparser.h"
#include "box.h"
#include <memory>


class NALParser;
class FileService;
class BitOperator;

class NalUnitFactory {
protected:
    NALParser* parser;
    FileService *fileService; //JEST TO BEZNADZIEJNE NA MAKSA!!!!!!!!!!! PISIONT RAZY TO SAMO
    BitOperator *bitOperator;

    unsigned long int valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    signed long int signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    unsigned long int valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const;
    QString stringValue(const unsigned int & length, const unsigned long& offset) const;
public:
    NalUnitFactory(NALParser* par, FileService* fs);
    ~NalUnitFactory();

    std::shared_ptr<NalUnit> getNalUnit(int typeCode, unsigned int nalRefIdc, unsigned long offset, const unsigned short & sl = 3);
};

#endif // NALUNITFACTORY_H
