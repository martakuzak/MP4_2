#include "sampletablebox.h"

SampleTableBox::SampleTableBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e): Box(s,t,off,e) {}
/////////////
/////////////
TimeToSampleBox::TimeToSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                 const unsigned int& v, const QList<unsigned int>& f,unsigned int ec, QList<unsigned int> sc,
                                 QList<unsigned int> sd):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    entryCount(ec),
    sampleCount(sc),
    sampleDelta(sd)
{}
QString TimeToSampleBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    tmp.append("\nSample count\t\t");
    for(unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(sampleCount.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nSample delta\t\t");
    for(unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(sampleDelta.at(i)));
        tmp.append(" | ");
    }
    return tmp;
}

/////////////
CompositionOffsetBox::CompositionOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                           const unsigned int& v, const QList<unsigned int>& f, unsigned int ec, QList<unsigned int> sc,
                                           QList<unsigned int> sd):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    entryCount(ec),
    sampleCount(sc),
    sampleOffset(sd)
{}
QString CompositionOffsetBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nSample count\t\t");
    for(unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(sampleCount.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nSample offset\t\t");
    for(unsigned int i = 0; i<entryCount; ++i) {
        tmp.append(QString::number(sampleOffset.at(i)));
        tmp.append(" | ");
    }
    return tmp;
}
/////////////
SampleDescriptionBox::SampleDescriptionBox(const unsigned int &s, const QString& t, const unsigned long int& off, const unsigned int &e,
                                           const unsigned int& v,const QList<unsigned int>& f, const unsigned int &ec):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    entryCount(ec)
{}
QString SampleDescriptionBox::getInfo(){
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    return tmp;
}

/////////////
SampleSizeBox::SampleSizeBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                             const unsigned int& v, const QList<unsigned int>& f, const unsigned long &sz, const unsigned long &sc,
                             const QList<unsigned long> &es):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    sampleSize(sz),
    sampleCount(sc),
    entrySize(es)
{}
QString SampleSizeBox::getInfo(){
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nSample size\t\t");
    tmp.append(QString::number(sampleSize));
    tmp.append("\nSample count\t\t");
    tmp.append(QString::number(sampleCount));
    if(sampleSize == 0) {
        for (unsigned int i = 0; i<sampleCount; ++i) {
            tmp.append("\nentry_size[");
            tmp.append(QString::number(i));
            tmp.append("]\t\t");
            tmp.append(QString::number(entrySize.at(i)));
        }
    }
    return tmp;
}

/////////////
CompactSampleSizeBox::CompactSampleSizeBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
/////////////
SampleToChunkBox::SampleToChunkBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                   const unsigned int& v, const QList<unsigned int>& f, const unsigned long &ec,
                                   const QList<unsigned long> &fc, const QList<unsigned long> &spc, const QList<unsigned long> &sdi):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    entryCount(ec),
    firstChunk(fc),
    samplesPerChunk(spc),
    sampleDescriptionIndex(sdi)
{}

QString SampleToChunkBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append("\nfirst_chunk[");
        tmp.append(QString::number(i));
        tmp.append("]\t\t");
        tmp.append(QString::number(firstChunk.at(i)));
        tmp.append("\nsamples_per_chunk[");
        tmp.append(QString::number(i));
        tmp.append("]\t");
        tmp.append(QString::number(samplesPerChunk.at(i)));
        tmp.append("\nsample_description_index[");
        tmp.append(QString::number(i));
        tmp.append("]\t");
        tmp.append(QString::number(sampleDescriptionIndex.at(i)));
    }
    return tmp;
}

/////////////
ChunkOffsetBox::ChunkOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                               const unsigned int& v, const QList<unsigned int>& f, const unsigned long &ec, const QList<unsigned long> &co):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    entryCount(ec),
    chunkOffset(co)
{}
QString ChunkOffsetBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append("\nchunk_offset[");
        tmp.append(QString::number(i));
        tmp.append("]\t");
        if(i < 10)
            tmp.append("\t");
        tmp.append(QString::number(chunkOffset.at(i)));
    }
    return tmp;
}

/////////////
ChunkLargeOffsetBox::ChunkLargeOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                                         const unsigned int& v, const QList<unsigned int>& f, const unsigned long int &ec,
                                         const QList<unsigned long int> &co):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    entryCount(ec),
    chunkOffset(co)
{}
QString ChunkLargeOffsetBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append("\nchunk_offset[");
        tmp.append(QString::number(i));
        tmp.append("]\t");
        if(i < 10)
            tmp.append("\t");
        tmp.append(QString::number(chunkOffset.at(i)));
    }
    return tmp;
}
/////////////
SyncSampleBox::SyncSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e,
                             const unsigned int& v, const QList<unsigned int>& f, const unsigned long &ec, const QList<unsigned long> sn):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    entryCount(ec),
    sampleNumber(sn)
{}
QString SyncSampleBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nEntry count\t\t");
    tmp.append(QString::number(entryCount));
    for (unsigned int i = 0; i<entryCount; ++i) {
        tmp.append("\nsample_number[");
        tmp.append(QString::number(i));
        tmp.append("]\t");
        tmp.append(QString::number(sampleNumber.at(i)));
    }
    return tmp;
}
/////////////
ShadowSyncSampleBox::ShadowSyncSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
////////////
DegradationPriorityBox::DegradationPriorityBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
///////////////
PaddingBitsBox::PaddingBitsBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int &  e, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f)
{}
