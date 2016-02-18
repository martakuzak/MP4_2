#ifndef NALUNITFACTORY_H
#define NALUNITFACTORY_H

#include "nalunit.h"
#include "nalparser.h"
#include "box.h"
#include <memory>


class NALParser;
class FileBitOperator;

class NalUnitFactory {
protected:
    NALParser* parser;
    FileBitOperator * fbOperator;

public:
    NalUnitFactory(NALParser* par, FileBitOperator* fs);
    ~NalUnitFactory();

    std::shared_ptr<NalUnit> getNalUnit(int typeCode, unsigned int nalRefIdc, unsigned long offset, const unsigned short & sl = 3);
};

#endif // NALUNITFACTORY_H
