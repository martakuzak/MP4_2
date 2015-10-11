#include <QApplication>
#include "controller.h"
#include "mainwindow.h"
#include <QHash>
#include <QString>
#include <QDebug>

#include <iostream>
#include <climits>
#include "fileservice.h"

/*! \mainpage
 *
 * \section intro_sec MP4 Multimedia File Editor
 * MP4 Multimedia File Editor is an GUI application for analysing and editing MP4 files. See the rest of
 * documentation for further details.
 *
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    Controller controller(w);
    w->show();
    BitOperator* b = new BitOperator();
    //11111111 11111111 11111111 10110000
    char* array = new char[3];
    array[0] = 0xFF;
    array[1] = 0xFF;
    array[2] = 176;
    int k = b->signedValueOfGroupOfBytes(array, 3);
    array[0] = 0;
    array[1] = 0;
    int l = b->signedValueOfGroupOfBytes(array, 3);
    qDebug()<<"wynik = " <<k<< " "<<l;
    return a.exec();
   // return 0;
    /*FileService* service = new FileService("D:\\j.txt");
    qDebug()<<service->openFile();
    int start = 0;
    int length = 10;
    char* tmp = new char(length);
    tmp = service->getBits(start, length); // 83 = 01010011b, 108 = 01101100b, 111 = 01101111b
    for(int i = 0; i < length; ++ i)
      qDebug()<<"tmp["<<i<<"]"<<(int)tmp[i];
    service->close();
    return 0;*/
}

/**
 * signed long BitOperator::signedValueOfGroupOfBytes(const char *array, const unsigned int &length) const{
    signed long num = 0;
    for(unsigned int i = 0; i< length; ++i) {
        num |= array[i] & 0xFF; //suma bit po bicie
        if(0 != length && i != (length - 1)) {
            num = (num << 8); //przesuniecie o 8 bitow w lewo
        }
    }
    return num;
}*/
