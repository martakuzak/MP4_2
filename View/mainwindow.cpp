#include "mainwindow.h"

////////////////////////////////////////////////////////////////////////////////////////////
///Public
////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    createActions();
    createMenu();

    setWindowTitle("MP4 ");

    setMinimumSize(160, 160);
    /*const int m_width = QApplication::desktop()->width();
    const int m_height = QApplication::desktop()->height();*/
    const int m_width = 2000;
    const int m_height = 1000;
    resize(0.6*m_width, 0.6*m_height);

    mainLayout = new QVBoxLayout();

    initPointers();

    QWidget *window = new QWidget();
    setWindowIcon(QIcon("img/icon.png"));
    setCentralWidget(window);

    window->setLayout(mainLayout);
}
////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow() {
    delete openAct;
    delete exitAct;
    delete helpAct;
    delete mainLayout;
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::fileAnalyzed(TreeModel *model, const QString& fileName) {
    fileAnalyzed(model, fileName, tabs);
}

////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::fileAnalyzed(TreeModel *model, const QString& fileName, QTabWidget* &tabs) {
    if(dashSection != NULL) {
        delete dashSection;
        dashSection = NULL;
    }

    if(tabs == NULL) {
        tabs = new QTabWidget();
        makeTabsConnection();
        mainLayout->addWidget(tabs);
    }

    for (int i = 0; i < tabs->count(); ++ i) {
        if(tabs->tabText(i) == fileName) {
            tabs->setCurrentIndex(i);
            return;
        }
    }
    AnalyzeSection* analyzeSection = new AnalyzeSection(model);
    tabs->addTab(analyzeSection, fileName);
    makeAnalyzeConnection(analyzeSection);
    tabs->setCurrentIndex(tabs->count() - 1);
    tabs->setTabsClosable(true);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::printSelectedBox(QStandardItemModel *model, TreeItem *item) {
    ((AnalyzeSection*)(tabs->currentWidget()))->printSelectedBox(model,item);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectBoxesFound(QModelIndexList &boxes, const QString &fullName) {
    ((AnalyzeSection*)(tabs->currentWidget()))->selectBoxesFound(boxes, fullName);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::showWarningDialog(const QString& mes) {

    QMessageBox *infoBox = new QMessageBox(this);
    infoBox->setIcon(QMessageBox::Warning);
    infoBox->setText(mes);
    infoBox->show();
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::showInfoDialog(const QString &mes) {
    QMessageBox *infoBox = new QMessageBox(this);
    infoBox->setIcon(QMessageBox::Information);
    infoBox->setText(mes);
    infoBox->show();
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setDashFileList(QAbstractItemModel *fileModel, const bool disabled) {
    dashSection->setDashFileList(fileModel, disabled);
}
////////////////////////////////////////////////////////////////////////////////////////////
///Slots
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::openFileSelected() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/");
    if(fileName.length()) {
        emit fileSelected(fileName);
    }

}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectionChanged(QItemSelectionModel *selection) {
    emit boxSelected(selection, tabs->tabText(tabs->currentIndex()));
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::searchButtonClicked(const QString& boxType) {
    emit searchBox(boxType, tabs->tabText(tabs->currentIndex()));
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::switchToDashMenuSelected() {
    setWindowTitle("MP4 MPEG-DASH");
    if(tabs != NULL) {
        delete tabs;
        tabs = NULL;
    }

    if(svcSection != NULL) {
        delete svcSection;
        svcSection = NULL;
    }

    if(dashSection == NULL) {
        dashSection = new DashSection();
        makeDashConnection();
        mainLayout->addWidget(dashSection);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::dashFilesSelected(const bool &oneFile, const QString &url) {
    emit dashFilesSelectedSignal(oneFile, url);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::dashDirSelected(const QString &directoryName) {
    emit dashDirSelectedSig(directoryName);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::removeButtonClicked(const int &row) {
    emit removeFileSig(row);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::launchHelpSelected() {
    QDesktopServices::openUrl(QUrl("help.html"));
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::tabClosed(int rowId) {
    if(tabs->count() > rowId)
        tabs->removeTab(rowId);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::nalParseSelected() {    
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/");

    setWindowTitle("MP4 - " + fileName);
    if(fileName.length()) {
        emit nalFileSelected(fileName);

        if(dashSection != NULL) {
            delete dashSection;
            dashSection = NULL;
        }

        if(tabs == NULL) {
            tabs = new QTabWidget();
            makeTabsConnection();
            mainLayout->addWidget(tabs);
        }

        for (int i = 0; i < tabs->count(); ++ i) {
            if(tabs->tabText(i) == ("SVC : " + fileName)) {
                tabs->setCurrentIndex(i);
                return;
            }
        }

        NALParser nalParser(fileName);
        NalUnitsBO* nalUnitsBO = nalParser.parseFile();
        if(!nalUnitsBO->getNalUnits().empty()) {
            svcSection = new SvcSection(nalUnitsBO, this);
            tabs->addTab(svcSection, "SVC : " + fileName);
            tabs->setCurrentIndex(tabs->count() - 1);
            tabs->setTabsClosable(true);

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Export NAL stream to xml?", "Export NAL stream to xml file?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                NALXml *nalXml = new NALXml(changeExtension(fileName, "xml"), nalUnitsBO);
                nalXml->writeXML();
            }
        } else
            showWarningDialog("No NAL found.");


    }
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::rawStreamSelected() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select raw stream"), "/");

    setWindowTitle("MP4 - " + fileName);
    if(fileName.length()) {
        emit rawStreamSelected(fileName);
        if(tabs != NULL) {
            delete tabs;
            tabs = NULL;
        }

        if(dashSection != NULL) {
            delete dashSection;
            dashSection = NULL;
        }

    }
}
////////////////////////////////////////////////////////////////////////////////////////////
///Private
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::initPointers() {
    dashSection = NULL;
    tabs = NULL;
    svcSection = NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createMenu() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *dashMenu = menuBar()->addMenu(tr("&MPEG-DASH"));
    dashMenu->addAction(dashAct);

    QMenu *nalMenu = menuBar()->addMenu(tr("&Parse stream"));
    nalMenu->addAction(nalAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createActions() {
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFileSelected()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    helpAct = new QAction(tr("&Help"), this);
    connect(helpAct, SIGNAL(triggered()), this, SLOT(launchHelpSelected()));

    dashAct = new QAction(tr("&Switch to DASH menu"), this);
    connect(dashAct, SIGNAL(triggered()), this, SLOT(switchToDashMenuSelected()));

    nalAct = new QAction(tr("&Search for NAL units"), this);
    connect(nalAct, SIGNAL(triggered()), this, SLOT(nalParseSelected()));

    svcAct = new QAction(tr("&Create MP4 file"), this);
    //connect(svcAct, SIGNAL(triggered()), this, SLOT(rawStreamSelected()));
}
////////////////////////////////////////////////////////////////////////////////////////////
QString MainWindow::changeExtension(const QString& fileName, const QString& newExtension) {
    int last = fileName.lastIndexOf(".");
    if(last == -1)
        return fileName + "." + newExtension;
    return fileName.mid(0, last + 1) + newExtension;
}
///////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeDashConnection() {
    connect(dashSection, SIGNAL(dashDirSig(QString)), this,
            SLOT(dashDirSelected(QString)), Qt::QueuedConnection);
    connect(dashSection, SIGNAL(dashFilesSelectedSignal(bool, QString)), this,
            SLOT(dashFilesSelected(bool, QString)), Qt::QueuedConnection);
    connect(dashSection, SIGNAL(removeFileSig(int)), this, SLOT(removeButtonClicked(int)), Qt::QueuedConnection);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeAnalyzeConnection(AnalyzeSection* analyze) {
    connect(analyze, SIGNAL(boxSelected(QItemSelectionModel*)), this,
            SLOT(selectionChanged(QItemSelectionModel*)), Qt::QueuedConnection);
    connect(analyze, SIGNAL(searchButtonClicked(QString)), this,
            SLOT(searchButtonClicked(QString)), Qt::QueuedConnection);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeSvcConnection() {
    //connect(this, SIGNAL(streamSelected(const QString& filePath)), this, SLOT(
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeTabsConnection() {
    connect(tabs, SIGNAL(tabCloseRequested(int)), this,
            SLOT(tabClosed(int)), Qt::QueuedConnection);
}
