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
///////////
MPD::MPD()
{}
/////////////
void MPD::addPeriod() {
    Period period;
    period.setStart(QString("PT0S"));

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

QList<Period> MPD::getPeriods() const{
    return periods;
}

void MPD::setPeriods(const QList<Period> &value){
    periods = value;
}

/////////////
/// \brief MPD::write
/// \param stream
///
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
    stream->writeEndElement();
}
/////////////////////////////////////////////////////////////////////////////////////////
QString MPDWriter::getDuration() {
    QList<std::shared_ptr <Box> > mvhds = model->getBoxes("mvhd");
    if(mvhds.empty())
        return QString("");
    std::shared_ptr <Box> mvhd = mvhds.back();
    unsigned long int timescale = mvhd->getTimeScale();
    unsigned long int duration = mvhd->getDuration();
    return getHMSFormat(duration/timescale);
}
/////////////////////////////////////////////////////////////////////////////////////////
QString MPDWriter::getHMSFormat(const double& value) {
    double durationInSec = value;
    unsigned int hours = durationInSec/3600;
    durationInSec -= 3600*hours;
    unsigned int minutes = durationInSec/60;
    durationInSec -= 60*minutes;
    return QString("PT" + QString::number(hours) + "H" + QString::number(minutes) + "M" + QString::number(durationInSec) + "S");
}

/////////////////////////////////////////////////////////////////////////////////////////
MPDWriter::MPDWriter(const QString& fn, TreeModel *mod): filename(fn), model(mod) {
    Analyzer* an = new Analyzer(fn);
    dashModel = new TreeModel(an);
}
void MPDWriter::setMPD() {
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
    setSegmentList();
}
////////////////////////
void MPDWriter::writeMPD(QFile* file) {
    setMPD();
    stream = new QXmlStreamWriter(file);
    stream->setAutoFormatting(true);
    stream->writeStartDocument();
    slist->write(stream);
    /*BaseURL b;
    b.setByteRange("100-200");
    b.setServiceLocation("u marty");
    b.setContent("zawartosc");

    QList<Representation> repr;
    Representation r;
    r.setBandwidth(200);
    r.setMimeType("mime");
    r.setStartsWithSAP(1);
    r.setBaseurl(b);
    repr.append(r);


    AdaptationSet* adapt = new AdaptationSet();
    adapt->setBitstreamSwitching(false);
    adapt->setLang("polish");
    adapt->setMaxWidth(14);
    //adapt->setRepresentations(repr);

    period = new Period();
    period->setDuration("dnufs");
    period->setId(3);
    period->addAdaptationSet();

    file->open(QIODevice::WriteOnly | QIODevice::Text);
    stream = new QXmlStreamWriter(file);
    stream->setAutoFormatting(true);
    stream->writeStartDocument();
    mpd->write(stream);
    period->write(stream);
    stream->writeEndDocument();*/
    file->close();
}
////////////////////////
void MPDWriter::setProgramInformation() {
    programInformation = new ProgramInformation();
    //    programInformation->setCopyright();//nic nieobowiązkowe
    //    programInformation->setLang();
    //    programInformation->setMoreInformationURL();
    //    programInformation->setSource();
    //    programInformation->setTitle();
}
////////////////////////
void MPDWriter::setSegmentList() {
    slist = new SegmentList();
    Initialization* init = new Initialization();
    QList< std::shared_ptr<Box> > mdats = dashModel->getBoxes("mdat");
    QList< std::shared_ptr<Box> > sidxs = dashModel->getBoxes("sidx");
    init->setRange(QString::number(0) + "-" + QString::number(sidxs.back()->getOffset() - 1));
    slist->setInitialization(init);
    while(!sidxs.empty()) {
        if(sidxs.size() == 1) {
            std::shared_ptr<Box> sidx = sidxs.back();
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
        //sidxs.pop_back();
    }
    while(!mdats.empty()) {
        qDebug()<<"mdats"<<QString::number(mdats.back()->getOffset());
        mdats.pop_back();
    }
}

