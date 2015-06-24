#ifndef BITOPERATOR_H
#define BITOPERATOR_H
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QVariant>
#include <QTextStream>
#include <qDebug>

class Analyzer;

class BitOperator {
public:
    BitOperator();
    ~BitOperator();

    unsigned long int valueOfGroupOfBytes(const char *array, const unsigned int & length) const;
    signed long int signedValueOfGroupOfBytes(const char *array, const unsigned int & length) const;
    unsigned long int valueOfGroupOfBits(const char *array, const unsigned int & length) const;
    QString stringValue(const char *entry, const unsigned int & length) const;

    //DO WYRZUCENIA STĄD
    unsigned long int unsignedExpGolomb(QFile *file, const unsigned long int& offset, int* resLength) const;
};

#endif // BITOPERATOR_H
