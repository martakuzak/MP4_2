#ifndef SEGMENTLIST_H
#define SEGMENTLIST_H

#include <QString>
#include <QList>
#include <QXmlStreamWriter>

class Initialization {
private:
    //attrs
    QString range;
    QString sourceURL;
public:
    Initialization();
//    Initialization(const QString& range, const QString& sURL);
    void write(QXmlStreamWriter *stream);
    QString getRange() const;
    void setRange(const QString &value);
};

class SegmentURL {
private:
    //attrs
    QString media;
    QString mediaRange;
    QString indexRange;
    //QString index;
public:
    SegmentURL();
//    SegmentURL(const QString& media, const QString& mediaRange, const QString& indexRange);
    void write(QXmlStreamWriter *stream);
    QString getMediaRange() const;
    void setMediaRange(const QString &value);
    QString getIndexRange() const;
    void setIndexRange(const QString &value);
};

class SegmentList {
private:
    //attrs
    unsigned int timescale;
    unsigned long int duration;
    Initialization* initialization;
    QList<SegmentURL*> segmentURLs;
public:
    SegmentList();
//    SegmentList(const unsigned int& ts, const unsigned long int& dur, const Initialization& init, const QList<SegmentURL> surl);
    void write(QXmlStreamWriter *stream);
    void addSegmentURL(const QString &mediaRange, const QString &indexRange);
    void addSegmentsURL();
    Initialization *getInitialization() const;
    void setInitialization(Initialization *value);
};



#endif // SEGMENTLIST_H
