#ifndef FILEBITOPERATOR_H
#define FILEBITOPERATOR_H

#include <QtMath>
#include "bitoperator.h"
#include "fileservice.h"

class ExpGolombResult {
private:
    unsigned int value;
    unsigned int length;
public:
    ExpGolombResult(const unsigned int& val, const unsigned int& len);
    unsigned int getValue() const;
    unsigned int getLength() const;
};

/*!
 * \brief The FileBitOperator class provides functionalities of both file service and bit operations.
 *
 */
class FileBitOperator {
private:
   BitOperator* bitOperator;
   FileService* fileService;
public:
   /*!
     * \brief FileBitOperator
     * \param name file name
     */
    FileBitOperator(const QString &name);
    ~FileBitOperator();
    /*!
     * \brief openFile Opens file with the name given in constructor paramater
     * \param openMode open mode
     * QIODevice::NotOpen	0x0000	The device is not open.
        QIODevice::ReadOnly	0x0001	The device is open for reading.
        QIODevice::WriteOnly	0x0002	The device is open for writing.
        QIODevice::ReadWrite	ReadOnly | WriteOnly	The device is open for reading and writing.
        QIODevice::Append	0x0004	The device is opened in append mode, so that all data is written to the end of the file.
        QIODevice::Truncate	0x0008	If possible, the device is truncated before it is opened. All earlier contents of the device are lost.
        QIODevice::Text	0x0010	When reading, the end-of-line terminators are translated to '\n'. When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32.
        QIODevice::Unbuffered	0x0020	Any buffer in the device is bypassed.
     * /return true if file opens with success
     */
    bool openFile(QIODevice::OpenMode openMode = QIODevice::ReadOnly) {
        return fileService->openFile(openMode);
    }
    /*!
     * \brief getSize
     * \return size of the file
     */
    qint64 getSize() { return fileService->getSize();}
    /*!
     * \brief close closes the file
     */
    void close() { fileService->close(); }
    /*!
     * \brief valueOfGroupOfBytes
     * \param length length of the byte array in bytes
     * \param offset offset in file (in bytes)
     * The array represents the number that is calculated by merging bytes next to each other.
     * In other words it is a decimal value of given number in 256 (8-byte) positial notation.
     * \return unsigned long value of the bytes in the array
     */
    unsigned long int valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    /*!
     * \brief signedValueOfGroupOfBytes
     * \param length length of the byte array in bytes
     * \param offset offset in file (in bytes)
     * \return signed long value of the bytes in the array
     */
    signed long int signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    /*!
     * \brief valueOfGroupOfBits
     * \param length length of the byte array in bytes
     * \param offset offset in file (in bytes)
     * \return unsigned long value of the bytes in the array
     */
    unsigned long int valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const;
    /*!
     * \brief stringValue
     * \param length length of the byte array in bytes
     * \param offset offset in file (in bytes)
     * \return string value created by combining the bytes together
     * \example entry = {77, 64, 114, 99, 105, 110}
     * The result is the combination of each entry character converted to the ASCII character: Marcin
     * \note ASCII coding used here
     */
    QString stringValue(const unsigned int & length, const unsigned long& offset) const;
    /*!
     * \brief unsignedExpGolombValue
     * \param offset bit offset in the file of coded number
     * \return unsigned integer value of a number coded with Exp-Golomb coding
     */
    ExpGolombResult unsignedExpGolombValue(const unsigned long & offset) const;
};

#endif // FILEBITOPERATOR_H
