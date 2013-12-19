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
    QList <Period> periods;
public:
    MPD();
    void addPeriod();
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
    QList<Period> getPeriods() const;
    void setPeriods(const QList<Period> &value);
};

class MPDWriter {
private:
    QString xmlHeader;// = "<?xml version=\"1.0\"?>";
    QXmlStreamWriter* stream;
    QString filename;
    QFile* mpdFile;
    //TreeModel* model;
    MPD* mpd;
    ProgramInformation* programInformation;
    Period* period;
    SegmentList* slist;
    TreeModel* dashModel;
    TreeModel* model;

    QString getDuration();
    QString getHMSFormat(const double& value);
    void setMPD();
    void setProgramInformation();
    void setSegmentList();
public:
    MPDWriter(const QString& fn, TreeModel *mod);
    void writeMPD(QFile* file);
};
/*QFile* file = new QFile("D://plik.xml");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    //m_file.open(QIODevice::WriteOnly | QIODevice::Text);

    QXmlStreamWriter stream(file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("bookmark");
        stream.writeAttribute("href", "http://qt-project.org/");
        stream.writeTextElement("title", "Qt Project");
        stream.writeEndElement(); // bookmark

        stream.writeEndDocument();
        file->close();*/

#endif // MPD_H
