#include "svcwriter.h"

SvcWriter::SvcWriter(NalUnitsBO *nalInfo): nalUnitsBO(nalInfo){
}

void SvcWriter::writeNAL(std::shared_ptr<NalUnit> nalUnit, QFile* file, unsigned short length) {
    QDataStream stream (outputFile);
    switch(length) {
    case 1:
        stream<<quint8(nalUnit->getStartCodeLength());
        break;
    case 2:
        stream<<quint16(nalUnit->getStartCodeLength());
        break;
    case 4:
        stream<<quint32(nalUnit->getStartCodeLength());
        break;
    }
    file->seek(nalUnit->getOffset() + nalUnit->getStartCodeLength());
    QByteArray array = file->read(nalUnit->getLength() - nalUnit->getStartCodeLength());
    outputFile->write(array);
}


bool SvcWriter::writeMP4File(const QString& name) {
    outputFile = new QFile(name);
    if(outputFile->open(QIODevice::ReadWrite)) {
        writeFtyp();
        writeMoov(1);
        writeMdat();
        outputFile->close();
        return true;
    }
    return false;
}

bool SvcWriter::writeBaseLayer(const QString &name) {
    outputFile = new QFile(name);
    QFile* file = new QFile(nalUnitsBO->getSvcName());
    if(outputFile->open(QIODevice::ReadWrite) && file->open(QIODevice::ReadOnly)) {
        QList<std::shared_ptr<NalUnit>>::const_iterator it;
        for(it = nalUnitsBO->getNalUnits().constBegin(); it < nalUnitsBO->getNalUnits().constEnd(); ++it) {
            if((*it)->getTypeCode() == NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP
                    || (*it)->getTypeCode() == IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP
                    || (*it)->getTypeCode() == SEQ_PARAMETER_SET_RBSP
                    || (*it)->getTypeCode() == PIC_PARAMETER_SET_RBSP) {
                file->seek((*it)->getOffset());
                QByteArray array = file->read((*it)->getLength());
                outputFile->write(array);
            }
        }
        file->close();
        outputFile->close();
        return true;
    }
    return false;
}


void SvcWriter::writeFtyp() {
    unsigned int size = 20; //PO DOPISANIU POPRAWIĆ
    QDataStream stream(outputFile);
    stream<<quint32(size);
    stream.writeRawData("ftyp", 4);//i teraz jaki typ?
    stream.writeRawData("avc1", 4); //major_brand //SPRAWDZIĆ
    stream<<quint32(0); //minor_version /SPRAWDZIĆ, ALE NIE MA TO TAKIEGO ZNACZENIA
    stream.writeRawData("mp41", 4); //compatible brands /SPRAWDZIĆ
}

