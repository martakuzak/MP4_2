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
    unsigned short sizeFieldLen;
    unsigned int allPrefLength;
    QList<unsigned long> newNalOffsets;
    void calcNewSampleOffsets();
public:
    NalUnitsBO(const QString& name, const QList<std::shared_ptr<NalUnit> >& nals, unsigned int sfl, unsigned int apl,
               const QList<unsigned int> sync);
    QString getSvcName() const;
    QList<std::shared_ptr<NalUnit> > getNalUnits() const;
    QList<unsigned int> getSyncIdx() const;
    unsigned short getSizeFieldLen() const;
    unsigned int getAllPrefLength() const;
};

#endif // NALUNITSDTO_H
