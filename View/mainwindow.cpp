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

    initializePointers();

    QWidget *window = new QWidget();
    setWindowIcon(QIcon("D://PDI//Code//Images//pear.png"));
    setCentralWidget(window);

    window->setLayout(mainLayout);
}
////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow() {
    delete fileMenu;
    delete openAct;
    delete exitAct;
    delete helpMenu;
    delete helpAct;
    delete dashMenu;
    delete mainLayout;
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

    helpAct = new QAction(tr("&Help"), this);
    connect(helpAct, SIGNAL(triggered()), this, SLOT(launchHelp()));

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
    dashMenu->addAction(dashAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
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
        emit fileSelected(fileName);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::printSelectedBox(QStandardItemModel *mod, TreeItem *item) {
    mainLayout->removeWidget(analyzeSection);
    analyzeSection->printSelectedBox(mod, item);
    mainLayout->addWidget(analyzeSection);
}
///////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::boxesFound(QModelIndexList &Items, const QString &textLabel) {
    analyzeSection->boxesFound(Items, textLabel);
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
    openAct = NULL;
    exitAct = NULL;
    helpMenu = NULL;
    helpAct = NULL;
    dashMenu = NULL;
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
    emit searchBox(boxType);
}
////////////////////////////////////

void MainWindow::switchToDashMenu() {
    setWindowTitle("MP4 MPEG-DASH");
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
