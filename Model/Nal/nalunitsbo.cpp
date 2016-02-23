#include "nalunitsbo.h"
#include <QDebug>

NalUnitsBO::NalUnitsBO(const QString& name, const QList<std::shared_ptr<NalUnit> >& nals, unsigned int sfl, unsigned int apl,
                       const QList<unsigned int> frames, const QList<unsigned int> sync, const QList<unsigned int> sps,
                       const QList<unsigned int> pps): fileName(name), nalUnits(nals), sizeFieldLen(sfl),
    allPrefLength(apl), syncNalIdx(sync), seqParSetIdx(sps), picParSetIdx(pps), startFrameNalIdx(frames) {
    calcNewNalOffsets();
}

QString NalUnitsBO::getFileName() const {
    return fileName;
}

QList<std::shared_ptr<NalUnit> > NalUnitsBO::getNalUnits() const {
    return nalUnits;
}

QList<unsigned int> NalUnitsBO::getSyncIdx() const {
    return syncNalIdx;
}

unsigned short NalUnitsBO::getSizeFieldLen() const {
    return sizeFieldLen;
}

unsigned int NalUnitsBO::getAllPrefLength() const {
    return allPrefLength;
}

QList<std::shared_ptr<NalUnit>> NalUnitsBO::getSeqParSet() const {
    QList<std::shared_ptr<NalUnit>> sps;
    for(int i = 0; i < seqParSetIdx.size(); ++ i)
        sps.append(nalUnits.at(seqParSetIdx.at(i)));
    return sps;
}

QList<std::shared_ptr<NalUnit>> NalUnitsBO::getPicParSet() const {
    QList<std::shared_ptr<NalUnit>> pps;
    for(int i = 0; i < picParSetIdx.size(); ++ i)
        pps.append(nalUnits.at(picParSetIdx.at(i)));
    return pps;
}

std::shared_ptr<NalUnit> NalUnitsBO::getNalUnit(unsigned int idx) const {
    if(idx >= nalUnits.size())
        return NULL;
    return nalUnits.at(idx);
}

unsigned int NalUnitsBO::getStartFrameNalIdx(unsigned int idx) const {
    return startFrameNalIdx.at(idx);
}

int NalUnitsBO::getFramesNumber() const {
    return startFrameNalIdx.size();
}

unsigned int NalUnitsBO::getFrameSize(int idx) const {
    if(idx > startFrameNalIdx.size())
        return 0;
    //NAL startowy
    // NalUnit nalStart = this->getNalUnit(getStart);
    //unsigned int size = 0;
    //for(int i = idx; i < idx; )
}


unsigned int NalUnitsBO::allSPSLen() {
    unsigned int len = 0;
    for(int i = 0; i < seqParSetIdx.size(); ++i) {
        len += (nalUnits.at(seqParSetIdx.at(i))->getLength() - nalUnits.at(i)->getStartCodeLength());
    }
    return len;
}

unsigned int NalUnitsBO::allPPSLen() {
    unsigned int len = 0;
    for(int i = 0; i < picParSetIdx.size(); ++i) {
        len += (nalUnits.at(picParSetIdx.at(i))->getLength() - nalUnits.at(i)->getStartCodeLength());
    }
    return len;
}

void NalUnitsBO::calcNewNalOffsets() {
    QList<std::shared_ptr<NalUnit>>::const_iterator it;
    unsigned long newOffset = 0;
    for(it = nalUnits.constBegin(); it < nalUnits.constEnd(); ++it) {
        newNalOffsets.append(newOffset);
        newOffset += ((*it)->getLength() + sizeFieldLen);
    }
}

unsigned long NalUnitsBO::getFrameOffset(unsigned int nalIdx) {
    return nalUnits.at(nalIdx)->getOffset();
}

unsigned long NalUnitsBO::getNalUnitsByteLen(int startIdx, int endIdx) {
    unsigned long size = 0;
    for(int idx = startIdx; idx <= endIdx; ++ idx)
        size += (nalUnits.at(idx)->getLength() + sizeFieldLen);
    return size;
}
