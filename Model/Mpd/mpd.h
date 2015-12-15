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
/*!
  *\brief The ProgramInformation class represents ProgramInformation element of Media Presentation Description xml file.
  * It's been not used yet.
  *\see ISO/IEC 23009-1:2012 Information technology – Dynamic adaptive streaming over HTTP (DASH) – Part 1: Media presentation description and segment formats
 */
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
/*!
  *\brief The MPD class represents MPD element of Media Presentation Description xml file.
  *\see ISO/IEC 23009-1:2012 Information technology – Dynamic adaptive streaming over HTTP (DASH) – Part 1: Media presentation description and segment formats
 */
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
  * contains methods that create and write MPD file.
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
    MPDWriter();
    /*!
     * \brief addRepresentation adds representation to MPD data model
     * \param path path to original file of representation
     * \param fn filename (without path) to original representation file
     * \param oneFile indicated wheter all the media data segments of each representation are located
     * in one file or not
     */
    void addRepresentation(const QString &path, const QString &fn, const bool &oneFile);
    /*!
     * \brief init sets init information (about presentation).
     * The method shall be called before write(...)
     * \param oneFile indicated wheter all the media data segments of each representation are located
     * in one file or not
     */
    void init(bool oneFile);
    /*!
     * \brief setDashPath
     * \param dashPath path to created files with media data segments
     */
    void setDashPath(const QString& dashPath);
    /*!
      *\brief write
      * Writes MPD file
      *\param url URL address where all the files will be located during transmission
     */
    void writeMPD(const QString &url);
    QString getOriginalFileName() const;
    void setOriginalFileName(const QString &value);
private:
    AdaptationSet *setAdaptationSet();
    Period *setPeriod();
    unsigned int getRepBandwidth(bool oneFile, SegmentList *slist = new SegmentList());
    QString getHMSFormat(const double& value);
    QString getDuration();
    unsigned int *getDimensions();
    void setMPD(const QString &url);
    SegmentList *setSegmentList(bool oneFile, const QString &dashName = "");
};

#endif // MPD_H
