#include "svcsection.h"

SvcSection::SvcSection(NalUnitsBO *nalInfo, QWidget *parent) : nalUnitsBO(nalInfo), QGroupBox(parent) {
    layout = new QVBoxLayout;
    QLabel *label = new QLabel("NAL UNITS IN THE STREAM");

    label->setMaximumSize(1000,50);
    label->setMinimumSize(1000,30);
    QFont serifFont("Calibri", 11, QFont::Bold);
    QFont font("Calibri", 10, QFont::Normal);
    label->setFont(serifFont);

    layout->addWidget(label);

    prepareNALtree(nalUnitsBO->getNalUnits());

    QPushButton* createMP4 = new QPushButton("Create MP4");
    connect(createMP4, SIGNAL(clicked()), this, SLOT(createMP4()), Qt::QueuedConnection);
    QPushButton* writeBaseLayer = new QPushButton("Export base layer");
    connect(writeBaseLayer, SIGNAL(clicked()), this, SLOT(writeBaseLayer()), Qt::QueuedConnection);
    layout->addWidget(createMP4);
    layout->addWidget(writeBaseLayer);

    setLayout(layout);
}

SvcSection::~SvcSection() {
}

void SvcSection::createMP4() {
    SvcWriter* writer = new SvcWriter(nalUnitsBO);
    writer->writeMP4File("F:\\atmp.mp4");
}

void SvcSection::writeBaseLayer() {
    SvcWriter* writer = new SvcWriter(nalUnitsBO);
    writer->writeBaseLayer("F:\\aatmp");
}

void SvcSection::prepareNALtree(QList<std::shared_ptr<NalUnit> > nalUnits) {
    QTreeView* treeView = new QTreeView(this);
    QStandardItemModel* standardModel = new QStandardItemModel ;
    standardModel->setHorizontalHeaderItem(0, new QStandardItem("NAL unit type"));
    standardModel->setHorizontalHeaderItem(1, new QStandardItem("Size"));
    standardModel->setHorizontalHeaderItem(2, new QStandardItem("Offset"));

    for(int i = 0; i < nalUnits.size(); ++ i) {
        std::shared_ptr<NalUnit> nalUnit = nalUnits.at(i);
        QList<QStandardItem *> preparedRow =prepareRow(QString::number(i + 1) + ". " + nalUnit->getName() + " (" +
                                                       QString::number(nalUnit->getTypeCode()) + ")", QString::number(nalUnit->getLength()),
                                                       QString("0x") + QString::number(nalUnit->getOffset(), 16));
        QStandardItem *item = standardModel->invisibleRootItem();
        // adding a row to the invisible root item produces a root element
        item->appendRow(preparedRow);

        QList<QStandardItem *> secondRow;
        QString temp = nalUnit->getHeader();
        if(nalUnit->getInfo().length())
            temp.append("\n" + nalUnit->getInfo());
        secondRow<<new QStandardItem(temp);
        // adding a row to an item starts a subtree
        preparedRow.first()->appendRow(secondRow);
    }

    treeView->setModel(standardModel);
    treeView->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::MinimumExpanding);
    treeView->resizeColumnToContents(0);

    layout->addWidget(treeView);
}

QList<QStandardItem *> SvcSection::prepareRow(const QString &first, const QString &second, const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}
