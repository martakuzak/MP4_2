#include "boxfactory.h"


BoxFactory::BoxFactory(FileService *fs) : fileService(fs) {
    bitOperator = new BitOperator();
}

std::shared_ptr<Box> BoxFactory::getBox(const unsigned int& size, QString type, unsigned long int off) {
    qDebug()<<"BOXFACTORY: getBox"<<type<<size;
    if(type.at(0)==QChar('m'))
        return this->getMBox(size, type, off);
    else if(type.at(0)==QChar('t'))
        return this->getTBox(size, type, off);
    else if(type.at(0)==QChar('s'))
        return this->getSBox(size, type, off);
    else if(type.at(0) == QChar('h'))
        return this->getHBox(size, type, off);
    else if(type == "ftyp") {
        QString majorBrand = bitOperator->stringValue(fileService->getBytes(4, off + 8), 4);
        unsigned int minorVersion = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 12), 4);

        QList<QString> compatibleBrands;
        unsigned int index = 16;
        while(index <= (size - 4)) {
            QString brand =  bitOperator->stringValue(fileService->getBytes(4, off + index), 4);
            compatibleBrands.append(brand);
            index += 4;
        }

        return std::shared_ptr<Box>(new FileTypeBox(size, type, off, majorBrand, minorVersion, compatibleBrands));
    } else if(type == "vmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 9 + i), 1));
        unsigned int graphicsMode = bitOperator ->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 13), 2);
        QList <unsigned int> opcolor;
        for (int i = 0; i < 3; ++ i)
            opcolor.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 15 + i*2), 2));
        std::shared_ptr<Box> ret(new VideoMediaHeaderBox(size, type, off, v, f, graphicsMode, opcolor));
        return ret;
    } else if(type == "nmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new NullMediaHeaderBox(size, type, off, v, f));
        return ret;
    } else if(type == "dinf"){
        std::shared_ptr<Box> ret(new DataInformationBox(size, type, off));
        return ret;
    } else if(type == "avc1"){
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 8 + i), 1));
        unsigned int dataReferenceIndex = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 14), 2);
        unsigned int predefined = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 16), 2);
        unsigned int reserved1 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 18), 2);
        QList <unsigned int> predefined1;
        for(int i = 0; i < 3; ++ i)
            predefined1.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 20 + i*4), 4));
        unsigned int width = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 32), 2);
        unsigned int height = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 34), 2);
        unsigned int horizonresolution = bitOperator ->valueOfGroupOfBytes(fileService->getBytes(4, off + 36), 4)/65536;
        unsigned int vertresolution = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 40), 4)/65536;
        unsigned int reserved2 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 44), 4);
        unsigned int frameCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 48), 2);
        QString compressorName = bitOperator->stringValue(fileService->getBytes(4, off + 50), 4);
        unsigned int depth = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 82), 2);
        int predefined2 = bitOperator->signedValueOfGroupOfBytes(fileService->getBytes(2, off + 84), 2);
        return std::shared_ptr<Box>(new AVCSampleEntry(size, type, off,reserved,dataReferenceIndex, predefined, reserved1, predefined1,
                                                       width,height,horizonresolution, vertresolution, reserved2, frameCount,
                                                       compressorName, depth, predefined2));
    } else if(type == "avcC") {
        unsigned int configurationVersion = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 8), 1);
        unsigned int AVCProfileIndication = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 9), 1);
        unsigned int profileCompatibility = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 10), 1);
        unsigned int AVCLevelIndication = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 11), 1);
        unsigned int reserved1 = bitOperator->valueOfGroupOfBits(fileService->getBits(6, (off + 12)*8), 6);
        unsigned int lengthSizeMinusOne = bitOperator->valueOfGroupOfBits(fileService->getBits(2, (off + 12)*8 + 6), 2);
        unsigned int reserved2 = bitOperator->valueOfGroupOfBits(fileService->getBits(3, (off + 13)*8), 3);
        unsigned int numOfSequenceParameterSets = bitOperator->valueOfGroupOfBits(fileService->getBits(5, (off + 13)*8 + 3), 5);
        QList <unsigned int> sequenceParameterSetLength;
        QList <unsigned long int> sequenceParameterSetNALUnit;
        unsigned int offset = 0;
        for (unsigned int i = 0; i <numOfSequenceParameterSets; ++ i) {
            sequenceParameterSetLength.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 14 ), 2));
            sequenceParameterSetNALUnit.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(sequenceParameterSetLength.at(i), off + offset + 16), sequenceParameterSetLength.at(i)));
            offset = offset + 2 + sequenceParameterSetLength.at(i);
        }
        unsigned int numOfPictureParameterSets = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 14), 1);
        QList <unsigned int> pictureParameterSetLength;
        QList <unsigned long int> pictureParameterSetNALUnit;
        for (unsigned int i = 0; i <numOfPictureParameterSets; ++ i) {
            pictureParameterSetLength.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 15 ), 2));
            pictureParameterSetNALUnit.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(pictureParameterSetLength.at(i), off + offset + 17), pictureParameterSetLength.at(i)));
            offset = offset + 2 + pictureParameterSetLength.at(i);
        }
        return std::shared_ptr<Box>(new AVCConfigurationBox(size, type, off, configurationVersion, AVCProfileIndication,
                                                            profileCompatibility, AVCLevelIndication, reserved1, lengthSizeMinusOne,
                                                            reserved2,numOfSequenceParameterSets, sequenceParameterSetLength,
                                                            sequenceParameterSetNALUnit, numOfPictureParameterSets,
                                                            pictureParameterSetLength, pictureParameterSetNALUnit));
    } else if(type == "url "){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        QString location;
        if(f.at(2) == 1)
            location = QString("this file");
        else {
            location = bitOperator->stringValue(fileService->getBytes(size - offset - 13, off + offset + 13), size - offset - 13); //?
        }
        std::shared_ptr<Box> ret(new DataEntryUrlBox(size, type, off, v, f, location));
        return ret;
    } else if(type == "urn "){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new DataEntryUrnBox(size, type, off, v, f));
        return ret;
    } else if(type == "dref"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        std::shared_ptr<Box> ret(new DataReferenceBox(size, type, off, v, f, entryCount));
        return ret;
    } else if(type == "ctts"){
        //qDebug()<<"BOXFACTORY: getBox ctss off = "<<off;
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        //qDebug()<<"BOXFACTORY: getBox ctts 1";
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));

        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        //qDebug()<<"BOXFACTORY: getBox ctts 4";

        QList<unsigned int> sampleCount;
        QList<unsigned int> sampleDelta;
        unsigned int index = 0;
        unsigned int i = 0;
        while(index < entryCount) {
            sampleCount.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + i + 16), 4));
            sampleDelta.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + i + 20), 4));
            ++ index;
            i += 8;
        }

        std::shared_ptr<Box> ret(new TimeToSampleBox(size, type, off, v, f, entryCount, sampleCount, sampleDelta));
        return ret;
    } else if(type == "co64"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned long int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        QList<unsigned long int> chunkOffset;
        for(unsigned int i = 0; i<entryCount; ++ i)
            chunkOffset.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16 + 4*i), 4));
        std::shared_ptr<Box> ret(new ChunkLargeOffsetBox(size, type, off, v, f, entryCount, chunkOffset));
        return ret;
    } else if(type == "btrt") {
        unsigned int bufferSizeDB = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 8), 4);
        unsigned int maxBitrate = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 12), 4);
        unsigned int avgBitrate = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 16), 4);

        return std::shared_ptr<Box> (new MPEG4BitRateBox(size, type, off, bufferSizeDB, maxBitrate, avgBitrate));
    } else if(type == "padb"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new PaddingBitsBox(size, type, off, v, f));
        return ret;
    } else if(type == "free"){
        std::shared_ptr<Box> ret(new FreeSpaceBox(false,size, type, off));
        return ret;
    } else if(type == "edts"){
        std::shared_ptr<Box> ret(new EditBox(size, type, off));
        return ret;
    } else if(type == "elst"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        QList<unsigned long int> segmentDuration;
        QList<unsigned long int> mediaTime;
        QList<unsigned int> mediaRateInteger;
        QList<unsigned int> mediaRateFraction;
        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        for(unsigned int i = 0; i < entryCount; ++ i) {
            if(v == 1) {
                segmentDuration.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 16), 8));
                mediaTime.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 24), 8));
                offset += 8;
            } else if(v == 0) {
                unsigned long tmp = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
                segmentDuration.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4));
                mediaTime.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 20), 4));
            }
            mediaRateInteger.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 24), 2));
            mediaRateFraction.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 27), 2));
        }
        std::shared_ptr<Box> ret(new EditListBox(size, type, off, v, f, entryCount, segmentDuration, mediaTime, mediaRateInteger,
                                                 mediaRateFraction));
        return ret;
    } else if(type == "udta"){
        std::shared_ptr<Box> ret(new UserDataBox(size, type, off));
        return ret;
    } else if(type == "cprt"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new CopyRightBox(size, type, off, v, f));
        return ret;
    } else if(type == "pdin"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new ProgressiveDownloadInfoBox(size, type, off, v, f));
        return ret;
    } else if(type == "xml "){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new XMLBox(size, type, off, v, f));
        return ret;
    } else if(type == "bxml"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new BinaryXMLBox(size, type, off, v, f));
        return ret;
    } else if(type == "iloc"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new ItemLocationBox(size, type, off, v, f));
        return ret;
    } else if(type == "pitm"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new PrimaryItemBox(size, type, off, v, f));
        return ret;
    } else if(type == "ipro"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new ItemProtectionBox(size, type, off, v, f));
        return ret;

    } else if(type == "infe"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new ItemInfoEntry(size, type, off, v, f));
        return ret;
    } else if(type == "iinf"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new ItemInfoBox(size, type, off, v, f));
        return ret;
    } else if(type == "frma"){
        std::shared_ptr<Box> ret(new OriginalFormatBox(size, type, off));
        return ret;
    } else if(type == "imif"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new IPMPInfoBox(size, type, off, v, f));
        return ret;
    } else if(type == "ipmc"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new IPMPControlBox(size, type, off, v, f));
        return ret;
    } else if(type == "rtp "){
        std::shared_ptr<Box> ret(new RTPMovieHintInformation(size, type, off));
        return ret;
    } else if(type == "iods"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        return std::shared_ptr<Box>(new ObjectDescriptorBox(size, type, off, v, f));
    } else if(type == "esds"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        return std::shared_ptr<Box>(new ESDBox(size, type, off, v, f));
    } else if(type == "leva"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        return std::shared_ptr<Box>(new LevelAssignmentBox(size, type, off, v, f));
    } else if(type == "prft"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        return std::shared_ptr<Box>(new ProducerReferenceTimeBox(size, type, off, v, f));
    } else if(type == "uuid") {
        QString extendedType = bitOperator->stringValue(fileService->getBytes(16, 8), 16);
        return std::shared_ptr<Box>(new UniversalUniqueIdentifier(size, type, off, extendedType));
    } else
        return std::shared_ptr<Box>(new Box(size, type, off));
    return NULL;
}
//////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getMBox(const unsigned int& size, QString type, unsigned long int off) {
    if(type== "moov")
        return std::shared_ptr<Box>(new MovieBox(size, type, off));
    else if(type == "mdat")
        return std::shared_ptr<Box>(new MediaDataBox(size, type, off));
    else if(type == "mvhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int version = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 9), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned long int creationTime;
        unsigned long int modificationTime;
        unsigned int timescale;
        unsigned long int duration;
        if(version == 1) {
            creationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 12), 8);
            modificationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 20), 8);
            timescale = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 28), 8);
            duration = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 36), 8);
            offset+=12;
        } else if(version == 0) {
            creationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
            modificationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
            timescale = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off+ offset + 20), 4);
            duration = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 24), 4);
        }
        QList<unsigned int> reserved32;
        QList<unsigned int> matrix;
        QList<unsigned int> predefined;
        unsigned int nextTrackId;
        unsigned int rate = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 28), 4)/65536;//fixed number
        unsigned int volume = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 32), 2)/256;
        unsigned int reserved16 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 34), 2);
        reserved32.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 36), 4));
        reserved32.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 40), 4));
        for(int i = 0; i < 9; ++ i)
            matrix.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 44 + 4*i), 4));
        for(int i = 0; i < 6; ++ i)
            predefined.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 80 +4*i), 4));
        nextTrackId = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 104), 4);

        std::shared_ptr<Box> ret(new MovieHeaderBox(size, type, off, version, f, creationTime, modificationTime, timescale, duration,
                                                    rate, volume, reserved16, reserved32, matrix, predefined, nextTrackId));
        return ret;
    } else if(type == "mdhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned long int creationTime;
        unsigned long int modificationTime;
        unsigned int timescale;
        unsigned long int duration;
        if(v == 1) {
            creationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 12), 8);
            modificationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off+ offset + 20), 8);
            timescale = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 28), 8);
            duration = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 43), 8);
            offset += 12;
        } else if (v == 0) {
            creationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
            modificationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
            timescale = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 20), 4);
            duration = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 24 ), 4);
        }

        unsigned long int byteValue = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 28), 4);
        QString tmpValue = QString::number(byteValue,2);
        int tmpSize = tmpValue.size();
        if(tmpSize < 32) {
            int delta = 32 - tmpSize;
            for (int i = 0; i<delta; ++ i)
                tmpValue = tmpValue.insert(0, "0");
        }
        QString qstringPad = tmpValue.mid(0,1);
        bool pad = (qstringPad.toUInt(0,2) == 0);
        QList<unsigned int> language;
        for(int i = 0; i < 3; ++ i) {
            QString qstringLan = tmpValue.mid(1+i*5,5);
            language.append(qstringLan.toUInt(0,2));
        }
        QString qstringPred = tmpValue.mid(16, 16);
        unsigned int predefined = qstringPred.toUInt(0,2);

        std::shared_ptr<Box> ret(new MediaHeaderBox(size, type, off, v, f, creationTime, modificationTime, timescale, duration,
                                                    pad, language, predefined));
        return ret;
    } else if(type == "mdia"){
        std::shared_ptr<Box> ret(new MediaBox(size, type, off));
        return ret;
    } else if(type == "moof"){
        std::shared_ptr<Box> ret(new MovieFragmentBox(size, type, off));
        return ret;
    } else if(type == "mfhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int sn = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        std::shared_ptr<Box> ret(new MovieFragmentHeaderBox(size, type, off, sn, v, f));
        return ret;
    } else if(type == "mp4v" /*|| type == "avc1"*/){
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 8 + i ), 1));

        unsigned int dataReferenceIndex = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 14), 2);
        unsigned int predefined = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 16), 2);
        unsigned int reserved1 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 18), 2);
        QList <unsigned int> predefined1;
        for(int i = 0; i < 3; ++ i)
            predefined1.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 20 + i*4), 4));
        unsigned int width = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 32), 2);
        unsigned int height = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 34), 2);
        unsigned int horizonresolution = bitOperator ->valueOfGroupOfBytes(fileService->getBytes(4, off + 36), 4)/65536;
        unsigned int vertresolution = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 40), 4)/65536;
        unsigned int reserved2 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 44), 4);
        unsigned int frameCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 48), 2);
        QString compressorName = bitOperator->stringValue(fileService->getBytes(4, off + 50), 4);
        unsigned int depth = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 82), 2);
        int predefined2 = bitOperator->signedValueOfGroupOfBytes(fileService->getBytes(2, off + 84), 2);
        return std::shared_ptr<Box>(new MP4VisualSampleEntry(size, type, off,reserved,dataReferenceIndex, predefined, reserved1,
                                                             predefined1, width, height, horizonresolution, vertresolution, reserved2,
                                                             frameCount, compressorName, depth, predefined2));
    } else if(type == "mp4a"){
        //SampleEntry
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 9 + i ), 1));
        unsigned int dataReferenceIndex = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off +14), 2);
        //AudioSampleEntry
        QList <unsigned int> reserved1;
        reserved1.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 16), 4));
        reserved1.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 20), 4));
        unsigned int channelCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 24), 2);
        unsigned int sampleSize = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 26), 2);
        unsigned int predefined = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 28), 2);
        unsigned int reserved2 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 30), 2);
        unsigned int sampleRate = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + 32), 2);
        return std::shared_ptr<Box>(new MP4AudioSampleEntry(size, type, off,reserved,dataReferenceIndex, reserved1, channelCount,
                                                            sampleSize, predefined, reserved2, sampleRate));
    } else if(type == "mp4s"){
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + 8 + i ), 1));
        unsigned int dataReferenceIndex = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off +14), 2);
        return std::shared_ptr<Box>(new MpegSampleEntry(size, type, off,reserved,dataReferenceIndex));
    } else if(type == "mvex"){
        std::shared_ptr<Box> ret(new MovieExtendsBox(size, type, off));
        return ret;
    } else if(type == "mehd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned long int fd;
        if(v)
            fd = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 12), 8);
        else
            fd = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        std::shared_ptr<Box> ret(new MovieExtendsHeaderBox(size, type, off, v, f, fd));
        return ret;
    } else if(type == "minf"){
        std::shared_ptr<Box> ret(new MediaInformationBox(size, type, off));
        return ret;
    } else if(type == "mfra"){
        std::shared_ptr<Box> ret(new MovieFragmentRandomAccessBox(size, type, off));
        return ret;
    } else if(type == "meta"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new MetaBox(size, type, off, v, f));
        return ret;
    } else if(type == "mfro"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new MovieFragmentRandomAccessOffsetBox(size, type, off, v, f));
        return ret;
    }
    return std::shared_ptr<Box>(new Box(size, type, off));
}
////////////////////////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getTBox(const unsigned int& size, QString type, unsigned long int off) {
    if(type == "trak"){
        std::shared_ptr<Box> ret(new TrackBox(size, type, off));
        return ret;
    } else if(type == "tkhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned long int creationTime = 0;
        unsigned long int modificationTime = 0;
        unsigned int trackID = 0;
        unsigned int reserved1;
        unsigned long int duration;
        if(v == 1) {
            creationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 12), 8);
            modificationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off+ offset + 20), 8);
            trackID = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 28), 4);
            reserved1 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 32), 4);
            duration = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 43), 8);
            offset += 12;
        } else if(v == 0) {
            creationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
            modificationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
            trackID = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 20), 4);
            reserved1 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 24 ), 4);
            duration = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 28), 4);
        }
        QList<unsigned int> reserved2;
        reserved2.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 32), 4));
        reserved2.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 36), 4));
        unsigned int layer = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 40), 2);
        unsigned int alternateGroup = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1,  off + offset + 42), 1);
        unsigned int volume = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 44), 2)/256;
        unsigned int reserved3 = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 46), 2);
        QList<unsigned int> matrix;
        for(int i = 0; i < 9; i ++) {
            matrix.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 48 ), 4));
            offset += 4;
        }
        offset -= 4;
        unsigned int width = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 50 ), 4);
        unsigned int height = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 54 ), 4);
        std::shared_ptr<Box> ret(new TrackHeaderBox(size, type, off, v, f, creationTime, modificationTime, trackID, reserved1, duration,
                                                    reserved2, layer, alternateGroup, volume, reserved3, matrix, width, height));
        return ret;
    } else if(type == "tref"){
        std::shared_ptr<Box> ret(new TrackReferenceBox(size, type, off));
        return ret;
    } else if(type == "trex"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));

        unsigned int tid = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        unsigned int dsdi = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
        unsigned int dsd = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 20), 4);
        unsigned int dss = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 24), 4);
        unsigned int dsf = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 28), 4);

        std::shared_ptr<Box> ret(new TrackExtendsBox(size, type, off, v, f, tid, dsdi, dsd, dss, dsf));
        return ret;
    } else if(type == "traf"){
        std::shared_ptr<Box> ret(new TrackFragmentBox(size, type, off));
        return ret;
    } else if(type == "tfhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int tid = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        unsigned long int bdo = 0;
        unsigned int sdi = 0;
        unsigned int dsd = 0;
        unsigned int dss = 0;
        unsigned int dsf = 0;
        if(size >= 24) {
            bdo = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 16), 8);
            if(size >= 28) {
                sdi = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 24 ), 4);
                if(size >= 32) {
                    dsd = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 28), 4);
                    if(size >= 36) {
                        dss = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 32), 4);
                        if(size >= 40)
                            dsf = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 36), 4);
                    }
                }
            }
        }
        std::shared_ptr<Box> ret(new TrackFragmentHeaderBox(size, type, off, v, f, tid, bdo, sdi, dsd, dss, dsf));
        return ret;
    } else if(type == "trun"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int sampleCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        long int dataOffset = 0;
        if(f.at(2) == 1 || f.at(2) == 5) {
            dataOffset = bitOperator->signedValueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
            offset += 4;
        }
        unsigned int firstSampleFlags = 0;
        if(f.at(2) == 4 || f.at(2) == 5) {
            firstSampleFlags = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
            offset += 4;
        }
        QList<unsigned int> sampleDuration;
        QList<unsigned int> sampleSize;
        QList<unsigned int> sampleFlags;
        QList<unsigned int> sampleCompositionTimeOffset;
        //?
        if(f.at(1) == 2)
            for (unsigned int i = 0; i<sampleCount; ++ i)
                sampleSize.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16 + 4*i), 4));

        std::shared_ptr<Box> ret(new TrackRunBox(size, type, off, v, f,sampleCount,dataOffset,firstSampleFlags,sampleDuration,
                                                 sampleSize,sampleFlags,sampleCompositionTimeOffset));
        return ret;
    } else if(type == "tfra"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));

        std::shared_ptr<Box> ret(new TrackFragmentRandomAccessBox(size, type, off, v, f));
        return ret;
    } else if(type == "tims"){
        std::shared_ptr<Box> ret(new TimeScaleEntry(size, type, off));
        return ret;
    } else if(type == "tsro"){
        std::shared_ptr<Box> ret(new TimeOffset(size, type, off));
        return ret;
    } else if(type == "tfdt"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned long int baseMediaDecodeTime;
        if(v == 1)
            baseMediaDecodeTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 12), 8);
        else if(v == 0)
            baseMediaDecodeTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        return std::shared_ptr<Box>(new TrackFragmentBaseMediaDecodeTimeBox(size, type, off, v, f, baseMediaDecodeTime));
    }
    return std::shared_ptr<Box>(new Box(size, type, off));
}
////////////////////////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getSBox(const unsigned int& size, QString type, unsigned long int off) {
    if(type == "smhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int balance = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 12), 2);
        unsigned int reserved = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 14), 2);
        std::shared_ptr<Box> ret(new SoundMediaHeaderBox(size, type, off, v, f, balance, reserved));
        return ret;
    } else if(type == "stbl"){
        std::shared_ptr<Box> ret(new SampleTableBox(size, type, off));
        return ret;
    } else if(type == "stts"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);

        QList<unsigned int> sampleCount;
        QList<unsigned int> sampleDelta;
        unsigned int index =0;
        unsigned int i = 0;
        while(index<entryCount) {
            sampleCount.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset+ i + 16), 4));
            sampleDelta.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + i + 20), 4));
            ++ index;
            i += 8;
        }
        std::shared_ptr<Box> ret(new TimeToSampleBox(size, type, off, v, f, entryCount, sampleCount, sampleDelta));
        return ret;
    } else if(type == "stsd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        std::shared_ptr<Box> ret(new SampleDescriptionBox(size, type, off,v,f,entryCount));
        return ret;
    } else if(type == "stsz"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int sampleSize = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        unsigned int sampleCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
        QList<unsigned int> entrySize;
        if(sampleSize == 0)
            for(unsigned int i = 0; i<sampleCount; ++ i)
                entrySize.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 20 + 4*i ), 4));

        std::shared_ptr<Box> ret(new SampleSizeBox(size, type, off, v, f, sampleSize, sampleCount, entrySize));
        return ret;
    } else if(type == "stz2"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int reserved = bitOperator->valueOfGroupOfBytes(fileService->getBytes(3, offset + off + 12), 3);
        unsigned int fieldSize = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 15), 1);
        unsigned int sampleCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, offset + off + 16), 4);
        QList<unsigned int> entrySize;
        for (unsigned int i = 0; i < 3; ++ i)
            entrySize.append(bitOperator->valueOfGroupOfBits(fileService->getBits(fieldSize, (off + offset + 20)*4 + i*fieldSize), fieldSize));
        std::shared_ptr<Box> ret(new CompactSampleSizeBox(size, type, off, v, f, reserved, fieldSize, sampleCount, entrySize));
        return ret;
    } else if(type == "stsc"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        QList<unsigned int> firstChunk;
        QList<unsigned int> samplesPerChunk;
        QList<unsigned int> sampleDescriptionIndex;
        for(unsigned int i = 0; i<entryCount; ++ i) {
            firstChunk.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 16 + 12*i ), 4));
            samplesPerChunk.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 20 + 12*i ), 4));
            sampleDescriptionIndex.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 24 + 12*i ), 4));
        }
        std::shared_ptr<Box> ret(new SampleToChunkBox(size, type, off, v, f, entryCount, firstChunk, samplesPerChunk,
                                                      sampleDescriptionIndex));
        return ret;
    } else if(type == "stco"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        QList<unsigned int> chunkOffset;
        for(unsigned int i = 0; i<entryCount; ++ i)
            chunkOffset.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16 + 4*i), 4));
        std::shared_ptr<Box> ret(new ChunkOffsetBox(size, type, off, v, f, entryCount, chunkOffset));
        return ret;
    } else if(type == "stss"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int entryCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        QList<unsigned int> sampleNumber;
        for (unsigned int i = 0; i<entryCount; ++ i)
            sampleNumber.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16 + 4*i), 4));
        std::shared_ptr<Box> ret(new SyncSampleBox(size, type, off, v, f, entryCount,sampleNumber));
        return ret;
    } else if(type == "styp") {
        QString majorBrand = bitOperator->stringValue(fileService->getBytes(4, off + 8), 4);
        unsigned int minorVersion = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + 12), 4);
        //QString minorVersion = bitOperator->stringValue(fileService->getBytes(4, off + 12);
        QList<QString> compatibleBrands;
        unsigned int index = 16;
        while(index <= (size - 4)) {
            QString brand =  bitOperator->stringValue(fileService->getBytes(4, off + index), 4);
            compatibleBrands.append(brand);
            index += 4;
        }

        return std::shared_ptr<Box>(new SegmentTypeBox(size, type, off, majorBrand, minorVersion, compatibleBrands));
    } else if(type == "stsh"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new ShadowSyncSampleBox(size, type, off, v, f));
        return ret;
    } else if(type == "stdp"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new DegradationPriorityBox(size, type, off, v, f));
        return ret;
    } else if(type == "skip"){
        std::shared_ptr<Box> ret(new FreeSpaceBox(true,size, type, off));
        return ret;
    } else if(type == "sdtp"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new SampleDependencyTypeBox(size, type, off, v, f));
        return ret;
    } else if(type == "sbgp"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new SampleToGroupBox(size, type, off, v, f));
        return ret;
    } else if(type == "sgpd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new SampleGroupDescriptionBox(size, type, off, v, f));
        return ret;
    } else if(type == "stsl"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new SampleScaleBox(size, type, off, v, f));
        return ret;
    } else if(type == "sidx"){
        QList<bool> boolList;
        QList<unsigned int> intList;
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int version = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 9), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int referenceId = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        unsigned int timescale = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
        unsigned long int earliestPresentationTime = 0;
        unsigned long int firstOffset = 0;
        if (version == 0){
            earliestPresentationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 20), 4);
            firstOffset = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 24 ), 4);
        } else if (version == 1) {
            earliestPresentationTime = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 20), 8);
            firstOffset = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, off + offset + 28), 8);
            offset += 8;
        }

        unsigned int reserved = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 28), 2);
        unsigned int referenceCount = bitOperator->valueOfGroupOfBytes(fileService->getBytes(2, off + offset + 30), 2);

        QList<bool> referenceType;
        QList<unsigned int> referenceSize;
        QList<unsigned int> subsegmentDuration;
        QList<bool> startsWithSAP;
        QList <unsigned int> SAPType;
        QList <unsigned int> SAPDeltaTime;
        qDebug()<<"BOXFACTOR: getBox sidx 9 referenceCount: "<<referenceCount;
        for(unsigned int i = 0; i < referenceCount; i ++) {
            referenceType.append(bitOperator->valueOfGroupOfBits(fileService->getBits(1, (off + offset + 32)*8), 1));
            qDebug()<<"BOXFACTOR: getBox sidx 10"<<i;
            referenceSize.append(bitOperator->valueOfGroupOfBits(fileService->getBits(31, (off + offset + 32)*8 + 1), 31));
            qDebug()<<"BOXFACTOR: getBox sidx 11"<<i;
            subsegmentDuration.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 36), 4));
            qDebug()<<"BOXFACTOR: getBox sidx 12"<<i;
            startsWithSAP.append(bitOperator->valueOfGroupOfBits(fileService->getBits(1, (off + offset + 40)*8), 1));
            qDebug()<<"BOXFACTOR: getBox sidx 13"<<i;
            SAPType.append(bitOperator->valueOfGroupOfBits(fileService->getBits(3, (off + offset + 40)*8 + 1), 3));
            qDebug()<<"BOXFACTOR: getBox sidx 14"<<i;
            SAPDeltaTime.append(bitOperator->valueOfGroupOfBits(fileService->getBits(28, (off + offset + 40)*8 + 4), 28));
            qDebug()<<"BOXFACTOR: getBox sidx 15"<<i;
            offset += 12;
        }
        return std::shared_ptr<Box>(new SegmentIndexBox(size, type, off, version, f, referenceId, timescale, earliestPresentationTime,
                                                        firstOffset, reserved, referenceType, referenceSize, subsegmentDuration,
                                                        startsWithSAP, SAPType, SAPDeltaTime));
    } else if(type == "ssix"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int version = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 9), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        return std::shared_ptr<Box>(new SubsegmentIndexBox(size, type, off, version, f));
    } else if(type == "subs"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new SubSampleInformationBox(size, type, off, v, f));
        return ret;
    } else if(type == "sinf"){
        std::shared_ptr<Box> ret(new ProtectionSchemeInfoBox(size, type, off));
        return ret;
    } else if(type == "schm"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new SchemeTypeBox(size, type, off, v, f));
        return ret;
    } else if(type == "schi"){
        std::shared_ptr<Box> ret(new SchemeInformationBox(size, type, off));
        return ret;
    } else if(type == "snro"){
        std::shared_ptr<Box> ret(new SequenceOffset(size, type, off));
        return ret;
    } else if(type == "srpp"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new SRTPProcessBox(size, type, off, v, f));
        return ret;
    } else if(type == "sdp "){
        std::shared_ptr<Box> ret(new RTPTrackSDPHintInformation(size, type, off));
        return ret;
    } else if(type == "saiz"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        return std::shared_ptr<Box>(new SampleAuxiliaryInformationSizesBox(size, type, off, v, f));
    } else if(type == "saio"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        return std::shared_ptr<Box>(new SampleAuxiliaryInformationOffsetsBox(size, type, off, v, f));
    }
    return std::shared_ptr<Box>(new Box(size, type, off));
}
////////////////////////////////////////////////////////////////
std::shared_ptr<Box> BoxFactory::getHBox(const unsigned int& size, QString type, unsigned long int off) {
    if(type == "hdlr"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        unsigned int predefined = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 12), 4);
        unsigned long int handlerType = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, off + offset + 16), 4);
        QList <unsigned int> reserved;
        for(int i = 0; i < 3; ++ i)
            reserved.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(4 , off + offset + 20 + 4*i ), 4));
        QString name = bitOperator->stringValue(fileService->getBytes(size - offset - 32, off + offset + 32), size - offset - 32);
        std::shared_ptr<Box> ret(new HandlerBox(size, type, off, v, f, predefined, handlerType, reserved, name));
        return ret;
    } else if(type == "hmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + 8), 1);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(bitOperator->valueOfGroupOfBytes(fileService->getBytes(1, off + offset + i + 9), 1));
        std::shared_ptr<Box> ret(new HintMediaHeaderBox(size, type, off, v, f));
        return ret;
    } else if(type == "hnti"){
        std::shared_ptr<Box> ret(new MovieHintInformation(size, type, off));
        return ret;
    } else if(type == "hinf"){
        std::shared_ptr<Box> ret(new HintStatisticsBox(size, type, off));
        return ret;
    }
    return std::shared_ptr<Box>(new Box(size, type, off));
}
