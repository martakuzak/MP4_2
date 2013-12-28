#include "dashproxy.h"

DashProxy::DashProxy(const QString& fileName, TreeModel* model, const QString& date) {
    int last = fileName.lastIndexOf("\\");
    if(last == -1)
        last = fileName.lastIndexOf("/");
    QString name = fileName.mid(last + 1);
    QString path = fileName.mid(0, last + 1);
    dashCreator = new DashCreator(fileName, model, date);
    mpdWriter = new MPDWriter(path, name, model, date);
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashProxy::writeMPD(QFile* mpdFile, bool oneFile) {
    mpdWriter->init(oneFile);
    qDebug()<<"dashProxy po init";
    mpdWriter->writeMPD(mpdFile, oneFile);
    qDebug()<<"dashProxy po writeMPD";
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashProxy::writeFile(const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFile(maxSampleNum/*, dashFile*/);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashProxy::writeFiles(const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFiles(maxSampleNum/*, dashFile*/);
}

