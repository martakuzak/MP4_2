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
    char* data = new char(1);
    data[0] = 53;
    char* tmp = service->getBits(0, 8);
    for(int i = 0; i < 8; ++ i)
      qDebug()<<(int)tmp[i];
    service->close();
    return 0;
}
