#include "nalparser.h"

NALParser::NALParser() {

}

NALParser::NALParser(const QString &fileName) {
    this->fileName=fileName;
    this->fileSize = 0;
    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        return ;
    }
    fileSize = file->size();
}

NALParser::~NALParser() {

}

void NALParser::parseFile() {
    QByteArray byteArray;
    unsigned long int offset= 0;//offset w pliku

}
