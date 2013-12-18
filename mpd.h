#ifndef MPD_H
#define MPD_H

#include <QString>
#include <QFile>
#include <QXmlStreamWriter>
#include "period.h"
#include "segmentlist.h"
//#include "treemodel.h"

//profiles="urn:mpeg:dash:profile:isoff-main:2011">

class MPD
{
private:
    QString type;
    QString xmlns;
    QString minBufferTime;
    QString mediaPresentationDuration;
    QString profiles;
public:
    MPD();
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
};

class MPDWriter {
private:
    QString xmlHeader;// = "<?xml version=\"1.0\"?>";
    QXmlStreamWriter* stream;
    QString filename;
    QFile* mpdFile;
    //TreeModel* model;
    MPD* mpd;
    Period* period;
public:
    MPDWriter(const QString& fn);
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
