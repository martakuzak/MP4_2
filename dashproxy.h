#ifndef DASHPROXY_H
#define DASHPROXY_H

#include "dashcreator.h"
#include "mpd.h"
#include "treemodel.h"

class TreeModel;
class DashCreator;
class MPDWriter;

class DashProxy {
public:
    DashProxy(const QString& fileName, TreeModel* model);
    void closeFileStream();
    void writeFile(const unsigned int &maxSampleNum, QFile* dashFile);
    void writeMPD(QFile* mpdFile);

private:
    DashCreator* dashCreator;
    MPDWriter* mpdWriter;
};

#endif // DASHPROXY_H
