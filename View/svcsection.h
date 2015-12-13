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

#include "nalunit.h"
#include "svcwriter.h"
#include "nalxml.h"

class SvcSection : public QGroupBox {
    Q_OBJECT
public:
    SvcSection(QList<std::shared_ptr<NalUnit>> nu, QWidget *parent = 0);
    ~SvcSection();
private slots:
    void createMP4();
    //void writeXML();
protected:
    void prepareNALtree(QList<std::shared_ptr<NalUnit> > nalUnits);
    QList<QStandardItem *> prepareRow(const QString &first, const QString &second, const QString &third);

    QVBoxLayout *layout;
    QList<std::shared_ptr<NalUnit> > nalUnits;
};

#endif // SVCSECTION_H
