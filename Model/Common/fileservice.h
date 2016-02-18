#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <cstring>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDebug>

/**
 * @brief The FileService class is destined to do basic operations on the file
 */
class FileService {
private:
    /**
     * @brief file file on which the class operates
     */
    QFile* file;
    /**
     * @brief BITS_IN_BYTE number of bits in the byte
     */
    const int BITS_IN_BYTE = 8;
public:
    /**
     * @brief FileService
     * @param name file name
     */
    FileService(const QString &name);
    ~FileService();

    /**
     * @brief openFile Opens file with the name given in constructor paramater
     * @param openMode open mode
     * QIODevice::NotOpen	0x0000	The device is not open.
        QIODevice::ReadOnly	0x0001	The device is open for reading.
        QIODevice::WriteOnly	0x0002	The device is open for writing.
        QIODevice::ReadWrite	ReadOnly | WriteOnly	The device is open for reading and writing.
        QIODevice::Append	0x0004	The device is opened in append mode, so that all data is written to the end of the file.
        QIODevice::Truncate	0x0008	If possible, the device is truncated before it is opened. All earlier contents of the device are lost.
        QIODevice::Text	0x0010	When reading, the end-of-line terminators are translated to '\n'. When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32.
        QIODevice::Unbuffered	0x0020	Any buffer in the device is bypassed.
     * @return true if file opens with success
     */
    bool openFile(QIODevice::OpenMode openMode = QIODevice::ReadOnly) {
        if(file == NULL)
            return NULL;
        bool tmp = file->open(openMode);
        return tmp;
    }
    /**
     * @brief getSize
     * @return size of the file
     */
    qint64 getSize() { return file->size(); }
    /**
     * @brief close closes the file
     */
    void close() { file->close(); }
    //offset i number w byte'ach
    /**
     * @brief getBytes puts char array containing the bytes of given length which are located in the file with given offset into destination array
     * @param dst destination
     * @param length length of the byte array in bytes
     * @param offset offset in file (in bytes)
     */
    void getBytes(char* dst, unsigned int length, unsigned long offset);
    //offset i number w bitach
    /**
     * @brief getBits puts char array containing the bits of given length which are located in the file with given offset into destination array
     * @param dst destination
     * @param length length of the bit array in bits
     * @param offset offset in file (in bits)
     */
    void getBits(char* dst, unsigned int length, unsigned long offset);
protected:
    /**
     * @brief toBitArray converts byte into char bit array
     * @param dst destination of the converted result
     * @param byte byte that contains bit sequence that is supposed to be returned
     * @param prefix number of bits to skip as a prefix (MSB)
     * @param suffix number of bits to skip as a suffix (LSB)
     * @example Let's say that char* tmp = toBitArray(254, 3, 1);
     * 254 -> 11111110b
     * We skip 3 MSB and 1 LSB, so the result is 1111b
     * tmp = {1, 1, 1, 1}
     */
    void toBitArray(char* dst,  char byte, int length, int suffix = 0);
};

#endif // FILESERVICE_H
