#include "sampletablebox.h"

SampleTableBox::SampleTableBox(const unsigned int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
////////////////////////////////////////////////////////////////////////////////////////////
TimeToSampleBox::TimeToSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                                 const unsigned int& v, const QList<unsigned int>& f,unsigned int ec, QList<unsigned int> sc,
                                 QList<unsigned int> sd):
    FullBox(s,t,off,v, f) ,


    entryCount(ec),
    sampleCount(sc),
    sampleDelta(sd)
{}

QStandardItemModel *TimeToSampleBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(5, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));
    model->setData(model->index(3, 0, QModelIndex()), "Sample count");
    tmp.clear();
    for(unsigned int i = 0; i < entryCount; ++i) {
        tmp.append(QString::number(sampleCount.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(3, 1, QModelIndex()), tmp);
    model->setData(model->index(4, 0, QModelIndex()), "Sample delta");
    tmp.clear();
    for(unsigned int i = 0; i < entryCount; ++i) {
        tmp.append(QString::number(sampleDelta.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(4, 1, QModelIndex()), tmp);

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
CompositionOffsetBox::CompositionOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                                           const unsigned int& v, const QList<unsigned int>& f, unsigned int ec, QList<unsigned int> sc,
                                           QList<unsigned int> sd):
    FullBox(s,t,off,v, f) ,


    entryCount(ec),
    sampleCount(sc),
    sampleOffset(sd)
{}

QStandardItemModel *CompositionOffsetBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(5, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));
    model->setData(model->index(3, 0, QModelIndex()), "Sample count");
    tmp.clear();
    for(unsigned int i = 0; i < entryCount; ++i) {
        tmp.append(QString::number(sampleCount.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(3, 1, QModelIndex()), tmp);
    model->setData(model->index(4, 0, QModelIndex()), "Sample offset");
    tmp.clear();
    for(unsigned int i = 0; i < entryCount; ++i) {
        tmp.append(QString::number(sampleOffset.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(4, 1, QModelIndex()), tmp);

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
SampleDescriptionBox::SampleDescriptionBox(const unsigned int &s, const QString& t, const unsigned long int& off,
                                           const unsigned int& v, const QList<unsigned int>& f, const unsigned int &ec):
    FullBox(s,t,off,v, f) ,


    entryCount(ec)
{}

QStandardItemModel *SampleDescriptionBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
SampleSizeBox::SampleSizeBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                             const unsigned int& v, const QList<unsigned int>& f, const unsigned long &sz, const unsigned long &sc,
                             const QList<unsigned long> &es):
    FullBox(s,t,off,v, f) ,


    sampleSize(sz),
    sampleCount(sc),
    entrySize(es)
{}

QStandardItemModel *SampleSizeBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3 + (sampleSize == 0)*sampleCount - 1, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Sample size");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(sampleSize));
    model->setData(model->index(2, 0, QModelIndex()), "Sample count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(sampleCount));
    if(sampleSize == 0) {
        for (unsigned int i = 0; i<sampleCount; ++i) {
            model->setData(model->index(2 + i, 0, QModelIndex()), "entry_size[" + QString::number(i) + "]");
            model->setData(model->index(2 + i, 1, QModelIndex()), QString::number(entrySize.at(i)));
        }
    }
    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
CompactSampleSizeBox::CompactSampleSizeBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
////////////////////////////////////////////////////////////////////////////////////////////
SampleToChunkBox::SampleToChunkBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                                   const unsigned int& v, const QList<unsigned int>& f, const unsigned long &ec,
                                   const QList<unsigned long> &fc, const QList<unsigned long> &spc, const QList<unsigned long> &sdi):
    FullBox(s,t,off,v, f),
    entryCount(ec),
    firstChunk(fc),
    samplesPerChunk(spc),
    sampleDescriptionIndex(sdi)
{}

QStandardItemModel *SampleToChunkBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3 + entryCount*3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");
    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));

    for (unsigned int i = 0; i<entryCount; ++i) {
        model->setData(model->index(2 + 3*i, 0, QModelIndex()), "first_chunk[" + QString::number(i) + "]");
        model->setData(model->index(2 + 3*i, 1, QModelIndex()), QString::number(firstChunk.at(i)));
        model->setData(model->index(3 + 3*i, 0, QModelIndex()), "samples_per_chunk[" + QString::number(i) + "]");
        model->setData(model->index(3 + 3*i, 1, QModelIndex()), QString::number(samplesPerChunk.at(i)));
        model->setData(model->index(4 + 3*i, 0, QModelIndex()), "sampleDescriptionIndex[" + QString::number(i) + "]");
        model->setData(model->index(4 + 3*i, 1, QModelIndex()), QString::number(sampleDescriptionIndex.at(i)));
    }

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
ChunkOffsetBox::ChunkOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                               const unsigned int& v, const QList<unsigned int>& f, const unsigned long &ec, const QList<unsigned long> &co):
    FullBox(s,t,off,v, f) ,


    entryCount(ec),
    chunkOffset(co)
{}

QStandardItemModel *ChunkOffsetBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3 + entryCount, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");
    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));

    for (unsigned int i = 0; i<entryCount; ++i) {
        model->setData(model->index(2 + i, 0, QModelIndex()), "chunk_offset[" + QString::number(i) + "]");
        model->setData(model->index(2 + i, 1, QModelIndex()), QString::number(chunkOffset.at(i)));
    }

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
ChunkLargeOffsetBox::ChunkLargeOffsetBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                                         const unsigned int& v, const QList<unsigned int>& f, const unsigned long int &ec,
                                         const QList<unsigned long int> &co):
    FullBox(s,t,off,v, f) ,


    entryCount(ec),
    chunkOffset(co)
{}

QStandardItemModel *ChunkLargeOffsetBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3 + entryCount, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");
    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));

    for (unsigned int i = 0; i<entryCount; ++i) {
        model->setData(model->index(2 + i, 0, QModelIndex()), "chunk_offset[" + QString::number(i) + "]");
        model->setData(model->index(2 + i, 1, QModelIndex()), QString::number(chunkOffset.at(i)));
    }

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
SyncSampleBox::SyncSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off,
                             const unsigned int& v, const QList<unsigned int>& f, const unsigned long &ec, const QList<unsigned long> sn):
    FullBox(s,t,off,v, f) ,


    entryCount(ec),
    sampleNumber(sn)
{}

QStandardItemModel *SyncSampleBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3 + entryCount*3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");
    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Entry count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(entryCount));

    for (unsigned int i = 0; i<entryCount; ++i) {
        model->setData(model->index(2 + i, 0, QModelIndex()), "sample_number[" + QString::number(i) + "]");
        model->setData(model->index(2 + i, 1, QModelIndex()), QString::number(sampleNumber.at(i)));
    }

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
ShadowSyncSampleBox::ShadowSyncSampleBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
////////////
DegradationPriorityBox::DegradationPriorityBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
////////////////////////////////////////////////////////////////////////////////////////////
PaddingBitsBox::PaddingBitsBox(const unsigned int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
