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
    unsigned long int valueOfGroupOfBytes(QFile *file, const int & length, const unsigned long int& offset = 0);
    /*!
      *\brief signedValueOfGroupOfBytes takes a given sequence of bytes and converts them into unsigned long int value
      *\param length number of bytes in the sequence
      *\param offset offset of the sequence in the file
      *\return signed value of byte sequence
     */
    signed long int signedValueOfGroupOfBytes(QFile *file, const int & length, const unsigned long int& offset = 0);
    /*!
      *\brief valueOfGroupOfBits takes a given sequence of bits and converts them into unsigned long int value
      *\param length number of bits in the sequence
      *\param offset bit offset of the sequnce in the file
      *\return unsigned value of bit sequence
     */
    unsigned long int valueOfGroupOfBits(QFile *file, const int & length, const unsigned long int& offset);
    /*!
      *\brief qstringValue takes a given sequence of bytes and converts them into QString value by
      *changing each byte using ASCII code
      *\param length number of bytes in the sequence
      *\param offset offset of the sequence in the file
      *\return QString value of byte sequence
     */
    QString qstringValue(QFile *file, const unsigned int& length, const unsigned int& offset);

};

#endif // BITOPERATOR_H
