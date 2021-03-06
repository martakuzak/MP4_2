#include "boxfactory.h"


BoxFactory::BoxFactory(FileService *fs) : fileService(fs) {
    bitOperator = new BitOperator();
}

std::shared_ptr<Box> BoxFactory::getBox(const unsigned int& size, QString type, unsigned long int off) {
    //qDebug()<<"BOXFACTORY: getBox"<<type<<size;
    if(type.at(0)==QChar('m'))
        return this->getMBox(size, type, off);
    else if(type.at(0)==QChar('t'))
        return this->getTBox(size, type, off);
    else if(type.at(0)==QChar('s'))
        return this->getSBox(size, type, off);
    else if(type.at(0) == QChar('h'))
        return this->getHBox(size, type, off);
    else if(type == "ftyp") {
        QString majorBrand = stringValue(4, off + 8);
        unsigned int minorVersion = valueOfGroupOfBytes(4, off + 12);
        QList<QString> compatibleBrands;
        unsigned int index = 16;
        while(index <= (size - 4)) {
            QString brand = stringValue(4, off + index);
            compatibleBrands.append(brand);
            index += 4;
        }
        return std::shared_ptr<Box>(new FileTypeBox(size, type, off, majorBrand, minorVersion, compatibleBrands));
    } else if(type == "vmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + 9 + i));
        unsigned int graphicsMode = valueOfGroupOfBytes(2, off + offset + 13);
        QList <unsigned int> opcolor;
        for (int i = 0; i < 3; ++ i)
            opcolor.append(valueOfGroupOfBytes(2, off + offset + 15 + 2*i));
        std::shared_ptr<Box> ret(new VideoMediaHeaderBox(size, type, off, v, f, graphicsMode, opcolor));
        return ret;
    } else if(type == "nmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new NullMediaHeaderBox(size, type, off, v, f));
        return ret;
    } else if(type == "dinf"){
        std::shared_ptr<Box> ret(new DataInformationBox(size, type, off));
        return ret;
    } else if(type == "avc1"){
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(valueOfGroupOfBytes(1, off + 8 + i));
        unsigned int dataReferenceIndex = valueOfGroupOfBytes(2, off + 14);
        unsigned int predefined = valueOfGroupOfBytes(2, off + 16);
        unsigned int reserved1 = valueOfGroupOfBytes(2, off + 18);
        QList <unsigned int> predefined1;
        for(int i = 0; i < 3; ++ i)
            predefined1.append(valueOfGroupOfBytes(4, off + 20 + i*4));
        unsigned int width = valueOfGroupOfBytes(2, off + 32);
        unsigned int height = valueOfGroupOfBytes(2, off + 34);
        unsigned int horizonresolution = valueOfGroupOfBytes(4, off + 36)/65536;
        unsigned int vertresolution = valueOfGroupOfBytes(4, off + 40)/65536;
        unsigned int reserved2 = valueOfGroupOfBytes(4, off + 44);
        unsigned int frameCount = valueOfGroupOfBytes(2, off + 48);
        QString compressorName = stringValue(4, off + 50);
        unsigned int depth = valueOfGroupOfBytes(2, off + 82);
        int predefined2 = signedValueOfGroupOfBytes(2, off + 84);
        return std::shared_ptr<Box>(new AVCSampleEntry(size, type, off,reserved,dataReferenceIndex, predefined, reserved1, predefined1,
                                                       width,height,horizonresolution, vertresolution, reserved2, frameCount,
                                                       compressorName, depth, predefined2));
    } else if(type == "avcC") {
        qDebug()<<"BOXFACTORY avcC 1";
        unsigned int configurationVersion = valueOfGroupOfBytes(1, off + 8);
        unsigned int AVCProfileIndication = valueOfGroupOfBytes(1, off + 9);
        unsigned int profileCompatibility = valueOfGroupOfBytes(1, off + 10);
        unsigned int AVCLevelIndication = valueOfGroupOfBytes(1, off + 11);
        unsigned int reserved1 = valueOfGroupOfBits(6, (off + 12)*8);
        unsigned int lengthSizeMinusOne = valueOfGroupOfBits(2, (off + 12)*8 + 6);
        unsigned int reserved2 = valueOfGroupOfBits(3, (off + 13)*8);
        unsigned int numOfSequenceParameterSets = valueOfGroupOfBits(5, (off + 13)*8 + 3);
        //qDebug()<<"BOXFACTORY avcC 2";
        QList <unsigned int> sequenceParameterSetLength;
        QList <unsigned long int> sequenceParameterSetNALUnit;
        unsigned int offset = 0;
        for (unsigned int i = 0; i <numOfSequenceParameterSets; ++ i) {
            //qDebug()<<"BOXFACTORY avcC 2.1"<<i<<(off + offset + 14);
            sequenceParameterSetLength.append(valueOfGroupOfBytes(2, off + offset + 14 ));
            //qDebug()<<"BOXFACTORY avcC 2.2"<<i<<sequenceParameterSetLength.at(i);
            valueOfGroupOfBytes(sequenceParameterSetLength.at(i), off + offset + 16);
            sequenceParameterSetNALUnit.append(valueOfGroupOfBytes(sequenceParameterSetLength.at(i), off + offset + 16));
            //qDebug()<<"BOXFACTORY avcC 2.3";
            offset = offset + 2 + sequenceParameterSetLength.at(i);
            //qDebug()<<"BOXFACTORY avcC 2.4";
        }
        //qDebug()<<"BOXFACTORY avcC 3";

        unsigned int numOfPictureParameterSets = valueOfGroupOfBytes(1, off + offset + 14);
        QList <unsigned int> pictureParameterSetLength;
        QList <unsigned long int> pictureParameterSetNALUnit;
        for (unsigned int i = 0; i <numOfPictureParameterSets; ++ i) {
            pictureParameterSetLength.append(valueOfGroupOfBytes(2, off + offset + 15 ));
            pictureParameterSetNALUnit.append(valueOfGroupOfBytes(pictureParameterSetLength.at(i), off + offset + 17));
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        QString location;
        if(f.at(2) == 1)
            location = QString("this file");
        else
            location = stringValue(size - offset - 13, off + offset + 13); //?
        std::shared_ptr<Box> ret(new DataEntryUrlBox(size, type, off, v, f, location));
        return ret;
    } else if(type == "urn "){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new DataEntryUrnBox(size, type, off, v, f));
        return ret;
    } else if(type == "dref"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);
        std::shared_ptr<Box> ret(new DataReferenceBox(size, type, off, v, f, entryCount));
        return ret;
    } else if(type == "ctts"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));

        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);

        QList<unsigned int> sampleCount;
        QList<unsigned int> sampleDelta;
        unsigned int index = 0;
        unsigned int i = 0;
        while(index < entryCount) {
            sampleCount.append(valueOfGroupOfBytes(4, off + offset + i + 16));
            sampleDelta.append(valueOfGroupOfBytes(4, off + offset + i + 20));
            ++ index;
            i += 8;
        }

        std::shared_ptr<Box> ret(new TimeToSampleBox(size, type, off, v, f, entryCount, sampleCount, sampleDelta));
        return ret;
    } else if(type == "co64"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned long int entryCount = valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned long int> chunkOffset;
        for(unsigned int i = 0; i<entryCount; ++ i)
            chunkOffset.append(valueOfGroupOfBytes(4, off + offset + 16 + 4*i));
        std::shared_ptr<Box> ret(new ChunkLargeOffsetBox(size, type, off, v, f, entryCount, chunkOffset));
        return ret;
    } else if(type == "btrt") {
        unsigned int bufferSizeDB = valueOfGroupOfBytes(4, off + 8);
        unsigned int maxBitrate = valueOfGroupOfBytes(4, off + 12);
        unsigned int avgBitrate = valueOfGroupOfBytes(4, off + 16);

        return std::shared_ptr<Box> (new MPEG4BitRateBox(size, type, off, bufferSizeDB, maxBitrate, avgBitrate));
    } else if(type == "padb"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        QList<unsigned long int> segmentDuration;
        QList<unsigned long int> mediaTime;
        QList<unsigned int> mediaRateInteger;
        QList<unsigned int> mediaRateFraction;
        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);
        for(unsigned int i = 0; i < entryCount; ++ i) {
            if(v == 1) {
                segmentDuration.append(valueOfGroupOfBytes(8, off + offset + 16));
                mediaTime.append(valueOfGroupOfBytes(8, off + offset + 24));
                offset += 8;
            } else if(v == 0) {
                segmentDuration.append(valueOfGroupOfBytes(4, off + offset + 16));
                mediaTime.append(valueOfGroupOfBytes(4, off + offset + 20));
            }
            mediaRateInteger.append(valueOfGroupOfBytes(2, off + offset + 24));
            mediaRateFraction.append(valueOfGroupOfBytes(2, off + offset + 27));
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new CopyRightBox(size, type, off, v, f));
        return ret;
    } else if(type == "pdin"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new ProgressiveDownloadInfoBox(size, type, off, v, f));
        return ret;
    } else if(type == "xml "){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new XMLBox(size, type, off, v, f));
        return ret;
    } else if(type == "bxml"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new BinaryXMLBox(size, type, off, v, f));
        return ret;
    } else if(type == "iloc"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new ItemLocationBox(size, type, off, v, f));
        return ret;
    } else if(type == "pitm"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new PrimaryItemBox(size, type, off, v, f));
        return ret;
    } else if(type == "ipro"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new ItemProtectionBox(size, type, off, v, f));
        return ret;

    } else if(type == "infe"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new ItemInfoEntry(size, type, off, v, f));
        return ret;
    } else if(type == "iinf"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new ItemInfoBox(size, type, off, v, f));
        return ret;
    } else if(type == "frma"){
        std::shared_ptr<Box> ret(new OriginalFormatBox(size, type, off));
        return ret;
    } else if(type == "imif"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new IPMPInfoBox(size, type, off, v, f));
        return ret;
    } else if(type == "ipmc"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new IPMPControlBox(size, type, off, v, f));
        return ret;
    } else if(type == "rtp "){
        std::shared_ptr<Box> ret(new RTPMovieHintInformation(size, type, off));
        return ret;
    } else if(type == "iods"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        return std::shared_ptr<Box>(new ObjectDescriptorBox(size, type, off, v, f));
    } else if(type == "esds"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        return std::shared_ptr<Box>(new ESDBox(size, type, off, v, f));
    } else if(type == "leva"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        return std::shared_ptr<Box>(new LevelAssignmentBox(size, type, off, v, f));
    } else if(type == "prft"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        return std::shared_ptr<Box>(new ProducerReferenceTimeBox(size, type, off, v, f));
    } else if(type == "uuid") {
        QString extendedType = stringValue(16, 8);
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
        unsigned int version = valueOfGroupOfBytes(1, off + offset + 9);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned long int creationTime;
        unsigned long int modificationTime;
        unsigned int timescale;
        unsigned long int duration;
        if(version == 1) {
            creationTime = valueOfGroupOfBytes(8, off + offset + 12);
            modificationTime = valueOfGroupOfBytes(8, off + offset + 20);
            timescale = valueOfGroupOfBytes(8, off + offset + 28);
            duration = valueOfGroupOfBytes(8, off + offset + 36);
            offset+=12;
        } else if(version == 0) {
            creationTime = valueOfGroupOfBytes(4, off + offset + 12);
            modificationTime = valueOfGroupOfBytes(4, off + offset + 16);
            timescale = valueOfGroupOfBytes(4, off+ offset + 20);
            duration = valueOfGroupOfBytes(4, off + offset + 24);
        }
        QList<unsigned int> reserved32;
        QList<unsigned int> matrix;
        QList<unsigned int> predefined;
        unsigned int nextTrackId;
        unsigned int rate = valueOfGroupOfBytes(4, off + offset + 28)/65536;//fixed number
        unsigned int volume = valueOfGroupOfBytes(2, off + offset + 32)/256;
        unsigned int reserved16 = valueOfGroupOfBytes(2, off + offset + 34);
        reserved32.append(valueOfGroupOfBytes(4, off + offset + 36));
        reserved32.append(valueOfGroupOfBytes(4, off + offset + 40));
        for(int i = 0; i < 9; ++ i)
            matrix.append(valueOfGroupOfBytes(4, off + offset + 44 + 4*i));
        for(int i = 0; i < 6; ++ i)
            predefined.append(valueOfGroupOfBytes(4, off + offset + 80 +4*i));
        nextTrackId = valueOfGroupOfBytes(4, off + offset + 104);

        std::shared_ptr<Box> ret(new MovieHeaderBox(size, type, off, version, f, creationTime, modificationTime, timescale, duration,
                                                    rate, volume, reserved16, reserved32, matrix, predefined, nextTrackId));
        return ret;
    } else if(type == "mdhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned long int creationTime;
        unsigned long int modificationTime;
        unsigned int timescale;
        unsigned long int duration;
        if(v == 1) {
            creationTime = valueOfGroupOfBytes(8, off + offset + 12);
            modificationTime = valueOfGroupOfBytes(8, off+ offset + 20);
            timescale = valueOfGroupOfBytes(8, off + offset + 28);
            duration = valueOfGroupOfBytes(8, off + offset + 43);
            offset += 12;
        } else if (v == 0) {
            creationTime = valueOfGroupOfBytes(4, off + offset + 12);
            modificationTime = valueOfGroupOfBytes(4, off + offset + 16);
            timescale = valueOfGroupOfBytes(4, off + offset + 20);
            duration = valueOfGroupOfBytes(4 , off + offset + 24 );
        }

        unsigned long int byteValue = valueOfGroupOfBytes(4, off + offset + 28);
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int sn = valueOfGroupOfBytes(4, off + offset + 12);
        std::shared_ptr<Box> ret(new MovieFragmentHeaderBox(size, type, off, sn, v, f));
        return ret;
    } else if(type == "mp4v" /*|| type == "avc1"*/){
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(valueOfGroupOfBytes(1, off + 8 + i ));

        unsigned int dataReferenceIndex = valueOfGroupOfBytes(2, off + 14);
        unsigned int predefined = valueOfGroupOfBytes(2, off + 16);
        unsigned int reserved1 = valueOfGroupOfBytes(2, off + 18);
        QList <unsigned int> predefined1;
        for(int i = 0; i < 3; ++ i)
            predefined1.append(valueOfGroupOfBytes(4, off + 20 + i*4));
        unsigned int width = valueOfGroupOfBytes(2, off + 32);
        unsigned int height = valueOfGroupOfBytes(2, off + 34);
        unsigned int horizonresolution = valueOfGroupOfBytes(4, off + 36)/65536;
        unsigned int vertresolution = valueOfGroupOfBytes(4, off + 40)/65536;
        unsigned int reserved2 = valueOfGroupOfBytes(4, off + 44);
        unsigned int frameCount = valueOfGroupOfBytes(2, off + 48);
        QString compressorName = stringValue(4, off + 50);
        unsigned int depth = valueOfGroupOfBytes(2, off + 82);
        int predefined2 = signedValueOfGroupOfBytes(2, off + 84);
        return std::shared_ptr<Box>(new MP4VisualSampleEntry(size, type, off,reserved,dataReferenceIndex, predefined, reserved1,
                                                             predefined1, width, height, horizonresolution, vertresolution, reserved2,
                                                             frameCount, compressorName, depth, predefined2));
    } else if(type == "mp4a"){
        //SampleEntry
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(valueOfGroupOfBytes(1, off + 9 + i ));
        unsigned int dataReferenceIndex = valueOfGroupOfBytes(2, off +14);
        //AudioSampleEntry
        QList <unsigned int> reserved1;
        reserved1.append(valueOfGroupOfBytes(4, off + 16));
        reserved1.append(valueOfGroupOfBytes(4, off + 20));
        unsigned int channelCount = valueOfGroupOfBytes(2, off + 24);
        unsigned int sampleSize = valueOfGroupOfBytes(2, off + 26);
        unsigned int predefined = valueOfGroupOfBytes(2, off + 28);
        unsigned int reserved2 = valueOfGroupOfBytes(2, off + 30);
        unsigned int sampleRate = valueOfGroupOfBytes(2, off + 32);
        return std::shared_ptr<Box>(new MP4AudioSampleEntry(size, type, off,reserved,dataReferenceIndex, reserved1, channelCount,
                                                            sampleSize, predefined, reserved2, sampleRate));
    } else if(type == "mp4s"){
        QList <unsigned int> reserved;
        for(int i = 0; i < 6; ++ i)
            reserved.append(valueOfGroupOfBytes(1, off + 8 + i ));
        unsigned int dataReferenceIndex = valueOfGroupOfBytes(2, off +14);
        return std::shared_ptr<Box>(new MpegSampleEntry(size, type, off,reserved,dataReferenceIndex));
    } else if(type == "mvex"){
        std::shared_ptr<Box> ret(new MovieExtendsBox(size, type, off));
        return ret;
    } else if(type == "mehd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned long int fd;
        if(v)
            fd = valueOfGroupOfBytes(8, off + offset + 12);
        else
            fd = valueOfGroupOfBytes(4, off + offset + 12);
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new MetaBox(size, type, off, v, f));
        return ret;
    } else if(type == "mfro"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned long int creationTime = 0;
        unsigned long int modificationTime = 0;
        unsigned int trackID = 0;
        unsigned int reserved1;
        unsigned long int duration;
        if(v == 1) {
            creationTime = valueOfGroupOfBytes(8, off + offset + 12);
            modificationTime = valueOfGroupOfBytes(8, off+ offset + 20);
            trackID = valueOfGroupOfBytes(4, off + offset + 28);
            reserved1 = valueOfGroupOfBytes(4, off + offset + 32);
            duration = valueOfGroupOfBytes(8, off + offset + 43);
            offset += 12;
        } else if(v == 0) {
            creationTime = valueOfGroupOfBytes(4, off + offset + 12);
            modificationTime = valueOfGroupOfBytes(4, off + offset + 16);
            trackID = valueOfGroupOfBytes(4, off + offset + 20);
            reserved1 = valueOfGroupOfBytes(4 , off + offset + 24 );
            duration = valueOfGroupOfBytes(4, off + offset + 28);
        }
        QList<unsigned int> reserved2;
        reserved2.append(valueOfGroupOfBytes(4, off + offset + 32));
        reserved2.append(valueOfGroupOfBytes(4, off + offset + 36));
        unsigned int layer = valueOfGroupOfBytes(2, off + offset + 40);
        unsigned int alternateGroup = valueOfGroupOfBytes(1,  off + offset + 42);
        unsigned int volume = valueOfGroupOfBytes(2, off + offset + 44)/256;
        unsigned int reserved3 = valueOfGroupOfBytes(2, off + offset + 46);
        QList<unsigned int> matrix;
        for(int i = 0; i < 9; i ++) {
            matrix.append(valueOfGroupOfBytes(4 , off + offset + 48 ));
            offset += 4;
        }
        offset -= 4;
        unsigned int width = valueOfGroupOfBytes(4 , off + offset + 50 );
        unsigned int height = valueOfGroupOfBytes(4 , off + offset + 54 );
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));

        unsigned int tid = valueOfGroupOfBytes(4, off + offset + 12);
        unsigned int dsdi = valueOfGroupOfBytes(4, off + offset + 16);
        unsigned int dsd = valueOfGroupOfBytes(4, off + offset + 20);
        unsigned int dss = valueOfGroupOfBytes(4 , off + offset + 24);
        unsigned int dsf = valueOfGroupOfBytes(4, off + offset + 28);

        std::shared_ptr<Box> ret(new TrackExtendsBox(size, type, off, v, f, tid, dsdi, dsd, dss, dsf));
        return ret;
    } else if(type == "traf"){
        std::shared_ptr<Box> ret(new TrackFragmentBox(size, type, off));
        return ret;
    } else if(type == "tfhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int tid = valueOfGroupOfBytes(4, off + offset + 12);
        unsigned long int bdo = 0;
        unsigned int sdi = 0;
        unsigned int dsd = 0;
        unsigned int dss = 0;
        unsigned int dsf = 0;
        if(size >= 24) {
            bdo = valueOfGroupOfBytes(8, off + offset + 16);
            if(size >= 28) {
                sdi = valueOfGroupOfBytes(4 , off + offset + 24 );
                if(size >= 32) {
                    dsd = valueOfGroupOfBytes(4, off + offset + 28);
                    if(size >= 36) {
                        dss = valueOfGroupOfBytes(4, off + offset + 32);
                        if(size >= 40)
                            dsf = valueOfGroupOfBytes(4, off + offset + 36);
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int sampleCount = valueOfGroupOfBytes(4, off + offset + 12);
        long int dataOffset = 0;
        if(f.at(2) == 1 || f.at(2) == 5) {
            dataOffset = signedValueOfGroupOfBytes(4, off + offset + 16);
            offset += 4;
        }
        unsigned int firstSampleFlags = 0;
        if(f.at(2) == 4 || f.at(2) == 5) {
            firstSampleFlags = valueOfGroupOfBytes(4, off + offset + 16);
            offset += 4;
        }
        QList<unsigned int> sampleDuration;
        QList<unsigned int> sampleSize;
        QList<unsigned int> sampleFlags;
        QList<unsigned int> sampleCompositionTimeOffset;
        //?
        if(f.at(1) == 2)
            for (unsigned int i = 0; i<sampleCount; ++ i)
                sampleSize.append(valueOfGroupOfBytes(4, off + offset + 16 + 4*i));

        std::shared_ptr<Box> ret(new TrackRunBox(size, type, off, v, f,sampleCount,dataOffset,firstSampleFlags,sampleDuration,
                                                 sampleSize,sampleFlags,sampleCompositionTimeOffset));
        return ret;
    } else if(type == "tfra"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));

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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned long int baseMediaDecodeTime;
        if(v == 1)
            baseMediaDecodeTime = valueOfGroupOfBytes(8, off + offset + 12);
        else if(v == 0)
            baseMediaDecodeTime = valueOfGroupOfBytes(4, off + offset + 12);
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int balance = valueOfGroupOfBytes(2, off + offset + 12);
        unsigned int reserved = valueOfGroupOfBytes(2, off + offset + 14);
        std::shared_ptr<Box> ret(new SoundMediaHeaderBox(size, type, off, v, f, balance, reserved));
        return ret;
    } else if(type == "stbl"){
        std::shared_ptr<Box> ret(new SampleTableBox(size, type, off));
        return ret;
    } else if(type == "stts"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);

        QList<unsigned int> sampleCount;
        QList<unsigned int> sampleDelta;
        unsigned int index =0;
        unsigned int i = 0;
        while(index<entryCount) {
            sampleCount.append(valueOfGroupOfBytes(4, off + offset+ i + 16));
            sampleDelta.append(valueOfGroupOfBytes(4, off + offset + i + 20));
            ++ index;
            i += 8;
        }
        std::shared_ptr<Box> ret(new TimeToSampleBox(size, type, off, v, f, entryCount, sampleCount, sampleDelta));
        return ret;
    } else if(type == "stsd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);
        std::shared_ptr<Box> ret(new SampleDescriptionBox(size, type, off,v,f,entryCount));
        return ret;
    } else if(type == "stsz"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int sampleSize = valueOfGroupOfBytes(4, off + offset + 12);
        unsigned int sampleCount = valueOfGroupOfBytes(4, off + offset + 16);
        QList<unsigned int> entrySize;
        if(sampleSize == 0)
            for(unsigned int i = 0; i<sampleCount; ++ i)
                entrySize.append(valueOfGroupOfBytes(4 , off + offset + 20 + 4*i ));

        std::shared_ptr<Box> ret(new SampleSizeBox(size, type, off, v, f, sampleSize, sampleCount, entrySize));
        return ret;
    } else if(type == "stz2"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int reserved = valueOfGroupOfBytes(3, offset + off + 12);
        unsigned int fieldSize = valueOfGroupOfBytes(1, off + offset + 15);
        unsigned int sampleCount = valueOfGroupOfBytes(4, offset + off + 16);
        QList<unsigned int> entrySize;
        for (unsigned int i = 0; i < 3; ++ i)
            entrySize.append(valueOfGroupOfBits((fieldSize, (off + offset + 20)*4 + i*fieldSize), fieldSize));
        std::shared_ptr<Box> ret(new CompactSampleSizeBox(size, type, off, v, f, reserved, fieldSize, sampleCount, entrySize));
        return ret;
    } else if(type == "stsc"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned int> firstChunk;
        QList<unsigned int> samplesPerChunk;
        QList<unsigned int> sampleDescriptionIndex;
        for(unsigned int i = 0; i<entryCount; ++ i) {
            firstChunk.append(valueOfGroupOfBytes(4 , off + offset + 16 + 12*i ));
            samplesPerChunk.append(valueOfGroupOfBytes(4, off + offset + 20 + 12*i ));
            sampleDescriptionIndex.append(valueOfGroupOfBytes(4, off + offset + 24 + 12*i ));
        }
        std::shared_ptr<Box> ret(new SampleToChunkBox(size, type, off, v, f, entryCount, firstChunk, samplesPerChunk,
                                                      sampleDescriptionIndex));
        return ret;
    } else if(type == "stco"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned int> chunkOffset;
        for(unsigned int i = 0; i<entryCount; ++ i)
            chunkOffset.append(valueOfGroupOfBytes(4, off + offset + 16 + 4*i));
        std::shared_ptr<Box> ret(new ChunkOffsetBox(size, type, off, v, f, entryCount, chunkOffset));
        return ret;
    } else if(type == "stss"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int entryCount = valueOfGroupOfBytes(4, off + offset + 12);
        QList<unsigned int> sampleNumber;
        for (unsigned int i = 0; i<entryCount; ++ i)
            sampleNumber.append(valueOfGroupOfBytes(4, off + offset + 16 + 4*i));
        std::shared_ptr<Box> ret(new SyncSampleBox(size, type, off, v, f, entryCount,sampleNumber));
        return ret;
    } else if(type == "styp") {
        QString majorBrand = stringValue(4, off + 8);
        unsigned int minorVersion = valueOfGroupOfBytes(4, off + 12);
        //QString minorVersion = bitOperator->stringValue(4, off + 12);
        QList<QString> compatibleBrands;
        unsigned int index = 16;
        while(index <= (size - 4)) {
            QString brand =  stringValue(4, off + index);
            compatibleBrands.append(brand);
            index += 4;
        }

        return std::shared_ptr<Box>(new SegmentTypeBox(size, type, off, majorBrand, minorVersion, compatibleBrands));
    } else if(type == "stsh"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new ShadowSyncSampleBox(size, type, off, v, f));
        return ret;
    } else if(type == "stdp"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new DegradationPriorityBox(size, type, off, v, f));
        return ret;
    } else if(type == "skip"){
        std::shared_ptr<Box> ret(new FreeSpaceBox(true,size, type, off));
        return ret;
    } else if(type == "sdtp"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new SampleDependencyTypeBox(size, type, off, v, f));
        return ret;
    } else if(type == "sbgp"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new SampleToGroupBox(size, type, off, v, f));
        return ret;
    } else if(type == "sgpd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new SampleGroupDescriptionBox(size, type, off, v, f));
        return ret;
    } else if(type == "stsl"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new SampleScaleBox(size, type, off, v, f));
        return ret;
    } else if(type == "sidx"){
        QList<bool> boolList;
        QList<unsigned int> intList;
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int version = valueOfGroupOfBytes(1, off + offset + 9);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int referenceId = valueOfGroupOfBytes(4, off + offset + 12);
        unsigned int timescale = valueOfGroupOfBytes(4, off + offset + 16);
        unsigned long int earliestPresentationTime = 0;
        unsigned long int firstOffset = 0;
        if (version == 0){
            earliestPresentationTime = valueOfGroupOfBytes(4, off + offset + 20);
            firstOffset = valueOfGroupOfBytes(4 , off + offset + 24 );
        } else if (version == 1) {
            earliestPresentationTime = valueOfGroupOfBytes(8, off + offset + 20);
            firstOffset = valueOfGroupOfBytes(8, off + offset + 28);
            offset += 8;
        }

        unsigned int reserved = valueOfGroupOfBytes(2, off + offset + 28);
        unsigned int referenceCount = valueOfGroupOfBytes(2, off + offset + 30);

        QList<bool> referenceType;
        QList<unsigned int> referenceSize;
        QList<unsigned int> subsegmentDuration;
        QList<bool> startsWithSAP;
        QList <unsigned int> SAPType;
        QList <unsigned int> SAPDeltaTime;
        for(unsigned int i = 0; i < referenceCount; i ++) {
            referenceType.append(valueOfGroupOfBits(1, (off + offset + 32)*8));
            referenceSize.append(valueOfGroupOfBits(31, (off + offset + 32)*8 + 1));
            subsegmentDuration.append(valueOfGroupOfBytes(4, off + offset + 36));
            startsWithSAP.append(valueOfGroupOfBits(1, (off + offset + 40)*8));
            SAPType.append(valueOfGroupOfBits(3, (off + offset + 40)*8 + 1));
            SAPDeltaTime.append(valueOfGroupOfBits(28, (off + offset + 40)*8 + 4));
            offset += 12;
        }
        return std::shared_ptr<Box>(new SegmentIndexBox(size, type, off, version, f, referenceId, timescale, earliestPresentationTime,
                                                        firstOffset, reserved, referenceType, referenceSize, subsegmentDuration,
                                                        startsWithSAP, SAPType, SAPDeltaTime));
    } else if(type == "ssix"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int version = valueOfGroupOfBytes(1, off + offset + 9);
        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        return std::shared_ptr<Box>(new SubsegmentIndexBox(size, type, off, version, f));
    } else if(type == "subs"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new SubSampleInformationBox(size, type, off, v, f));
        return ret;
    } else if(type == "sinf"){
        std::shared_ptr<Box> ret(new ProtectionSchemeInfoBox(size, type, off));
        return ret;
    } else if(type == "schm"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        std::shared_ptr<Box> ret(new SRTPProcessBox(size, type, off, v, f));
        return ret;
    } else if(type == "sdp "){
        std::shared_ptr<Box> ret(new RTPTrackSDPHintInformation(size, type, off));
        return ret;
    } else if(type == "saiz"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        return std::shared_ptr<Box>(new SampleAuxiliaryInformationSizesBox(size, type, off, v, f));
    } else if(type == "saio"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
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
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
        unsigned int predefined = valueOfGroupOfBytes(4, off + offset + 12);
        unsigned long int handlerType = valueOfGroupOfBytes(4, off + offset + 16);
        QList <unsigned int> reserved;
        for(int i = 0; i < 3; ++ i)
            reserved.append(valueOfGroupOfBytes(4 , off + offset + 20 + 4*i ));
        QString name = stringValue(size - offset - 32, off + offset + 32);
        std::shared_ptr<Box> ret(new HandlerBox(size, type, off, v, f, predefined, handlerType, reserved, name));
        return ret;
    } else if(type == "hmhd"){
        unsigned int offset = 0;
        if(size == 1)
            offset += 8;
        unsigned int v = valueOfGroupOfBytes(1, off + offset + 8);

        QList<unsigned int> f;
        for (unsigned int i = 0; i < 3; ++ i)
            f.append(valueOfGroupOfBytes(1, off + offset + i + 9));
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

unsigned long int BoxFactory::valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}
signed long int BoxFactory::signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    long int ret = bitOperator->signedValueOfGroupOfBytes(ptr, length);
    delete[] ptr;
    return ret;
}
unsigned long int BoxFactory::valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBits(ptr, length, offset);
    unsigned long int ret = bitOperator->valueOfGroupOfBits(ptr, length);
    delete[] ptr;
    return ret;
}
QString BoxFactory::stringValue(const unsigned int & length, const unsigned long& offset) const {
    char* ptr = new char[length];
    fileService->getBytes(ptr, length, offset);
    QString ret = bitOperator->stringValue(ptr, length);
    delete[] ptr;
    return ret;
}
