#include "svcwriter.h"

SvcWriter::SvcWriter(NalUnitsBO *nalInfo): nalUnitsBO(nalInfo){
}

void SvcWriter::writeNAL(std::shared_ptr<NalUnit> nalUnit, QFile* file, unsigned short length, bool size) {
    QDataStream stream (outputFile);
    if(size) {
        switch(length) {
        case 1:
            stream<<quint8(nalUnit->getLength());
            break;
        case 2:
            stream<<quint16(nalUnit->getLength());//było getStartCodeLength
            break;
        case 4:
            stream<<quint32(nalUnit->getLength());
            break;
        }
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
    QFile* file = new QFile(nalUnitsBO->getFileName());
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

        stream<<quint32(65536); //rate, typically 1.0
        stream<<quint16(256); //volume, typically full volume
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
    unsigned int size = 8 + 4 + 4 + writeUrl(false);
    if(write) {
        unsigned short version = 0; //0 lub 1
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("dref", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(1); //flag3
        stream<<quint32(1); //entry_count
        //for(int i = 0; i < 0; ++i) //tyle ile entry_count
        writeUrl(true);
    }
    return size;
}
unsigned int SvcWriter::writeUrl(bool write) {
    unsigned int size = 8 + 4;
    if(write) {
        unsigned short version = 0; //0 lub 1
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("url ", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(1); //flag3 -  this file
    }
    return size;
}
unsigned int SvcWriter::writeStbl(bool write){
    unsigned int stsd = writeStsd(false);
    unsigned int stts = writeStts(false);
    unsigned int stsc = writeStsc(false);
    unsigned int stsz = writeStsz(false);
    unsigned int stco = writeStco(false);
    unsigned int stss = writeStss(false);

    unsigned int size = 8 + stsd + stts + stsc + stsz + stco + stss;
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
    unsigned int size = 16 + writeAvc1(false);
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
        writeAvc1(true);
        //writeMP4V/AVC1
    }
    return size;
}


unsigned int SvcWriter::writeAvc1(bool write) {
    unsigned int size = 86 + writeAvcC(false);
    if(write) {
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("avc1", 4);
        for(int i = 0; i < 6; ++ i)
            stream<<quint8(0); //reserved
        stream<<quint16(1); //data_reference_index
        stream<<quint16(0); //pre_defined
        stream<<quint16(0); //reserved
        stream<<quint64(0); //2 x pre_defined
        stream<<quint32(0); //pre_defined
        stream<<quint16(352); //width //POLICZYĆ?
        stream<<quint16(288); //height //POLICZYĆ?
        stream<<quint32(4718592); //horizresolution 0x00480000 - 72 dpi //?????
        stream<<quint32(4718592); //vetresoultion 0x00480000 - 72 dpi
        stream<<quint32(0); //reserved
        stream<<quint16(1); //frame_count
        stream.writeRawData("                                ", 32); //compressorname
        stream<<quint16(24); //depth, 0x0018
        stream<<quint16(-1);
        writeAvcC(true);
    }
    return size;
}

unsigned int SvcWriter::writeAvcC(bool write) {
    unsigned int size = 8 + 7 + 2*(nalUnitsBO->getPicParSet().size() + nalUnitsBO->getSeqParSet().size()) +
            nalUnitsBO->allPPSLen() + nalUnitsBO->allSPSLen();
    if(write) {
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("avcC", 4);
        stream<<quint8(1); //configurationVersion
        stream<<quint8(100); //AVCProfileIndication //
        stream<<quint8(0); //profile_compatibility //
        stream<<quint8(5); //AVCLevelIndication //
        stream<<quint8(252 + nalUnitsBO->getSizeFieldLen() - 1); //reserved ‘111111’b +lengthSizeMinusOne
        QList<std::shared_ptr<NalUnit>> sps = nalUnitsBO->getSeqParSet();
        QList<std::shared_ptr<NalUnit>> pps = nalUnitsBO->getPicParSet();

        stream<<quint8(224 + sps.size()); //reserved ‘111’b; + seqPicSet num
        QFile* svcFile = new QFile(nalUnitsBO->getFileName());
        if(svcFile->open(QIODevice::ReadOnly)) {
            for(int i = 0; i < sps.size(); ++ i) { //for (i=0; i< numOfSequenceParameterSets; i++) {
                std::shared_ptr<NalUnit> unit = sps.at(i);
                stream<<quint16(unit->getLength() - unit->getStartCodeLength());//sequenceParameterSetLength
                this->writeNAL(unit, svcFile, nalUnitsBO->getSizeFieldLen(), false);
                //bit(8*sequenceParameterSetLength) sequenceParameterSetNALUnit;
                qDebug()<<"SPS write i = "<<QString::number(i);
            }
            stream<<quint8(pps.size());
            for(int i = 0; i < pps.size(); ++ i) { //for (i=0; i< numOfPictureParameterSets; i++) {
                std::shared_ptr<NalUnit> unit = pps.at(i);
                stream<<quint16(unit->getLength() - unit->getStartCodeLength());//pictureParameterSetLength
                this->writeNAL(unit, svcFile, nalUnitsBO->getSizeFieldLen(), false);
                //bit(8*pictureParameterSetLength) pictureParameterSetNALUnit;
                qDebug()<<"PPS write i = "<<QString::number(i);

            }
        }
        svcFile->close();

    }

    return size;
}

unsigned int SvcWriter::writeStts(bool write) {
    unsigned int size = 12 + 4 + 5*8;
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
    unsigned int size = 12 + 4 + 1*12;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stsc", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(1); //entry_count
        for(int i = 0; i < 1; ++ i) {
            stream<<quint32(1); //first_chunk
            stream<<quint32(1); //samples_per_chunk
            stream<<quint32(1); //sample_description_index
        }
    }

    return size;
}

unsigned int SvcWriter::writeStsz(bool write) { //stz2?
    int frameCount = nalUnitsBO->getFramesNumber();
    unsigned int size = 12 +  8 + frameCount*4;
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
        stream<<quint32(frameCount); //sample_count
        for(int i = 0; i < frameCount - 1; ++ i) {
            stream<<quint32(nalUnitsBO->getNalUnitsByteLen(nalUnitsBO->getStartFrameNalIdx(i),
                                                        nalUnitsBO->getStartFrameNalIdx(i + 1) - 1)); //entry_size
        }
        stream<<quint32(nalUnitsBO->getNalUnitsByteLen(nalUnitsBO->getStartFrameNalIdx(frameCount - 2),
                        nalUnitsBO->getNalUnits().length() - 1));
        /*
         * if (sample_size==0) {
            for (i=1; i u sample_count; i++) {
                unsigned int(32) entry_size;
            }
           }*/
    }

    return size;
}

unsigned int SvcWriter::writeStco(bool write) {
    unsigned int size = 12 + 4 + 5*4;
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
    unsigned int syncSize = nalUnitsBO->getSyncIdx().size();
    unsigned int size = 12 + 4 + syncSize*4;
    if(write) {
        unsigned short version = 0;
        QDataStream stream(outputFile);
        stream<<quint32(size);
        stream.writeRawData("stss", 4);
        stream<<quint8(version);
        stream<<quint8(0); //flag1
        stream<<quint8(0); //flag2
        stream<<quint8(0); //flag3
        stream<<quint32(syncSize); //entry_count
        for(unsigned int i = 0; i < syncSize; ++i)
            stream<<quint32(nalUnitsBO->getSyncIdx().at(i)); //sample_number
    }

    return size;
}

void SvcWriter::writeMdat() {
    QDataStream stream(outputFile);
    short len = nalUnitsBO->getSizeFieldLen();
    if(len != -1) {
        QFile* svcFile = new QFile(nalUnitsBO->getFileName());
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
