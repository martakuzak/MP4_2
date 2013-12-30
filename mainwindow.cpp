#include <QtWidgets>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenu();

    title = QString("MP4 ");
    setWindowTitle(title);

    setMinimumSize(160, 160);
    const int m_width = QApplication::desktop()->width();
    const int m_height = QApplication::desktop()->height();
    resize(0.8*m_width, 0.65*m_height);

    mainLayout = new QVBoxLayout();
    boxParseLayout = new QHBoxLayout();
    searchBoxLayout = new QGridLayout();
    boxInfoLayout = new QVBoxLayout();
    fileLayout = new QHBoxLayout();
    rightLayout = new QVBoxLayout();

    analyzer = new Analyzer();

    QWidget *window = new QWidget();
    setWindowIcon(QIcon("D://PDI//Code//Images//pear.png"));
    setCentralWidget(window);

    window->setLayout(mainLayout);
}
////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    delete fileMenu;
    delete treeView;
    delete openAct;
    delete exitAct;
    delete helpMenu;
    delete helpAct;
    delete dashMenu;
    delete dashOneFileAct;
    delete dashSeparatedFilesAct;
    delete model;
    delete boxInfo;
    delete nextSearchButton;
    delete typeBoxType;
    delete searchLabel;
    delete searchBoxGroupBox;
    delete boxParseGroupBox;
    delete hSplitter;
    delete vSplitter;
    delete mainLayout;
    delete boxParseLayout;
    delete searchBoxLayout;
    delete analyzer;
    delete dashProxy;
    delete dashDialog;
    delete fileList;
    delete addFile;
    delete removeFile;
    delete addFileAct;
    delete removeFileAct;
    delete dashOption;
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    searchBoxAct = new QAction(tr("&Search"), this);
    connect(searchBoxAct, SIGNAL(triggered()), this, SLOT(searchBox()));

    helpAct = new QAction(tr("&Help"), this);
    connect(helpAct, SIGNAL(triggered()), this, SLOT(launchHelp()));

    dashOneFileAct = new QAction(tr("&Split into segments in one file"), this);
    connect(dashOneFileAct, SIGNAL(triggered()), this, SLOT(splitOneFile()));

    dashSeparatedFilesAct = new QAction(tr("&Split with each segment in separated file"), this);
    connect(dashSeparatedFilesAct, SIGNAL(triggered()), this, SLOT(splitIntoMoreFiles()));

    addFileAct = new QAction(tr("&Add file"), this);

    removeFileAct = new QAction(tr("&Remove file"), this);

}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    dashMenu = menuBar()->addMenu(tr("&MPEG-DASH"));
    //dashMenu->addMenu(tr("&Create"));
    dashMenu->addAction(dashOneFileAct);
    dashMenu->addAction(dashSeparatedFilesAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setSearchBoxSection() {
    searchBoxGroupBox = new QGroupBox();
    qDebug()<<"jjj 1";
    searchLabel = new QLabel("Type box type: ");
    qDebug()<<"jjj 2";
    searchLabel->setMaximumSize(200,40);

    typeBoxType = new QLineEdit();
    typeBoxType->setMaximumWidth(50);
    typeBoxType->setMaxLength(4);
    qDebug()<<"jjj 3";
    nextSearchButton = new QPushButton("Find");
    nextSearchButton->addAction(searchBoxAct);
    connect(nextSearchButton,
            SIGNAL(clicked()),
            this, SLOT(searchBox()));
    qDebug()<<"jjj 4";

    searchBoxGroupBox->setMaximumHeight(50);
    searchBoxGroupBox->setMinimumHeight(40);
    qDebug()<<"jjj 5";
    searchBoxLayout->addWidget(searchLabel, 1, 0);
    searchBoxLayout->addWidget(typeBoxType, 1, 1);
    searchBoxLayout->addWidget(nextSearchButton, 1, 2);
    searchBoxLayout->setColumnStretch(10, 1);
    qDebug()<<"jjj 6";
    searchBoxGroupBox->setLayout(searchBoxLayout);

    vSplitter = new QSplitter();
    qDebug()<<"jjj 7";
    vSplitter->addWidget(searchBoxGroupBox);
    mainLayout->addWidget(vSplitter);

}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setBoxInfoSection(const QString& fileName) {
    if(!boxParseLayout->count()) {
        boxParseGroupBox = new QGroupBox();
        boxInfoGroupBox = new QGroupBox();
        treeView = new QTreeView(this);
        //boxInfo = new QTextEdit();
        //boxInfo->setReadOnly(true);
        tableView = new QTableView();
        hSplitter = new QSplitter();
        boxNameLabel = new QLabel();
        boxNameLabel->setMaximumHeight(20);
        boxNameLabel->setFont(QFont("Arial", 13));
    }
    delete analyzer;
    analyzer = new Analyzer(fileName);
    model = new TreeModel(analyzer);
    treeView->setModel(model);
    //treeView->setFont(QFont("Arial", 12));
    //treeView->header()->setStretchLastSection(false);
    //treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    treeView->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    connect(treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(printSelectedBox()));

    boxNameLabel->setSizePolicy(QSizePolicy::Expanding,
                                QSizePolicy::Expanding);
    boxNameLabel->clear();

    /*boxInfo->setSizePolicy(QSizePolicy::Expanding,
                           QSizePolicy::Expanding);
    boxInfo->setText("");*/
    tableView->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Expanding);


    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setStretchLastSection(true);
    //tableView->horizontalHeader()->hide();
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

    mainLayout->update();
    title = QString("MP4 " + fileName);
    setWindowTitle(title);
}

