#include "dashcreator.h"

DashCreator::DashCreator(const QString &path, const QString &name, TreeModel *mod):
    dashPath(path), fileName(name), model(mod) {
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool DashCreator::writeFile(const unsigned int & maxSampleNum) {
    int last = fileName.lastIndexOf("\\");
    if(last == -1)
        last = fileName.lastIndexOf("/");
    QString name = fileName.mid(last + 1);
    file = new QFile(fileName);
    if(file->open(QIODevice::ReadOnly)) {
        QDir().mkdir(dashPath);
        QString dashName = QString(dashPath + "dash_" + name);
        dashFile = new QFile(dashName);
        if(dashFile->open(QIODevice::ReadWrite)) {
            writeFtyp(dashFile);
            writeFree(dashFile);
            writeMoov(dashFile);
            writeSegments(maxSampleNum, dashFile);

            dashFile->close();
            return true;
        }
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool DashCreator::writeFiles(const unsigned int & maxSampleNum) {
    int last = fileName.lastIndexOf("\\");
    if(last == -1)
        last = fileName.lastIndexOf("/");
    QString name = fileName.mid(last + 1);
    file = new QFile(fileName);
    if(file->open(QIODevice::ReadOnly)) {
        QDir().mkdir(dashPath);
        QString initName = QString(dashPath + "dash_init_" + name);
        initFile = new QFile(initName);
        if(initFile->open(QIODevice::ReadWrite)) {
            writeFtyp(initFile);
            writeFree(initFile);
            writeMoov(initFile);
            return writeSegments(maxSampleNum, initFile, dashPath, name);
        }
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::copyBox(const QString& type, QFile *dashFile, const unsigned long &maxSize) {
    QList<std::shared_ptr<Box>> boxes = model->getBoxes(type);
    if(dashFile == NULL) {
        if(!boxes.empty())
            return boxes.at(0)->getSize();
        else
            return 0;
    }
    unsigned long int size = 0;
    if(!boxes.empty()) {
        std::shared_ptr<Box> box = boxes.back();
        unsigned long int offset = box->getOffset();
        size = box->getSize();
        if(maxSize)
            size = maxSize;
        file->seek(offset);
        QByteArray array = file->read(size);
        dashFile->write(array);
        boxes.pop_back();
    }
    return size;
}
//////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::copyBox(const QString& type, std::shared_ptr<Box> parent, QFile *dashFile,
                                  const unsigned long &maxSize) {
    unsigned long int parentOffset = parent->getOffset();
    TreeItem *parentItem = model->getChild(parentOffset);
    if(parentItem ==  NULL) {
        //
    }
    TreeItem *boxChild = model->getChild(parentItem, type);
    if(boxChild == NULL)
        return 0;
    std::shared_ptr<Box> box = boxChild->getBox();
    if(box == NULL)
        return 0;
    if(dashFile == NULL) {
        return box->getSize();
    }
    unsigned long int size = 0;
    unsigned long int offset = box->getOffset();
    size = box->getSize();
    if(maxSize)
        size = maxSize;
    file->seek(offset);
    QByteArray array = file->read(size);
    dashFile->write(array);

    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned long int DashCreator::mdatSize(const unsigned long int& firstSample,
                                        const unsigned int& sampleNumber, SampleSizeBox *stsz) {
    unsigned long int mdatSize = 8;
    for (unsigned int i = firstSample; i< (firstSample + sampleNumber); ++i) {
        mdatSize += stsz->getSampleSize(i);
    }
    return mdatSize;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeAvc1(QFile *dashFile) {
    if(model->getBoxes("avc1").empty())
        return 0;
    std::shared_ptr<Box> avc1 = model->getBoxes("avc1").at(0); //nie ma potrzeby konwersji
    unsigned long int size = avc1->getSize();
    unsigned long int maxSize = avc1->getContainerOffset();
    if(dashFile == NULL)
        return size;
    copyBox("avc1", dashFile, maxSize);
    copyBox("avcC", dashFile);
    copyBox("btrt", dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeAvcC(QFile *dashFile) {
    if(model->getBoxes("avcC").empty())
        return 0;
    std::shared_ptr<Box> avcC = model->getBoxes("avcC").at(0); //nie ma potrzeby konwersji
    unsigned long int size = avcC->getSize();
    if(dashFile == NULL)
        return size;
    copyBox("avcC", dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeBtrt(QFile *dashFile) {
    if(model->getBoxes("btrt").empty())
        return 0;
    std::shared_ptr<Box> btrt = model->getBoxes("btrt").at(0); //nie ma potrzeby konwersji
    unsigned long int size = btrt->getSize();
    if(dashFile == NULL)
        return size;
    copyBox("btrt", dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeFree(QFile *dashFile) {
    QList <std::shared_ptr<Box>> free = model->getBoxes("free"); //nie ma potrzeby konwersji
    free.append(model->getBoxes("skip"));
    unsigned int size = 0;
    while (!free.empty()) {
        std::shared_ptr<Box> free1 = free.back();
        unsigned long int offset = free1->getOffset();
        unsigned long int size1 = free1->getSize();
        file->seek(offset);
        QByteArray array = file->read(size1);
        if(dashFile != NULL)
            dashFile->write(array);
        free.pop_back();
        size += size1;
    }
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeFtyp(QFile *dashFile) {
    QDataStream stream(dashFile);
    unsigned int size = 28;
    if(dashFile == NULL)
        return size;
    stream<<quint32(size);
    stream.writeRawData("ftyp", 4);
    stream.writeRawData("iso5", 4); //major_brand
    stream<<quint32(0); //minor_version
    stream.writeRawData("avc1", 4); //copatible brands
    stream.writeRawData("iso5", 4);
    stream.writeRawData("dash", 4);

    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMdat(const unsigned long int& firstSample, const unsigned int &sampleNumber,
                                    SampleSizeBox *stsz, QFile *dashFile) {
    unsigned long int size = mdatSize(firstSample, sampleNumber, stsz);
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    stream<<quint32(size); //4 bajty
    stream.writeRawData("mdat", 4); //4 bajty
    unsigned long int mdatOffset = model->getBoxes("mdat").at(0)->getOffset(); //nie ma potrzeby konwersji
    QByteArray array;
    if(firstSample) {
        unsigned long int offset = mdatSize(0, firstSample, stsz);
        file->seek(offset + mdatOffset);
    }
    else {
        file->seek(mdatOffset + 8);
    }

    if(size <= 2028) {
        array = file->read(size - 8);
        dashFile->write(array);
    }
    else {
        unsigned int position = 0;
        while(position <= (size - 8)) {
            if(position + 2028 > size - 8)
                array = file->read(size - 8 - position);
            else
                array = file->read(2028);
            dashFile->write(array);
            position += 2028;
        }

    }
    return size;
}

////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMdhd(std::shared_ptr<Box> parent, QFile *dashFile) {
    unsigned long int parentOffset = parent->getOffset();
    TreeItem *parentItem = model->getChild(parentOffset);
    MediaHeaderBox *mdhd = dynamic_cast <MediaHeaderBox *> (model->getChild(parentItem, "mdhd")->getBox().get());
    unsigned long int size = mdhd->getSize();
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    unsigned int version = mdhd->getVersion();
    unsigned int maxSize = 24;
    if(version)
        maxSize = 32;
    copyBox("mdhd", dashFile, maxSize);
    if(version)
        stream<<quint64(0);
    else
        stream<<quint32(0);
    unsigned long int offset = mdhd->getOffset() + maxSize + 4 + 4*version;
    file->seek(offset);
    QByteArray array = file->read(size - maxSize - 4*(version + 1));
    dashFile->write(array);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMdia(std::shared_ptr<Box> parent, QFile *dashFile) {
    unsigned long int parentOffset = parent->getOffset();
    TreeItem *parentItem = model->getChild(parentOffset);
    std::shared_ptr<Box> mdia = model->getChild(parentItem, "mdia")->getBox();
    unsigned int long size = 8; //naglowek
    size = size + writeMdhd(mdia) + copyBox("hdlr", mdia) + writeMinf(mdia);
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    stream<<quint32(size);
    stream.writeRawData("mdia", 4);
    writeMdhd(mdia, dashFile);
    copyBox("hdlr", mdia, dashFile);
    writeMinf(mdia, dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMehd(QFile *dashFile) {
    MovieHeaderBox *mvhd = dynamic_cast <MovieHeaderBox*> (model->getBoxes("mvhd").at(0).get());
    unsigned long int duration = mvhd->getDuration();
    QDataStream stream(dashFile);

    if(duration > 0xFFFFFFFF) {
        if(dashFile == NULL)
            return 20;
        stream<<quint32(20);
        stream.writeRawData("mehd", 4);
        stream<<quint8(1); //version
        stream<<quint8(0); //flags
        stream<<quint16(0);
        stream<<quint64(duration);
        return 20;
    }
    else {
        if(dashFile == NULL)
            return 16;
        stream<<quint32(16);
        stream.writeRawData("mehd", 4);
        stream<<quint8(0); //version
        stream<<quint8(0); //flags
        stream<<quint16(0);
        stream<<quint32(duration);
        return 16;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMfhd(const unsigned long int& sequenceNumber, QFile *dashFile) {
    if(dashFile == NULL)
        return 16;
    QDataStream stream(dashFile);
    stream<<quint32(16); //size
    stream.writeRawData("mfhd", 4);
    stream<<quint8(0); //version
    stream<<quint8(0); //flags
    stream<<quint16(0);
    stream<<quint32(sequenceNumber);
    return 16;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMinf(std::shared_ptr<Box> parent, QFile *dashFile) {
    unsigned long int offset = parent->getOffset();
    TreeItem *parentItem = model->getChild(offset);
    std::shared_ptr<Box> minf = model->getChild(parentItem, "minf")->getBox();
    unsigned long int size = 8; //naglowek
    size = size + copyBox("vmhd", minf) + copyBox("smhd", minf) +copyBox("dinf", minf) + writeStbl(minf);
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    stream<<quint32(size);
    stream.writeRawData("minf", 4);
    copyBox("vmhd", minf, dashFile);
    copyBox("smhd", minf, dashFile);
    copyBox("dinf", minf, dashFile); //wszystko kopiujemy, lacznie z dziecmi: dref i url
    writeStbl(minf, dashFile);
    return size;
}////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMoof(const unsigned long int& sequenceNumber, const unsigned int& trackID,
                                    const unsigned long &baseMediaDecodeTime, const unsigned int& trunFlag2,
                                    const unsigned int& trunFlag3,
                                    const unsigned int& sampleCount, const unsigned int& firstSampleFlags,
                                    const unsigned long int& firstSample, SampleSizeBox *stsz,
                                    QFile *dashFile) {
    QDataStream stream(dashFile);
    //obliczenie obrazu
    int size = 8;
    size += 64; //po 16 od mfhd, tfhd i tfdt, początek trun
    //poniżej dalej trun
    size += 8; //naglowek traf
    if(trunFlag2 == 2) //sample sizes are present
        size += sampleCount*4;
    if(trunFlag3 == 1 || trunFlag3 == 4) //1- data-offset, 4 - firstsampleflags
        size += 4;
    else if(trunFlag3 == 5) //oba
        size += 8;
    //
    if(dashFile == NULL)
        return size;
    stream<<quint32(size);
    stream.writeRawData("moof", 4);

    writeMfhd(sequenceNumber, dashFile);
    writeTraf(trackID, baseMediaDecodeTime, trunFlag2, trunFlag3, sampleCount, size + 8, firstSampleFlags,
              firstSample, stsz, dashFile);

    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMoov(QFile *dashFile) {
    unsigned long int traksSize = 0;
    QList <std::shared_ptr<Box>> traks = model->getBoxes("trak");
    for (int i = 0; i < traks.size(); ++i) {
        traksSize += writeTrak(traks.at(i));
    }
    unsigned long int size = 8;
    size = size + writeMvhd() + writeMvex() + traksSize + copyBox("udta");
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    stream<<quint32(size);
    stream.writeRawData("moov", 4);
    writeMvhd(dashFile);
    writeMvex(dashFile);
    while(!traks.empty()){
        writeTrak(traks.back(), dashFile);
        traks.pop_back();
    }
    copyBox("udta", dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMvex(QFile *dashFile) {
    unsigned int size = 8;
    size += writeMehd();
    size += writeTrex();
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    stream<<quint32(size);
    stream.writeRawData("mvex", 4);
    writeMehd(dashFile);
    writeTrex(dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeMvhd(QFile *dashFile) {
    MovieHeaderBox *mvhd = dynamic_cast<MovieHeaderBox*> (model->getBoxes("mvhd").at(0).get());
    if(dashFile == NULL)
        return mvhd->getSize();
    QDataStream stream(dashFile);
    unsigned int version = mvhd->getVersion();
    unsigned int size = mvhd->getSize();
    stream<<quint32(size);
    stream.writeRawData("mvhd", 4);
    stream<<quint8(version); //version
    stream<<quint8(0); //flags
    stream<<quint16(0);
    file->seek(mvhd->getOffset() + 12);
    if(version) {
        QByteArray array = file->read(20); //creation_time, modification_time, timescale
        dashFile->write(array);
        stream<<quint64(0); //duration
        file->seek(mvhd->getOffset() + 12 + 28); //ustawiamy sie po duration
        array = file->read(size - 12 - 28); //wczytujemy wszystko po duration
        dashFile->write(array);
    }
    else {
        QByteArray array = file->read(12); //creation_time, modification_time, timescale
        dashFile->write(array);
        stream<<quint32(0); //duration
        file->seek(mvhd->getOffset() + 12 + 16);  //ustawiamy sie po duration
        array = file->read(size - 12 - 16); //wczytujemy wszystko po duration
        dashFile->write(array);
    }
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeSidx(const unsigned short int& version, const unsigned int& referenceID, const unsigned int& timescale,
                                    const unsigned long int& earliestPresentationTime, const unsigned long int& firstOffset,
                                    const unsigned int& referenceCount, const QList<unsigned short int>& referenceType,
                                    const QList<unsigned long int>& referenceSize, const QList<unsigned long int>& subsegmentDuration,
                                    const QList <unsigned short int>& startsWithSAP, const QList <unsigned short int>& SAPType,
                                    const QList <unsigned long int>& SAPDeltaTime, QFile *dashFile) {
    QDataStream stream(dashFile);
    unsigned int size = 12; //bo dziedziczy po FullBox
    size += 8; //referenceID, timescale
    if(version)
        size += 16; //earliestPresentationTime, firstOffset
    else
        size += 8;
    size += 4; //reserved, referenceCount
    size += referenceCount*12;
    if(dashFile == NULL)
        return size;
    stream<<quint32(size);
    stream.writeRawData("sidx", 4);
    stream<<quint8(version); //version
    stream<<quint8(0); //flags
    stream<<quint16(0);
    stream<<quint32(referenceID);
    stream<<quint32(timescale);
    if(version) {
        stream<<quint64(earliestPresentationTime);
        stream<<quint64(firstOffset);
    }
    else {
        stream<<quint32(earliestPresentationTime);
        stream<<quint32(firstOffset);
    }
    stream<<quint16(0); //reserved
    stream<<quint16(referenceCount);
    for(unsigned int i = 0; i <referenceCount; ++i) {
        unsigned long int tmp = referenceType.at(i);
        tmp = tmp << 31;
        tmp += referenceSize.at(i);
        stream<<quint32(tmp);
        stream<<quint32(subsegmentDuration.at(i));
        tmp = startsWithSAP.at(i);
        tmp = tmp << 3;
        tmp += SAPType.at(i);
        tmp = tmp <<28;
        tmp += SAPDeltaTime.at(i);
        stream<<quint32(tmp);
    }
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeStbl(std::shared_ptr<Box> minf, QFile *dashFile) {
    unsigned long int offset = minf->getOffset();
    TreeItem *parentItem = model->getChild(offset);
    std::shared_ptr<Box> stbl = model->getChild(parentItem, "stbl")->getBox();
    unsigned long int size = 8;
    size = size + writeStsd(stbl) + writeStsz(stbl) + writeStxx("stco") + writeStxx("stsc") +
            writeStxx("stts");
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    stream<<quint32(size);
    stream.writeRawData("stbl", 4);
    writeStsd(stbl, dashFile);
    writeStxx("stts", dashFile);
    writeStxx("stsc", dashFile);
    writeStsz(stbl, dashFile);
    writeStxx("stco", dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeStsd(std::shared_ptr<Box> stbl, QFile *dashFile) {
    unsigned long int offset = stbl->getOffset();
    TreeItem *parentItem = model->getChild(offset);
    std::shared_ptr<Box> stsd = model->getChild(parentItem, "stsd")->getBox();
    unsigned long int size = stsd->getSize();
    if(dashFile == NULL)
        return size;
    copyBox("stsd", stbl, dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeStsz(std::shared_ptr<Box> stbl, QFile *dashFile) {
    unsigned long int offset = stbl->getOffset();
    TreeItem *parentItem = model->getChild(offset);
    SampleSizeBox *stsz = dynamic_cast <SampleSizeBox*> (model->getChild(parentItem, "stsz")->getBox().get());
    if(dashFile == NULL)
        return 20;
    QDataStream stream(dashFile);
    stream<<quint32(20); //size
    stream.writeRawData("stsz", 4);
    stream<<quint32(0); //version i flags
    stream<<quint32(stsz->getSampleSize());
    stream<<quint32(0); //sample count
    return 20;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeStxx(const QString& type, QFile *dashFile) {
    if(dashFile == NULL)
        return 16;
    QDataStream stream(dashFile);
    stream<<quint32(16); //size
    stream.writeRawData(type.toStdString().c_str(), 4);
    stream<<quint32(0); //version i flags
    stream<<quint32(0); //entryCount
    return 16;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeStyp(QFile *dashFile) {
    QDataStream stream(dashFile);
    unsigned int size = 24;
    if(dashFile == NULL)
        return size;
    stream<<quint32(size);
    stream.writeRawData("styp", 4);
    stream.writeRawData("msdh", 4); //major_brand
    stream<<quint32(0); //minor_version
    stream.writeRawData("msdh", 4); //compatible brands
    stream.writeRawData("msix", 4);

    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeTfdt(const unsigned long int& baseMediaDecodeTime, QFile *dashFile) {
    if(dashFile == NULL)
        return 16;
    QDataStream stream(dashFile);
    stream<<quint32(16); //size
    stream.writeRawData("tfdt", 4);
    int version;
    if(baseMediaDecodeTime > 65535)
        version = 1;
    else
        version = 0;
    stream<<quint8(version); //version
    stream<<quint8(0); //flags //dlaczego 2?
    stream<<quint16(0);
    if(version)
        stream<<quint64(baseMediaDecodeTime);
    else
        stream<<quint32(baseMediaDecodeTime);
    return 16;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeTfhd(const unsigned int& trackID, QFile *dashFile) {
    if(dashFile == NULL)
        return 16;
    QDataStream stream(dashFile);
    stream<<quint32(16); //size
    stream.writeRawData("tfhd", 4);
    stream<<quint8(0); //version
    stream<<quint8(2); //flags //dlaczego 2?
    stream<<quint16(0);
    stream<<quint32(trackID);
    return 16;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeTkhd(std::shared_ptr<Box> parent, QFile *dashFile) {
    unsigned long int parentOffset = parent->getOffset();
    TreeItem *parentItem = model->getChild(parentOffset);
    TrackHeaderBox *tkhd = dynamic_cast <TrackHeaderBox*> (model->getChild(parentItem, "tkhd")->getBox().get());
    unsigned long int size = tkhd->getSize();
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    unsigned int version = tkhd->getVersion();
    unsigned int maxSize = 24;
    if(version)
        maxSize = 32;
    copyBox("tkhd", dashFile, maxSize);
    if(version)
        stream<<quint64(0);
    else
        stream<<quint32(0);
    unsigned long int offset = tkhd->getOffset() + maxSize + 4 + 4*version;
    file->seek(offset);
    QByteArray array = file->read(size - maxSize - 4*(version + 1));
    dashFile->write(array);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeTraf(const unsigned int& trackID, const unsigned long &baseMediaDecodeTime,
                                    const unsigned int& flag2, const unsigned int& flag3,
                                    const unsigned int& sampleCount, const signed int& dataOffset,
                                    const unsigned int& firstSampleFlags, const unsigned long int& firstSample,
                                    SampleSizeBox *stsz, QFile *dashFile) {
    QDataStream stream(dashFile);
    //obliczenie rozmiaru
    int size = 8;
    size += 48; //po 16 od tfhd i tfdt, początek trun
    //poniżej dalej trun
    if(flag2 == 2) //sample sizes are present
        size += sampleCount*4;
    if(flag3 == 1 || flag3 == 4) //1- data-offset, 4 - firstsampleflags
        size += 4;
    else if(flag3 == 5) //oba
        size += 8;
    //
    if(dashFile == NULL)
        return size;
    stream<<quint32(size);
    stream.writeRawData("traf", 4);

    writeTfhd(trackID, dashFile);
    writeTfdt(baseMediaDecodeTime, dashFile);
    writeTrun(flag2, flag3, sampleCount, dataOffset, firstSampleFlags, firstSample, stsz, dashFile);

    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeTrak(std::shared_ptr<Box> trak, QFile *dashFile) {
    unsigned long int size = 8;
    size = size + writeTkhd(trak) + writeMdia(trak);
    if(dashFile == NULL)
        return size;
    QDataStream stream(dashFile);
    stream<<quint32(size);
    stream.writeRawData("trak", 4);
    writeTkhd(trak, dashFile);
    writeMdia(trak, dashFile);
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeTrex(QFile *dashFile) {
    if(dashFile == NULL)
        return 32;
    TrackHeaderBox *tkhd = dynamic_cast <TrackHeaderBox *> (model->getBoxes("tkhd").at(0).get());
    QDataStream stream(dashFile);
    stream<<quint32(32);
    stream.writeRawData("trex", 4);
    stream<<quint8(0); //version
    stream<<quint8(0); //flags
    stream<<quint16(0);
    stream<<quint32(tkhd->getTrackID()); //trackID
    stream<<quint32(1); // ? default_sample_description_index
    stream<<quint32(1); // ? default_sample_duration
    stream<<quint32(1); // ? default_sample_size
    stream<<quint32(65536); //? default_sample_flags
    return 32;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeTrun(const unsigned int& flag2, const unsigned int& flag3,
                                    const unsigned int& sampleCount, const signed int& dataOffset,
                                    const unsigned int& firstSampleFlags, const unsigned long int& firstSample,
                                    SampleSizeBox *stsz, QFile *dashFile) {
    QDataStream stream(dashFile);
    int size = 16; //size + type + version + flags + sampleCount
    if(flag2 == 2) //sample sizes are present
        size += sampleCount*4;
    if(flag3 == 1 || flag3 == 4) //1- data-offset, 4 - firstsampleflags
        size += 4;
    else if(flag3 == 5) //oba
        size += 8;
    if(dashFile == NULL)
        return size;
    stream<<quint32(size); //size
    stream.writeRawData("trun", 4);
    stream<<quint8(0); //version
    stream<<quint8(0); //flags
    stream<<quint8(flag2);
    stream<<quint8(flag3);
    stream<<quint32(sampleCount); //sample count
    if(flag3 == 1 || flag3 == 5)
        stream<<qint32(dataOffset);
    if(flag3 == 2 || flag3 == 5)
        stream<<quint32(firstSampleFlags);
    if(flag2 == 2) {
        for(unsigned int i = firstSample; i< firstSample + sampleCount; ++i) {
            stream<<quint32(stsz->getSampleSize(i));
        }
    }
    return size;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashCreator::writeVmhd(std::shared_ptr<Box> parent, QFile *dashFile) {
    unsigned long int offset = parent->getOffset();
    TreeItem *parentItem = model->getChild(offset);
    std::shared_ptr<Box> vmhd = model->getChild(parentItem, "vmhd")->getBox();
    if(dashFile == NULL)
        return 20;
    QDataStream stream(dashFile);
    stream<<quint32(20); //size
    stream.writeRawData("vmhd", 4);
    stream<<quint16(0); //version i pierwsza flaga
    stream<<quint16(1); //druga i trzecia flaga
    stream<<quint32(0); //graphics mode i r z opcolor
    stream<<quint32(0); //opcolor g i b
    return 20;
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashCreator::writeSegments(const unsigned int& maxSampleNum, QFile *dashFile, const QString &path,
                                const QString &fileName) {
    SampleSizeBox *stsz = dynamic_cast <SampleSizeBox*> (model->getBoxes("stsz").at(0).get()); //Sample Size Box
    SyncSampleBox *stss = dynamic_cast <SyncSampleBox*> (model->getBoxes("stss").at(0).get()); //Sync Sample Box
    MediaHeaderBox *mdhd = dynamic_cast <MediaHeaderBox*> (model->getBoxes("mdhd").at(0).get()); //Media Header Box
    TrackHeaderBox *tkhd = dynamic_cast <TrackHeaderBox*> (model->getBoxes("tkhd").at(0).get()); //Track Header Box
    unsigned int flag3 = 5;
    unsigned int maxSegmentNum = stss->getEntryCount(); //segmentow tyle co sync punktow?
    unsigned int segmentID = 0; //aktualny numer segmentu
    unsigned long int sequenceNumber = 0;
    unsigned long int baseMediaDecodeTime = 0;
    while(segmentID < maxSegmentNum) {
        unsigned int subsegmentID = 0; //numer podsegmentu

        unsigned int firstSample; //numer pierwszej probki segmentu
        unsigned int secondSample; //numer pierwszej probki poza segmentem
        firstSample = stss->getSyncSample(segmentID);
        if(segmentID == maxSegmentNum - 1) {
            secondSample = stsz->getEntryCount() + 1;
        }
        else {
            secondSample = stss->getSyncSample(segmentID + 1);
        }
        unsigned int samplesInSegmentNum = secondSample - firstSample; //ilosc probek w segmencie
        unsigned int subsegmentNum = 1; //ilosc podsegmentow - co najmniej 1
        if(samplesInSegmentNum > maxSampleNum) { //jesli jest ich wiecej niz maxSampleNum
            subsegmentNum = samplesInSegmentNum/maxSampleNum; //to ilosc podsegmentow jest ilorazem wszystkich probek w segmencie i maxSampleNum
            if(samplesInSegmentNum % maxSampleNum) {//zaokraglone ku gorze
                ++ subsegmentNum;
            }
        }
        //write styp
        if(path != QString("")) {
            dashFile->close();
            QString dashName = QString(path + "dash_" +
                                       QString::number(segmentID) + "_" + fileName + "s");
            dashFile = new QFile(dashName);
            if(dashFile->open(QIODevice::ReadWrite))
                writeStyp(dashFile);
            else
                return false;
        }
        //write sidx
        //przygotowanie parametrow
        unsigned short int version = 0;
        unsigned int referenceID = tkhd->getTrackID(); //numer tracku z tkhd
        unsigned int timescale = mdhd->getMediaTimeScale(); //timescale z mdhd
        unsigned long int earliestPresentationTime = stss->getSyncSample(segmentID) - 1;//odleglosc od poprzedniej sync sample?
        unsigned long int firstOffset = 0; //?
        unsigned int referenceCount = subsegmentNum;
        QList <unsigned short int> referenceType;
        QList <unsigned long int> referenceSize;
        QList <unsigned long int> subsegmentDuration;
        QList <unsigned short int> startsWithSAP;
        QList <unsigned short int> SAPType;
        QList <unsigned long int> SAPDeltaTime;
        //unsigned int dataOffset = 296;
        while(subsegmentID < subsegmentNum) { //dla wszystkich podsegmentow
            unsigned long int baseTMP = baseMediaDecodeTime;
            unsigned long int sequenceTMP = sequenceNumber;
            unsigned int subsegmentLen = maxSampleNum; //normalnie wynosi maxSampleNum
            if(subsegmentID + 1 == subsegmentNum) //ale dla ostatniego podsegmentu to jest tylko reszta z dzielenia
                subsegmentLen = samplesInSegmentNum % maxSampleNum;
            referenceType.append(0);
            //przygotowanie parametrow moof
            referenceSize.append(writeMoof(++sequenceTMP, referenceID, baseTMP, 2, flag3, subsegmentLen, 0, baseTMP , stsz)
                                 +
                                 mdatSize(baseTMP, subsegmentLen, stsz));

            //
            subsegmentDuration.append(subsegmentLen);
            startsWithSAP.append(subsegmentID == 0);
            SAPType.append(subsegmentID == 0);
            SAPDeltaTime.append(0);
            baseTMP += subsegmentLen;
            ++ subsegmentID;
        }
        writeSidx(version, referenceID, timescale, earliestPresentationTime, firstOffset, referenceCount, referenceType,
                  referenceSize, subsegmentDuration, startsWithSAP, SAPType, SAPDeltaTime, dashFile);
        subsegmentID = 0;
        while(subsegmentID < subsegmentNum) { //dla wszystkich podsegmentow
            unsigned int subsegmentLen = maxSampleNum; //normalnie wynosi maxSampleNum
            if(subsegmentID + 1 == subsegmentNum) //ale dla ostatniego podsegmentu to jest tylko reszta z dzielenia
                subsegmentLen = samplesInSegmentNum % maxSampleNum;

            //write moof
            writeMoof(++sequenceNumber, referenceID, baseMediaDecodeTime, 2, flag3, subsegmentLen, 0, baseMediaDecodeTime, stsz, dashFile);
            //write mdat
            writeMdat(baseMediaDecodeTime, subsegmentLen, stsz, dashFile);
            baseMediaDecodeTime += subsegmentLen;
            ++ subsegmentID;
            if(flag3 == 1)
                flag3 = 5;
            else if(flag3 == 5)
                flag3 = 1;
        }
        ++ segmentID;
    }
    dashFile->close();
    return true;
}
