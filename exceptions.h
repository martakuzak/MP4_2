#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "QException"
#include <qDebug>

class MainWindow;
class NoSuchABoxException: public QException
{
public:
    void raise() const { throw *this; }
    NoSuchABoxException *clone() const { return new NoSuchABoxException(*this); }
};

#endif // EXCEPTIONS_H
