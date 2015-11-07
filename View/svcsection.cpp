#include "svcsection.h"

SvcSection::SvcSection(QList<std::shared_ptr<NalUnit> > nalUnits, QWidget *parent):
    QGroupBox(parent) {
    qDebug()<<"SVC SECTION constructor 1";
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
        qDebug()<<"SVC SECTION num"<<i;
        std::shared_ptr<NalUnit> nalUnit = nalUnits.at(i);
        tmp->append(nalUnits.at(i)->getName());
        tmp->append("\n");
        //nalInfo->setText(nalInfo->toPlainText() + nalUnits.at(i)->getName() + "\n");
        nalInfo->setCurrentFont(serifFont);
        nalInfo->append(QString::number(i + 1) + ". " + nalUnit->getName());
        nalInfo->setCurrentFont(font);
        nalInfo->append("Offset : 0x" + (QString::number(nalUnit->getOffset(), 16)) + "");

        nalInfo->append("NalRefIdc : " + (QString::number(nalUnit->getNalRefIdc())));
        QString info = nalUnit->getInfo();
        if(info.length())
            nalInfo->append(info);
        //nalInfo->setCurrentFont(font);

        //qDebug()<<"SVC SECTION"<<nalUnits.at(i)->getName();
    }
    //nalInfo->setText(*tmp);
    qDebug()<<"SVC SECTION 11";

    layout->addWidget(label);
    qDebug()<<"SVC SECTION 12";
    layout->addWidget(nalInfo);
    qDebug()<<"SVC SECTION 13";
    setLayout(layout);
    qDebug()<<"SVC SECTION 14";
}

SvcSection::~SvcSection() {

}

