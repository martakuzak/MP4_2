#ifndef NALPARSER_H
#define NALPARSER_H

#include <QString>
#include <QFile>
#include "bitoperator.h"
#include <QByteArray>
#include "nalunittype.h"

class NALParser
{
public:
    NALParser();
    NALParser(const QString& fileName);
    ~NALParser();

    void parseFile();

    QString fileName;
    QFile* file;
    unsigned long int fileSize;
    BitOperator* bitOperator;
};

#endif // NALPARSER_H
