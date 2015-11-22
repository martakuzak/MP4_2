#include "sampletablebox.h"

SampleTableBox::SampleTableBox(const unsigned long int& s, const QString& t, const unsigned long int& off): Box(s,t,off) {}
////////////////////////////////////////////////////////////////////////////////////////////
TimeToSampleBox::TimeToSampleBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                                 const unsigned int& v, const QList<unsigned int>& f,unsigned int ec, QList<unsigned int> sc,
                                 QList<unsigned int> sd):
    FullBox(s,t,off,v, f) ,
    entryCount(ec),
    sampleCount(sc),
    sampleDelta(sd)
{}

QStandardItemModel *TimeToSampleBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3 + (entryCount)*2, 2, 0);
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
    unsigned int index = 3;
    for(unsigned int i = 0; i < entryCount; ++i) {
        model->setData(model->index(index, 0, QModelIndex()), "SampleCount[" + QString::number(i) + "]");
        model->setData(model->index(index, 1, QModelIndex()), QString::number(sampleCount.at(i)));
        model->setData(model->index(index + 1, 0, QModelIndex()), "SampleDelta[" + QString::number(i) + "]");
        model->setData(model->index(index + 1, 1, QModelIndex()), QString::number(sampleDelta.at(i)));
        index += 2;
    }
    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
CompositionOffsetBox::CompositionOffsetBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
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
SampleDescriptionBox::SampleDescriptionBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
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
SampleSizeBox::SampleSizeBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                             const unsigned int& v, const QList<unsigned int>& f, const unsigned int &sz, const unsigned int &sc,
                             const QList<unsigned int> &es):
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
            qDebug()<<entrySize.at(i);
            model->setData(model->index(2 + i, 0, QModelIndex()), "entry_size[" + QString::number(i) + "]");
            model->setData(model->index(2 + i, 1, QModelIndex()), QString::number(entrySize.at(i)));
        }
    }
    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
CompactSampleSizeBox::CompactSampleSizeBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v,
                                           const QList<unsigned int>& f, const unsigned int &res, const unsigned int &fs,
                                           const unsigned long int& sc, const QList<unsigned int> &es):
    FullBox(s,t,off,v, f), reserved(res), fieldSize(fs), sampleCount(sc), entrySize(es)
{}
QStandardItemModel *CompactSampleSizeBox::getModel() {
    QStandardItemModel *model = new QStandardItemModel(3 + (fieldSize == 0)*sampleCount - 1, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Field size");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(fieldSize));
    model->setData(model->index(2, 0, QModelIndex()), "Sample count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(sampleCount));
    if(fieldSize == 0) {
        for (unsigned int i = 0; i<sampleCount; ++i) {
            model->setData(model->index(2 + i, 0, QModelIndex()), "entry_size[" + QString::number(i) + "]");
            model->setData(model->index(2 + i, 1, QModelIndex()), QString::number(entrySize.at(i)));
        }
    }
    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
SampleToChunkBox::SampleToChunkBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                                   const unsigned int& v, const QList<unsigned int>& f, const unsigned int &ec,
                                   const QList<unsigned int> &fc, const QList<unsigned int> &spc, const QList<unsigned int> &sdi):
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
        model->setData(model->index(3 + 3*i, 0, QModelIndex()), "first_chunk[" + QString::number(i) + "]");
        model->setData(model->index(3 + 3*i, 1, QModelIndex()), QString::number(firstChunk.at(i)));
        model->setData(model->index(4 + 3*i, 0, QModelIndex()), "samples_per_chunk[" + QString::number(i) + "]");
        model->setData(model->index(4 + 3*i, 1, QModelIndex()), QString::number(samplesPerChunk.at(i)));
        model->setData(model->index(5 + 3*i, 0, QModelIndex()), "sampleDescriptionIndex[" + QString::number(i) + "]");
        model->setData(model->index(5 + 3*i, 1, QModelIndex()), QString::number(sampleDescriptionIndex.at(i)));
    }

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
ChunkOffsetBox::ChunkOffsetBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                               const unsigned int& v, const QList<unsigned int>& f, const unsigned int &ec, const QList<unsigned int> &co):
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
        model->setData(model->index(3 + i, 0, QModelIndex()), "chunk_offset[" + QString::number(i) + "]");
        model->setData(model->index(3 + i, 1, QModelIndex()), QString::number(chunkOffset.at(i)));
    }

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
ChunkLargeOffsetBox::ChunkLargeOffsetBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
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
SyncSampleBox::SyncSampleBox(const unsigned long int& s, const QString& t, const unsigned long int& off,
                             const unsigned int& v, const QList<unsigned int>& f, const unsigned int &ec, const QList<unsigned int> sn):
    FullBox(s,t,off,v, f) ,
    entryCount(ec),
    sampleNumber(sn)
{}

QStandardItemModel *SyncSampleBox::getModel() {
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
        model->setData(model->index(3 + i, 0, QModelIndex()), "sample_number[" + QString::number(i) + "]");
        model->setData(model->index(3 + i, 1, QModelIndex()), QString::number(sampleNumber.at(i)));
    }

    return model;
}
////////////////////////////////////////////////////////////////////////////////////////////
ShadowSyncSampleBox::ShadowSyncSampleBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
////////////
DegradationPriorityBox::DegradationPriorityBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
////////////////////////////////////////////////////////////////////////////////////////////
PaddingBitsBox::PaddingBitsBox(const unsigned long int& s, const QString& t, const unsigned long int& off, const unsigned int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,v, f)
{}
