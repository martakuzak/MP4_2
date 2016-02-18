#ifndef DASHPROXY_H
#define DASHPROXY_H

#include "dashcreator.h"
#include "mpd.h"
#include "treemodel.h"
#include "filebitoperator.h"

class TreeModel;
class DashCreator;
class MPDWriter;

/*!
  *\brief The DashWrapper class
  * provides methods that adapts DashCreator and MPDWriter to Controller interface.
  * Using this class MP4 files can be easily converted to forms appropriate to DASH streaming and MPD file
  * can easily generated.
 */
class DashWrapper {
private:
    /*!
      *\brief catalog catalog for all dash files
     */
    QString catalog;
    /*!
      *\brief path path to catalog
     */
    QString path;
    /*!
      *\brief fileName name of the file that is transformed (without path)
     */
    QString fileName;
    /*!
      *\brief mpdWriter
     */
    MPDWriter *mpdWriter;
public:
    DashWrapper();
    ~DashWrapper();
    /*!
     * \brief setFileProp
     * \param fullPath
     */
    void setFileProp(const QString& fullPath);
    /*!
     * \brief writeFile generates one file with all the segments of the presentation
     * \param date date - used to name catalof for generated file
     * \param name full name of the original file which contains presentation (with path)
     * \param maxSampleNum max sample number in the segment
     * \return true if file was successfully written
     */
    bool writeFile(const QString& date, const QString& name, const unsigned int& maxSampleNum);
    /*!
     * \brief writeFiles generates files each with one segment of the presentation
     * \param date date - used to name catalof for generated file
     * \param name full name of the original file which contains presentation (with path)
     * \param maxSampleNum max sample number in the segment
     * \return true if files were successfully written
     */
    bool writeFiles(const QString& date, const QString& name, const unsigned int& maxSampleNum);
    /*!
     * \brief setMpdProps
     * Sets some MPDWriter attributes that are necessary to generate MPD:
     * - name of the original file (wihout path)
     * - path to generated dash files
     */
    void setMpdProps();
    /*!
     * \brief initMPD
     * \param oneFile indicates wheter all the segments of presentation shall be placed in one file
     * sets box tree model of original file in mpdWriter
     */
    void initMPD(const bool& oneFile);
    /*!
     * \brief addRepresentation adds representation of presentation to MPD model
     * \param oneFile indicates wheter all the segments of presentation shall be placed in one file
     */
    void addRepresentation(const bool& oneFile);
    /*!
     * \brief writeMPD
     * \param url URL address where all the dash files will be place
     * Writes Media Presentation File with earlier set parameters. The file is located in the same catalog
     * as files with segments
     */
    void writeMPD(const QString &url);
    /*!
     * \brief clear
     * clear all the attributes (deletes mpdWriter and sets to NULL, all QString are set to "")
     */
    void clear();
};

#endif // DASHPROXY_H
