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
class DashProxy {
public:
    /*!
     * \brief DashProxy
     * \param fileName name of mp4 file that is transformed into dash mp4 file
     * \param model model of boxes of mp4 file that is transformed into dash mp4 file
     */
    DashProxy(const QString& fileName, TreeModel* model);
    /*!
     * \brief closeFileStream
     * closes file stream
     */
    void closeFileStream();
    /*!
     * \brief writeFile
     * Writes dash file
     * \param maxSampleNum maximum number of samples in one mdat
     * \param dashFile
     */
    void writeFile(const unsigned int &maxSampleNum, QFile* dashFile);
    /*!
     * \brief writeMPD
     * Writes Media Presentation Description File
     * \param mpdFile Media Presentation Description file that is created
     */
    void writeMPD(QFile* mpdFile);

private:
    DashCreator* dashCreator;
    MPDWriter* mpdWriter;
};

#endif // DASHPROXY_H
