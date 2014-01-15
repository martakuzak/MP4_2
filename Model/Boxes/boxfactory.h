#ifndef BOXFACTORY_H
#define BOXFACTORY_H

#include <QList>
#include <memory>
#include <qDebug>
#include <cmath>
#include "exceptions.h"
#include "analyzer.h"
#include "box.h"
#include "trackbox.h"
#include "sampleentry.h"
#include "sampletablebox.h"

class Analyzer;

class BoxFactory {
private:
    /*!
      *\brief analyzer
     */
    Analyzer *analyzer;
public:
    /*!
      *\brief BoxFactory
      *\param an analyzer that enables reading extra parameters of the box.
     */
    BoxFactory(Analyzer *an);
    /*!
      *\brief getBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getBox(const unsigned int& size=0, QString type="", unsigned long int off=0);
private:
    /*!
      *\brief getMBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 'm' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getMBox(const unsigned int& size=0, QString type="", unsigned long int off=0);
    /*!
      *\brief getTBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 't' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getTBox(const unsigned int& size=0, QString type="", unsigned long int off=0);
    /*!
      *\brief getSBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 's' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getSBox(const unsigned int& size=0, QString type="", unsigned long int off=0);
    /*!
      *\brief getHBox creates Box according to the given parameters and adds extra parameters depending on type of the box.
      *Box types begins with 'h' letter.
      *\param size size of the box
      *\param type type of the box
      *\param byte offset of the box location
      *\return Box created according to the given and extra parametrs
     */
    std::shared_ptr<Box> getHBox(const unsigned int& size=0, QString type="", unsigned long int off=0);
};

#endif // BOXFACTORY_H
