#include "controller.h"

Controller::Controller(MainWindow *mw): window(mw) {
    connect(window, SIGNAL(fileSelected(QString)), this, SLOT(fileSelected(QString)), Qt::QueuedConnection);
    connect(window, SIGNAL(boxSelected(QItemSelectionModel*)), this, SLOT(boxSelected(QItemSelectionModel*)), Qt::QueuedConnection);
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
        QModelIndex child = model->index(id.row(), 2, id.parent());
        TreeItem* item = model->getChild(model->data(child, Qt::DisplayRole).toInt());
        QStandardItemModel* mod = item->getModel();
        mod->setHeaderData(0, Qt::Horizontal, tr(""));
        mod->setHeaderData(1, Qt::Horizontal, tr(""));
        window->printSelectedBox(mod, item);
    }
    else
        window->printSelectedBox(new QStandardItemModel(), new TreeItem());
}

