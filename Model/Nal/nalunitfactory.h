#ifndef NALUNITFACTORY_H
#define NALUNITFACTORY_H

#include "nalunit.h"
#include "nalunittype.h"
#include "filebitoperator.h"
#include "box.h"
#include <memory>


class FileBitOperator;

/*!
 * \brief The NalUnitFactory class factory of NAL unit objects
 */
class NalUnitFactory {
protected:
    FileBitOperator * fbOperator;

public:
    /*!
     * \brief NalUnitFactory
     * \param fbo
     */
    NalUnitFactory(FileBitOperator* fbo);
    ~NalUnitFactory();
    /*!
     * \brief getNalUnit
     * \param typeCode type code of NAL unit
     * \param nalRefIdc NAL reference indicator
     * \param offset offset in bytes of NAL unit in the file
     * \param sl start code length (it should be either 3 or 4)
     * \return NAL unit regarding of given parameters
     */
    std::shared_ptr<NalUnit> getNalUnit(int typeCode, unsigned int nalRefIdc, unsigned long offset,
                                        const unsigned short & sl = 3);
};

#endif // NALUNITFACTORY_H
