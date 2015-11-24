#include "svcwriter.h"

SvcWriter::SvcWriter(const QString &name): fileName(name){
}

bool SvcWriter::writeFile(const QString& name) {
    fileName = name;
    file = new QFile(name);
    if(file->open(QIODevice::ReadWrite)) {
        writeFtyp();
        writeMoov(2);
        file->close();
    } else return false;
}

void SvcWriter::writeFtyp() {
    QDataStream stream(file);
    unsigned int size = 20; //PO DOPISANIU POPRAWIĆ
    stream<<quint32(size);
    stream.writeRawData("ftyp", 4);//i teraz jaki typ?
    stream.writeRawData("avc1", 4); //major_brand //SPRAWDZIĆ
    stream<<quint32(0); //minor_version /SPRAWDZIĆ, ALE NIE MA TO TAKIEGO ZNACZENIA
    stream.writeRawData("avc2", 4); //compatible brands /SPRAWDZIĆ

}

void SvcWriter::writeMoov(int layerNum) {
    QDataStream stream(file);
    unsigned int size = 8 + writeMvhd(false, layerNum);
    for(int i = 0; i < layerNum; ++i)
        size += writeTrak(false, 0);
    stream<<quint32(size);
    stream.writeRawData("moov", 4);
    writeMvhd(true, layerNum);
    for(int i = 0; i < layerNum; ++i)
        writeTrak(true, i);
}

unsigned int SvcWriter::writeMvhd(bool write, int trackNum) {
    unsigned short version = 0; //0 lub 1
    unsigned int size = (version) ? MVHD_SIZE_1: MVHD_SIZE_0;
    if(write) {
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("mvhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        if(version) {
            stream<<quint64(0); //creation_time
            stream<<quint64(0); //modfication_time)
            stream<<quint32(0); //timescale
            stream<<quint64(0); //duration
        } else {
            stream<<quint32(0); //creation_time
            stream<<quint32(0); //modfication_time)
            stream<<quint32(0); //timescale
            stream<<quint32(0); //duration
        }

        stream<<quint32(16); //rate, typically 1.0
        stream<<quint16(4); //volume, typically full volume
        stream<<quint16(0); //reserved = 0
        stream<<quint64(0); //usnigned int(32([2] reserved = 0
        stream<<quint32(65536); //unity matrix, kolejno 0x00010000
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(65536); // 0x00010000
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(1073741824); // 0x40000000
        for(int i = 0; i < 6; ++i)
            stream<<quint32(0); //predefined = 0
        stream<<quint32(trackNum); //next_track_id
    }
    return size;
}

unsigned int SvcWriter::writeTrak(bool write, int trackID) {
    unsigned int size = 8 + writeTkhd(false, trackID) + writeMdia(false);
    if(write) {
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("trak", 4);
        writeTkhd(true, trackID);
        writeMdia(true);
    }
    return size;
}

unsigned int SvcWriter::writeTkhd(bool write, int trackID) {
    unsigned short version = 0; //0 lub 1
    unsigned int size = (version) ? TKHD_SIZE_1: TKHD_SIZE_0;
    if(write){
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("tkhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        if(version) {
            stream<<quint64(0); //creation_time
            stream<<quint64(0); //modfication_time)
            stream<<quint32(0); //timescale
            stream<<quint32(0); //reserved
            stream<<quint64(0); //duration
        } else {
            stream<<quint32(0); //creation_time
            stream<<quint32(0); //modfication_time)
            stream<<quint32(0); //timescale
            stream<<quint32(0); //reserved
            stream<<quint32(0); //duration
        }

        stream<<quint64(0); //unsigned int(32)[2] reserved = 0
        stream<<quint16(0); //layer !!!
        stream<<quint16(0); //alternate_group = 0
        stream<<quint16(0); //volume, 0x0100 gdy audio
        stream<<quint16(0); //reserved = 0
        stream<<quint32(65536); //unity matrix, kolejno 0x00010000
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(65536); // 0x00010000
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(0); //0
        stream<<quint32(1073741824); // 0x40000000
        stream<<quint32(0); //width
        stream<<quint32(0); //height
    }
    return size;
}

unsigned int SvcWriter::writeMdia(bool write) {
    unsigned int size = 8 + writeMdhd(false) + writeHdlr(false) + writeMinf(false);
    if(write) {
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("mdia", 4);
        writeMdhd(true);
        writeHdlr(true);
        writeMinf(true);
    }
    return size;
}

unsigned int SvcWriter::writeMdhd(bool write) {
    unsigned short version = 0; //0 lub 1
    unsigned int size = (version) ? MDHD_SIZE_1: MDHD_SIZE_0;
    if(write) {
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("mdhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        if(version) {
            stream<<quint64(0); //creation_time
            stream<<quint64(0); //modfication_time)
            stream<<quint32(0); //timescale
            stream<<quint64(0); //duration
        } else {
            stream<<quint32(0); //creation_time
            stream<<quint32(0); //modfication_time)
            stream<<quint32(0); //timescale
            stream<<quint32(0); //duration
        }
        stream<<quint16(0); //pad (1 bit) + unsigned int(5) [3] language //ISO-639-2/T language code
        stream<<quint16(0); //pre_defined = 0
    }
    return size;
}
unsigned int SvcWriter::writeHdlr(bool write) {
    unsigned short version = 0; //0 lub 1
    unsigned int size = 44; //zależy od name (na dole)
    if(write) {
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("hdlr", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(0); //pre_defined = 0
        stream.writeRawData("vide", 4); //video track (soun, hint)
        for(int i = 0; i < 3; ++ i)
            stream<<quint32(0); //reserved = 0
        stream.writeRawData("VideoHandler", 12); //string name
    }
    return size;
}

unsigned int SvcWriter::writeMinf(bool write) {
    unsigned int size = 8 + writeVmhd(false) + writeDinf(false) + writeStbl(false);
    if(write) {
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("minf", 4);
        writeVmhd(true);
        writeDinf(true);
        writeStbl(true);
    }
    return size;
}

unsigned int SvcWriter::writeVmhd(bool write) {
    unsigned int size = 20;
    if(write){
        unsigned short version = 0; //0 lub 1
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("vmhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint16(0); //graphicsmode = 0
        for(int i = 0; i < 3; ++ i)
            stream<<quint16(0); //opcolor = {0, 0, 0}
    }
    return size;
}
unsigned int SvcWriter::writeDinf(bool write){
    unsigned int size = 8 + writeDref(false);
    if(write) {
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("dinf", 4);
        writeDref(true);
    }
    return size;
}
unsigned int SvcWriter::writeDref(bool write){
    unsigned int size = 16;
    if(write) {
        unsigned short version = 0; //0 lub 1
        QDataStream stream(file);
        stream<<quint32(size);
        stream.writeRawData("dref", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(0); //entry_count
        //for(int i = 0; i < 0; ++i) //tyle ile entry_count
          //  writeUrl(true);
    }
    return size;
}
unsigned int SvcWriter::writeStbl(bool write){
    return 0;
}
/*unsigned int writeStsd(bool write);
    unsigned int writeStts(bool write);
    unsigned int writeCtts(bool write);
    unsigned int writeStsc(bool write);
    unsigned int writeStsz(bool write); //stz2?
    unsigned int writeStco(bool write);
    unsigned int writeStss(bool write);
    void writeMdat();
    */
