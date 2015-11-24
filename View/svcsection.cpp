#include "svcsection.h"

SvcSection::SvcSection(QList<std::shared_ptr<NalUnit> > nalUnits, QWidget *parent):
    QGroupBox(parent) {
    //qDebug()<<"SVC SECTION constructor 1";
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel("NAL UNITS IN THE STREAM");

    label->setMaximumSize(1000,50);
    label->setMinimumSize(1000,30);
    QFont serifFont("Calibri", 11, QFont::Bold);
    QFont font("Calibri", 10, QFont::Normal);
    label->setFont(serifFont);

    QTreeView* treeView = new QTreeView(this);
    QStandardItemModel* standardModel = new QStandardItemModel ;
    standardModel->setHorizontalHeaderItem(0, new QStandardItem("NAL unit type"));
    standardModel->setHorizontalHeaderItem(1, new QStandardItem("Offset"));

    QString* tmp = new QString("");
    for(int i = 0; i < nalUnits.size(); ++ i) {
        std::shared_ptr<NalUnit> nalUnit = nalUnits.at(i);
        tmp->append(nalUnits.at(i)->getName());
        tmp->append("\n");

        QList<QStandardItem *> preparedRow =prepareRow(QString::number(i + 1) + ". " + nalUnit->getName() + " (" +
                                                       QString::number(nalUnit->getTypeCode()) + ")", QString("0x") +QString::number(nalUnit->getOffset(), 16));
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
    layout->addWidget(label);
    layout->addWidget(treeView);
    QPushButton* createMP4 = new QPushButton("Create MP4 file");
    layout->addWidget(createMP4);

    setLayout(layout);
}

SvcSection::~SvcSection() {

}

QList<QStandardItem *> SvcSection::prepareRow(const QString &first, const QString &second)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    return rowItems;
}

