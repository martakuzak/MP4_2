#ifndef NALPARSER_H
#define NALPARSER_H

#include <QString>
#include <QFile>
#include <QByteArray>
#include <QList>
#include <QHash>
#include <memory>

#include "nalunit.h"
#include "nalunitfactory.h"
#include "nalunitsbo.h"
#include "nalunittype.h"
#include "filebitoperator.h"

class Box;

/*!
 * \brief The NALParser class is responsible for analyzing NAL unit stream.
 */
class NALParser {
protected:
    /*!
     * \brief fileName name of the analyzed file
     */
    QString fileName;
    /*!
     * \brief fileSize size of the analyzed file
     */
    unsigned long int fileSize;
    /*!
     * \brief fbOperator
     */
    FileBitOperator* fbOperator;
public:
    NALParser();
    /*!
     * \brief NALParser
     * \param fileName name of the analyzed file
     */
    NALParser(const QString& fileName);
    ~NALParser();
    /*!
     * \brief parseFile The function parses NAL unit stream by recognizing all the NAL unit types and reading some
     * of the inner parameters
     * \return an object filled with data that describe NAL unit stream in the file
     */
    NalUnitsBO* parseFile();
//    int parseSEI(int offset);
//    int parseSEIPayload(int payloadType, int payloadSize, int offset);
//    int scalabilityInfo(int payloadSize, int offset);
//    int sliceLayerWithoutPartitioningRbsp(int offset);
//    int sliceHeader(int offset);

protected:
    /*!
     * \brief isAUStarter It decides whether the given NAL unit is Access Unit starter or not
     * \param type NAL unit type
     * \return true if the NAL unit starts Access Unit
     */
    bool isAUStarter(NalUnitType type);
    /*!
     * \brief isVCL It says whether the given NAL unit is VCL
     * \param type NAL unit type
     * \param sync true if the function is supposed to look for IDR NAL units only
     * \return true if the given NAL unit is VCL and if specified is IDR
     */
    bool isVCL(NalUnitType type, bool sync = false);
};

#endif // NALPARSER_H
