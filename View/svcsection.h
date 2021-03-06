#ifndef SVCSECTION_H
#define SVCSECTION_H

#include <QObject>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QFont>
#include <QList>
#include <memory>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAction>
#include <QString>

#include "nalunit.h"
#include "svcwriter.h"
#include "nalxml.h"
#include "nalunitsbo.h"

class SvcSection : public QGroupBox {
    Q_OBJECT
public:
    SvcSection(NalUnitsBO* nalInfo, QWidget *parent = 0);
    ~SvcSection();
private slots:
    void createMP4();
    void writeBaseLayer();
    //void writeXML();
protected:
    void prepareNALtree(QList<std::shared_ptr<NalUnit> > nalUnits);
    QList<QStandardItem *> prepareRow(const QString &first, const QString &second, const QString &third);

    QVBoxLayout *layout;
    NalUnitsBO* nalUnitsBO;
};

#endif // SVCSECTION_H
