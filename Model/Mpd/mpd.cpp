#include "mpd.h"

ProgramInformation::ProgramInformation() {
    lang = "";
    moreInformationURL = "";
    title = "";
    source = "";
    copyright = "";
}
///////////////////////////////////////////////////////////////////////////////////////////
QString ProgramInformation::getLang() const {
    return lang;
}
///////////////////////////////////////////////////////////////////////////////////////////
void ProgramInformation::setLang(const QString &value) {
    lang = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString ProgramInformation::getCopyright() const {
    return copyright;
}
///////////////////////////////////////////////////////////////////////////////////////////
void ProgramInformation::setCopyright(const QString &value) {
    copyright = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString ProgramInformation::getSource() const{
    return source;
}
///////////////////////////////////////////////////////////////////////////////////////////
void ProgramInformation::setSource(const QString &value){
    source = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString ProgramInformation::getTitle() const {
    return title;
}
///////////////////////////////////////////////////////////////////////////////////////////
void ProgramInformation::setTitle(const QString &value) {
    title = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString ProgramInformation::getMoreInformationURL() const {
    return moreInformationURL;
}
///////////////////////////////////////////////////////////////////////////////////////////
void ProgramInformation::setMoreInformationURL(const QString &value){
    moreInformationURL = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
MPD::MPD() {
    type = "";
    xmlns = "";
    minBufferTime = "";
    mediaPresentationDuration = "";
    profiles = "";
    baseURL = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////
BaseURL *MPD::getBaseURL() const {
    return baseURL;
}
//////////////////////////////////////////////////////////////////////////////////////////
void MPD::setBaseURL(const QString& url){
    baseURL = new BaseURL();
    baseURL->setContent(url);
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPD::addPeriod() {
    Period *period = new Period();
    period->setStart(QString("PT0S"));
    periods.append(period);
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPD::addPeriod(Period *period) {
    periods.append(period);
}
///////////////////////////////////////////////////////////////////////////////////////////
QString MPD::getProfiles() const {
    return profiles;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPD::setProfiles(const QString &value) {
    profiles = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString MPD::getMediaPresentationDuration() const {
    return mediaPresentationDuration;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPD::setMediaPresentationDuration(const QString &value) {
    mediaPresentationDuration = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString MPD::getMinBufferTime() const {
    return minBufferTime;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPD::setMinBufferTime(const QString &value) {
    minBufferTime = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString MPD::getXmlns() const {
    return xmlns;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPD::setXmlns(const QString &value) {
    xmlns = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
QString MPD::getType() const {
    return type;
}
///////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////
void MPD::write(QXmlStreamWriter *stream ) {
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
    if(periods.size()) {
        int size = periods.size();
        for(int i = 0; i < size; ++i) {
            periods.at(i)->write(stream);
        }
    }
    stream->writeEndElement();
}
///////////////////////////////////////////////////////////////////////////////////////////
QString MPDWriter::getDuration() {
    QList<std::shared_ptr <Box> > mvhds = originalModel->getBoxes("mvhd");
    if(mvhds.empty())
        return QString("");
    MovieHeaderBox *mvhd = dynamic_cast <MovieHeaderBox*> (mvhds.back().get());
    unsigned long int timescale = mvhd->getTimeScale();
    unsigned long int duration = mvhd->getDuration();
    return getHMSFormat(duration/timescale);
}
///////////////////////////////////////////////////////////////////////////////////////////
unsigned int *MPDWriter::getDimensions() {
    unsigned int *ret = new unsigned int[2];
    QList<std::shared_ptr <Box> > visualEntries = originalModel->getBoxes("avc1");
    if(visualEntries.empty()) {
        visualEntries = originalModel->getBoxes("mp4v");
        if(visualEntries.empty()) {
            QList<std::shared_ptr <Box> > a = originalModel->getBoxes("ftyp");
            ret[0] = 0;
            ret[1] = 0;
            return ret;
        }
    }
    std::shared_ptr <Box> visualEntry = visualEntries.at(0);
    VisualSampleEntry *as = dynamic_cast <VisualSampleEntry*> (visualEntries.at(0).get());
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
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
MPDWriter::MPDWriter() {
    dashPath = "";
    dashModel = NULL;
    originalModel = NULL;
    originalFileName = "";
    mpd = NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPDWriter::init(bool oneFile) {
    if(oneFile) {
        Analyzer *an = new Analyzer(dashPath + "/dash_" + originalFileName);
        dashModel = new TreeModel(an);
        return;
    }
    Analyzer *an = new Analyzer(dashPath + "/dash_init_" + originalFileName);
    dashModel = new TreeModel(an);
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPDWriter::setMPD(const QString &url) {
    //MPD
    mpd = new MPD();
    //mpd->setId(unisgned int); //nieobowiazkowe, poza tym bedzie jedno mpd, wiec bez tego
    mpd->setProfiles(QString("urn:mpeg:dash:profile:full:2011")); //obowiązkowe; urn:mpeg:dash:profil:isoff-main:2011?
    mpd->setType("static"); //static jest domyślne, dynamic (MPD może być zmieniane); typowo dynamic przy live streamach
    //mpd->setAvailibilityStartTime(); //obowiazkowe przy dynamic
    //mpd->setAvailibilityEndTime(); //nieobowiazkowe
    mpd->setMediaPresentationDuration(getDuration()); //obowiazkowe dla static
    //mpd->setMinimumUpdatePeriod(); //w static zakazane
    mpd->setMinBufferTime("PT1.500000S"); //obowiązkowe - jak to ustawić?
    //mpd->getTimeShitBufferDepth(); //w staticu zbędne
    //mpd->getSuggestedPresentationDelay();//w staticu ignorowane
    //mpd->getMaxSegmentDuration(); //nieobowiązkowe
    //mpd->getMaxSubsegmentDuration(); //nieobowiązkowe
    mpd->addPeriod(setPeriod());
    mpd->setBaseURL(url);
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPDWriter::writeMPD(const QString &url) {
    QString mpdName = originalFileName;
    mpdName.replace(".mp4", ".mpd");
    QFile *mpdFile = new QFile(dashPath + "/" + mpdName);
    if(mpdFile->open(QIODevice::ReadWrite)) {
        setMPD(url);
        QXmlStreamWriter *stream = new QXmlStreamWriter(mpdFile);
        stream->setAutoFormatting(true);
        stream->writeStartDocument();
        mpd->write(stream);
        stream->writeEndDocument();
    }
    mpdFile->close();
}
///////////////////////////////////////////////////////////////////////////////////////////
AdaptationSet *MPDWriter::setAdaptationSet() {
    AdaptationSet *adapt = new AdaptationSet();
    adapt->addRepresentations(representations);
    return adapt;
}
///////////////////////////////////////////////////////////////////////////////////////////
Period *MPDWriter::setPeriod() {
    Period *period = new Period();
    period->setStart(QString("PT0S"));
    period->setDuration(getDuration());
    period->addAdaptationSet(setAdaptationSet());
    return period;
}
////////////////////////////////////////////////////////////////////////////////////////////
QString MPDWriter::getOriginalFileName() const {
    return originalFileName;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPDWriter::setOriginalFileName(const QString &value) {
    originalFileName = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPDWriter::addRepresentation(const QString& path, const QString& fn, const bool& oneFile) {
    Analyzer *an = new Analyzer(path + fn);
    originalModel = new TreeModel(an);
    Representation *repr = new Representation();
    QString dashName;
    if(oneFile)
        dashName = "dash_" + fn;
    else
        dashName = "dash_init_" + fn;

    BaseURL *baseURL = new BaseURL();
    baseURL->setContent(dashPath + "/" + dashName);
    //repr->setBaseurl(baseURL);
    //if(!segmentList) {
    SegmentBase *segmentBase = new SegmentBase();
    Initialization *init = new Initialization();
    QList< std::shared_ptr<Box> > sidxs = dashModel->getBoxes("sidx");
    if(oneFile) {
        init->setRange(QString::number(0) + "-" + QString::number(sidxs.back()->getOffset() - 1));
        init->setSourceURL(dashName);
        segmentBase->setInitialization(init);
    }
    else {
        init->setSourceURL(dashName); //setting initalization
        segmentBase->setInitialization(init);
    }
    repr->setSegmentBase(segmentBase);
    //}
    SegmentList *slist = setSegmentList(oneFile, dashName);
    repr->setBandwidth(getRepBandwidth(oneFile, slist));
    repr->setSegmentList(slist);
    unsigned int *dim = getDimensions();
    repr->setHeight(dim[0]);
    repr->setWidth(dim[1]);
    repr->setMimeType("video/mp4");
    repr->setStartWithSAP(1);
    representations.append(repr);
}
///////////////////////////////////////////////////////////////////////////////////////////
void MPDWriter::setDashPath(const QString &dPath) {
    dashPath = dPath;
}
///////////////////////////////////////////////////////////////////////////////////////////
unsigned int MPDWriter::getRepBandwidth(bool oneFile, /*const QString &dashName, */SegmentList *slist) {
    unsigned int mediaSize = 0;
    QList<std::shared_ptr<Box>> mvhds = originalModel->getBoxes("mvhd");
    MovieHeaderBox *mvhd = dynamic_cast <MovieHeaderBox*> (mvhds.back().get());
    unsigned long int duration = mvhd->getDuration();
    unsigned long int timescale = mvhd->getTimeScale();
    unsigned long time = duration/timescale;
    if(oneFile) {
        SegmentURL *first = slist->getSegmentURL(0);
        SegmentURL *last = slist->getSegmentURL(-1);
        QString firstRange = first->getMediaRange();
        QString lastRange = last->getMediaRange();
        int flast = firstRange.lastIndexOf("-");
        unsigned int firstID = firstRange.mid(0, flast).toInt();
        int llast = lastRange.lastIndexOf("-");
        unsigned int lastID = lastRange.mid(llast + 1).toInt();
        mediaSize = lastID - firstID;
    }
    else {
        unsigned int index = 0;
        QString str("dash_" + QString::number(index) + "_" + originalFileName + "s");
        while(QFile(dashPath + "/" + str).exists()) {//setting SegmentList
            QFile *segment = new QFile(dashPath + "/" +str);
            mediaSize += segment->size();
            ++ index;
            str = QString("dash_" + QString::number(index) + "_" + originalFileName + "s");
        }
    }
    if(duration == 0)
        return 0;
    return (8*mediaSize)/time;
}
///////////////////////////////////////////////////////////////////////////////////////////
SegmentList *MPDWriter::setSegmentList(bool oneFile, const QString& dashName) {
    SegmentList *slist = new SegmentList();
    Initialization *init = new Initialization();
    if(oneFile) {
        QList< std::shared_ptr<Box> > mdats = dashModel->getBoxes("mdat");
        QList< std::shared_ptr<Box> > sidxs = dashModel->getBoxes("sidx");
        init->setRange(QString::number(0) + "-" + QString::number(sidxs.back()->getOffset() - 1));
        init->setSourceURL(dashName);
        slist->setInitialization(init);
        while(!sidxs.empty()) {
            if(sidxs.size() == 1) {
                std::shared_ptr<Box> sidx = sidxs.back();
                std::shared_ptr<Box> mdat = mdats.front();
                unsigned int firstMediaRange = sidx->getOffset();
                unsigned int secondMediaRange = mdat->getOffset() + mdat->getSize() - 1;
                QString mediaRange(QString::number(firstMediaRange) + "-" + QString::number(secondMediaRange));
                unsigned int secondIndexRange = sidx->getOffset() + sidx->getSize() - 1;
                QString indexRange(QString::number(firstMediaRange) + "-" + QString::number(secondIndexRange));
                slist->addSegmentURL(mediaRange, indexRange, dashName);
                sidxs.pop_back();
            }
            else {
                std::shared_ptr<Box> sidx1 = sidxs.back();
                sidxs.pop_back();
                std::shared_ptr<Box> sidx2 = sidxs.back();
                unsigned int firstMediaRange = sidx1->getOffset();
                unsigned int secondMediaRange = sidx2->getOffset() - 1;
                QString mediaRange(QString::number(firstMediaRange) + "-" + QString::number(secondMediaRange));
                unsigned int secondIndexRange = sidx1->getOffset() + sidx1->getSize() - 1;
                QString indexRange(QString::number(firstMediaRange) + "-" + QString::number(secondIndexRange));
                slist->addSegmentURL(mediaRange, indexRange, dashName);
            }
        }
    }
    else {
        init->setSourceURL(dashName); //setting initalization
        slist->setInitialization(init);

        unsigned int index = 0;
        QString str("dash_" + QString::number(index) + "_" + originalFileName + "s");
        while(QFile(dashPath + "/" + str).exists()) {//setting SegmentList
            slist->addSegmentURL(str);
            ++ index;
            str = QString("dash_" + QString::number(index) + "_" + originalFileName + "s");
        }
    }
    return slist;
}
