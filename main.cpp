#include <QApplication>
#include "controller.h"
#include "mainwindow.h"
#include <QHash>
#include <QString>
#include <QDebug>

#include "fileservice.h"

/*! \mainpage
 *
 * \section intro_sec MP4 Multimedia File Editor
 * MP4 Multimedia File Editor is an GUI application for analysing and editing MP4 files. See the rest of
 * documentation for further details.
 *
 */
int main(int argc, char *argv[]) {
    /*QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    Controller controller(w);
    w->show();
    return a.exec();*/
    FileService* service = new FileService("D:\\j.txt");
    qDebug()<<service->openFile();
    int start = 0;
    int length = 150;
    char* tmp = new char(length);
    tmp = service->getBits(start, length); // 83 = 01010011b, 108 = 01101100b, 111 = 01101111b
    for(int i = 0; i < length; ++ i)
      qDebug()<<"tmp["<<i<<"]"<<(int)tmp[i];
    service->close();
    return 0;
}
