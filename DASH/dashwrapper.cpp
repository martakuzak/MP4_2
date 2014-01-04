#include "dashwrapper.h"

DashWrapper::DashWrapper(const QString& fileName, TreeModel* model, const QString& date) {
    int last = fileName.lastIndexOf("\\");
    if(last == -1)
        last = fileName.lastIndexOf("/");
    QString name = fileName.mid(last + 1);
    QString path = fileName.mid(0, last + 1);
    dashCreator = new DashCreator(fileName, model);
    mpdWriter = new MPDWriter(path, name, model, date);
}
////////////////////////////////////////////////////////////////////////////////////////////
DashWrapper::DashWrapper() {}
////////////////////////////////////////////////////////////////////////////////////////////
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
bool DashWrapper::writeFile(const QString& date, const QString& fileName, const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFile(date, fileName, maxSampleNum/*, dashFile*/);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFiles(const QString &date, const QString& fileName, const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    return dashCreator->writeFiles(date, fileName, maxSampleNum/*, dashFile*/);
}
///////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::setDashCreator(const QString& fileName) {
    if(dashCreator != NULL)
        delete dashCreator;
    Analyzer* an = new Analyzer(fileName);
    TreeModel* model = new TreeModel(an);
    dashCreator = new DashCreator(fileName, model);
}
