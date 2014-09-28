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
    const int m_width = QApplication::desktop()->width();
    const int m_height = QApplication::desktop()->height();
    resize(0.6*m_width, 0.6*m_height);

    mainLayout = new QVBoxLayout();
    tabs = new QTabWidget();
    makeTabsConnection();
    analyzedFiles = new QHash<QString, std::shared_ptr<AnalyzeSection>>;
    mainLayout->addWidget(tabs);

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
    if(dashSection != NULL) {
        delete dashSection;
        dashSection = NULL;
    }

    if(analyzedFiles->contains(fileName)) {
        for (int i = 0; i < tabs->count(); ++ i) {
            if(tabs->tabText(i) == fileName) {
                tabs->setCurrentIndex(i);
                break;
            }
        }
    } else {
        std::shared_ptr<AnalyzeSection> analyzeSection = std::shared_ptr<AnalyzeSection>(new AnalyzeSection(model));
        analyzedFiles->insert(fileName, analyzeSection);
        tabs->addTab(analyzeSection.get(), fileName);
        makeAnalyzeConnection(analyzeSection);
        tabs->setCurrentIndex(tabs->count() - 1);
        tabs->setTabsClosable(true);
        //mainLayout->addWidget(analyzeSection);
        setWindowTitle("MP4 ");
    }

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
    emit boxSelected(selection);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::searchButtonClicked(const QString& boxType) {
    emit searchBox(boxType);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::switchToDashMenuSelected() {
    setWindowTitle("MP4 MPEG-DASH");
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
///Private
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::initPointers() {
    dashSection = NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createMenu() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *dashMenu = menuBar()->addMenu(tr("&MPEG-DASH"));
    dashMenu->addAction(dashAct);

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

}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeDashConnection() {
    connect(dashSection, SIGNAL(dashDirSig(QString)), this,
            SLOT(dashDirSelected(QString)), Qt::QueuedConnection);
    connect(dashSection, SIGNAL(dashFilesSelectedSignal(bool, QString)), this,
            SLOT(dashFilesSelected(bool, QString)), Qt::QueuedConnection);
    connect(dashSection, SIGNAL(removeFileSig(int)), this, SLOT(removeButtonClicked(int)), Qt::QueuedConnection);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeAnalyzeConnection(std::shared_ptr<AnalyzeSection> analyze) {
    connect(analyze.get(), SIGNAL(boxSelected(QItemSelectionModel*)), this,
            SLOT(selectionChanged(QItemSelectionModel*)), Qt::QueuedConnection);
    connect(analyze.get(), SIGNAL(searchButtonClicked(QString)), this,
            SLOT(searchButtonClicked(QString)), Qt::QueuedConnection);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::makeTabsConnection() {
    connect(tabs, SIGNAL(tabCloseRequested(int)), this,
            SLOT(tabClosed(int)), Qt::QueuedConnection);
}

