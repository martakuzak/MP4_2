#ifndef NALUNITSDTO_H
#define NALUNITSDTO_H

#include <QString>
#include <QList>
#include <memory>
#include "nalunit.h"


class NalUnitsBO {   
protected:
    QString svcName;
    QList<std::shared_ptr<NalUnit> > nalUnits;
    QList<unsigned int> syncIdx;
    QList<unsigned int> seqParSetIdx;
    QList<unsigned int> picParSetIdx;
    unsigned short sizeFieldLen;
    unsigned int allPrefLength;
    QList<unsigned long> newNalOffsets;
    QList<unsigned int> startFrameNalIdx;
    void calcNewSampleOffsets();
public:
    NalUnitsBO(const QString& name, const QList<std::shared_ptr<NalUnit> >& nals, unsigned int sfl, unsigned int apl, const QList<unsigned int> frames,
               const QList<unsigned int> sync, const QList<unsigned int> sps, const QList<unsigned int> pps);
    QString getSvcName() const;
    QList<std::shared_ptr<NalUnit> > getNalUnits() const;
    QList<unsigned int> getSyncIdx() const;
    unsigned short getSizeFieldLen() const;
    unsigned int getAllPrefLength() const;
    QList<std::shared_ptr<NalUnit>> getSeqParSet() const;
    QList<std::shared_ptr<NalUnit>> getPicParSet() const;
    std::shared_ptr<NalUnit> getNalUnit(unsigned int idx) const;
    unsigned int getStartFrameNalUnitIdx(unsigned int idx) const;
    int getFrameNum() const;
    unsigned int getFrameSize(int idx) const;
    unsigned int allSPSLen();
    unsigned int allPPSLen();
    unsigned long getFrameOffset(unsigned int nalIdx);
    unsigned long getNalUnitsSize(int startIdx, int endIdx);

};

#endif // NALUNITSDTO_H
