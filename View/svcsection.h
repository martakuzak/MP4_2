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

#include "nalunit.h"

class SvcSection : public QGroupBox {
    Q_OBJECT
public:
    SvcSection(QList<std::shared_ptr<NalUnit>> nalUnits, QWidget *parent = 0);
    ~SvcSection();
protected:
    QTextEdit* nalInfo;
};

#endif // SVCSECTION_H