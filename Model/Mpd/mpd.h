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
public:
    void addRepresentation(const QString &fn, const bool &oneFile);
    void setDashPath(const QString& dashPath);
    SegmentList *setSegmentList(bool oneFile);
    void init(bool oneFile);
    void writeMPD(bool oneFile, const QString &url);

//private:
//    QString xmlHeader;// = "<?xml version=\"1.0\"?>";
//    QXmlStreamWriter *stream;
//    /*!
//      *\brief fileName
//     */
//    QString fileName;
//    QString path;
//    unsigned int segmentsNum;
//    QFile *mpdFile;
//    //TreeModel *model;
//    MPD *mpd;
//    TreeModel *dashModel;
//    TreeModel *model;
//    QList<Representation*> representations;

    QString getDuration();
    unsigned int *getDimensions();
    QString getHMSFormat(const double& value);
    void setMPD(bool oneFile, const QString &url);
//    //void setProgramInformation();
//    SegmentList *setSegmentList(bool oneFile);
//    BaseURL *setBaseURL(const QString &url);
//    Representation *setRepresentation(bool oneFile);
    AdaptationSet *setAdaptationSet();
    Period *setPeriod();
//public:
//    /*!
//      *\brief MPDWriter
//      *\param fn name of mp4 dash file
//      *\param mod model of mp4 original file
//     */
//    MPDWriter(const QString &path, const QString& fn, TreeModel *mod, const QString& dt);
//    /*!
//      *\brief init
//      *Creates tree model of mp4 dash file
//     */
//    void init(bool b);
//    /*!
//      *\brief writeMPD
//      *Writes Media Description File
//      *\param file Media Presentation Description file that is created
//     */
//    void writeMPD(QFile *file, bool oneFile);
//    void addRepresentation(const QString& fn, const bool& oneFile);
    QString getOriginalFileName() const;
    void setOriginalFileName(const QString &value);
};


#endif // MPD_H
