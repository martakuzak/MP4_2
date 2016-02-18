#ifndef FILEBITOPERATOR_H
#define FILEBITOPERATOR_H

#include "bitoperator.h"
#include "fileservice.h"

class FileBitOperator {
private:
   BitOperator* bitOperator;
   FileService* fileService;
public:
    FileBitOperator(const QString &name);
    ~FileBitOperator();
    bool openFile(QIODevice::OpenMode openMode = QIODevice::ReadOnly) {
        return fileService->openFile(openMode);
    }
    qint64 getSize() { return fileService->getSize();}

    void close() { fileService->close(); }
    unsigned long int valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    signed long int signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    unsigned long int valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const;
    QString stringValue(const unsigned int & length, const unsigned long& offset) const;
};

#endif // FILEBITOPERATOR_H
