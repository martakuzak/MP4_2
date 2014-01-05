#include "mpd.h"


QString ProgramInformation::getLang() const {
    return lang;
}
/////////////
void ProgramInformation::setLang(const QString &value) {
    lang = value;
}
/////////////
QString ProgramInformation::getCopyright() const {
    return copyright;
}
/////////////
void ProgramInformation::setCopyright(const QString &value) {
    copyright = value;
}
/////////////
QString ProgramInformation::getSource() const{
    return source;
}
/////////////
void ProgramInformation::setSource(const QString &value){
    source = value;
}
/////////////
QString ProgramInformation::getTitle() const {
    return title;
}
/////////////
void ProgramInformation::setTitle(const QString &value) {
    title = value;
}
/////////////
QString ProgramInformation::getMoreInformationURL() const {
    return moreInformationURL;
}
/////////////
void ProgramInformation::setMoreInformationURL(const QString &value){
    moreInformationURL = value;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
MPD::MPD()
{}

BaseURL *MPD::getBaseURL() const {
    return baseURL;
}
//////////////////////
void MPD::setBaseURL(const QString& url){
    baseURL = new BaseURL();
    baseURL->setContent(url);
}

/////////////
void MPD::addPeriod() {
    Period* period = new Period();
    period->setStart(QString("PT0S"));
    
    periods.append(period);
}
/////////////
void MPD::addPeriod(Period* period) {
    periods.append(period);
}
/////////////
QString MPD::getProfiles() const {
    return profiles;
}
/////////////
void MPD::setProfiles(const QString &value) {
    profiles = value;
}
/////////////
QString MPD::getMediaPresentationDuration() const {
    return mediaPresentationDuration;
}
/////////////
void MPD::setMediaPresentationDuration(const QString &value) {
    mediaPresentationDuration = value;
}
/////////////
QString MPD::getMinBufferTime() const {
    return minBufferTime;
}
/////////////
void MPD::setMinBufferTime(const QString &value) {
    minBufferTime = value;
}
/////////////
QString MPD::getXmlns() const {
    return xmlns;
}
/////////////
void MPD::setXmlns(const QString &value) {
    xmlns = value;
}
/////////////
QString MPD::getType() const {
    return type;
}
/////////////
void MPD::setType(const QString &value) {
    type = value;
}
////////////

QList<Period *> MPD::getPeriods() const{
    return periods;
}

void MPD::setPeriods(const QList<Period*> &value){
    periods = value;
}
//////////////////////////////////
void MPD::write(QXmlStreamWriter* stream ) {
    stream->writeStartElement("MPD");
    if(type.size())
        stream->writeAttribute("type", type);
    if(xmlns.size())
        stream->writeAttribute("xmlns", xmlns);
    if(minBufferTime.size())
        stream->writeAttribute("minBufferTime", minBufferTime);
    if(profiles.size())
        stream->writeAttribute("profiles", profiles);
    if(mediaPresentationDuration.size())
        stream->writeAttribute("mediaPresentationDuration", mediaPresentationDuration);
    if(baseURL != NULL)
        baseURL->write(stream);
    qDebug()<<"mpdwrite2";
    if(periods.size()) {
        int size = periods.size();
        for(int i = 0; i < size; ++i) {
            periods.at(i)->write(stream);
        }
    }
    stream->writeEndElement();
}
/////////////////////////////////////////////////////////////////////////////////////////
QString MPDWriter::getDuration() {
    QList<std::shared_ptr <Box> > mvhds = originalModel->getBoxes("mvhd");
    if(mvhds.empty())
        return QString("");
    MovieHeaderBox* mvhd = dynamic_cast <MovieHeaderBox*> (mvhds.back().get());
    unsigned long int timescale = mvhd->getTimeScale();
    unsigned long int duration = mvhd->getDuration();
    return getHMSFormat(duration/timescale);
}
///////////////////////////////////////////////////////////////////////////////////////////
unsigned int* MPDWriter::getDimensions() {
    unsigned int* ret = new unsigned int[2];
    QList<std::shared_ptr <Box> > visualEntries = originalModel->getBoxes("avc1");
    if(visualEntries.empty()) {
        visualEntries = originalModel->getBoxes("mp4v");
        if(visualEntries.empty()) {
            QList<std::shared_ptr <Box> > a = originalModel->getBoxes("ftyp");
            qDebug()<<"no visual"<<QString::number(a.size());
            ret[0] = 0;
            ret[1] = 0;
            return ret;
        }
    }
    std::shared_ptr <Box> visualEntry = visualEntries.at(0);
    AVCSampleEntry* as = dynamic_cast <AVCSampleEntry*> (visualEntries.at(0).get());
    ret[0] = as->getHeight();
    ret[1] = as->getWidth();
    return ret;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString MPDWriter::getHMSFormat(const double& value) {
    double durationInSec = value;
    unsigned int hours = durationInSec/3600;
    durationInSec -= 3600*hours;
    unsigned int minutes = durationInSec/60;
    durationInSec -= 60*minutes;
    return QString("PT" + QString::number(hours) + "H" + QString::number(minutes) + "M" + QString::number(durationInSec) + "S");
}
////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//MPDWriter::MPDWriter(const QString& pth, const QString &fn, TreeModel *mod, const QString& dt): path(pth),
//    fileName(fn), model(mod) {
//    path.append("DASH " + dt + "/");
//}
void MPDWriter::init(bool oneFile) {
    qDebug()<<"mpdw init";
    if(oneFile) {
        Analyzer* an = new Analyzer(dashPath + "/dash_" + originalFileName);
        //qDebug()<<"init"<<(dashPath + "/dash_" + originalFileName);
        dashModel = new TreeModel(an);
        return;
    }
    qDebug()<<"bdbf"<<(dashPath + "/dash_init_" + originalFileName);
    Analyzer* an = new Analyzer(dashPath + "/dash_init_" + originalFileName);
    dashModel = new TreeModel(an);
}

void MPDWriter::setMPD(bool oneFile) {
    //MPD
    mpd = new MPD();
    //mpd->setId(unisgned int); //nieobowiazkowe, poza tym bedzie jedno mpd, wiec bez tego
    mpd->setProfiles(QString("urn:mpeg:dash:profile:full:2011")); //obowiązkowe; urn:mpeg:dash:profil:isoff-main:2011?
    mpd->setType("static"); //static jest domyślne, dynamic (MPD może być zmieniane); typowo dynamic przy live streamach
    //mpd->setAvailibilityStartTime(); //obowiazkowe przy dynamic
    //mpd->setAvailibilityEndTime(); //nieobowiazkowe
    mpd->setMediaPresentationDuration(getDuration()); //obowiazkowe dla static
    //mpd->setMinimumUpdatePeriod(); //w static zakazane
    mpd->setMinBufferTime("10229"); //obowiązkowe - jak to ustawić?
    //mpd->getTimeShitBufferDepth(); //w staticu zbędne
    //mpd->getSuggestedPresentationDelay();//w staticu ignorowane
    //mpd->getMaxSegmentDuration(); //nieobowiązkowe
    //mpd->getMaxSubsegmentDuration(); //nieobowiązkowe
    mpd->addPeriod(setPeriod(oneFile));
    mpd->setBaseURL(dashPath);
}
//////////////////////////
void MPDWriter::writeMPD(/*QFile* file, */bool oneFile) {
    qDebug()<<"WRITEMPD1";
    QString mpdName = originalFileName;
    mpdName.replace(".mp4", ".mpd");
    QFile* mpdFile = new QFile(dashPath + "/" + mpdName);
    if(mpdFile->open(QIODevice::ReadWrite)) {
        setMPD(oneFile);
        QXmlStreamWriter* stream = new QXmlStreamWriter(mpdFile);
        stream->setAutoFormatting(true);
        stream->writeStartDocument();
        qDebug()<<"WRITEMPD2";
        //return;
        mpd->write(stream);
        stream->writeEndDocument();
    }
    
    mpdFile->close();
}
//////////////////////////
////void MPDWriter::setProgramInformation() {
////    programInformation = new ProgramInformation();
////    //    programInformation->setCopyright();//nic nieobowiązkowe
////    //    programInformation->setLang();
////    //    programInformation->setMoreInformationURL();
////    //    programInformation->setSource();
////    //    programInformation->setTitle();
////}
//////////////////////////
//SegmentList* MPDWriter::setSegmentList(bool oneFile) {
//    SegmentList* slist = new SegmentList();
//    Initialization* init = new Initialization();
//    if(oneFile) {
//        QList< std::shared_ptr<Box> > mdats = dashModel->getBoxes("mdat");
//        QList< std::shared_ptr<Box> > sidxs = dashModel->getBoxes("sidx");
//        init->setRange(QString::number(0) + "-" + QString::number(sidxs.back()->getOffset() - 1));
//        slist->setInitialization(init);
//        while(!sidxs.empty()) {
//            if(sidxs.size() == 1) {
//                std::shared_ptr<Box> sidx = sidxs.back();
//                std::shared_ptr<Box> mdat = mdats.front();
//                unsigned int firstMediaRange = sidx->getOffset();
//                unsigned int secondMediaRange = mdat->getOffset() + mdat->getSize() - 1;
//                QString mediaRange(QString::number(firstMediaRange) + "-" + QString::number(secondMediaRange));
//                unsigned int secondIndexRange = sidx->getOffset() + sidx->getSize();
//                QString indexRange(QString::number(firstMediaRange) + "-" + QString::number(secondIndexRange));
//                slist->addSegmentURL(mediaRange, indexRange);
//                sidxs.pop_back();
//            }
//            else {
//                std::shared_ptr<Box> sidx1 = sidxs.back();
//                sidxs.pop_back();
//                std::shared_ptr<Box> sidx2 = sidxs.back();
//                unsigned int firstMediaRange = sidx1->getOffset();
//                unsigned int secondMediaRange = sidx2->getOffset() - 1;
//                QString mediaRange(QString::number(firstMediaRange) + "-" + QString::number(secondMediaRange));
//                unsigned int secondIndexRange = sidx1->getOffset() + sidx1->getSize();
//                QString indexRange(QString::number(firstMediaRange) + "-" + QString::number(secondIndexRange));
//                slist->addSegmentURL(mediaRange, indexRange);
//            }
//        }
//    }
//    else {
//        init->setSourceURL("dash_init_" + fileName); //setting initalization
//        slist->setInitialization(init);
//        unsigned int index = 0;
//        QString str("dash_" + QString::number(index) + "_" + fileName + "s");
//        while(QFile(path + str).exists()) {//setting SegmentList
//            Analyzer* an = new Analyzer(path + str);
//            dashModel = new TreeModel(an);
//            slist->addSegmentURL(str);
//            ++ index;
//            str = QString("dash_" + QString::number(index) + "_" + fileName + "s");
//        }
//    }
//    return slist;
//}
////////////////
//BaseURL* MPDWriter::setBaseURL(const QString& url) {
//    BaseURL* burl = new BaseURL;
//    burl->setContent(url);
//    return burl;
//}
///////////////
//Representation* MPDWriter::setRepresentation(bool oneFile) {
//    Representation* repr = new Representation();
//    if(oneFile)
//        repr->setBaseurl(setBaseURL("dash_" + fileName));
//    else
//        repr->setBaseurl(setBaseURL("dash_init_" + fileName));
//    repr->setSegmentList(setSegmentList(oneFile));
//    unsigned int* dim = getDimensions();
//    repr->setHeight(dim[0]);
//    repr->setWidth(dim[1]);
//    repr->setMimeType("video/mp4");
//    repr->setStartsWithSAP(1);
//    return repr;
//}
///////////////
AdaptationSet* MPDWriter::setAdaptationSet(bool oneFile) {
    AdaptationSet* adapt = new AdaptationSet();
    adapt->addRepresentations(representations);
    /*unsigned int* dim = getDimensions();
    adapt->setMaxHeight(dim[0]);
    adapt->setMaxWidth(dim[1]);*/
    return adapt;
}
//////////////////
Period* MPDWriter::setPeriod(bool oneFile) {
    Period* period = new Period();
    period->setStart(QString("PT0S"));
    period->setDuration(getDuration());
    period->addAdaptationSet(setAdaptationSet(oneFile));
    return period;
}
///////////////////
//void MPDWriter::addRepresentation(const QString& fn, const bool& oneFile) {
//    fileName = fn;
//    Representation* repr = new Representation();

//    QString dashName;
//    if(oneFile) {
//        dashName = "dash_" + fileName;/*
//        Analyzer* an = new Analyzer(fileName);
//        TreeModel* mod = new TreeModel(an);*/
//    }
//    else
//        dashName = "dash_init_" + fileName;

//    repr->setBaseurl(setBaseURL(dashName));
//    repr->setSegmentList(setSegmentList(oneFile));
//    unsigned int* dim = getDimensions();
//    repr->setHeight(dim[0]);
//    repr->setWidth(dim[1]);
//    repr->setMimeType("video/mp4");
//    repr->setStartsWithSAP(1);
//}



QString MPDWriter::getOriginalFileName() const
{
    return originalFileName;
}

void MPDWriter::setOriginalFileName(const QString &value)
{
    originalFileName = value;
}
void MPDWriter::addRepresentation(const QString& fn, const bool& oneFile) {
    Analyzer *an = new Analyzer(fn);
    originalModel = new TreeModel(an);
    //qDebug()<<"mpd addrepr";
    //originalFileName = fn;
    qDebug()<<"funffun"<<fn;
    Representation* repr = new Representation();
    //qDebug()<<"mpd addrepr 2";
    QString dashName;
    //qDebug()<<"mpd addrepr 3";
    if(oneFile) {
        //qDebug()<<"mpd addrepr 4";
        dashName = "dash_" + originalFileName;/*
            Analyzer* an = new Analyzer(fileName);
            TreeModel* mod = new TreeModel(an);*/
    }
    else
        dashName = "dash_init_" + originalFileName;
    //qDebug()<<"mpd addrepr 5"<<originalFileName;

    BaseURL* baseURL = new BaseURL();
    baseURL->setContent(dashPath + "/" + dashName);
    repr->setBaseurl(baseURL);
    //qDebug()<<"mpd addrepr 6";
    repr->setSegmentList(setSegmentList(oneFile));
    //qDebug()<<"mpd addrepr 7";
    unsigned int* dim = getDimensions();
    repr->setHeight(dim[0]);
    repr->setWidth(dim[1]);
    qDebug()<<"heighwid"<<QString::number(dim[0])<<QString::number(dim[1]);
    repr->setMimeType("video/mp4");
    repr->setStartsWithSAP(1);
    representations.append(repr);
}

void MPDWriter::setDashPath(const QString &dPath) {
    dashPath = dPath;
}

SegmentList* MPDWriter::setSegmentList(bool oneFile) {
    qDebug()<<"setsegmn 1";
    SegmentList* slist = new SegmentList();
    Initialization* init = new Initialization();
    //qDebug()<<"setsegmn 2";
    if(oneFile) {
        //qDebug()<<"setsegmn 2.01"<<originalFileName;
        QList< std::shared_ptr<Box> > mdats = dashModel->getBoxes("mdat");
        //qDebug()<<"setsegmn 2.1";
        QList< std::shared_ptr<Box> > sidxs = dashModel->getBoxes("sidx");
        //qDebug()<<"setsegmn 3";
        init->setRange(QString::number(0) + "-" + QString::number(sidxs.back()->getOffset() - 1));
        //qDebug()<<"setsegmn 3.1";
        slist->setInitialization(init);
        //qDebug()<<"setsegmn 4";
        while(!sidxs.empty()) {
            //qDebug()<<"setsegmn 5";
            if(sidxs.size() == 1) {
                std::shared_ptr<Box> sidx = sidxs.back();
                //qDebug()<<"setsegmn 6";
                std::shared_ptr<Box> mdat = mdats.front();
                unsigned int firstMediaRange = sidx->getOffset();
                unsigned int secondMediaRange = mdat->getOffset() + mdat->getSize() - 1;
                QString mediaRange(QString::number(firstMediaRange) + "-" + QString::number(secondMediaRange));
                unsigned int secondIndexRange = sidx->getOffset() + sidx->getSize();
                QString indexRange(QString::number(firstMediaRange) + "-" + QString::number(secondIndexRange));
                slist->addSegmentURL(mediaRange, indexRange);
                sidxs.pop_back();
            }
            else {
                std::shared_ptr<Box> sidx1 = sidxs.back();
                sidxs.pop_back();
                std::shared_ptr<Box> sidx2 = sidxs.back();
                unsigned int firstMediaRange = sidx1->getOffset();
                unsigned int secondMediaRange = sidx2->getOffset() - 1;
                QString mediaRange(QString::number(firstMediaRange) + "-" + QString::number(secondMediaRange));
                unsigned int secondIndexRange = sidx1->getOffset() + sidx1->getSize();
                QString indexRange(QString::number(firstMediaRange) + "-" + QString::number(secondIndexRange));
                slist->addSegmentURL(mediaRange, indexRange);
            }
        }
    }
    else {
        init->setSourceURL("dash_init_" + originalFileName); //setting initalization
        slist->setInitialization(init);
        unsigned int index = 0;
        QString str("dash_" + QString::number(index) + "_" + originalFileName + "s");
        while(QFile(dashPath + "/" + str).exists()) {//setting SegmentList
            Analyzer* an = new Analyzer(dashPath + str);
            TreeModel* segmentModel = new TreeModel(an);
            slist->addSegmentURL(str);
            ++ index;
            str = QString("dash_" + QString::number(index) + "_" + originalFileName + "s");
        }
    }
    return slist;
}
