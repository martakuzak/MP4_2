#ifndef NALUNITFACTORY_H
#define NALUNITFACTORY_H

#include "nalunit.h"
#include "nalparser.h"
#include <memory>


class NALParser;

class NalUnitFactory {
protected:
    NALParser* parser;
public:
    NalUnitFactory(NALParser* par);
    ~NalUnitFactory();

    std::shared_ptr<NalUnit> getNalUnit(int typeCode, unsigned int nalRefIdc, unsigned long offset);
};

#endif // NALUNITFACTORY_H
