#ifndef MPD_H
#define MPD_H

#include <QString>
#include <QFile>
#include <QXmlStreamWriter>
#include <QList>
#include "box.h"
#include "period.h"
#include "segmentlist.h"
#include "treemodel.h"
#include "analyzer.h"

//profiles="urn:mpeg:dash:profile:isoff-main:2011">
class TreeModel;

class ProgramInformation {
public:
    QString getLang() const;
    void setLang(const QString &value);

    QString getMoreInformationURL() const;
    void setMoreInformationURL(const QString &value);

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getSource() const;
    void setSource(const QString &value);

    QString getCopyright() const;
    void setCopyright(const QString &value);

private:
    QString lang;
    QString moreInformationURL;
    //
    QString title;
    QString source;
    QString copyright;
};

class MPD {
private:
    QString type;
    QString xmlns;
    QString minBufferTime;
    QString mediaPresentationDuration;
    QString profiles;
    QList <Period*> periods;
public:
    MPD();
    void addPeriod();
    void addPeriod(Period* period);
    QString getType() const;
    void setType(const QString &value);
    QString getXmlns() const;
    void setXmlns(const QString &value);
    QString getMinBufferTime() const;
    void setMinBufferTime(const QString &value);
    QString getMediaPresentationDuration() const;
    void setMediaPresentationDuration(const QString &value);
    QString getProfiles() const;
    void setProfiles(const QString &value);
    void write(QXmlStreamWriter *stream);
    QList<Period*> getPeriods() const;
    void setPeriods(const QList<Period *> &value);
};

class MPDWriter {
private:
    QString xmlHeader;// = "<?xml version=\"1.0\"?>";
    QXmlStreamWriter* stream;
    QString filename;
    QFile* mpdFile;
    //TreeModel* model;
    MPD* mpd;
    TreeModel* dashModel;
    TreeModel* model;

    QString getDuration();
    QString getHMSFormat(const double& value);
    void setMPD();
    //void setProgramInformation();
    SegmentList *setSegmentList();
    BaseURL* setBaseURL();
    Representation* setRepresentation();
    AdaptationSet* setAdaptationSet();
    Period* setPeriod();
public:
    MPDWriter(const QString& fn, TreeModel *mod);
    void init();
    void writeMPD(QFile* file);
};


#endif // MPD_H
