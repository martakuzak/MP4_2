#ifndef NALPARSER_H
#define NALPARSER_H

#include <QString>
#include <QFile>
#include <QByteArray>

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
};

#endif // NALPARSER_H
