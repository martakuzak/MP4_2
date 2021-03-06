#ifndef BOXFACTORY_H
#define BOXFACTORY_H

#include <QList>
#include <memory>
#include <qDebug>
#include <cmath>
#include "analyzer.h"
#include "box.h"
#include "trackbox.h"
#include "sampleentry.h"
#include "sampletablebox.h"
#include "fileservice.h"
#include "bitoperator.h"

/*!
 * \brief The BoxFactory class is a factory that creates Box objects.
 */
class BoxFactory {
protected:
    FileService *fileService;
    BitOperator *bitOperator;
public:
    /*!
      *\brief BoxFactory
      *\param an analyzer that enables reading extra parameters of the box.
     */
    BoxFactory(FileService *fs);
    /*!
      *\brief getBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getBox(const unsigned int& size = 0, QString type = "", unsigned long int off = 0);
    ~BoxFactory() { delete bitOperator; }
private:
    /*!
      *\brief getMBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 'm' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getMBox(const unsigned int& size = 0, QString type = "", unsigned long int off = 0);
    /*!
      *\brief getTBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 't' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getTBox(const unsigned int& size = 0, QString type = "", unsigned long int off = 0);
    /*!
      *\brief getSBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 's' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getSBox(const unsigned int& size = 0, QString type = "", unsigned long int off = 0);
    /*!
      *\brief getHBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 'h' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getHBox(const unsigned int& size = 0, QString type = "", unsigned long int off = 0);
    unsigned long int valueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    signed long int signedValueOfGroupOfBytes(const unsigned int & length, const unsigned long& offset) const;
    unsigned long int valueOfGroupOfBits(const unsigned int & length, const unsigned long& offset) const;
    QString stringValue(const unsigned int & length, const unsigned long& offset) const;
};

#endif // BOXFACTORY_H
