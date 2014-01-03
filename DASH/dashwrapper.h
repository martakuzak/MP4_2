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
public:
    /*!
     * \brief DashProxy
     * \param fileName name of mp4 file that is transformed into dash mp4 file
     * \param model model of boxes of mp4 file that is transformed into dash mp4 file
     */
    DashWrapper(const QString& fileName, TreeModel* model, const QString &date);
    ~DashWrapper();
    /*!
     * \brief closeFileStream
     * closes file stream
     */
    void closeFileStream();
    /*!
     * \brief writeFile
     * Writes dash file
     * \param maxSampleNum maximum number of samples in one mdat
     * \return true, if file was successfully written
     */
    bool writeFile(const unsigned int &maxSampleNum/*, QFile* dashFile*/);
    /*!
     * \brief writeFiles
     * Writes dash files - each segment has its own file
     * \param maxSampleNum maximum number of samples in one mdat
     * \return true, if all files were successfully written
     */
    bool writeFiles(const unsigned int& maxSampleNum);
    /*!
     * \brief writeMPD
     * Writes Media Presentation Description File
     * \param mpdFile Media Presentation Description file that is created
     */
    void writeMPD(QFile *mpdFile, bool oneFile);

private:
    DashCreator* dashCreator;
    MPDWriter* mpdWriter;
};

#endif // DASHPROXY_H