void SvcWriter::writeMoov(int layerNum) {
    QDataStream stream(outputFile);
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
    unsigned int size = version ? MVHD_SIZE_1: MVHD_SIZE_0;
    if(write) {
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("mvhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        if(version) {
            stream<<quint64(getTimeSince1904()); //creation_time in seconds since midnight, Jn. 1, 1904, in UTC time
            stream<<quint64(getTimeSince1904()); //modfication_time in seconds since midnight, Jn. 1, 1904, in UTC time
            stream<<quint32(25); //timescale czas_trwania_w_s = duration/timescale
            stream<<quint64(81); //duration
        } else {
            stream<<quint32(getTimeSince1904()); //creation_time in seconds since midnight, Jn. 1, 1904, in UTC time
            stream<<quint32(getTimeSince1904()); //modfication_time in seconds since midnight, Jn. 1, 1904, in UTC time
            stream<<quint32(25); //timescale
            stream<<quint32(81); //duration
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
        QDataStream stream(outputFile);
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
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("tkhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        if(version) {
            stream<<quint64(getTimeSince1904()); //creation_time
            stream<<quint64(getTimeSince1904()); //modfication_time)
            stream<<quint32(trackID); //trackID
            stream<<quint32(0); //reserved
            stream<<quint64(81); //duration
        } else {
            stream<<quint32(getTimeSince1904()); //creation_time
            stream<<quint32(getTimeSince1904()); //modfication_time)
            stream<<quint32(trackID); //trackID
            stream<<quint32(0); //reserved
            stream<<quint32(81); //duration
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
        QDataStream stream(outputFile);
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
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("mdhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        if(version) {
            stream<<quint64(getTimeSince1904()); //creation_time
            stream<<quint64(getTimeSince1904()); //modfication_time)
            stream<<quint32(25); //timescale
            stream<<quint64(81); //duration
        } else {
            stream<<quint32(getTimeSince1904()); //creation_time
            stream<<quint32(getTimeSince1904()); //modfication_time)
            stream<<quint32(25); //timescale
            stream<<quint32(81); //duration
        }
        stream.writeRawData(UND_LAN_CODE, 2); //pad (1 bit) + unsigned int(5) [3] language //ISO-639-2/T language code
        stream<<quint16(0); //pre_defined = 0
    }
    return size;
}
unsigned int SvcWriter::writeHdlr(bool write) {
    unsigned short version = 0; //0 lub 1
    unsigned int size = 44; //zależy od name (na dole)
    if(write) {
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("hdlr", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(0); //pre_defined = 0
        stream.writeRawData(VIDE_TRACK, 4); //video track (soun, hint)
        for(int i = 0; i < 3; ++ i)
            stream<<quint32(0); //reserved = 0
        stream.writeRawData(VIDEO_HANDLER, 12); //string name
    }
    return size;
}

unsigned int SvcWriter::writeMinf(bool write) {
    unsigned int size = 8 + writeVmhd(false) + writeDinf(false) + writeStbl(false);
    if(write) {
        QDataStream stream(outputFile);
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
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("vmhd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(1); //flag3
        stream<<quint16(0); //graphicsmode = 0
        for(int i = 0; i < 3; ++ i)
            stream<<quint16(0); //opcolor = {0, 0, 0}
    }
    return size;
}
unsigned int SvcWriter::writeDinf(bool write){
    unsigned int size = 8 + writeDref(false);
    if(write) {
        QDataStream stream(outputFile);
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
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("dref", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(1); //flag3
        stream<<quint32(0); //entry_count
        //for(int i = 0; i < 0; ++i) //tyle ile entry_count
        //  writeUrl(true);
    }
    return size;
}
unsigned int SvcWriter::writeStbl(bool write){
    unsigned int size = 8 + writeStsd(false) + writeStts(false) + writeStsc(false) + writeStsz(false) + writeStco(false) + writeStss(false);
    if(write) {
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stbl", 4);
        writeStsd(true);
        writeStts(true);
        writeStsc(true);
        writeStsz(true);
        writeStco(true);
        writeStss(true);
    }
    return size;
}
unsigned int SvcWriter::writeStsd(bool write) {
    unsigned int size = 16 /* + writeMP4V/AVC1*/;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stsd", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(0); //entry_count
        //writeMP4V/AVC1
    }
    return size;
}

unsigned int SvcWriter::writeStts(bool write) {
    unsigned int size = 16 + 5*8;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stts", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(5); //entry_count
        for(int i = 0; i < 5; ++ i) {
            stream<<quint32(0); //sample_count
            stream<<quint32(0); //sample_delta
        }
    }
    return size;
}

unsigned int SvcWriter::writeCtts(bool write) {
    unsigned int size = 16 + 5*8;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("ctts", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(5); //entry_count
        for(int i = 0; i < 5; ++ i) {
            stream<<quint32(0); //sample_count
            stream<<quint32(0); //sample_offset
        }
    }
    return size;
}

unsigned int SvcWriter::writeStsc(bool write) {
    unsigned int size = 16 + 5*12;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stsc", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(5); //entry_count
        for(int i = 0; i < 5; ++ i) {
            stream<<quint32(0); //first_chunk
            stream<<quint32(0); //samples_per_chunk
            stream<<quint32(0); //sample_description_index
        }
    }
    return size;
}

unsigned int SvcWriter::writeStsz(bool write) { //stz2?
    unsigned int size = 20 + 5*4;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stsz", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(0); //sample_size
        stream<<quint32(5); //sample_count
        for(int i = 0; i < 5; ++ i) {
            stream<<quint32(0); //entry_size
        }
    }
    return size;
}

unsigned int SvcWriter::writeStco(bool write) {
    unsigned int size = 16 + 5*4;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stco", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(5); //entry_count
        for(int i = 0; i < 5; ++ i) {
            stream<<quint32(0); //chunk_offset
        }
    }
    return size;
}

unsigned int SvcWriter::writeStss(bool write) {
    unsigned int size = 16 + 5*4;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stss", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(5); //entry_count
        for(int i = 0; i < 5; ++i)
            stream<<quint32(0); //sample_number
    }
    return size;
}

void SvcWriter::writeMdat() {
    QDataStream stream(outputFile);
    short len = nalUnitsBO->getSizeFieldLen();
    if(len != -1) {
        QFile* svcFile = new QFile(nalUnitsBO->getSvcName());
        if(svcFile->open(QIODevice::ReadOnly)) {
            //oblicz rozmiar mdat
            unsigned int size = 8 + svcFile->size() - nalUnitsBO->getSizeFieldLen() +
                    nalUnitsBO->getSizeFieldLen() * nalUnitsBO->getNalUnits().size();
            stream<<quint32(size);
            stream.writeRawData("mdat", 4);
            QList<std::shared_ptr<NalUnit>>::const_iterator it;
            for(it =  nalUnitsBO->getNalUnits().constBegin(); it <  nalUnitsBO->getNalUnits().constEnd(); ++it)
                writeNAL(*it, svcFile, len);
        }
        svcFile->close();
    } else {
        stream<<quint32(8);
        stream.writeRawData("mdat", 4);
    }
}

unsigned int SvcWriter::getTimeSince1904() {
    return SEC_1904_1970 + QDateTime::currentMSecsSinceEpoch()/1000;
}
