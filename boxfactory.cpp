#include "boxfactory.h"


BoxFactory::BoxFactory(Analyzer *an): analyzer(an)
{}

std::shared_ptr<Box> BoxFactory::getBox(const unsigned int& size, QString type, unsigned long int off, const unsigned int&  e) {
    if(type.at(0)==QChar('m'))
        return this->getMBox(size, type, off, e);
    else if(type.at(0)==QChar('t'))
        return this->getTBox(size, type, off, e);
    else if(type.at(0)==QChar('s'))
        return this->getSBox(size, type, off, e);
    else if(type.at(0) == QChar('h'))
        return this->getHBox(size, type, off, e);
    else if(type == "ftyp") {
        QString majorBrand = analyzer->qstringValue(4, off + 8);
        //QString minorVersion = analyzer->qstringValue(4, off + 12);
        unsigned int minorVersion = analyzer->valueOfGroupOfBytes(4, off + 12);

        QList<QString> compatibleBrands;
        unsigned int index = 16;
        while(index <= (size-4)) {
            QString brand =  analyzer->qstringValue(4, off + index);
            compatibleBrands.append(brand);
            index+=4;
        }

        return std::shared_ptr<Box>(new FileTypeBox(size, type, off, e, majorBrand, minorVersion, compatibleBrands));
    }
    else if(type == "vmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + 9 + i));
        }
        unsigned int graphicsMode = analyzer ->valueOfGroupOfBytes(2, off + offset + 13);
        QList <unsigned int> opcolor;
        for (int i = 0; i<3; ++i) {
            opcolor.append(analyzer->valueOfGroupOfBytes(2, off + offset + 15 + i*2));
        }
        std::shared_ptr<Box> ret(new VideoMediaHeaderBox(size, type, off, e, v, f, graphicsMode, opcolor));
        return ret;
    }
    else if(type == "nmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new NullMediaHeaderBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "dinf"){
        std::shared_ptr<Box> ret(new DataInformationBox(size, type, off, e));
        return ret;
    }
    else if(type == "avc1"){
        QList <unsigned int> reserved;
        for(int i = 0; i<6; ++i) {
            reserved.append(analyzer->valueOfGroupOfBytes(1, off + 8 + i));
        }
        unsigned int dataReferenceIndex = analyzer->valueOfGroupOfBytes(2, off + 14);
        unsigned int predefined = analyzer->valueOfGroupOfBytes(2, off + 16);
        unsigned int reserved1 = analyzer->valueOfGroupOfBytes(2, off + 18);
        QList <unsigned int> predefined1;
        for(int i = 0; i<3; ++i) {
            predefined1.append(analyzer->valueOfGroupOfBytes(4, off + 20 + i*4));
        }
        unsigned int width = analyzer->valueOfGroupOfBytes(2, off + 32);
        unsigned int height = analyzer->valueOfGroupOfBytes(2, off + 34);
        unsigned int horizonresolution = analyzer ->valueOfGroupOfBytes(4, off + 36)/65536;
        unsigned int vertresolution = analyzer->valueOfGroupOfBytes(4, off + 40)/65536;
        unsigned int reserved2 = analyzer->valueOfGroupOfBytes(4, off + 44);
        unsigned int frameCount = analyzer->valueOfGroupOfBytes(2, off + 48);
        QString compressorName = analyzer->qstringValue(4, off + 50);
        unsigned int depth = analyzer->valueOfGroupOfBytes(2, off + 82);
        int predefined2 = analyzer->valueOfGroupOfBytes(2, off + 84);
        return std::shared_ptr<Box>(new AVCSampleEntry(size, type, off, e,reserved,dataReferenceIndex, predefined, reserved1, predefined1,
                                                       width,height,horizonresolution, vertresolution, reserved2, frameCount,
                                                       compressorName, depth, predefined2));
    }
    else if(type == "avcC") {
        unsigned int configurationVersion = analyzer->valueOfGroupOfBytes(1, off + 8);
        unsigned int AVCProfileIndication = analyzer->valueOfGroupOfBytes(1, off + 9);
        unsigned int profileCompatibility = analyzer->valueOfGroupOfBytes(1, off + 10);
        unsigned int AVCLevelIndication = analyzer->valueOfGroupOfBytes(1, 11);
        unsigned int reserved1 = analyzer->valueOfGroupOfBits(6, (off + 12)*8);
        unsigned int lengthSizeMinusOne = analyzer->valueOfGroupOfBits(2, (off + 12)*8 + 6);
        unsigned int reserved2 = analyzer->valueOfGroupOfBits(3, (off + 13)*8);
        unsigned int numOfSequenceParameterSets = analyzer->valueOfGroupOfBits(5, (off + 13)*8 + 3);
        QList <unsigned int> sequenceParameterSetLength;
        QList <unsigned long int> sequenceParameterSetNALUnit;
        unsigned int offset = 0;
        for (unsigned int i = 0; i <numOfSequenceParameterSets; ++i) {
            sequenceParameterSetLength.append(analyzer->valueOfGroupOfBytes(2, off + offset + 14 ));
            sequenceParameterSetNALUnit.append(analyzer->valueOfGroupOfBytes(sequenceParameterSetLength.at(i), off + offset + 16));
            offset = offset + 2 + sequenceParameterSetLength.at(i);
        }
        unsigned int numOfPictureParameterSets = analyzer->valueOfGroupOfBytes(1, off + offset + 14);
        QList <unsigned int> pictureParameterSetLength;
        QList <unsigned long int> pictureParameterSetNALUnit;
        for (unsigned int i = 0; i <numOfPictureParameterSets; ++i) {
            pictureParameterSetLength.append(analyzer->valueOfGroupOfBytes(2, off + offset + 15 ));
            pictureParameterSetNALUnit.append(analyzer->valueOfGroupOfBytes(pictureParameterSetLength.at(i), off + offset + 17));
            offset = offset + 2 + pictureParameterSetLength.at(i);
        }
        return std::shared_ptr<Box>(new AVCConfigurationBox(size, type, off, e, configurationVersion, AVCProfileIndication,
                                                            profileCompatibility, AVCLevelIndication, reserved1, lengthSizeMinusOne,
                                                            reserved2,numOfSequenceParameterSets, sequenceParameterSetLength,
                                                            sequenceParameterSetNALUnit, numOfPictureParameterSets,
                                                            pictureParameterSetLength, pictureParameterSetNALUnit));
    }
    else if(type == "url "){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        QString location;
        if(f.at(2) == 1)
            location = QString("this file");
        else {
            location = analyzer->qstringValue(size - offset - 13, off + offset + 13); //?
        }
        std::shared_ptr<Box> ret(new DataEntryUrlBox(size, type, off, e, v, f, location));
        return ret;
    }
    else if(type == "urn "){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new DataEntryUrnBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "dref"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        std::shared_ptr<Box> ret(new DataReferenceBox(size, type, off, e, v, f, entryCount));
        return ret;
    }
    else if(type == "ctts"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);

        QList<unsigned int> sampleCount;
        QList<unsigned int> sampleDelta;
        unsigned int index =0;
        unsigned int i = 0;
        while(index<entryCount) {
            sampleCount.append(analyzer->valueOfGroupOfBytes(4, off + offset + i + 16));
            sampleDelta.append(analyzer->valueOfGroupOfBytes(4, off + offset + i + 23));
            index++;
            i+=8;
        }
        std::shared_ptr<Box> ret(new TimeToSampleBox(size, type, off, e, v, f, entryCount, sampleCount, sampleDelta));
        return ret;
    }
    else if(type == "co64"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned long int> chunkOffset;
        for(unsigned int i = 0; i<entryCount; ++i) {
            chunkOffset.append(analyzer->valueOfGroupOfBytes(4, off + offset + 16 + 4*i));
        }
        std::shared_ptr<Box> ret(new ChunkLargeOffsetBox(size, type, off, e, v, f, entryCount, chunkOffset));
        return ret;
    }
    else if(type == "btrt") {
        unsigned long int bufferSizeDB = analyzer->valueOfGroupOfBytes(4, off + 8);
        unsigned long int maxBitrate = analyzer->valueOfGroupOfBytes(4, off + 12);
        unsigned long int avgBitrate = analyzer->valueOfGroupOfBytes(4, off + 16);

        return std::shared_ptr<Box> (new MPEG4BitRateBox(size, type, off, e, bufferSizeDB, maxBitrate, avgBitrate));
    }
    else if(type == "padb"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new PaddingBitsBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "free"){
        std::shared_ptr<Box> ret(new FreeSpaceBox(false,size, type, off, e));
        return ret;
    }
    else if(type == "edts"){
        std::shared_ptr<Box> ret(new EditBox(size, type, off, e));
        return ret;
    }
    else if(type == "elst"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        QList<unsigned long int> segmentDuration;
        QList<unsigned long int> mediaTime;
        QList<unsigned int> mediaRateInteger;
        QList<unsigned int> mediaRateFraction;
        unsigned int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        for(unsigned int i = 0; i<entryCount; ++i) {
            if(v==1) {
                segmentDuration.append(analyzer->valueOfGroupOfBytes(8, off + offset + 16));
                mediaTime.append(analyzer->valueOfGroupOfBytes(8, off + offset + 24));
                offset += 8;
            }
            else if(v == 0) {
                segmentDuration.append(analyzer->valueOfGroupOfBytes(4, off + offset + 16));
                mediaTime.append(analyzer->valueOfGroupOfBytes(4, off + offset + 20));
            }
            else {
                qDebug()<<type<<QString::number(v);
            }
            mediaRateInteger.append(analyzer->valueOfGroupOfBytes(2, off + offset + 24));
            mediaRateFraction.append(analyzer->valueOfGroupOfBytes(2, off + offset + 27));
        }
        std::shared_ptr<Box> ret(new EditListBox(size, type, off, e, v, f, entryCount, segmentDuration, mediaTime, mediaRateInteger,
                                                 mediaRateFraction));
        return ret;
    }
    else if(type == "udta"){
        std::shared_ptr<Box> ret(new UserDataBox(size, type, off, e));
        return ret;
    }
    else if(type == "cprt"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new CopyRightBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "pdin"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new ProgressiveDownloadInfoBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "xml "){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new XMLBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "bxml"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new BinaryXMLBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "iloc"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new ItemLocationBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "pitm"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new PrimaryItemBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "ipro"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new ItemProtectionBox(size, type, off, e, v, f));
        return ret;

    }
    else if(type == "infe"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new ItemInfoEntry(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "iinf"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new ItemInfoBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "frma"){
        std::shared_ptr<Box> ret(new OriginalFormatBox(size, type, off, e));
        return ret;
    }
    else if(type == "imif"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new IPMPInfoBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "ipmc"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new IPMPControlBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "rtp "){
        std::shared_ptr<Box> ret(new RTPMovieHintInformation(size, type, off, e));
        return ret;
    }
    else if(type == "iods"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        return std::shared_ptr<Box>(new ObjectDescriptorBox(size, type, off, e, v, f));
    }
    else if(type == "esds"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        return std::shared_ptr<Box>(new ESDBox(size, type, off, e, v, f));
    }
    /*else if(type == "avc1"){
        return std::shared_ptr<Box>(new VisualSampleEntry(size, type, off, e,0,0,0,0,analyzer->valueOfGroupOfFields(2, off + 33),analyzer->valueOfGroupOfFields(34,35)));

    }*/
    else if(type == "leva"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        return std::shared_ptr<Box>(new LevelAssignmentBox(size, type, off, e, v, f));
    }
    else if(type == "prft"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        return std::shared_ptr<Box>(new ProducerReferenceTimeBox(size, type, off, e, v, f));
    }
    else{
        return std::shared_ptr<Box>(new Box(size, type, off, e));
        throw NoSuchABoxException();
    }

    return NULL;
}
//////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getMBox(const unsigned int& size, QString type, unsigned long int off, const unsigned int&  e) {
    if(type== "moov"){
        return std::shared_ptr<Box>(new MovieBox(size, type, off, e));
    }
    else if(type == "mdat"){
        return std::shared_ptr<Box>(new MediaDataBox(size, type, off, e));
    }
    else if(type == "mvhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int version = analyzer->valueOfGroupOfBytes(1, off + offset + 9);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int creationTime;
        unsigned long int modificationTime;
        unsigned long int timescale;
        unsigned long int duration;
        if(version == 1) {
            creationTime = analyzer->valueOfGroupOfBytes(8, off + offset + 12);
            modificationTime = analyzer->valueOfGroupOfBytes(8, off + offset + 20);
            timescale = analyzer->valueOfGroupOfBytes(8, off + offset + 28);
            duration = analyzer->valueOfGroupOfBytes(8, off + offset + 36);
            offset+=12;
        }
        else if(version == 0) {
            creationTime = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
            modificationTime = analyzer->valueOfGroupOfBytes(4, off + offset + 16);
            timescale = analyzer->valueOfGroupOfBytes(4, off+ offset + 20);
            duration = analyzer->valueOfGroupOfBytes(4, off + offset + 24);
        }
        QList<unsigned long int> reserved32;
        QList<unsigned long int> matrix;
        QList<unsigned long int> predefined;
        unsigned long int nextTrackId;
        unsigned int rate = analyzer->valueOfGroupOfBytes(4, off + offset + 28)/65536;//fixed number
        unsigned int volume = analyzer->valueOfGroupOfBytes(2, off + offset + 32)/256;
        unsigned int reserved16 = analyzer->valueOfGroupOfBytes(2, off + offset + 34);
        reserved32.append(analyzer->valueOfGroupOfBytes(4, off + offset + 36));
        reserved32.append(analyzer->valueOfGroupOfBytes(4, off + offset + 40));
        for(int i = 0; i<9; ++i) {
            matrix.append(analyzer->valueOfGroupOfBytes(4, off + offset + 44 + 4*i));
        }
        for(int i = 0; i<6; ++i) {
            predefined.append(analyzer->valueOfGroupOfBytes(4, off + offset + 80 +4*i));
        }
        nextTrackId = analyzer->valueOfGroupOfBytes(4, off + offset + 104);

        std::shared_ptr<Box> ret(new MovieHeaderBox(size, type, off, e, version, f, creationTime, modificationTime, timescale, duration,
                                                    rate, volume, reserved16, reserved32, matrix, predefined, nextTrackId));
        return ret;
    }
    else if(type == "mdhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int creationTime;
        unsigned long int modificationTime;
        unsigned int timescale;
        unsigned long int duration;
        if(v == 1) {
            creationTime = analyzer->valueOfGroupOfBytes(8, off + offset + 12);
            modificationTime = analyzer->valueOfGroupOfBytes(8, off+ offset + 20);
            timescale = analyzer->valueOfGroupOfBytes(8, off + offset + 28);
            duration = analyzer->valueOfGroupOfBytes(8, off + offset + 43);
            offset += 12;
        }
        else if (v == 0) {
            creationTime = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
            modificationTime = analyzer->valueOfGroupOfBytes(4, off + offset + 16);
            timescale = analyzer->valueOfGroupOfBytes(4, off + offset + 20);
            duration = analyzer->valueOfGroupOfBytes(4 , off + offset + 24 );
        }

        unsigned long int byteValue = analyzer->valueOfGroupOfBytes(4, off + offset + 28);
        QString tmpValue = QString::number(byteValue,2);
        int tmpSize = tmpValue.size();
        if(tmpSize < 32) {
            int delta = 32 - tmpSize;
            for (int i = 0; i<delta; ++i) {
                tmpValue = tmpValue.insert(0, "0");
            }
        }
        QString qstringPad = tmpValue.mid(0,1);
        bool pad = (qstringPad.toUInt(0,2) == 0);
        QList<unsigned int> language;
        for(int i = 0; i<3; ++i) {
            QString qstringLan = tmpValue.mid(1+i*5,5);
            language.append(qstringLan.toUInt(0,2));
        }
        QString qstringPred = tmpValue.mid(16, 16);
        unsigned int predefined = qstringPred.toUInt(0,2);
        //        QString qstringStarsWithSAP = tmpValue.mid(0,1);
        //        startsWithSAP.append(qstringStarsWithSAP.toUInt(0,2));
        //        QString qstringSAPType = tmpValue.mid(1,3);
        //        SAPType.append(qstringSAPType.toUInt(0,2));
        //        QString qstringSAPDeltaTime = tmpValue.mid(4,28);
        //        SAPDeltaTime.append(qstringSAPDeltaTime.toUInt(0,2))

        std::shared_ptr<Box> ret(new MediaHeaderBox(size, type, off, e, v, f, creationTime, modificationTime, timescale, duration,
                                                    pad, language, predefined));
        return ret;
    }
    else if(type == "mdia"){
        std::shared_ptr<Box> ret(new MediaBox(size, type, off, e));
        return ret;
    }
    else if(type == "moof"){
        std::shared_ptr<Box> ret(new MovieFragmentBox(size, type, off, e));
        return ret;
    }
    else if(type == "mfhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int sn = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        std::shared_ptr<Box> ret(new MovieFragmentHeaderBox(size, type, off, e, sn, v, f));
        return ret;
    }
    else if(type == "mp4v" /*|| type == "avc1"*/){
        QList <unsigned int> reserved;
        for(int i = 0; i<6; ++i) {
            reserved.append(analyzer->valueOfGroupOfBytes(1, off + 8 + i ));
        }

        unsigned int dataReferenceIndex = analyzer->valueOfGroupOfBytes(2, off + 14);
        unsigned int predefined = analyzer->valueOfGroupOfBytes(2, off + 16);
        unsigned int reserved1 = analyzer->valueOfGroupOfBytes(2, off + 18);
        QList <unsigned int> predefined1;
        for(int i = 0; i<3; ++i) {
            predefined1.append(analyzer->valueOfGroupOfBytes(4, off + 20 + i*4));
        }
        unsigned int width = analyzer->valueOfGroupOfBytes(2, off + 32);
        unsigned int height = analyzer->valueOfGroupOfBytes(2, off + 34);
        unsigned int horizonresolution = analyzer ->valueOfGroupOfBytes(4, off + 36)/65536;
        unsigned int vertresolution = analyzer->valueOfGroupOfBytes(4, off + 40)/65536;
        unsigned int reserved2 = analyzer->valueOfGroupOfBytes(4, off + 44);
        unsigned int frameCount = analyzer->valueOfGroupOfBytes(2, off + 48);
        QString compressorName = analyzer->qstringValue(4, off + 50);
        unsigned int depth = analyzer->valueOfGroupOfBytes(2, off + 82);
        int predefined2 = analyzer->valueOfGroupOfBytes(2, off + 84);
        return std::shared_ptr<Box>(new MP4VisualSampleEntry(size, type, off, e,reserved,dataReferenceIndex, predefined, reserved1,
                                                             predefined1, width, height, horizonresolution, vertresolution, reserved2,
                                                             frameCount, compressorName, depth, predefined2));
    }
    else if(type == "mp4a"){
        //SampleEntry
        QList <unsigned int> reserved;
        for(int i = 0; i<6; ++i) {
            reserved.append(analyzer->valueOfGroupOfBytes(1, off + 9 + i ));
        }
        unsigned int dataReferenceIndex = analyzer->valueOfGroupOfBytes(2, off +14);
        //AudioSampleEntry
        QList <unsigned int> reserved1;
        reserved1.append(analyzer->valueOfGroupOfBytes(4, off + 16));
        reserved1.append(analyzer->valueOfGroupOfBytes(4, off + 20));
        unsigned int channelCount = analyzer->valueOfGroupOfBytes(2, off + 24);
        unsigned int sampleSize = analyzer->valueOfGroupOfBytes(2, off + 26);
        unsigned int predefined = analyzer->valueOfGroupOfBytes(2, off + 28);
        unsigned int reserved2 = analyzer->valueOfGroupOfBytes(2, off + 30);
        unsigned int sampleRate = analyzer->valueOfGroupOfBytes(2, off + 32);
        return std::shared_ptr<Box>(new MP4AudioSampleEntry(size, type, off, e,reserved,dataReferenceIndex, reserved1, channelCount,
                                                            sampleSize, predefined, reserved2, sampleRate));
    }
    else if(type == "mp4s"){
        QList <unsigned int> reserved;
        for(int i = 0; i<6; ++i) {
            reserved.append(analyzer->valueOfGroupOfBytes(1, off + 8 + i ));
        }
        unsigned int dataReferenceIndex = analyzer->valueOfGroupOfBytes(2, off +14);
        return std::shared_ptr<Box>(new MpegSampleEntry(size, type, off, e,reserved,dataReferenceIndex));
    }
    else if(type == "mvex"){
        std::shared_ptr<Box> ret(new MovieExtendsBox(size, type, off, e));
        return ret;
    }
    else if(type == "mehd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int fd;
        if(v)
            fd = analyzer->valueOfGroupOfBytes(8, off + offset + 12);
        else
            fd = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        std::shared_ptr<Box> ret(new MovieExtendsHeaderBox(size, type, off, e, v, f, fd));
        return ret;
    }
    else if(type == "minf"){
        std::shared_ptr<Box> ret(new MediaInformationBox(size, type, off, e));
        return ret;
    }
    else if(type == "mfra"){
        std::shared_ptr<Box> ret(new MovieFragmentRandomAccessBox(size, type, off, e));
        return ret;
    }
    else if(type == "meta"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new MetaBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "mfro"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new MovieFragmentRandomAccessOffsetBox(size, type, off, e, v, f));
        return ret;
    }
    return std::shared_ptr<Box>(new Box(size, type, off, e));
}
////////////////////////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getTBox(const unsigned int& size, QString type, unsigned long int off, const unsigned int&  e) {
    if(type == "trak"){
        std::shared_ptr<Box> ret(new TrackBox(size, type, off, e));
        return ret;
    }
    else if(type == "tkhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int creationTime = 0;
        unsigned long int modificationTime = 0;
        unsigned int trackID = 0;
        unsigned int reserved1;
        unsigned long int duration;
        if(v == 1) {
            creationTime = analyzer->valueOfGroupOfBytes(8, off + offset + 12);
            modificationTime = analyzer->valueOfGroupOfBytes(8, off+ offset + 20);
            trackID = analyzer->valueOfGroupOfBytes(4, off + offset + 28);
            reserved1 = analyzer->valueOfGroupOfBytes(4, off + offset + 32);
            duration = analyzer->valueOfGroupOfBytes(8, off + offset + 43);
            offset += 12;
        }
        else if(v == 0) {
            creationTime = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
            modificationTime = analyzer->valueOfGroupOfBytes(4, off + offset + 16);
            trackID = analyzer->valueOfGroupOfBytes(4, off + offset + 20);
            reserved1 = analyzer->valueOfGroupOfBytes(4 , off + offset + 24 );
            duration = analyzer->valueOfGroupOfBytes(4, off + offset + 28);
        }
        QList<unsigned int> reserved2;
        reserved2.append(analyzer->valueOfGroupOfBytes(4, off + offset + 32));
        reserved2.append(analyzer->valueOfGroupOfBytes(4, off + offset + 36));
        unsigned int layer = analyzer->valueOfGroupOfBytes(2, off + offset + 40);
        unsigned int alternateGroup = analyzer->valueOfGroupOfBytes(1,  off + offset + 42);
        unsigned int volume = analyzer->valueOfGroupOfBytes(2, off + offset + 44)/256;
        unsigned int reserved3 = analyzer->valueOfGroupOfBytes(2, off + offset + 46);
        QList<unsigned long int> matrix;
        for(int i = 0; i<9; i++) {
            matrix.append(analyzer->valueOfGroupOfBytes(4 , off + offset + 48 ));
            offset += 4;
        }
        offset -= 4;
        unsigned int width = analyzer->valueOfGroupOfBytes(4 , off + offset + 50 );
        unsigned int height = analyzer->valueOfGroupOfBytes(4 , off + offset + 54 );
        std::shared_ptr<Box> ret(new TrackHeaderBox(size, type, off, e, v, f, creationTime, modificationTime, trackID, reserved1, duration,
                                                    reserved2, layer, alternateGroup, volume, reserved3, matrix, width, height));
        return ret;
    }
    else if(type == "tref"){
        std::shared_ptr<Box> ret(new TrackReferenceBox(size, type, off, e));
        return ret;
    }
    else if(type == "trex"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int tid = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        unsigned int dsdi = analyzer->valueOfGroupOfBytes(4, off + offset + 16);
        unsigned int dsd = analyzer->valueOfGroupOfBytes(4, off + offset + 20);
        unsigned int dss = analyzer->valueOfGroupOfBytes(4 , off + offset + 24 );
        unsigned int dsf = analyzer->valueOfGroupOfBytes(4, off + offset + 28);

        std::shared_ptr<Box> ret(new TrackExtendsBox(size, type, off, e, v, f, tid, dsdi, dsd, dss, dsf));
        return ret;
    }
    else if(type == "traf"){
        std::shared_ptr<Box> ret(new TrackFragmentBox(size, type, off, e));
        return ret;
    }
    else if(type == "tfhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int tid = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        unsigned long int bdo = 0;
        unsigned long int sdi = 0;
        unsigned long int dsd = 0;
        unsigned long int dss = 0;
        unsigned long int dsf = 0;
        if(size >= 24) {
            bdo = analyzer->valueOfGroupOfBytes(8, off + offset + 16);
            if(size >= 28) {
                sdi = analyzer->valueOfGroupOfBytes(4 , off + offset + 24 );
                if(size >= 32) {
                    dsd = analyzer->valueOfGroupOfBytes(4, off + offset + 28);
                    if(size >= 36) {
                        dss = analyzer->valueOfGroupOfBytes(4, off + offset + 32);
                        if(size >=40)
                            dsf = analyzer->valueOfGroupOfBytes(4, off + offset + 36);
                    }
                }
            }
        }
        std::shared_ptr<Box> ret(new TrackFragmentHeaderBox(size, type, off, e, v, f, tid, bdo, sdi, dsd, dss, dsf));
        return ret;
    }
    else if(type == "trun"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int sampleCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        long int dataOffset = 0;
        if(f.at(2) == 1 || f.at(2) == 5) {
            dataOffset = analyzer->signedValueOfGroupOfBytes(4, off + offset + 16);
            offset += 4;
        }
        unsigned int firstSampleFlags = 0;
        if(f.at(2) == 4 || f.at(2) == 5) {
            firstSampleFlags = analyzer->valueOfGroupOfBytes(4, off + offset + 16);
            offset += 4;
        }
        QList<unsigned long int> sampleDuration;
        QList<unsigned long int> sampleSize;
        QList<unsigned int> sampleFlags;
        QList<unsigned long int> sampleCompositionTimeOffset;
        //?
        if(f.at(1) == 2) {
            for (unsigned int i = 0; i<sampleCount; ++i) {
                sampleSize.append(analyzer->valueOfGroupOfBytes(4, off + offset + 16 + 4*i));
            }
        }
        std::shared_ptr<Box> ret(new TrackRunBox(size, type, off, e, v, f,sampleCount,dataOffset,firstSampleFlags,sampleDuration,
                                                 sampleSize,sampleFlags,sampleCompositionTimeOffset));
        return ret;
    }
    else if(type == "tfra"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }

        std::shared_ptr<Box> ret(new TrackFragmentRandomAccessBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "tims"){
        std::shared_ptr<Box> ret(new TimeScaleEntry(size, type, off, e));
        return ret;
    }
    else if(type == "tsro"){
        std::shared_ptr<Box> ret(new TimeOffset(size, type, off, e));
        return ret;
    }
    else if(type == "tfdt"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int baseMediaDecodeTime;
        if(v == 1)
            baseMediaDecodeTime = analyzer->valueOfGroupOfBytes(8, off + offset + 12);
        else if(v == 0)
            baseMediaDecodeTime = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        return std::shared_ptr<Box>(new TrackFragmentBaseMediaDecodeTimeBox(size, type, off, e, v, f, baseMediaDecodeTime));
    }
    return std::shared_ptr<Box>(new Box(size, type, off, e));
}
////////////////////////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getSBox(const unsigned int& size, QString type, unsigned long int off, const unsigned int&  e) {
    if(type == "smhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int balance = analyzer->valueOfGroupOfBytes(2, off + offset + 12);
        unsigned int reserved = analyzer->valueOfGroupOfBytes(2, off + offset + 14);
        std::shared_ptr<Box> ret(new SoundMediaHeaderBox(size, type, off, e, v, f, balance, reserved));
        return ret;
    }
    else if(type == "stbl"){
        std::shared_ptr<Box> ret(new SampleTableBox(size, type, off, e));
        return ret;
    }
    else if(type == "stts"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);

        QList<unsigned int> sampleCount;
        QList<unsigned int> sampleDelta;
        unsigned int index =0;
        unsigned int i = 0;
        while(index<entryCount) {
            sampleCount.append(analyzer->valueOfGroupOfBytes(4, off + offset+ i + 16));
            sampleDelta.append(analyzer->valueOfGroupOfBytes(4, off + offset + i + 20));
            index++;
            i+=8;
        }
        std::shared_ptr<Box> ret(new TimeToSampleBox(size, type, off, e, v, f, entryCount, sampleCount, sampleDelta));
        return ret;
    }
    else if(type == "stsd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        std::shared_ptr<Box> ret(new SampleDescriptionBox(size, type, off, e,v,f,entryCount));
        return ret;
    }
    else if(type == "stsz"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int sampleSize = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        unsigned long int sampleCount = analyzer->valueOfGroupOfBytes(4, off + offset + 16);
        QList<unsigned long int> entrySize;
        if(sampleSize == 0) {
            for(unsigned int i = 0; i<sampleCount; ++i) {
                entrySize.append(analyzer->valueOfGroupOfBytes(4 , off + offset + 20 + 4*i ));
            }
        }
        std::shared_ptr<Box> ret(new SampleSizeBox(size, type, off, e, v, f, sampleSize, sampleCount, entrySize));
        return ret;
    }
    else if(type == "stz2"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new CompactSampleSizeBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "stsc"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned long int> firstChunk;
        QList<unsigned long int> samplesPerChunk;
        QList<unsigned long int> sampleDescriptionIndex;
        for(unsigned int i = 0; i<entryCount; ++i) {
            firstChunk.append(analyzer->valueOfGroupOfBytes(4 , off + offset + 16 + 12*i ));
            samplesPerChunk.append(analyzer->valueOfGroupOfBytes(4, off + offset + 20 + 12*i ));
            sampleDescriptionIndex.append(analyzer->valueOfGroupOfBytes(4, off + offset + 24 + 12*i ));
        }
        std::shared_ptr<Box> ret(new SampleToChunkBox(size, type, off, e, v, f, entryCount, firstChunk, samplesPerChunk,
                                                      sampleDescriptionIndex));
        return ret;
    }
    else if(type == "stco"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned long int> chunkOffset;
        for(unsigned int i = 0; i<entryCount; ++i) {
            chunkOffset.append(analyzer->valueOfGroupOfBytes(4, off + offset + 16 + 4*i));
        }
        std::shared_ptr<Box> ret(new ChunkOffsetBox(size, type, off, e, v, f, entryCount, chunkOffset));
        return ret;
    }
    else if(type == "stss"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned long int entryCount = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned long int> sampleNumber;
        for (unsigned int i = 0; i<entryCount; ++i) {
            sampleNumber.append(analyzer->valueOfGroupOfBytes(4, off + offset + 16 + 4*i));
        }
        std::shared_ptr<Box> ret(new SyncSampleBox(size, type, off, e, v, f, entryCount,sampleNumber));
        return ret;
    }
    else if(type == "styp") {
        QString majorBrand = analyzer->qstringValue(4, off + 8);
        unsigned int minorVersion = analyzer->valueOfGroupOfBytes(4, off + 12);
        //QString minorVersion = analyzer->qstringValue(4, off + 12);

        QList<QString> compatibleBrands;
        unsigned int index = 16;
        while(index <= (size-4)) {
            QString brand =  analyzer->qstringValue(4, off + index);
            compatibleBrands.append(brand);
            index+=4;
        }

        return std::shared_ptr<Box>(new SegmentTypeBox(size, type, off, e, majorBrand, minorVersion, compatibleBrands));
    }
    else if(type == "stsh"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new ShadowSyncSampleBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "stdp"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new DegradationPriorityBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "skip"){
        std::shared_ptr<Box> ret(new FreeSpaceBox(true,size, type, off, e));
        return ret;
    }
    else if(type == "sdtp"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new SampleDependencyTypeBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "sbgp"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new SampleToGroupBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "sgpd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new SampleGroupDescriptionBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "stsl"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new SampleScaleBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "sidx"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int version = analyzer->valueOfGroupOfBytes(1, off + offset + 9);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int referenceId = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        unsigned int timescale = analyzer->valueOfGroupOfBytes(4, off + offset + 16);

        unsigned int earliestPresentationTime = 0;
        unsigned int firstOffset = 0;
        if (version == 0){
            earliestPresentationTime = analyzer->valueOfGroupOfBytes(4, off + offset + 20);
            firstOffset = analyzer->valueOfGroupOfBytes(4 , off + offset + 24 );
        }
        else if (version == 1) {
            earliestPresentationTime = analyzer->valueOfGroupOfBytes(8, off + offset + 20);
            firstOffset = analyzer->valueOfGroupOfBytes(8, off + offset + 28);
            offset += 8;
        }
        unsigned int reserved = analyzer->valueOfGroupOfBytes(2, off + offset + 28);
        unsigned int referenceCount = analyzer->valueOfGroupOfBytes(2, off + offset + 30);
        QList<bool> referenceType;
        QList<unsigned int> referenceSize;
        QList<unsigned int> subsegmentDuration;
        QList<bool> startsWithSAP;
        QList <unsigned int> SAPType;
        QList <unsigned int> SAPDeltaTime;
        for(unsigned int i = 0; i<referenceCount; i++) {
            //referenceType.append(analyzer->bitValue(offset +32,0));
            referenceType.append(analyzer->valueOfGroupOfBits(1, (off + offset + 32)*8));
            //int referenceSizeBitOffset = (offset + 31) * 8;
            //referenceSize.append(analyzer->valueOfBits(referenceSizeBitOffset+249, referenceSizeBitOffset+279));
            //            if (referenceType.at(i)) {
            //                referenceSize.append(analyzer->valueOfGroupOfBytes(4, off + offset + 32) - pow(2.0,31) );
            //            }
            //            else
            //                referenceSize.append(analyzer->valueOfGroupOfBytes(4, off + offset + 32));
            referenceSize.append(analyzer->valueOfGroupOfBits(31, (off + offset + 32)*8 + 1));
            subsegmentDuration.append(analyzer->valueOfGroupOfBytes(4, off + offset + 36));
            startsWithSAP.append(analyzer->valueOfGroupOfBits(1, (off + offset + 40)*8));
            SAPType.append(analyzer->valueOfGroupOfBits(3, (off + offset + 40)*8 + 1));
            SAPDeltaTime.append(analyzer->valueOfGroupOfBits(28, (off + offset + 40)*8 + 4));
            //unsigned long int byteValue = analyzer->valueOfGroupOfBytes(4, off + offset + 40);
            //            QString tmpValue = QString::number(byteValue,2);
            //            int tmpSize = tmpValue.size();
            //            if(tmpSize < 32) {
            //                int delta = 32 - tmpSize;
            //                for (int i = 0; i<delta; ++i) {
            //                    tmpValue = tmpValue.insert(0, "0");
            //                }
            //            }
            //            QString qstringStarsWithSAP = tmpValue.mid(0,1);
            //            startsWithSAP.append(qstringStarsWithSAP.toUInt(0,2));
            //            QString qstringSAPType = tmpValue.mid(1,3);
            //            SAPType.append(qstringSAPType.toUInt(0,2));
            //            QString qstringSAPDeltaTime = tmpValue.mid(4,28);
            //            SAPDeltaTime.append(qstringSAPDeltaTime.toUInt(0,2));

            //            startsWithSAP.append(analyzer->bitValue(offset+40,0));
            //            int SAPTypeBitOffset = (offset + 39) * 8;
            //            SAPType.append(analyzer->valueOfBits(SAPTypeBitOffset+312,SAPTypeBitOffset+314));
            //            SAPDeltaTime.append(analyzer->valueOfBits(SAPTypeBitOffset+315,SAPTypeBitOffset+342));
            offset += 12;
        }
        return std::shared_ptr<Box>(new SegmentIndexBox(size, type, off, e, version, f, referenceId, timescale, earliestPresentationTime,
                                                        firstOffset, reserved, referenceType, referenceSize, subsegmentDuration,
                                                        startsWithSAP, SAPType, SAPDeltaTime));
    }
    else if(type == "ssix"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int version = analyzer->valueOfGroupOfBytes(1, off + offset + 9);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        return std::shared_ptr<Box>(new SubsegmentIndexBox(size, type, off, e, version, f));
    }
    else if(type == "subs"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new SubSampleInformationBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "sinf"){
        std::shared_ptr<Box> ret(new ProtectionSchemeInfoBox(size, type, off, e));
        return ret;
    }
    else if(type == "schm"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new SchemeTypeBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "schi"){
        std::shared_ptr<Box> ret(new SchemeInformationBox(size, type, off, e));
        return ret;
    }
    else if(type == "snro"){
        std::shared_ptr<Box> ret(new SequenceOffset(size, type, off, e));
        return ret;
    }
    else if(type == "srpp"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new SRTPProcessBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "sdp "){
        std::shared_ptr<Box> ret(new RTPTrackSDPHintInformation(size, type, off, e));
        return ret;
    }
    else if(type == "saiz"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        return std::shared_ptr<Box>(new SampleAuxiliaryInformationSizesBox(size, type, off, e, v, f));
    }
    else if(type == "saio"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        return std::shared_ptr<Box>(new SampleAuxiliaryInformationOffsetsBox(size, type, off, e, v, f));
    }
    return std::shared_ptr<Box>(new Box(size, type, off, e));
}
////////////////////////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getHBox(const unsigned int& size, QString type, unsigned long int off, const unsigned int&  e) {
    if(type == "hdlr"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        unsigned int predefined = analyzer->valueOfGroupOfBytes(4, off + offset + 12);
        unsigned long int handlerType = analyzer->valueOfGroupOfBytes(4, off + offset + 16);
        QList <unsigned int> reserved;
        for(int i = 0; i<3; ++i) {
            reserved.append(analyzer->valueOfGroupOfBytes(4 , off + offset + 20 + 4*i ));
        }
        QString name = analyzer->qstringValue(size - offset - 32, off + offset + 32);
        /*int nameLength = size - offset - 32;
        int i = 0;
        while(i < nameLength) {
            unsigned long int intName;
            if((nameLength-i)>=4) {
                intName = analyzer->valueOfGroupOfBytes(4, off + offset + 32 + i);
                name.append(analyzer->toQString(intName, 4));
            }
            else {
                int newLen = nameLength - i;
                intName = analyzer->valueOfGroupOfBytes(newLen + i, offset + 32 + newLen + i);
                name.append(analyzer->toQString(intName, newLen));
            }
            i+=4;
        }*/
        std::shared_ptr<Box> ret(new HandlerBox(size, type, off, e, v, f, predefined, handlerType, reserved, name));
        return ret;
    }
    else if(type == "hmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset+=8;
        if(type == QString("uuid"))
            offset+=16;
        unsigned int v = analyzer->valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i<3; ++i) {
            f.append(analyzer->valueOfGroupOfBytes(1, off + offset + i + 9));
        }
        std::shared_ptr<Box> ret(new HintMediaHeaderBox(size, type, off, e, v, f));
        return ret;
    }
    else if(type == "hnti"){
        std::shared_ptr<Box> ret(new MovieHintInformation(size, type, off, e));
        return ret;
    }
    else if(type == "hinf"){
        std::shared_ptr<Box> ret(new HintStatisticsBox(size, type, off, e));
        return ret;
    }
    return std::shared_ptr<Box>(new Box(size, type, off, e));
}