////////////////////////////////////////////////////////////////////////////////////////////
///Slots
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::openFile()
{
    QFileDialog dialog(this);
    // qDebug()<<"openFile 1";
    dialog.setFileMode(QFileDialog::AnyFile);
    //qDebug()<<"openFile 2";
    //    QString fileName = QFileDialog::getOpenFileName(this,
    //                                                    tr("Open File"), "/", tr("MP4 Files (*.mp4)"));
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/");

    //qDebug()<<"openFile 3";
    if(fileName.length()) {

        // qDebug()<<"openFile: fileName.length() 1";
        //        boxParsingProgressDialog = new QProgressDialog(this);
        //        boxParsingProgress = new QProgressBar();
        //        boxParsingProgress->setFormat("Box analyzing %p");
        //        boxParsingProgressDialog->setBar(boxParsingProgress);
        //        boxParsingProgressDialog->show();
        if(fileLayout->count()) {
//            qDebug()<<":(1";
//            mainLayout->removeWidget(dash);
//            delete readyGroup;
//            qDebug()<<":(4";
//            delete fileGroup;
//            qDebug()<<":(5";
//            //delete fileLayout;
//            mainLayout->addStretch(1);
//            qDebug()<<":(7";
//            mainLayout->update();
//            qDebug()<<":(8";
//            //delete fileLayout;
            delete dash;
            dash = new QWidget();

            fileLayout = new QHBoxLayout();
            rightLayout = new QVBoxLayout();
            //mainLayout = new QVBoxLayout();
            qDebug()<<":(9";
        }
//        else if(boxParseLayout->count()) {
//            return;
//        }
        if(mainLayout->isEmpty())
            qDebug()<<":(6";
        else
            qDebug()<<"wut";
        if(!searchBoxLayout->count()) {
            // qDebug()<<"openFile: fileName.length() 2";
            setSearchBoxSection();
        }
        qDebug()<<":(7";

        //qDebug()<<"openFile: fileName.length() 3";
        setBoxInfoSection(fileName);
        qDebug()<<":(8";

        //boxParsingProgressDialog->close();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::printSelectedBox() {
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QModelIndex child = model->index(index.row(), 2, index.parent());
    TreeItem* item = model->getChild(model->data(child, Qt::DisplayRole).toInt());
    QStandardItemModel* model = item->getModel();
    model->setHeaderData(0, Qt::Horizontal, tr(""));
    model->setHeaderData(1, Qt::Horizontal, tr(""));
    //boxInfoLayout->removeWidget(
    boxInfoLayout->removeWidget(tableView);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(model);
    tableView->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    //tableView->resizeColumnsToContents();
    if(model->columnCount() > 1) {
        tableView->horizontalHeader()->resizeSection(1, 300);
        tableView->resizeColumnsToContents();
        tableView->horizontalHeader()->setStretchLastSection(true);
    }
    boxInfoLayout->addWidget(tableView);
    QString text = item->fullName();
    if(text!=NULL) {
        boxNameLabel->setText(text);
    }
    //boxInfoLayout->addWidget(boxNameLabel);
    //boxInfoLayout->addWidget(tableView);

}
////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::searchBox() {
    QString boxType = typeBoxType->text();
    qDebug()<<"searchBox"<<boxType;
    //if boxType hasn't 4 characters
    if(boxType.size()!=4) {
        QMessageBox *infoBox = new QMessageBox(this);
        infoBox->setIcon(QMessageBox::Warning);
        infoBox->setText("Box type should have 4 characters.");
        infoBox->show();
        //boxInfo->clear();
        return;
    }
    //otherwise application looks for boxes
    QModelIndex index = treeView->selectionModel()->currentIndex();
    int row;
    int col;
    if(index.isValid()) {
        row = index.row();
        col = index.column();
    }
    else { //no selection
        row = 0;
        col = 0;
    }
    QModelIndexList Items = model->match(model->index(row,col),
                                         Qt::DisplayRole,
                                         QVariant::fromValue(QString(boxType)),
                                         -1,
                                         Qt::MatchRecursive);
    treeView->clearSelection();
    //no box found
    if(Items.size()==0) {
        treeView->clearSelection();
        QMessageBox *infoBox = new QMessageBox(this);
        infoBox->setIcon(QMessageBox::Warning);
        infoBox->setText("No box found");
        infoBox->show();
        treeView->clearSelection();
        //boxInfo->clear();
        return;

    }
    //selects found boxes and expands their predecessors
    QModelIndex tmpId;
    while (!Items.isEmpty()) {
        QModelIndex backId = Items.back();
        tmpId = backId;
        QModelIndex tmpParent = tmpId.parent();
        while(tmpParent.isValid()) {
            treeView->setExpanded(tmpParent, true);
            tmpParent = tmpParent.parent();
        }
        treeView->selectionModel()->select(backId, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        Items.pop_back();
    }
    QModelIndex child = model->index(tmpId.row(), 2, tmpId.parent());
    boxNameLabel->setText(model->getChild(model->data(child,
                                                      Qt::DisplayRole).toInt())->fullName());
    QString text= model->getChild(model->data(child,
                                              Qt::DisplayRole).toInt())->fullName();
    if(text!=NULL) {
        boxNameLabel->setText(text);
        printSelectedBox();
        //boxInfo->setText(model->getChild(model->data(child,Qt::DisplayRole).toInt())->getInfo());
    }
    mainLayout->update();

}
////////////////////////////////////////////////////////////
void MainWindow::splitOneFile() {
    QString fileName = title.mid(4);
    QDateTime local(QDateTime::currentDateTime());
    QString date = local.toString();
    date.replace(QString(":"), QString("_"));
    dashProxy = new DashProxy(fileName, model, date);
    if(dashProxy->writeFile(50/*, dashFile*/)) {
        int last = fileName.lastIndexOf("\\");
        if(last == -1)
            last = fileName.lastIndexOf("/");
        QString name = fileName.mid(last + 1);
        QString path = fileName.mid(0, last + 1);
        path.append("DASH " + date + "/");
        name.replace(".mp4", ".mpd");
        QString mpdName = QString(path + "dash_" + name);
        QFile* mpdFile = new QFile(mpdName);
        if(mpdFile->open(QIODevice::ReadWrite)) {
            dashProxy->writeMPD(mpdFile, true);
        }
        else {
            delete dashProxy;
            return;
        }
        mpdFile->close();
    }
    else {
        QMessageBox *infoBox = new QMessageBox(this);
        infoBox->setIcon(QMessageBox::Warning);
        infoBox->setText("Could not write file.");
        infoBox->show();
        return;
    }
    QMessageBox *infoBox = new QMessageBox(this);
    infoBox->setIcon(QMessageBox::Information);
    infoBox->setText("Dash files prepared.");
    infoBox->show();
    delete dashProxy;
}
////////////////////////////////////////////////////////////
void MainWindow::splitIntoMoreFiles() {
    QString fileName = title.mid(4);
    QDateTime local(QDateTime::currentDateTime());
    QString date = local.toString();
    date.replace(QString(":"), QString("_"));
    dashProxy = new DashProxy(fileName, model, date);
    if(dashProxy->writeFiles(50/*, dashFile*/)) {
        //return;
        int last = fileName.lastIndexOf("\\");
        if(last == -1)
            last = fileName.lastIndexOf("/");
        QString name = fileName.mid(last + 1);
        QString path = fileName.mid(0, last + 1);
        path.append("DASH " + date + "/");
        name.replace(".mp4", ".mpd");
        QString mpdName = QString(path + "dash_" + name);
        QFile* mpdFile = new QFile(mpdName);
        if(mpdFile->open(QIODevice::ReadWrite)) {
            dashProxy->writeMPD(mpdFile, false);
        }
        else {
            delete dashProxy;
            return;
        }
        mpdFile->close();
    }
    else {
        QMessageBox *infoBox = new QMessageBox(this);
        infoBox->setIcon(QMessageBox::Warning);
        infoBox->setText("Could not write file.");
        infoBox->show();
        return;
    }
    QMessageBox *infoBox = new QMessageBox(this);
    infoBox->setIcon(QMessageBox::Information);
    infoBox->setText("Dash files prepared.");
    infoBox->show();
    delete dashProxy;
}
////////////////////////////////////////////////////////////
void MainWindow::setDashDialog() {

}
////////////////////////////////////////////////////////////
void MainWindow::launchHelp() {
    //QDesktopServices::openUrl(QUrl("D://PDI//Code//help.html"));
    /*QDialog* dialog = new QDialog();
    addFile = new QPushButton("Add file");
    addFile->addAction(addFileAct);
    connect(addFile, SIGNAL(clicked()), this, SLOT(addFileToDash()));

    removeFile = new QPushButton("Remove");
    removeFile->addAction(removeFileAct);
    connect(removeFile, SIGNAL(clicked()), this, SLOT(removeFileFromDash()));

    fileList = new QListView();
    QStandardItemModel* model = new QStandardItemModel(5, 1, 0);
    fileList->setModel(model);
    fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QComboBox* option = new QComboBox();
    option->addItem("One file for all segments");
    option->addItem("Each segment has its own file");
    DashPage* dashPage = new DashPage(addFile, option, removeFile, fileList);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(dashPage);

    dialog->setLayout(horizontalLayout);
    dialog->show();*/
    setWindowTitle("MP4 MPEG-DASH");
    if(boxParseLayout->count()) {
//        mainLayout->removeWidget(vSplitter);
        delete vSplitter;
        vSplitter = new QSplitter();
        boxParseLayout = new QHBoxLayout();
        searchBoxLayout = new QGridLayout();
        boxInfoLayout = new QVBoxLayout();
qDebug()<<"dnefsnjrsdgfr";
//        boxParseLayout = new QHBoxLayout();
//        searchBoxLayout = new QGridLayout();
//        boxInfoLayout = new QVBoxLayout();
//        mainLayout->update();
        mainLayout->update();
    }
    else if(rightLayout->count()) {
        return;
    }
    qDebug()<<"figa";
    fileModel = new QStandardItemModel;
    addFile = new QPushButton("Add file");
    addFile->addAction(addFileAct);
    connect(addFile, SIGNAL(clicked()), this, SLOT(addFileToDash()));

    removeFile = new QPushButton("Remove");
    removeFile->addAction(removeFileAct);
    connect(removeFile, SIGNAL(clicked()), this, SLOT(removeFileFromDash()));

    fileList = new QListView();
    //QStandardItemModel* model = new QStandardItemModel(5, 1, 0);
    fileList->setModel(fileModel);
    fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QComboBox* option = new QComboBox();
    option->addItem("One file for all segments");
    option->addItem("Each segment has its own file");
    //DashPage* dashPage = new DashPage(addFile, option, removeFile, fileList, fileLayout, rightGroup);

    //QHBoxLayout *horizontalLayout = new QHBoxLayout;
    //mainLayout->addWidget(dashPage);
    readyButton = new QPushButton("Ready");
    oneFile = new QLabel("All segments in one file");
    moreFile = new QLabel("Each segment in seperated file");
    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(option);
    rightLayout->addWidget(addFile);
    rightLayout->addWidget(removeFile);
    rightGroup = new QGroupBox;
    rightGroup->setLayout(rightLayout);
    fileLayout = new QHBoxLayout;
    fileLayout->addWidget(fileList);
    fileLayout->addWidget(rightGroup);
    fileGroup = new QGroupBox();
    fileGroup->setLayout(fileLayout);

    readyGroup = new QGroupBox;
    readyGroup->setMaximumHeight(50);
    readyGroup->setMinimumHeight(40);

    QGridLayout* downLayout = new QGridLayout();
    downLayout->addWidget(readyButton, 1, 0);
    downLayout->setColumnStretch(10, 1);
    readyGroup->setLayout(downLayout);

    QVBoxLayout* dashLayout = new QVBoxLayout;
    dashLayout->addWidget(readyGroup);

    dashLayout->addWidget(fileGroup);
    dash = new QWidget();
    dash->setLayout(dashLayout);
    mainLayout->addWidget(dash);

    //mainLayout->addStretch(1);
    mainLayout->update();
    //setLayout(mainLayout);
}
void MainWindow::addFileToDash() {
    //int row = model->rowCount();
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    //    QString fileName = QFileDialog::getOpenFileName(this,
    //                                                    tr("Open File"), "/", tr("MP4 Files (*.mp4)"));
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/");
    qDebug()<<"3";
    if(fileName.length()) {
        QStandardItem* tmpItem = new QStandardItem();
        tmpItem->setText(fileName);
        qDebug()<<"4";
        QList<QStandardItem*> list;
        list.append(tmpItem);
        qDebug()<<"6";
        fileLayout->removeWidget(rightGroup);
        qDebug()<<"5";
        fileLayout->removeWidget(fileList);
        fileModel->appendColumn(list);
        qDebug()<<"1";
        fileList->setModel(fileModel);
        fileLayout->addWidget(fileList);
        qDebug()<<"2";
        fileLayout->addWidget(rightGroup);
    }

    mainLayout->update();
}

void MainWindow::removeFileFromDash() {
    qDebug()<<"remo";
    int row = fileList->currentIndex().row();
    if(row>0 && row < ( fileList->model()->rowCount() - 1)) {
        fileList->model()->removeRow(row);
        fileList->setModel(fileModel);
    }
    mainLayout->update();

}

////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//DashPage::DashPage(QPushButton *addFile, QComboBox *option, QPushButton *remove,
//                   QListView *fileList, QHBoxLayout* fileLayout, QGroupBox* rightGroup,
//                   QWidget *parent): QWidget(parent) {
//    mainLayout = new QVBoxLayout();
//    readyButton = new QPushButton("Ready");
//    oneFile = new QLabel("All segments in one file");
//    moreFile = new QLabel("Each segment in seperated file");
//    QVBoxLayout* rightLayout = new QVBoxLayout;
//    rightLayout->addWidget(option);
//    rightLayout->addWidget(addFile);
//    rightLayout->addWidget(remove);
//    rightGroup = new QGroupBox;
//    rightGroup->setLayout(rightLayout);
//    fileLayout = new QHBoxLayout;
//    fileLayout->addWidget(fileList);
//    fileLayout->addWidget(rightGroup);
//    QGroupBox* fileGroup = new QGroupBox();
//    fileGroup->setLayout(fileLayout);
//    mainLayout->addWidget(fileGroup);

//    QGroupBox* readyGroup = new QGroupBox;
//    readyGroup->setMaximumHeight(50);
//    readyGroup->setMinimumHeight(40);

//    QGridLayout* downLayout = new QGridLayout();
//    downLayout->addWidget(readyButton, 1, 0);
//    downLayout->setColumnStretch(10, 1);
//    readyGroup->setLayout(downLayout);

//    mainLayout->addWidget(readyGroup);
//    //mainLayout->addStretch(1);
//    setLayout(mainLayout);
//    //connect(addFileAct, SIGNAL(triggered()), this, SLOT(addFile()));

//    //QFileDialog dialog(this);
//    // qDebug()<<"openFile 1";
//    //dialog.setFileMode(QFileDialog::AnyFile);
//    /*QString fileName = QFileDialog::getOpenFileName(this,
//                                                    tr("Add File"), "/");
//*/
//    /*nextSearchButton->addAction(searchBoxAct);
//    connect(nextSearchButton,
//            SIGNAL(clicked()),
//            this, SLOT(searchBox()));*/
//}

