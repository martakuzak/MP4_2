#include "controller.h"

Controller::Controller(MainWindow *mw): window(mw) {
    dashWrap = new DashWrapper();
    makeConnection();
}
void Controller::makeConnection() {
    connect(window, SIGNAL(fileSelected(QString)), this, SLOT(fileSelected(QString)), Qt::QueuedConnection);
    connect(window, SIGNAL(boxSelected(QItemSelectionModel*)), this,
            SLOT(boxSelected(QItemSelectionModel*)), Qt::QueuedConnection);
    connect(window, SIGNAL(searchBox(QString)), this, SLOT(searchBox(QString)), Qt::QueuedConnection);
    connect(window, SIGNAL(dashFilesSelectedSignal(QAbstractItemModel*, bool)), this,
            SLOT(dashFilesSelected(QAbstractItemModel*, bool)), Qt::QueuedConnection);
}
////////////////////
void Controller::fileSelected(const QString& fileName) {
    if(model == NULL)
        delete model;
    Analyzer* analyzer = new Analyzer(fileName);
    model = new TreeModel(analyzer);
    window->fileAnalyzed(model, fileName);
}
//////////////////
void Controller::boxSelected(QItemSelectionModel *selection) {
    if(selection->hasSelection()) {
        QModelIndex id = selection->currentIndex();
        //qDbug()<<"wust"<<QString::number(id.row());
        QModelIndex child = model->index(id.row(), 2, id.parent());
        TreeItem* item = model->getChild(model->data(child, Qt::DisplayRole).toInt());
        QStandardItemModel* mod = item->getModel();
        mod->setHeaderData(0, Qt::Horizontal, tr(""));
        mod->setHeaderData(1, Qt::Horizontal, tr(""));
        window->printSelectedBox(mod, item);
    }
    else {
        //qDbug()<<"wut";
        window->printSelectedBox(new QStandardItemModel(), new TreeItem());
    }
}

void Controller::searchBox(const QString &boxType) {
    if(boxType.length() != 4) {
        window->showWarningDialog("Box type should has at least 4 characters.");
        return;
    }
    int row = 0;
    int col = 0;
    QModelIndexList Items = model->match(model->index(row,col),
                                             Qt::DisplayRole,
                                             QVariant::fromValue(QString(boxType)),
                                             -1,
                                             Qt::MatchRecursive);
    //    treeView->clearSelection();
    //    //no box found
    if(Items.size()==0) {
        window->showWarningDialog("No box found.");
        return;
    }
    //    //selects found boxes and expands their predecessors
    //    QModelIndex tmpId;
    //    while (!Items.isEmpty()) {
    //        QModelIndex backId = Items.back();
    //        tmpId = backId;
    //        QModelIndex tmpParent = tmpId.parent();
    //        while(tmpParent.isValid()) {
    //            treeView->setExpanded(tmpParent, true);
    //            tmpParent = tmpParent.parent();
    //        }
    //        treeView->selectionModel()->select(backId, QItemSelectionModel::Select | QItemSelectionModel::Rows);
    //        Items.pop_back();
    //    }
    //    QModelIndex child = model->index(tmpId.row(), 2, tmpId.parent());
    //    boxNameLabel->setText(model->getChild(model->data(child,
    //                                                      Qt::DisplayRole).toInt())->fullName());
    //    QString text= model->getChild(model->data(child,
    //                                              Qt::DisplayRole).toInt())->fullName();
    //    if(text!=NULL) {
    //        boxNameLabel->setText(text);
    //        //printSelectedBox(false, child);
    //    }
    //    mainLayout->update();
    QModelIndex tmpId = Items.front();
    QModelIndex child = model->index(tmpId.row(), 2, tmpId.parent());
    QString textLabel = model->getChild(model->data(child,
                                                    Qt::DisplayRole).toInt())->fullName();
    TreeItem* item = model->getChild(model->data(child, Qt::DisplayRole).toInt());
    QStandardItemModel* mod = item->getModel();
    mod->setHeaderData(0, Qt::Horizontal, tr(""));
    mod->setHeaderData(1, Qt::Horizontal, tr(""));
    window->boxesFound(Items, textLabel);
    //qDbug()<<"gowno";
    window->printSelectedBox(mod, item);
    //qDbug()<<"i co";
}
////////////////////////////////////////////
void Controller::dashFilesSelected(QAbstractItemModel* model, const bool& oneFile) {
    //for each file
    //create aFile
    //create mpdRepr

    //createMPD
    QDateTime local(QDateTime::currentDateTime());
    QString date = local.toString();
    date.replace(QString(":"), QString("_"));
    if(model->rowCount()) {
        dashWrap->setFileProp(model->index(0,0).data(Qt::DisplayRole).toString());
    }
    for ( int i = 0 ; i < model->rowCount() ; ++i ) {
        QString fileName = model->index( i, 0 ).data( Qt::DisplayRole ).toString() ;
        //qDbug()<<fileName<<"asd";
        //dashWrap->setDashCreator(fileName);
        bool result;
        if(oneFile)
            result = dashWrap->writeFile(date, fileName, 50);
        else
            result = dashWrap->writeFiles(date, fileName, 50);
        if(!result) {
            window->showWarningDialog("Error while writing files");
            return;
        }
    }
}

