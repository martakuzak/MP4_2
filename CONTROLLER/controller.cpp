#include "controller.h"

Controller::Controller(MainWindow *mw): window(mw) {
    dashWrap = new DashWrapper();
    fileModel = new QStandardItemModel();
    makeConnection();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Controller::makeConnection() {
    connect(window, SIGNAL(fileSelected(QString)), this, SLOT(fileSelected(QString)), Qt::QueuedConnection);
    connect(window, SIGNAL(boxSelected(QItemSelectionModel*)), this,
            SLOT(boxSelected(QItemSelectionModel*)), Qt::QueuedConnection);
    connect(window, SIGNAL(searchBox(QString)), this, SLOT(searchBox(QString)), Qt::QueuedConnection);
    connect(window, SIGNAL(dashFilesSelectedSignal(bool, QString, bool)), this,
            SLOT(dashFilesSelected(bool, QString, bool)), Qt::QueuedConnection);
    connect(window, SIGNAL(dashDirSelectedSig(QString)), this,
            SLOT(dashDirSelected(QString)), Qt::QueuedConnection);
    connect(window, SIGNAL(removeFileSig(int)), this, SLOT(removeFile(int)), Qt::QueuedConnection);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Controller::fileSelected(const QString& fileName) {
    if(model == NULL)
        delete model;
    Analyzer *analyzer = new Analyzer(fileName);
    model = new TreeModel(analyzer);
    window->fileAnalyzed(model, fileName);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Controller::boxSelected(QItemSelectionModel *selection) {
    if(selection->hasSelection()) {
        QModelIndex id = selection->currentIndex();
        QModelIndex child = model->index(id.row(), 2, id.parent());
        TreeItem *item = model->getChild(model->data(child, Qt::DisplayRole).toInt());
        QStandardItemModel *mod = item->getModel();
        mod->setHeaderData(0, Qt::Horizontal, tr(""));
        mod->setHeaderData(1, Qt::Horizontal, tr(""));
        window->printSelectedBox(mod, item);
    }
    else
        window->printSelectedBox(new QStandardItemModel(), new TreeItem());
}
//////////////////////////////////////////////////////////////////////////////////////////////
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
    if(Items.size()==0) {
        window->showWarningDialog("No box found.");
        return;
    }
    QModelIndex tmpId = Items.front();
    QModelIndex child = model->index(tmpId.row(), 2, tmpId.parent());
    QString textLabel = model->getChild(model->data(child,
                                                    Qt::DisplayRole).toInt())->fullName();
    TreeItem *item = model->getChild(model->data(child, Qt::DisplayRole).toInt());
    QStandardItemModel *mod = item->getModel();
    mod->setHeaderData(0, Qt::Horizontal, tr(""));
    mod->setHeaderData(1, Qt::Horizontal, tr(""));
    window->selectBoxesFound(Items, textLabel);
    window->printSelectedBox(mod, item);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Controller::dashFilesSelected(const bool& oneFile, const QString &url, const bool &slist) {
    QDateTime local(QDateTime::currentDateTime());
    QString date = local.toString();
    date.replace(QString(":"), QString("_"));
    dashWrap->clear();
    if(fileModel->rowCount()) {
        dashWrap->setFileProp(fileModel->index(0,0).data(Qt::DisplayRole).toString());
    }
    for ( int i = 0 ; i < fileModel->rowCount() ; ++i ) {
        QString fileName = fileModel->index( i, 0 ).data( Qt::DisplayRole ).toString() ;
        bool result;
        if(oneFile)
            result = dashWrap->writeFile(date, fileName, 50);
        else
            result = dashWrap->writeFiles(date, fileName, 50);
        if(!result) {
            window->showWarningDialog("Error while writing files");
            return;
        }
        qDebug()<<QString::number(i)<<fileModel->index(i,0).data(Qt::DisplayRole).toString();
        dashWrap->setFileProp(fileModel->index(i,0).data(Qt::DisplayRole).toString());
        dashWrap->setMpdProps();
        if(!i) {
            dashWrap->initMPD(oneFile, slist);
        }
        dashWrap->addRepresentation(oneFile);
    }

    dashWrap->writeMPD(oneFile, url);
    window->showInfoDialog("Dash files generated.");
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Controller::dashDirSelected(const QString &dir) {
    if(dir.length()) {
        QDir *directory = new QDir(dir);
        QStringList files;
        files = directory->entryList(QStringList("*.mp4"),
                               QDir::Files | QDir::NoSymLinks);
        if(!files.empty()) {
            fileModel->clear();
            while(!files.empty()) {
                QList<QStandardItem*> list;
                QStandardItem *tmpItem = new QStandardItem();
                tmpItem->setText(dir + "/" + files.back());
                list.append(tmpItem);
                fileModel->appendRow(list);
                files.pop_back();
            }
            window->setDashFileList(fileModel);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Controller::removeFile(const int &row) {
        if(row >= 0 && row < (fileModel->rowCount())) {
            fileModel->removeRow(row);
            if(fileModel->rowCount())
                window->setDashFileList(fileModel);
            else
                window->setDashFileList(fileModel, false);
        }
}
