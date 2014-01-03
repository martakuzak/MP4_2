#include "dashwrapper.h"

DashWrapper::DashWrapper(const QString& fileName, TreeModel* model, const QString& date) {
    int last = fileName.lastIndexOf("\\");
    if(last == -1)
        last = fileName.lastIndexOf("/");
    QString name = fileName.mid(last + 1);
    QString path = fileName.mid(0, last + 1);
    dashCreator = new DashCreator(fileName, model, date);
    mpdWriter = new MPDWriter(path, name, model, date);
}
DashWrapper::~DashWrapper() {
    //delete mpdWriter;
    //delete dashCreator;
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::closeFileStream() {
    dashCreator->closeFileStream();
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::writeMPD(QFile* mpdFile, bool oneFile) {
    mpdWriter->init(oneFile);
    mpdWriter->writeMPD(mpdFile, oneFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFile(const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFile(maxSampleNum/*, dashFile*/);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFiles(const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFiles(maxSampleNum/*, dashFile*/);
}
