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
bool DashWrapper::writeFile(const QString& date, const QString& name, const unsigned int &maxSampleNum/*, QFile *dashFile*/) {
    //return dashCreator->writeFile(date, fileName, maxSampleNum/*, dashFile*/);
    int last = name.lastIndexOf("\\");
    if(last == -1)
        last = name.lastIndexOf("/");
    fileName = name.mid(last + 1);
    catalog = "DASH_" + date;
    QString dashPath = path + catalog + "/";
    ////qDebug()<<"dw write file 1";
    Analyzer *an = new Analyzer(name);
    ////qDebug()<<"dw write file 2";
    TreeModel *model = new TreeModel(an);
    QList<std::shared_ptr<Box>> mdats = model->getBoxes("mdat");
    if(mdats.size() != 1)
        return false;
    //qDebug()<<"dw write file 3"<<path<<fileName;
    DashCreator *dashCreator = new DashCreator(dashPath, path + fileName, model);
    //qDebug()<<"dw write file 4";
    return dashCreator->writeFile(maxSampleNum);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFiles(const QString &date, const QString& name, const unsigned int &maxSampleNum/*, QFile *dashFile*/) {
    int last = name.lastIndexOf("\\");
    if(last == -1)
        last = name.lastIndexOf("/");
    fileName = name.mid(last + 1);
    catalog = "DASH_" + date;
    QString dashPath = path + catalog + "/";
    qDebug()<<"dw write file 1";
    Analyzer *an = new Analyzer(name);
    qDebug()<<"dw write file 2";
    TreeModel *model = new TreeModel(an);
    qDebug()<<"dw write file 3"<<path<<fileName;
    DashCreator *dashCreator = new DashCreator(dashPath, path + fileName, model);
    //return dashCreator->writeFiles(date, fileName, maxSampleNum/*, dashFile*/);
    return dashCreator->writeFiles(maxSampleNum);
}

void DashWrapper::addRepresentation(const bool &oneFile) {
    //qDebug()<<"dw addrepr";
    return mpdWriter->addRepresentation(path + fileName, oneFile);
}
void DashWrapper::writeMPD(const bool& oneFile, const QString &url) {
    mpdWriter->writeMPD(oneFile, url);
}

void DashWrapper::initMPD(const bool& oneFile) {
    mpdWriter->init(oneFile);
}

void DashWrapper::setMpdProps() {
    //qDebug()<<path<<catalog<<fileName;
    mpdWriter->setDashPath(path  + catalog);
    mpdWriter->setOriginalFileName(fileName);
}

void DashWrapper::clear() {
    if(mpdWriter != NULL)
        delete mpdWriter;
    mpdWriter = new MPDWriter();
}
