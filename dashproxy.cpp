#include "dashproxy.h"

DashProxy::DashProxy(const QString& fileName, TreeModel* model) {
    int last = fileName.lastIndexOf("\\");
    if(last == -1)
        last = fileName.lastIndexOf("/");
    QString name = fileName.mid(last + 1);
    QString path = fileName.mid(0, last + 1);
    QString dashName = QString(path + "dash_" + name);
    dashCreator = new DashCreator(fileName, model);
    mpdWriter = new MPDWriter(dashName, model);
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashProxy::writeMPD(QFile* mpdFile) {
    mpdWriter->init();
    mpdWriter->writeMPD(mpdFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashProxy::writeFile(const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFile(maxSampleNum/*, dashFile*/);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashProxy::writeFiles(const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFiles(maxSampleNum/*, dashFile*/);
}

