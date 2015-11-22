#include "svcwriter.h"

SvcWriter::SvcWriter(const QString &name): fileName(name){
}

bool SvcWriter::writeFile(const QString& name) {
    fileName = name;
    file = new QFile(name);
    if(file->open(QIODevice::ReadWrite)) {
        writeFtyp();
        file->close();
    } else return false;
}

unsigned int SvcWriter::writeFtyp() {
    QDataStream stream(file);
    unsigned int size = 28; //JAKI???
    stream<<quint32(size);
    stream.writeRawData("ftyp", 4);//i teraz jaki typ?
    stream<<quint32(0); //minor_version
    //stream.writeRawData("avc1", 4); //copatible brands

    /*unsigned int size = 28;
    if(dashFile == NULL)
        return size;
    stream<<quint32(size);
    stream.writeRawData("ftyp", 4);
    stream.writeRawData("iso5", 4); //major_brand
    stream<<quint32(0); //minor_version
    stream.writeRawData("avc1", 4); //copatible brands
    stream.writeRawData("iso5", 4);
    stream.writeRawData("dash", 4);*/

    return size;
}
