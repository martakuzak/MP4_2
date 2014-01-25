#include "dashwrapper.h"

DashWrapper::DashWrapper() {
    mpdWriter = NULL;
    catalog = "";
    path = "";
    fileName = "";
}
//////////////////////////////////////////////////////////////////////////////////////////////
DashWrapper::~DashWrapper() {
    if(mpdWriter != NULL)
        delete mpdWriter;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/// Files
//////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::setFileProp(const QString& fullPath) {
    int last = fullPath.lastIndexOf("\\");
    if(last == -1)
        last = fullPath.lastIndexOf("/");
    fileName = fullPath.mid(last + 1);
    path = fullPath.mid(0, last + 1);
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFile(const QString& date, const QString& name, const unsigned int &maxSampleNum) {
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
    DashCreator *dashCreator = new DashCreator(dashPath, path + fileName, model);
    return dashCreator->writeFile(maxSampleNum);
}
////////////////////////////////////////////////////////////////////////////////////////////
bool DashWrapper::writeFiles(const QString &date, const QString& name, const unsigned int &maxSampleNum) {
    int last = name.lastIndexOf("\\");
    if(last == -1)
        last = name.lastIndexOf("/");
    fileName = name.mid(last + 1);
    catalog = "DASH_" + date;
    QString dashPath = path + catalog + "/";
    Analyzer *an = new Analyzer(name);
    TreeModel *model = new TreeModel(an);
    DashCreator *dashCreator = new DashCreator(dashPath, path + fileName, model);
    return dashCreator->writeFiles(maxSampleNum);
}
//////////////////////////////////////////////////////////////////////////////////////////////
/// MPD
//////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::setMpdProps() {
    mpdWriter = new MPDWriter();
    mpdWriter->setDashPath(path  + catalog);
    mpdWriter->setOriginalFileName(fileName);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::initMPD(const bool& oneFile, const bool &slist) {
    mpdWriter->init(oneFile, slist);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::addRepresentation(const bool &oneFile) {
    qDebug()<<"addr"<<(path + fileName);
    return mpdWriter->addRepresentation(path, fileName, oneFile);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::writeMPD(const bool& oneFile, const QString &url) {
    mpdWriter->writeMPD(oneFile, url);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void DashWrapper::clear() {
    if(mpdWriter != NULL) {
        delete mpdWriter;
        mpdWriter = NULL;
    }
    catalog = "";
    path = "";
    fileName = "";
}
