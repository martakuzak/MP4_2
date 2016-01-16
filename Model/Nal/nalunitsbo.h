#ifndef NALUNITSDTO_H
#define NALUNITSDTO_H

#include <QString>
#include <QList>
#include <memory>
#include "nalunit.h"


class NalUnitsBO {
public:
    NalUnitsBO(const QString& name, const QList<std::shared_ptr<NalUnit> >& nals, unsigned int sfl, unsigned int apl);
    QString getSvcName() const;
    QList<std::shared_ptr<NalUnit> > getNalUnits() const;
    unsigned short getSizeFieldLen() const;
    unsigned int getAllPrefLength() const;

protected:
    QString svcName;
    QList<std::shared_ptr<NalUnit> > nalUnits;
    unsigned short sizeFieldLen;
    unsigned int allPrefLength;
};

#endif // NALUNITSDTO_H
