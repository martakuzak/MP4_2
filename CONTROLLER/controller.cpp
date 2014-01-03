#include "controller.h"

Controller::Controller(MainWindow *mw): window(mw) {
    connect(window, SIGNAL(fileSelected(QString)), this, SLOT(fileSelected(QString)), Qt::QueuedConnection);
}
////////////////////
void Controller::fileSelected(const QString& fileName) {

}
