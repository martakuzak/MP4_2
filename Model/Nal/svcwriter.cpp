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

void SvcWriter::writeFtyp() {
    QDataStream stream(file);
    unsigned int size = 20; //PO DOPISANIU POPRAWIĆ
    stream<<quint32(size);
    stream.writeRawData("ftyp", 4);//i teraz jaki typ?
    stream.writeRawData("iso5", 4); //major_brand //SPRAWDZIĆ
    stream<<quint32(0); //minor_version /SPRAWDZIĆ, ALE NIE MA TO TAKIEGO ZNACZENIA
    stream.writeRawData("avc1", 4); //compatible brands /SPRAWDZIĆ

}
    void SvcWriter::writeMoov() {
        QDataStream stream(file);
        unsigned int size = 8 + writeMvhd(false) + writeTrak(false);
        stream<<quint32(size);
        stream.writeRawData("moov", 4);
        writeMvhd(true);
        writeTrak(true);

    }
    unsigned int SvcWriter::writeMvhd(bool write) {
        unsigned short version = 0; //0 lub 1
        unsigned int size = (version) ? MVHD_SIZE_1: MVHD_SIZE_0;
        if(!write)
            return size;
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("mvhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        /*if(version) {
            stream<<quint64(creation_time);
            stream<<quint64(modfication_time);
            stream<<quint32(timescale);
            stream<<quint64(duration);
        }
        else {
            stream<<quint32(creation_time);
            stream<<quint32(modfication_time);
            stream<<quint32(timescale);
            stream<<quint32(duration);
        }*/
        return size;
    }

    unsigned int SvcWriter::writeTrak(bool write) {
        return 0;
    }

   /* unsigned int writeTkhd(bool write);
    unsigned int writeMdia(bool write);
    unsigned int writeMdhd(bool write);
    unsigned int writeHdlr(bool write);
    unsigned int writeMinf(bool write);
    unsigned int writeVmhd(bool write);
    unsigned int writeDinf(bool write);
    unsigned int writeDref(bool write);
    unsigned int writeStbl(bool write);
    unsigned int writeStsd(bool write);
    unsigned int writeStts(bool write);
    unsigned int writeCtts(bool write);
    unsigned int writeStsc(bool write);
    unsigned int writeStsz(bool write); //stz2?
    unsigned int writeStco(bool write);
    unsigned int writeStss(bool write);
    void writeMdat();
    */
