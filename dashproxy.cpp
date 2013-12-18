#include "dashproxy.h"

DashProxy::DashProxy(const QString& fileName, TreeModel* model) {
    dashCreator = new DashCreator(fileName, model);
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashProxy::closeFileStream() {
    dashCreator->closeFileStream();
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned long int DashProxy::mdatSize(const unsigned long int& firstSample, const unsigned int& sampleNumber, std::shared_ptr<Box>& stsz) {
    return dashCreator->mdatSize(firstSample, sampleNumber, stsz);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMdat(const unsigned long int& firstSample, const unsigned int& sampleNumber, std::shared_ptr<Box>& stsz,
                                  QFile* dashFile) {
    return dashCreator->writeMdat(firstSample, sampleNumber, stsz, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMdia(QFile* dashFile) {
    return dashCreator->writeMdia(dashFile);
}////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMinf(QFile* dashFile) {
    return dashCreator->writeMinf(dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMoof(const unsigned long int& sequenceNumber, const unsigned int& trackID,
                                  const unsigned long &baseMediaDecodeTime, const unsigned int& trunFlag2, const unsigned int& trunFlag3,
                                  const unsigned int& sampleCount, const signed int& dataOffset, const unsigned int& firstSampleFlags,
                                  const unsigned long int& firstSample, std::shared_ptr<Box>& stsz, QFile* dashFile) {
    return dashCreator->writeMoof(sequenceNumber, trackID, baseMediaDecodeTime, trunFlag2, trunFlag3, sampleCount, dataOffset,
                                  firstSampleFlags, firstSample, stsz, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMoov(QFile* dashFile) {
    return dashCreator->writeMoov(dashFile);
}

////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMfhd(const unsigned long int& sequenceNumber, QFile* dashFile) {
    return dashCreator->writeMfhd(sequenceNumber, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeTraf(const unsigned int& trackID, const unsigned long &baseMediaDecodeTime, const unsigned int& trunFlag2,
                                  const unsigned int& trunFlag3, const unsigned int& sampleCount, const signed int& dataOffset,
                                  const unsigned int& firstSampleFlags, const unsigned long int& firstSample, std::shared_ptr<Box>& stsz,
                                  QFile* dashFile) {
    return dashCreator->writeTraf(trackID, baseMediaDecodeTime, trunFlag2, trunFlag3, sampleCount, dataOffset, firstSampleFlags, firstSample,
                                  stsz, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeTrak(QFile* dashFile) {
    return dashCreator->writeTrak(dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeTfhd(const unsigned int& trackID, QFile* dashFile) {
    return dashCreator->writeTfhd(trackID, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeTfdt(const unsigned long &baseMediaDecodeTime, QFile* dashFile) {
    return dashCreator->writeTfdt(baseMediaDecodeTime, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeTrun(const unsigned int& flag2, const unsigned int& flag3, const unsigned int& sampleCount,
                                  const signed int& dataOffset, const unsigned int& firstSampleFlags, const unsigned long int& firstSample,
                                  std::shared_ptr<Box>& stsz, QFile* dashFile) {
    return dashCreator->writeTrun(flag2, flag3, sampleCount, dataOffset, firstSampleFlags, firstSample, stsz, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy:: writeSidx(const unsigned short int& version, const unsigned int& referenceID, const unsigned int& timescale,
                                   const unsigned long int& earliestPresentationTime, const unsigned long int& firstOffset,
                                   const unsigned int &referenceCount, const QList<unsigned short int>& referenceType,
                                   const QList<unsigned long int>& referenceSize, const QList<unsigned long int>& subsegmentDuration,
                                   const QList <unsigned short int>& startsWithSAP, const QList <unsigned short int>& SAPType,
                                   const QList <unsigned long int>& SAPDeltaTime, QFile* dashFile) {
    return dashCreator->writeSidx(version, referenceID, timescale, earliestPresentationTime, firstOffset, referenceCount, referenceType,
                                  referenceSize, subsegmentDuration, startsWithSAP, SAPType, SAPDeltaTime, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeStbl(QFile* dashFile) {
    return dashCreator->writeStbl(dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeFree(QFile* dashFile) {
    return dashCreator->writeFree(dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeFtyp(QFile* dashFile) {
    return dashCreator->writeFtyp(dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMvhd(QFile* dashFile) {
    return dashCreator->writeMvhd(dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMehd(QFile* dashFile) {
    return dashCreator->writeMehd(dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeMvex(QFile* dashFile) {
    return dashCreator->writeMvex(dashFile);
}

////////////////////////////////////////////////////////////////////////////////////////////
unsigned int DashProxy::writeTrex(QFile* dashFile) {
    return dashCreator->writeTrex(dashFile);
}

////////////////////////////////////////////////////////////////////////////////////////////
void DashProxy::writeSegments(const unsigned int &maxSampleNum, QFile* dashFile) {
    dashCreator->writeSegments(maxSampleNum, dashFile);
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashProxy::writeFile(const unsigned int &maxSampleNum, QFile* dashFile) {
    dashCreator->writeFile(maxSampleNum, dashFile);
}


