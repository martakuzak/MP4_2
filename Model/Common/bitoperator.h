#ifndef BITOPERATOR_H
#define BITOPERATOR_H
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QVariant>
#include <QTextStream>
#include <qDebug>

class Analyzer;
/*!
 * /brief The BitOperator class performes bit and byte operations
 */
class BitOperator {
public:
    BitOperator();
    ~BitOperator();
    /*!
     * /brief valueOfGroupOfBytes
     * /param array array of bytes
     * /param length length of array
     * /return unsigned long value of the bytes in the array
     * /example array = {0, 0, 0, 0, 2, 0, 1, 3}
     * The array represents the number that is calculated by merging bytes next to each other.
     * In other words it is a decimal value of given number (here 2013) in 256 (8-byte) positial notation.
     * /note unsigned int coding is assumed
     */
    unsigned long int valueOfGroupOfBytes(const char *array, const unsigned int & length) const;
    /*!
     * /brief signedValueOfGroupOfBytes
     * /param array array of bytes
     * /param length length of array
     * /return signed long value of the bytes in the array
     * /example array =
     *
     */
    signed long int signedValueOfGroupOfBytes(const char *array, const unsigned int & length) const;
    /*!
     * /brief valueOfGroupOfBits
     * /param array array of bits
     * /param length length of array
     * /return unsigned long value of the bytes in the array
     * /example array = {0, 0, 0, 1, 0, 0, 1, 0)
     * The array represents the number 00010010b which is 18. 18 is returned.
     * /note unsigned int coding is assumed
     */
    unsigned long int valueOfGroupOfBits(const char *array, const unsigned int & length) const;
    /*!
     * /brief stringValue
     * /param entry array that represents the bytes
     * /param length length of the array
     * /return string value created by combining the bytes together
     * /example entry = {77, 64, 114, 99, 105, 110}
     * The result is the combination of each entry character converted to the ASCII character: Marcin
     * /note ASCII coding used here
     */
    QString stringValue(const char *entry, const unsigned int & length) const;
};

#endif // BITOPERATOR_H
