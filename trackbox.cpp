#include "trackbox.h"
///////////////////
TrackBox::TrackBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
/////////////
TrackHeaderBox::TrackHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                               const unsigned  int& v, const QList<unsigned int>& f, const unsigned long &ct, const unsigned long &mt,
                               const unsigned int &tid, const unsigned int &r1, const unsigned long &dur, const QList<unsigned int> &r2,
                               const unsigned int &lay, const unsigned int &ag, const unsigned int &vol, const unsigned int &r3,
                               const QList<unsigned long> mx, const unsigned int &wdth, const unsigned int &hght):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    creationTime(ct),
    modificationTime(mt),
    trackID(tid),
    duration(dur),
    volume(vol),
    reserved1(r1),
    reserved2(r2),
    reserved3(r3),
    layer(lay),
    alternateGroup(ag),
    width(wdth),
    height(hght),
    matrix(mx)
{}
QString TrackHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nCreation time\t\t");
    tmp.append(QString::number(creationTime));
    tmp.append("\nModification time\t");
    tmp.append(QString::number(modificationTime));
    tmp.append("\nTrack ID\t\t");
    tmp.append(QString::number(trackID));
    tmp.append("\nReserved1\t\t");
    tmp.append(QString::number(reserved1));
    tmp.append("\nDuration\t\t");
    tmp.append(QString::number(duration));
    tmp.append("\nReserved2\t\t");
    int reserved2Size = reserved2.size();
    for (int i = 0; i<reserved2Size; ++i) {
        tmp.append(QString::number(reserved2.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nLayer\t\t");
    tmp.append(QString::number(layer));
    tmp.append("\nAlternate group\t\t");
    tmp.append(QString::number(alternateGroup));
    tmp.append("\nVolume\t\t");
    tmp.append(QString::number(volume));
    tmp.append("\nReserved3\t\t");
    tmp.append(QString::number(reserved3));
    tmp.append("\nMatrix\t\t");
    int matrixSize = matrix.size();
    for (int i = 0; i<matrixSize; ++i) {
        tmp.append(QString::number(matrix.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nWidth\t\t");
    tmp.append(QString::number(width));
    tmp.append("\nHeight\t\t");
    tmp.append(QString::number(height));
    return tmp;
}
QStandardItemModel* TrackHeaderBox::getModel() {
    QStandardItemModel* model = new QStandardItemModel(15, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Creation time");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(creationTime));
    model->setData(model->index(3, 0, QModelIndex()), "Modification time");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(modificationTime));
    model->setData(model->index(4, 0, QModelIndex()), "Track ID");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(trackID));
    model->setData(model->index(5, 0, QModelIndex()), "Reserved1");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(reserved1));
    model->setData(model->index(6, 0, QModelIndex()), "Duration");
    model->setData(model->index(6, 1, QModelIndex()), QString::number(duration));
    tmp.clear();
    for(int i = 0; i < reserved2.size(); ++i) {
        tmp.append(QString::number(reserved2.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(7, 0, QModelIndex()), "Reserved2");
    model->setData(model->index(7, 1, QModelIndex()), tmp);
    model->setData(model->index(8, 0, QModelIndex()), "Layer");
    model->setData(model->index(8, 1, QModelIndex()), QString::number(layer));
    model->setData(model->index(9, 0, QModelIndex()), "Alternate group");
    model->setData(model->index(9, 1, QModelIndex()), QString::number(alternateGroup));
    model->setData(model->index(10, 0, QModelIndex()), "Volume");
    model->setData(model->index(10, 1, QModelIndex()), QString::number(volume));
    model->setData(model->index(11, 0, QModelIndex()), "Reserved3");
    model->setData(model->index(11, 1, QModelIndex()), QString::number(reserved3));
    tmp.clear();
    for(int i = 0; i < matrix.size(); ++i) {
        tmp.append(QString::number(matrix.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(12, 0, QModelIndex()), "Matrix");
    model->setData(model->index(12, 1, QModelIndex()), tmp);
    model->setData(model->index(13, 0, QModelIndex()), "Width");
    model->setData(model->index(13, 1, QModelIndex()), QString::number(width));
    model->setData(model->index(14, 0, QModelIndex()), "Height");
    model->setData(model->index(14, 1, QModelIndex()), QString::number(height));
    return model;
}
/////////////
TrackReferenceBox::TrackReferenceBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
/////////////
HandlerBox::HandlerBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                       const unsigned  int& v, const QList<unsigned int>& f, const unsigned int &pred, const unsigned int &hand,
                       const QList<unsigned int> &res, const QString &nam):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    predefined(pred),
    handlerType(hand),
    reserved(res),
    name(nam)
{}
QString HandlerBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nPredefined\t\t");
    tmp.append(QString::number(predefined));
    tmp.append("\nHandler type\t\t");
    tmp.append(QString::number(handlerType));
    tmp.append("\nReserved\t\t");
    int resSize = reserved.size();
    for (int i = 0; i<resSize; ++i) {
        tmp.append(QString::number(reserved.at(i)));
        tmp.append(" | ");
    }
    tmp.append("\nName\t\t");
    tmp.append(name);
    return tmp;
}
QStandardItemModel* HandlerBox::getModel() {
    QStandardItemModel* model = new QStandardItemModel(6, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Predefined");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(predefined));
    model->setData(model->index(3, 0, QModelIndex()), "Handler type");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(handlerType));
    tmp.clear();
    for(int i = 0; i < reserved.size(); ++i) {
        tmp.append(QString::number(reserved.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(4, 0, QModelIndex()), "Reserved");
    model->setData(model->index(4, 1, QModelIndex()), tmp);
    model->setData(model->index(5, 0, QModelIndex()), "Name");
    model->setData(model->index(5, 1, QModelIndex()), name);

    return model;
}
/////////////
TrackExtendsBox::TrackExtendsBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                 const unsigned  int& v, const QList<unsigned int>& f, const unsigned int& tid, const unsigned int& dsdi,
                                 const unsigned int& dsd,const unsigned int& dss, const unsigned int& dsf):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    getTrackID(tid),
    defaultSampleDescriptionIndex(dsdi),
    defaultSampleDuration(dsd),
    defaultSampleSize(dss),
    defaultSampleFlags(dsf)
{}
QString TrackExtendsBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nTrack ID\t\t");
    tmp.append(QString::number(getTrackID));
    tmp.append("\nDefault Sample Description Index\t");
    tmp.append(QString::number(defaultSampleDescriptionIndex));
    tmp.append("\nDefault Sample Duration\t");
    tmp.append(QString::number(defaultSampleDuration));
    tmp.append("\nDefault Sample Size\t");
    tmp.append(QString::number(defaultSampleSize));
    tmp.append("\nDefault Sample Flags\t");
    tmp.append(QString::number(defaultSampleFlags));
    return tmp;
}
QStandardItemModel* TrackExtendsBox::getModel() {
    QStandardItemModel* model = new QStandardItemModel(7, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Track ID");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(getTrackID));
    model->setData(model->index(3, 0, QModelIndex()), "Default sample description index");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(defaultSampleDescriptionIndex));
    model->setData(model->index(4, 0, QModelIndex()), "Default sample duration");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(defaultSampleDuration));
    model->setData(model->index(5, 0, QModelIndex()), "Default sample size");
    model->setData(model->index(5, 1, QModelIndex()), QString::number(defaultSampleSize));
    model->setData(model->index(6, 0, QModelIndex()), "Default sample flags");
    model->setData(model->index(6, 1, QModelIndex()), QString::number(defaultSampleFlags));

    return model;
}
///////////////
TrackFragmentBox::TrackFragmentBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e): Box(s,t,off,e) {}
///////////////
TrackFragmentHeaderBox::TrackFragmentHeaderBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                               const unsigned  int &  e, const unsigned  int& v, const QList<unsigned int>& f,
                                               const unsigned long int& tid, const unsigned long &bdo, const unsigned long &dsdi,
                                               const unsigned long &dsd, const unsigned long &dss, const unsigned long &dsf):
    FullBox(s,t,off,e, v, f),
    getTrackID(tid),
    baseDataOffset(bdo),
    sampleDescriptionIndex(dsdi),
    defaultSampleDuration(dsd),
    defaultSampleSize(dss),
    defaultSampleFlags(dsf)
{}
QString TrackFragmentHeaderBox::getInfo() {
    QString tmp("");
    tmp.append(FullBox::getInfo());
    tmp.append("\nTrack ID\t\t");
    tmp.append(QString::number(getTrackID));
    if (getSize() >= 24) {
        tmp.append(("\nBase Data Offset\t"));
        tmp.append(QString::number(baseDataOffset));
        if (getSize() >= 28) {
            tmp.append("\nSample Description Index\t");
            tmp.append(QString::number(sampleDescriptionIndex));
            if (getSize() >=32 ) {
                tmp.append("\nDefault Sample Duration\t");
                tmp.append(QString::number(defaultSampleDuration));
                if (getSize() >=36 ) {
                    tmp.append("\nDefault Sample Size\t");
                    tmp.append(QString::number(defaultSampleSize));
                    if (getSize() >= 40) {
                        tmp.append("\nDefault Sample Flags\t");
                        tmp.append(QString::number(defaultSampleFlags));
                    }
                }
            }
        }
    }
    return tmp;
}
QStandardItemModel* TrackFragmentHeaderBox::getModel() {
    int row = 0;
    if(getSize() < 24)
        row = 3;
    else if(getSize() < 28)
        row = 4;
    else if(getSize() < 32)
        row = 5;
    else if(getSize() < 36)
        row = 5;
    else if(getSize() < 40)
        row = 5;
    else
        row = 6;
    QStandardItemModel* model = new QStandardItemModel(row, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");

    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Track ID");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(getTrackID));
    if (getSize() >= 24) {
        model->setData(model->index(3, 0, QModelIndex()), "Base data offset");
        model->setData(model->index(3, 1, QModelIndex()), QString::number(baseDataOffset));
        if (getSize() >= 28) {
            model->setData(model->index(4, 0, QModelIndex()), "Sample description index");
            model->setData(model->index(4, 1, QModelIndex()), QString::number(sampleDescriptionIndex));
            if (getSize() >=32 ) {
                model->setData(model->index(5, 0, QModelIndex()), "Default sample duration");
                model->setData(model->index(5, 1, QModelIndex()), QString::number(defaultSampleDuration));
                if (getSize() >=36 ) {
                    model->setData(model->index(6, 0, QModelIndex()), "Default sample size");
                    model->setData(model->index(6, 1, QModelIndex()), QString::number(defaultSampleSize));
                    if (getSize() >= 40) {
                        model->setData(model->index(7, 0, QModelIndex()), "Default sample flags");
                        model->setData(model->index(7, 1, QModelIndex()), QString::number(defaultSampleFlags));
                    }
                }
            }
        }
    }

    return model;
}
///////////////
TrackRunBox::TrackRunBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                         const unsigned  int& v, const QList<unsigned int>& f, const unsigned long &sc, const long &dof,
                         const unsigned int &fsf, const QList<unsigned long> &sd, const QList<unsigned long> &ss,
                         const QList<unsigned int> &sf, const QList<unsigned long> &scto):
    FullBox(s,t,off,e, v, f) ,
    version(v),
    flags(f),
    sampleCount(sc),
    dataOffset(dof),
    firstSampleFlags(fsf),
    sampleDuration(sd),
    sampleSize(ss),
    sampleFlags(sf),
    sampleCompositionTimeOffset(scto)
{}
QString TrackRunBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nSample count\t\t");
    tmp.append(QString::number(sampleCount));
    tmp.append("\nData offset\t\t");
    tmp.append(QString::number(dataOffset));
    tmp.append("\nFirst sample flags\t");
    tmp.append(QString::number(firstSampleFlags));
    if(!sampleDuration.empty()) {
        QList<unsigned long int>::iterator i;
        int index = 0;
        for (i = sampleDuration.begin(); i !=sampleDuration.end(); ++i) {
            tmp.append("\nSample duration[");
            tmp.append(QString::number(index));
            tmp.append("]\t\t");
            tmp.append(QString::number(sampleDuration.at(index)));
            index ++;
        }
    }
    else if(!sampleSize.empty()) {
        QList<unsigned long int>::iterator i;
        int index = 0;
        for (i = sampleSize.begin(); i !=sampleSize.end(); ++i) {
            tmp.append("\nSample size[");
            tmp.append(QString::number(index));
            tmp.append("]\t\t");
            tmp.append(QString::number(sampleSize.at(index)));
            index ++;
        }
    }
    else if(!sampleFlags.empty()) {
        QList<unsigned int>::iterator i;
        int index = 0;
        for (i = sampleFlags.begin(); i !=sampleFlags.end(); ++i) {
            tmp.append("\nSample flags[");
            tmp.append(QString::number(index));
            tmp.append("]\t\t");
            tmp.append(QString::number(sampleFlags.at(index)));
            index ++;
        }
    }
    if(!sampleCompositionTimeOffset.empty()) {
        QList<unsigned long int>::iterator i;
        int index = 0;
        for (i = sampleCompositionTimeOffset.begin(); i !=sampleCompositionTimeOffset.end(); ++i) {
            tmp.append("\nSample composition time offset[");
            tmp.append(QString::number(index));
            tmp.append("]\t");
            tmp.append(QString::number(sampleCompositionTimeOffset.at(index)));
            index ++;
        }
    }
    return tmp;
}
QStandardItemModel* TrackRunBox::getModel() {
    QStandardItemModel* model = new QStandardItemModel(5 + sampleDuration.size() + sampleSize.size() +
                                                       sampleFlags.size() + sampleCompositionTimeOffset.size(),
                                                       2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");
    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Sample count");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(sampleCount));
    model->setData(model->index(3, 0, QModelIndex()), "Data offset");
    model->setData(model->index(3, 1, QModelIndex()), QString::number(dataOffset));
    model->setData(model->index(4, 0, QModelIndex()), "First sample flags");
    model->setData(model->index(4, 1, QModelIndex()), QString::number(firstSampleFlags));
    int k = 0;
    tmp.clear();
    if(!sampleDuration.empty()) {
        QList<unsigned long int>::iterator i;
        int index = 0;
        for (i = sampleDuration.begin(); i !=sampleDuration.end(); ++i) {
            model->setData(model->index(5 + index, 0, QModelIndex()), "Sample duration[" +
                           QString::number(index) + "]");
            model->setData(model->index(5 + index, 1, QModelIndex()),
                           QString::number(sampleDuration.at(index)));
            index ++;
        }
        tmp.clear();
        k+= index;
    }
    if(!sampleSize.empty()) {
        QList<unsigned long int>::iterator i;
        int index = 0;
        for (i = sampleSize.begin(); i !=sampleSize.end(); ++i) {
            model->setData(model->index(5 + k + index, 0, QModelIndex()), "Sample size[" +
                           QString::number(index) + "]");
            model->setData(model->index(5 + k + index, 1, QModelIndex()),
                           QString::number(sampleSize.at(index)));
            index ++;
        }
        tmp.clear();
        k+= index;
    }
    if(!sampleFlags.empty()) {
        QList<unsigned int>::iterator i;
        int index = 0;
        for (i = sampleFlags.begin(); i !=sampleFlags.end(); ++i) {
            model->setData(model->index(5 + k + index, 0, QModelIndex()), "Sample flags[" +
                           QString::number(index) + "]");
            model->setData(model->index(5 + k + index, 1, QModelIndex()),
                           QString::number(sampleFlags.at(index)));
            index ++;
        }
        tmp.clear();
        k+= index;
    }
    else if(!sampleCompositionTimeOffset.empty()) {
        QList<unsigned long int>::iterator i;
        int index = 0;
        for (i = sampleCompositionTimeOffset.begin(); i !=sampleCompositionTimeOffset.end(); ++i) {
            model->setData(model->index(5 + k + index, 0, QModelIndex()), "Sample composition time offset[" +
                           QString::number(index) + "]");
            model->setData(model->index(5 + k + index, 1, QModelIndex()),
                           QString::number(sampleCompositionTimeOffset.at(index)));
            index ++;
        }
        tmp.clear();
        k+= index;
    }

    return model;
}
///////////////
TrackFragmentRandomAccessBox::TrackFragmentRandomAccessBox(const unsigned  int& s, const QString& t, const unsigned long int& off, const unsigned  int &  e,
                                                           const unsigned  int& v, const QList<unsigned int>& f):
    FullBox(s,t,off,e, v, f)
{}
///////////////
TrackFragmentBaseMediaDecodeTimeBox::TrackFragmentBaseMediaDecodeTimeBox(const unsigned  int& s, const QString& t, const unsigned long int& off,
                                                                         const unsigned  int &  e, const unsigned  int& v,
                                                                         const QList<unsigned int>& f, const unsigned long &bmdt):
    FullBox(s,t,off,e, v, f),
    baseMediaDecodeTime(bmdt)
{}
QString TrackFragmentBaseMediaDecodeTimeBox::getInfo() {
    QString tmp;
    tmp.append(FullBox::getInfo());
    tmp.append("\nBase Media Decode Time\t");
    tmp.append(QString::number(baseMediaDecodeTime));
    return tmp;
}
QStandardItemModel* TrackFragmentBaseMediaDecodeTimeBox::getModel() {
    QStandardItemModel* model = new QStandardItemModel(3, 2, 0);
    model->setData(model->index(0, 0, QModelIndex()), "Version");
    model->setData(model->index(0, 1, QModelIndex()), FullBox::getVersion());
    model->setData(model->index(1, 0, QModelIndex()), "Flags");
    QString tmp("");
    for(int i = 0; i < flags.size(); ++i) {
        tmp.append(QString::number(flags.at(i)));
        tmp.append(" | ");
    }
    model->setData(model->index(1, 1, QModelIndex()), tmp);
    model->setData(model->index(2, 0, QModelIndex()), "Base Media Decode Time");
    model->setData(model->index(2, 1, QModelIndex()), QString::number(baseMediaDecodeTime));

    return model;
}
