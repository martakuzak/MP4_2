#include "filebitoperator.h"

FileBitOperator::FileBitOperator(const QString &name) {
    fileService = new FileService(name);
    bitOperator = new BitOperator();
}

FileBitOperator::~FileBitOperator() {
    fileService->close();
    delete fileService;
    delete bitOperator;
}

unsigned long int FileBitOperator::valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}

signed long int FileBitOperator::signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    long int ret = bitOperator->signedValueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}

unsigned long int FileBitOperator::valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBits(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBits(ptr, length);
    delete[] ptr;
    return ret;
}

QString FileBitOperator::stringValue(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    QString ret = bitOperator->stringValue(ptr, length);
    delete[] ptr;
    return ret;
}

ExpGolombResult FileBitOperator::unsignedExpGolombValue(const unsigned long & offset) const {
    int leadingZeroBits = -1;
    int off = offset;
    for(unsigned int b = 0; !b; leadingZeroBits ++, off++)
        b = valueOfGroupOfBits(1, off);
    unsigned int codeNum = qPow(2, leadingZeroBits) - 1 + valueOfGroupOfBits(leadingZeroBits, off);
    return ExpGolombResult(codeNum, 2*leadingZeroBits + 1);
}

ExpGolombResult::ExpGolombResult(const unsigned int& val, const unsigned int& len) : value(val), length(len) {}

unsigned int ExpGolombResult::getValue() const {
    return value;
}

unsigned int ExpGolombResult::getLength() const {
    return length;
}
