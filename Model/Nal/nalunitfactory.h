#ifndef NALUNITFACTORY_H
#define NALUNITFACTORY_H

#include "nalunit.h"
#include "nalparser.h"
#include <memory>


class NalUnitFactory {
public:
    NalUnitFactory();
    ~NalUnitFactory();

    std::shared_ptr<NalUnit> getNalUnit(int typeCode);
protected:
    NALParser* parser;
};

#endif // NALUNITFACTORY_H
