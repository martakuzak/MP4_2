#include "dashwrapper.h"

DashWrapper::DashWrapper() {
    mpdWriter = new MPDWriter();
}
void DashWrapper::setFileProp(const QString& fullPath) {
    int last = fullPath.lastIndexOf("\\");
    if(last == -1)
        last = fullPath.lastIndexOf("/");
    fileName = fullPath.mid(last + 1);
    path = fullPath.mid(0, last + 1);
   // mpdWriter->setOriginalFileName(fullPath);
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFile(const QString& date, const QString& name, const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    //return dashCreator->writeFile(date, fileName, maxSampleNum/*, dashFile*/);
    int last = name.lastIndexOf("\\");
    if(last == -1)
        last = name.lastIndexOf("/");
    fileName = name.mid(last + 1);
    catalog = "DASH_" + date;
    QString dashPath = path + catalog + "/";
    ////qDbug()<<"dw write file 1";
    Analyzer* an = new Analyzer(name);
    ////qDbug()<<"dw write file 2";
    TreeModel* model = new TreeModel(an);
    //qDbug()<<"dw write file 3"<<path<<fileName;
    DashCreator* dashCreator = new DashCreator(dashPath, path + fileName, model);
    //qDbug()<<"dw write file 4";
    return dashCreator->writeFile(maxSampleNum);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFiles(const QString &date, const QString& name, const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
    int last = name.lastIndexOf("\\");
    if(last == -1)
        last = name.lastIndexOf("/");
    fileName = name.mid(last + 1);
    catalog = "DASH_" + date;
    QString dashPath = path + catalog + "/";
    ////qDbug()<<"dw write file 1";
    Analyzer* an = new Analyzer(name);
    ////qDbug()<<"dw write file 2";
    TreeModel* model = new TreeModel(an);
    //qDbug()<<"dw write file 3"<<path<<fileName;
    DashCreator* dashCreator = new DashCreator(dashPath, path + fileName, model);
    //return dashCreator->writeFiles(date, fileName, maxSampleNum/*, dashFile*/);
    return dashCreator->writeFiles(maxSampleNum);
}

void DashWrapper::addRepresentation(const bool &oneFile) {
    qDebug()<<"dw addrepr";
    return mpdWriter->addRepresentation(fileName, oneFile);
}
void DashWrapper::writeMPD(const bool& oneFile) {
    mpdWriter->writeMPD(oneFile);
}

void DashWrapper::initMPD(const bool& oneFile) {
    mpdWriter->init(oneFile);
}

//DashWrapper::DashWrapper(const QString& fileName, TreeModel* model, const QString& date) {
//    int last = fileName.lastIndexOf("\\");
//    if(last == -1)
//        last = fileName.lastIndexOf("/");
//    QString name = fileName.mid(last + 1);
//    QString path = fileName.mid(0, last + 1);
//    dashCreator = new DashCreator(fileName, model);
//    mpdWriter = new MPDWriter(path, name, model, date);
//}
//////////////////////////////////////////////////////////////////////////////////////////////
//DashWrapper::DashWrapper() {}
//////////////////////////////////////////////////////////////////////////////////////////////
//DashWrapper::~DashWrapper() {
//    //delete mpdWriter;
//    //delete dashCreator;
//}
//////////////////////////////////////////////////////////////////////////////////////////////
//void DashWrapper::closeFileStream() {
//    dashCreator->closeFileStream();
//}
//////////////////////////////////////////////////////////////////////////////////////////////
//void DashWrapper::writeMPD(QFile* mpdFile, bool oneFile) {
//    mpdWriter->init(oneFile);
//    mpdWriter->writeMPD(mpdFile, oneFile);
//}
//////////////////////////////////////////////////////////////////////////////////////////////
//bool DashWrapper::writeFile(const QString& date, const QString& fileName, const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
//    return dashCreator->writeFile(date, fileName, maxSampleNum/*, dashFile*/);
//}
//////////////////////////////////////////////////////////////////////////////////////////////
//bool DashWrapper::writeFiles(const QString &date, const QString& fileName, const unsigned int &maxSampleNum/*, QFile* dashFile*/) {
//    return dashCreator->writeFiles(date, fileName, maxSampleNum/*, dashFile*/);
//}
/////////////////////////////////////////////////////////////////////////////////////////////
//void DashWrapper::setDashCreator(const QString& fileName) {
//    if(dashCreator != NULL)
//        delete dashCreator;
//    Analyzer* an = new Analyzer(fileName);
//    TreeModel* model = new TreeModel(an);
//    dashCreator = new DashCreator(fileName, model);
//}
