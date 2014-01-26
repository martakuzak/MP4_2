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
private:
    QString lang;
    QString moreInformationURL;
    //
    QString title;
    QString source;
    QString copyright;
public:
    ProgramInformation();

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
};

class MPD {
private:
    QString type;
    QString xmlns;
    QString minBufferTime;
    QString mediaPresentationDuration;
    QString profiles;
    QList <Period*> periods;
    BaseURL *baseURL;
public:
    MPD();
    /*!
      *\brief write
      *Writes MPD vertex into Media Presentation Description file
      *\param stream stream of the MPD file
     */
    void write(QXmlStreamWriter *stream);
    void addPeriod();
    void addPeriod(Period *period);
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
    QList<Period*> getPeriods() const;
    void setPeriods(const QList<Period *> &value);
    BaseURL *getBaseURL() const;
    void setBaseURL(const QString &url);
};

/*!
  *\brief The MPDWriter class
 */
class MPDWriter {
private:
    QList<Representation*> representations;
    QString dashPath;
    TreeModel *dashModel;
    TreeModel *originalModel;
    QString originalFileName;
    MPD *mpd;
    bool segmentList; //InitializationSegment in SegmentList (true), SegmentBase (false)
public:
    MPDWriter();
    void addRepresentation(const QString &path, const QString &fn, const bool &oneFile);
    void init(bool oneFile, bool slist);
    void writeMPD(bool oneFile, const QString &url);

    AdaptationSet *setAdaptationSet();
    Period *setPeriod();

    QString getOriginalFileName() const;
    void setOriginalFileName(const QString &value);
    void setDashPath(const QString& dashPath);
private:
    unsigned int getRepBandwidth(bool oneFile, const QString &dashName = "", SegmentList *slist = new SegmentList());
    QString getHMSFormat(const double& value);
    QString getDuration();
    unsigned int *getDimensions();
    void setMPD(const QString &url);
    SegmentList *setSegmentList(bool oneFile, const QString &dashName = "");
};


#endif // MPD_H
