#ifndef DASHPROXY_H
#define DASHPROXY_H

#include "dashcreator.h"
#include "mpd.h"
#include "treemodel.h"

class TreeModel;
class DashCreator;
class MPDWriter;

/*!
 * \brief The DashProxy class
 */
class DashWrapper {
private:
    /*!
     * \brief catalog catalog for all dash files
     */
    QString catalog;
    /*!
     * \brief path path to catalog
     */
    QString path;
    /*!
     * \brief fileName name of the file that is transformed (without path)
     */
    QString fileName;
    /*!
     * \brief mpdWriter
     */
    MPDWriter* mpdWriter;
public:
    DashWrapper();
    void setFileProp(const QString& fullPath);
    bool writeFile(const QString& date, const QString& name, const unsigned int& maxSampleNum);
    bool writeFiles(const QString& date, const QString& name, const unsigned int& maxSampleNum);
    void addRepresentation(const bool& oneFile);
    void writeMPD(const bool& oneFile);
    void initMPD(const bool& oneFile);
    void setMpdProps();
//public:
//    /*!
//     * \brief DashProxy
//     * \param fileName name of mp4 file that is transformed into dash mp4 file
//     * \param model model of boxes of mp4 file that is transformed into dash mp4 file
//     */
//    DashWrapper(const QString& fileName, TreeModel* model, const QString &date);
//    DashWrapper();
//    ~DashWrapper();
//    /*!
//     * \brief closeFileStream
//     * closes file stream
//     */
//    void closeFileStream();
//    /*!
//     * \brief writeFile
//     * Writes dash file
//     * \param maxSampleNum maximum number of samples in one mdat
//     * \return true, if file was successfully written
//     */
//    bool writeFile(const QString& date, const QString &fileName, const unsigned int &maxSampleNum/*, QFile* dashFile*/);
//    /*!
//     * \brief writeFiles
//     * Writes dash files - each segment has its own file
//     * \param maxSampleNum maximum number of samples in one mdat
//     * \return true, if all files were successfully written
//     */
//    bool writeFiles(const QString& date, const QString& fileName, const unsigned int& maxSampleNum);
//    /*!
//     * \brief writeMPD
//     * Writes Media Presentation Description File
//     * \param mpdFile Media Presentation Description file that is created
//     */
//    void writeMPD(QFile *mpdFile, bool oneFile);

//private:
//    void setDashCreator(const QString &fileName);

//    DashCreator* dashCreator;
//    MPDWriter* mpdWriter;
};

#endif // DASHPROXY_H
