#include "nalunitsbo.h"

NalUnitsBO::NalUnitsBO(const QString& name, const QList<std::shared_ptr<NalUnit> >& nals, unsigned int sfl, unsigned int apl): svcName(name),
    nalUnits(nals), sizeFieldLen(sfl), allPrefLength(apl) {}

QString NalUnitsBO::getSvcName() const {
    return svcName;
}

QList<std::shared_ptr<NalUnit> > NalUnitsBO::getNalUnits() const {
    return nalUnits;
}

unsigned short NalUnitsBO::getSizeFieldLen() const {
    return sizeFieldLen;
}

unsigned int NalUnitsBO::getAllPrefLength() const {
    return allPrefLength;
}
