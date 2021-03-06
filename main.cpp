#include <QApplication>
#include "controller.h"
#include "mainwindow.h"
#include <QHash>
#include <QString>
#include <QDebug>

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
    return a.exec();
}
