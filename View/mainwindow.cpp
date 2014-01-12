#include <QtWidgets>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    createActions();
    createMenu();

    setWindowTitle("MP4 ");

    setMinimumSize(160, 160);
    const int m_width = QApplication::desktop()->width();
    const int m_height = QApplication::desktop()->height();
    resize(0.8*m_width, 0.65*m_height);

    mainLayout = new QVBoxLayout();
    boxParseLayout = new QHBoxLayout();
    searchBoxLayout = new QGridLayout();
    boxInfoLayout = new QVBoxLayout();

    initializePointers();
    //AnalyzeSection *as = new AnalyzeSection();

    QWidget *window = new QWidget();
    setWindowIcon(QIcon("D://PDI//Code//Images//pear.png"));
    setCentralWidget(window);

    window->setLayout(mainLayout);
}
////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow() {
    delete fileMenu;
    //delete treeView;
    delete openAct;
    delete exitAct;
    delete helpMenu;
    delete helpAct;
    delete dashMenu;
    delete dashOneFileAct;
    delete dashSeparatedFilesAct;
    //delete nextSearchButton;
    //delete typeBoxType;
    //delete searchLabel;
    //delete searchBoxGroupBox;
    //delete boxParseGroupBox;
    //delete hSplitter;
    //delete vSplitter;
    delete mainLayout;
    //delete boxParseLayout;
    //delete searchBoxLayout;
    //delete fileList;
    //delete dashSection;
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeDashConnection() {
    connect(dashSection, SIGNAL(dashDirSig(QString)), this,
            SLOT(dashDirSelected(QString)), Qt::QueuedConnection);
    connect(dashSection, SIGNAL(dashFilesSelectedSignal(bool, QString)), this,
            SLOT(dashFilesSelected(bool, QString)), Qt::QueuedConnection);
    connect(dashSection, SIGNAL(removeFileSig(int)), this, SLOT(removedButtonClicked(int)), Qt::QueuedConnection);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeAnalyzeConnection() {
    connect(analyzeSection, SIGNAL(boxSelected(QItemSelectionModel*)), this,
            SLOT(selectionChanged(QItemSelectionModel*)), Qt::QueuedConnection);
    connect(analyzeSection, SIGNAL(searchBox(QString)), this,
            SLOT(searchButtonClicked(QString)), Qt::QueuedConnection);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createActions() {
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    searchBoxAct = new QAction(tr("&Search"), this);
    //connect(searchBoxAct, SIGNAL(triggered()), this, SLOT(searchButtonClicked()));

    helpAct = new QAction(tr("&Help"), this);
    connect(helpAct, SIGNAL(triggered()), this, SLOT(launchHelp()));

    dashOneFileAct = new QAction(tr("&Split into segments in one file"), this);
    connect(dashOneFileAct, SIGNAL(triggered()), this, SLOT(splitOneFile()));

    dashSeparatedFilesAct = new QAction(tr("&Split with each segment in separated file"), this);
    connect(dashSeparatedFilesAct, SIGNAL(triggered()), this, SLOT(splitIntoMoreFiles()));

    dashAct = new QAction(tr("&Switch to DASH menu"), this);
    connect(dashAct, SIGNAL(triggered()), this, SLOT(switchToDashMenu()));

}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createMenu() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    dashMenu = menuBar()->addMenu(tr("&MPEG-DASH"));
    dashMenu->addAction(dashOneFileAct);
    dashMenu->addAction(dashSeparatedFilesAct);
    dashMenu->addAction(dashAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setSearchBoxSection() {
    searchBoxGroupBox = new QGroupBox();
    searchBoxGroupBox->setTitle("Search for box");
    searchLabel = new QLabel("Type box type: ");
    searchLabel->setMaximumSize(200,40);

    typeBoxType = new QLineEdit();
    typeBoxType->setMaximumWidth(50);
    typeBoxType->setMaxLength(4);
    nextSearchButton = new QPushButton("Find");
    nextSearchButton->addAction(searchBoxAct);
   // connect(nextSearchButton,
     //       SIGNAL(clicked()),
       //     this, SLOT(searchButtonClicked()));

    searchBoxGroupBox->setMaximumHeight(50);
    searchBoxGroupBox->setMinimumHeight(40);

    searchBoxLayout->addWidget(searchLabel, 1, 0);
    searchBoxLayout->addWidget(typeBoxType, 1, 1);
    searchBoxLayout->addWidget(nextSearchButton, 1, 2);
    searchBoxLayout->setColumnStretch(10, 1);
    searchBoxGroupBox->setLayout(searchBoxLayout);

    vSplitter = new QSplitter();
    vSplitter->addWidget(searchBoxGroupBox);
    mainLayout->addWidget(vSplitter);

}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setBoxInfoSection(const QString& fileName, TreeModel *model) {
    if(!boxParseLayout->count()) {
        boxParseGroupBox = new QGroupBox();
        boxInfoGroupBox = new QGroupBox();
        treeView = new QTreeView(this);
        tableView = new QTableView();
        hSplitter = new QSplitter();
        boxNameLabel = new QLabel();
        boxNameLabel->setMaximumHeight(20);
        boxNameLabel->setFont(QFont("Arial", 13));
    }

    treeView->setModel(model);
    treeView->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    connect(treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(selectionChanged()));

    boxNameLabel->setSizePolicy(QSizePolicy::Expanding,
                                QSizePolicy::Expanding);
    boxNameLabel->clear();
    tableView->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Expanding);


    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->resizeSection(1, 300);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    boxInfoLayout->addWidget(boxNameLabel);
    boxInfoLayout->addWidget(tableView);
    boxInfoGroupBox->setLayout(boxInfoLayout);

    hSplitter->addWidget(treeView);
    hSplitter->addWidget(boxInfoGroupBox);
    hSplitter->setOrientation(Qt::Horizontal);
    boxParseLayout->addWidget(hSplitter);

    boxParseGroupBox->setLayout(boxParseLayout);
    boxParseGroupBox->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);

    vSplitter->addWidget(boxParseGroupBox);
    vSplitter->setOrientation(Qt::Vertical);

    //emit selectionChanged();
    setWindowTitle("MP4 " + fileName);
}

////////////////////////////////////////////////////////////////////////////////////////////
///Slots
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::openFile() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/");
    if(fileName.length()) {
        //delete dashSection;
        //dashSection = NULL;
        emit fileSelected(fileName);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::printSelectedBox(QStandardItemModel *mod, TreeItem *item) {
//    boxInfoLayout->removeWidget(tableView);
//    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    tableView->setModel(mod);
//    tableView->setSizePolicy(QSizePolicy::Expanding,
//                             QSizePolicy::Expanding);
//    if(mod->columnCount() > 1) {
//        tableView->horizontalHeader()->resizeSection(1, 300);
//        tableView->resizeColumnsToContents();
//        tableView->horizontalHeader()->setStretchLastSection(true);
//    }
//    boxInfoLayout->addWidget(tableView);
//    QString text = item->fullName();
//    if(text!=NULL) {
//        boxNameLabel->setText(text);
//    }
    qDebug()<<"printselectedbox mw1";
    mainLayout->removeWidget(analyzeSection);
    analyzeSection->printSelectedBox(mod, item);
    mainLayout->addWidget(analyzeSection);
}
///////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::boxesFound(QModelIndexList &Items, const QString &textLabel) {
    analyzeSection->boxesFound(Items, textLabel);
//    treeView->clearSelection();

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
//    boxNameLabel->setText(textLabel);

}
////////////////////////////////////////////////////////////
void MainWindow::splitOneFile() {
    //    QString fileName = title.mid(4);
    //    if(fileName.isEmpty()) {
    //        QMessageBox *infoBox = new QMessageBox(this);
    //        infoBox->setIcon(QMessageBox::Warning);
    //        infoBox->setText("No file specified");
    //        infoBox->show();
    //        return;
    //    }
    //    QDateTime local(QDateTime::currentDateTime());
    //    QString date = local.toString();
    //    date.replace(QString(":"), QString("_"));
    //    dashProxy = new DashWrapper(fileName, model, date);
    //    if(dashProxy->writeFile(50/*, dashFile*/)) {
    //        int last = fileName.lastIndexOf("\\");
    //        if(last == -1)
    //            last = fileName.lastIndexOf("/");
    //        QString name = fileName.mid(last + 1);
    //        QString path = fileName.mid(0, last + 1);
    //        path.append("DASH " + date + "/");
    //        name.replace(".mp4", ".mpd");
    //        QString mpdName = QString(path + "dash_" + name);
    //        QFile *mpdFile = new QFile(mpdName);
    //        if(mpdFile->open(QIODevice::ReadWrite)) {
    //            dashProxy->writeMPD(mpdFile, true);
    //            dashProxy->closeFileStream();
    //        }
    //        else {
    //            delete dashProxy;
    //            return;
    //        }
    //        mpdFile->close();
    //    }
    //    else {
    //        QMessageBox *infoBox = new QMessageBox(this);
    //        infoBox->setIcon(QMessageBox::Warning);
    //        infoBox->setText("Could not write file.");
    //        infoBox->show();
    //        return;
    //    }
    //    QMessageBox *infoBox = new QMessageBox(this);
    //    infoBox->setIcon(QMessageBox::Information);
    //    infoBox->setText("Dash files prepared.");
    //    infoBox->show();
    //    delete dashProxy;
}
////////////////////////////////////////////////////////////
void MainWindow::splitIntoMoreFiles() {
    //    QString fileName = title.mid(4);
    //    if(fileName.isEmpty()) {
    //        QMessageBox *infoBox = new QMessageBox(this);
    //        infoBox->setIcon(QMessageBox::Warning);
    //        infoBox->setText("No file specified");
    //        infoBox->show();
    //        return;
    //    }
    //    QDateTime local(QDateTime::currentDateTime());
    //    QString date = local.toString();
    //    date.replace(QString(":"), QString("_"));
    //    dashProxy = new DashWrapper(fileName, model, date);
    //    if(dashProxy->writeFiles(50/*, dashFile*/)) {
    //        //return;
    //        int last = fileName.lastIndexOf("\\");
    //        if(last == -1)
    //            last = fileName.lastIndexOf("/");
    //        QString name = fileName.mid(last + 1);
    //        QString path = fileName.mid(0, last + 1);
    //        path.append("DASH " + date + "/");
    //        name.replace(".mp4", ".mpd");
    //        QString mpdName = QString(path + "dash_" + name);
    //        QFile *mpdFile = new QFile(mpdName);
    //        if(mpdFile->open(QIODevice::ReadWrite)) {
    //            dashProxy->writeMPD(mpdFile, false);
    //        }
    //        else {
    //            dashProxy->closeFileStream();
    //            delete dashProxy;
    //            return;
    //        }
    //        mpdFile->close();
    //    }
    //    else {
    //        QMessageBox *infoBox = new QMessageBox(this);
    //        infoBox->setIcon(QMessageBox::Warning);
    //        infoBox->setText("Could not write file.");
    //        infoBox->show();
    //        return;
    //    }
    //    QMessageBox *infoBox = new QMessageBox(this);
    //    infoBox->setIcon(QMessageBox::Information);
    //    infoBox->setText("Dash files prepared.");
    //    infoBox->show();
    //    delete dashProxy;
}
////////////////////////////////////////////////////////////
void MainWindow::generateDash() {
    dashSection->generateDash();
}
///////////////////////////////////////////////////////////
void MainWindow::setDashDialog() {

}
////////////////////////////////////////////////////////////
void MainWindow::launchHelp() {
    //QDesktopServices::openUrl(QUrl("D://PDI//Code//help.html"));

}
void MainWindow::addFileToDash(QAbstractItemModel *fileModel) {
    dashSection->addFileToDash(fileModel);
    mainLayout->update();
}

void MainWindow::dashRowRemoved(QAbstractItemModel *fileModel, const bool empty) {
    dashSection->removeFileFromDash(fileModel, empty);
}

void MainWindow::initializePointers() {
    fileMenu = NULL;
    treeView = NULL;
    openAct = NULL;
    exitAct = NULL;
    helpMenu = NULL;
    helpAct = NULL;
    dashMenu = NULL;
    dashOneFileAct = NULL;
    dashSeparatedFilesAct = NULL;
    nextSearchButton = NULL;
    typeBoxType = NULL;
    searchLabel = NULL;
    searchBoxGroupBox = NULL;
    boxParseGroupBox = NULL;
    hSplitter = NULL;
    vSplitter = NULL;
    fileList = NULL;
    dashSection = NULL;
    analyzeSection = NULL;
}

void MainWindow::removeFileFromDash(QAbstractItemModel *fileModel) {
    dashSection->removeFileFromDash(fileModel);
}
///////////////////////////////////
void MainWindow::fileAnalyzed(TreeModel *mod, const QString& fileName) {
    if(dashSection != NULL) {
        delete dashSection;
        dashSection = NULL;
    }
   if(analyzeSection != NULL) {
        delete analyzeSection;
        analyzeSection = NULL;
   }
    analyzeSection = new AnalyzeSection(fileName, mod);
    makeAnalyzeConnection();
    mainLayout->addWidget(analyzeSection);
    setWindowTitle("MP4 " + fileName);
}
/////////////////////////////////
void MainWindow::selectionChanged(QItemSelectionModel *selection) {
    //QItemSelectionModel *selection = treeView->selectionModel();
    qDebug()<<"selectionchanged";
    emit boxSelected(selection);
}
//////////////////////////////////
void MainWindow::showWarningDialog(const QString& mes) {
    QMessageBox *infoBox = new QMessageBox(this);
    infoBox->setIcon(QMessageBox::Warning);
    infoBox->setText(mes);
    infoBox->show();
}
void MainWindow::showInfoDialog(const QString &mes) {
    QMessageBox *infoBox = new QMessageBox(this);
    infoBox->setIcon(QMessageBox::Information);
    infoBox->setText(mes);
    infoBox->show();
}

///////////////////////////////////
void MainWindow::searchButtonClicked(const QString& boxType) {
    //QString boxType = typeBoxType->text();
    emit searchBox(boxType);
}
////////////////////////////////////

void MainWindow::switchToDashMenu() {
    setWindowTitle("MP4 MPEG-DASH");
//    if(boxInfoLayout->count()) {
//        delete vSplitter;
//        vSplitter = NULL;

//        boxParseLayout = new QHBoxLayout();
//        searchBoxLayout = new QGridLayout();
//        boxInfoLayout = new QVBoxLayout();
//    }
    if(analyzeSection != NULL) {
        delete analyzeSection;
        analyzeSection = NULL;
    }
    if(dashSection == NULL) {
        dashSection = new DashSection();
        makeDashConnection();
        mainLayout->addWidget(dashSection);
    }
}
void MainWindow::dashFilesSelected(const bool &oneFile, const QString &url) {
    emit dashFilesSelectedSignal(oneFile, url);
}
void MainWindow::dashDirSelected(const QString &directoryName) {
    emit dashDirSelectedSig(directoryName);
}
void MainWindow::removedButtonClicked(const int &row) {
    emit removeFileSig(row);
}
