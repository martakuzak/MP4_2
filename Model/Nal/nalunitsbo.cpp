#include "nalunitsbo.h"

NalUnitsBO::NalUnitsBO(const QString& name, const QList<std::shared_ptr<NalUnit> >& nals, unsigned int sfl, unsigned int apl,
                       const QList<unsigned int> sync): svcName(name), nalUnits(nals), sizeFieldLen(sfl), allPrefLength(apl), syncIdx(sync) {
    calcNewSampleOffsets();
}

QString NalUnitsBO::getSvcName() const {
    return svcName;
}

QList<std::shared_ptr<NalUnit> > NalUnitsBO::getNalUnits() const {
    return nalUnits;
}

QList<unsigned int> NalUnitsBO::getSyncIdx() const {
    return syncIdx;
}

unsigned short NalUnitsBO::getSizeFieldLen() const {
    return sizeFieldLen;
}

unsigned int NalUnitsBO::getAllPrefLength() const {
    return allPrefLength;
}

void NalUnitsBO::calcNewSampleOffsets() {
    QList<std::shared_ptr<NalUnit>>::const_iterator it;
    unsigned long newOffset = 0;
    for(it = nalUnits.constBegin(); it < nalUnits.constEnd(); ++it) {
        newNalOffsets.append(newOffset);
        newOffset += ((*it)->getLength() + sizeFieldLen);
    }
}

