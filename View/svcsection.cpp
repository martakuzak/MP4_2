#include "svcsection.h"

SvcSection::SvcSection(QList<std::shared_ptr<NalUnit> > nalUnits, QWidget *parent):
    QGroupBox(parent) {
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel("NAL UNITS IN THE STREAM");

    label->setMaximumSize(1000,50);
    label->setMinimumSize(1000,30);
    QFont serifFont("Calibri", 11, QFont::Bold);
    QFont font("Calibri", 10, QFont::Normal);
    label->setFont(serifFont);
    nalInfo = new QTextEdit();
    nalInfo->setAcceptRichText(true);

    qDebug()<<"SVC SECTION"<<nalUnits.size();
    QString* tmp = new QString("");
    for(int i = 0; i < nalUnits.size(); ++ i) {
        tmp->append(nalUnits.at(i)->getName());
        tmp->append("\n");
        //nalInfo->setText(nalInfo->toPlainText() + nalUnits.at(i)->getName() + "\n");
        nalInfo->setCurrentFont(serifFont);
        nalInfo->append(QString::number(i + 1) + ". " + nalUnits.at(i)->getName());

        nalInfo->setCurrentFont(font);
        nalInfo->append("Offset : 0x" + (QString::number(nalUnits.at(i)->getOffset(), 16)) + "");

        nalInfo->append("NalRefIdc : " + (QString::number(nalUnits.at(i)->getNalRefIdc())) + "\n");
        //nalInfo->setCurrentFont(font);

        //qDebug()<<"SVC SECTION"<<nalUnits.at(i)->getName();
    }
    //nalInfo->setText(*tmp);

    layout->addWidget(label);
    layout->addWidget(nalInfo);
    setLayout(layout);

}

SvcSection::~SvcSection() {

}

