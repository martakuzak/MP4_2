#ifndef NALUNITSDTO_H
#define NALUNITSDTO_H

#include <QString>
#include <QList>
#include <memory>
#include <QHash>
#include "nalunit.h"

/*!
 * \brief The NalUnitsBO class contains of parameters that describe NAL unit stream
 */
class NalUnitsBO {   
protected:
    /*!
     * \brief fileName name of the file with NAL unit stream
     */
    QString fileName;
    /*!
     * \brief nalUnits list of NAL units from the stream
     */
    QList<std::shared_ptr<NalUnit> > nalUnits;
    /*!
     * \brief syncNalIdx list of indexes of the begin of access units
     */
    QList<unsigned int> syncNalIdx;
    /*!
     * \brief seqParSetIdx list of indexes of sequence parameter set NAL units
     */
    QHash<unsigned int, QList<unsigned int>> seqParSetIdx;
    /*!
     * \brief picParSetIdx list of indexes of picture parameter set NAL units
     */
    QHash<unsigned int, QList<unsigned int>> picParSetIdx;
    /*!
     * \brief sizeFieldLen length in bytes of size field that precedes each NAL unit in AVC stream
     */
    unsigned short sizeFieldLen;
    /*!
     * \brief allPrefLength The length of all the start codes that were present in the stream (0x000001 or 0x00000001)
     */
    unsigned int allPrefLength;
    /*!
     * \brief newNalOffsets The list of offsets of the NAL stream after putting size field before each unit
     */
    QList<unsigned long> newNalOffsets;
    /*!
     * \brief startFrameNalIdx List of indexes of the NAL units that starts new frames
     */
    QList<unsigned int> startFrameNalIdx;
public:
    /*!
     * \brief NalUnitsBO
     * \param name name of the file that contains NAL unit stream
     * \param nals NAL units list
     * \param sfl length of size field (in bytes) that precedes every NAL unit in AVC NAL unit stream
     * \param apl length of all the start codes that are present in the stream (in bytes)
     * \param frames list of indexes of the NAL units that starts new frames
     * \param sync list of indexes of the begin of access units
     * \param sps list of indexes of sequence parameter set NAL units
     * \param pps list of indexes of picture parameter set NAL units
     */
    NalUnitsBO(const QString& name, const QList<std::shared_ptr<NalUnit> >& nals, unsigned int sfl, unsigned int apl,
               const QList<unsigned int> frames, const QList<unsigned int> sync,
               const QHash<unsigned int, QList<unsigned int>> sps,
               const QHash<unsigned int, QList<unsigned int>> pps);
    QString getFileName() const;
    QList<std::shared_ptr<NalUnit> > getNalUnits() const;
    QList<unsigned int> getSyncIdx() const;
    unsigned short getSizeFieldLen() const;
    unsigned int getAllPrefLength() const;
    QList<std::shared_ptr<NalUnit> > getSeqParSet() const;
    QList<std::shared_ptr<NalUnit>> getPicParSet() const;
    std::shared_ptr<NalUnit> getNalUnit(unsigned int idx) const;
    unsigned int getStartFrameNalIdx(unsigned int idx) const;
    /*!
     * \brief getFrameNumber
     * \return frames number
     */
    int getFramesNumber() const;
    unsigned int getFrameSize(int idx) const;
    unsigned int allSPSLen();
    unsigned int allPPSLen();
    /*!
     * \brief getFrameOffset
     * \param nalIdx NAL unit index that starts the frame
     * \return byte offset in file of the given frame
     */
    unsigned long getFrameOffset(unsigned int nalIdx);
    /*!
     * \brief getNalUnitsByteLen
     * \param startIdx first NAL unit index
     * \param endIdx last NAL unit index
     * \return length in bytes of all NAL units in the given range
     */
    unsigned long getNalUnitsByteLen(int startIdx, int endIdx);
protected:
    /*!
     * \brief calcNewNalOffsets The function calculates the offsets of the NAL units after putting size field before
     * each one.
     */
    void calcNewNalOffsets();
};

#endif // NALUNITSDTO_H
