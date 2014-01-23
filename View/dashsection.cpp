#include "dashsection.h"

////////////////////////////////////////////////////////////////////////////////////////////
///Public
////////////////////////////////////////////////////////////////////////////////////////////
DashSection::DashSection(QWidget *parent):
    QGroupBox(parent){

    addFilesButton = new QPushButton("Add files");
    connect(addFilesButton, SIGNAL(clicked()), this, SLOT(dashDirSelected()));

    removeButton = new QPushButton("Remove");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));

    fileList = new QListView();
    fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dashOptions = new QComboBox();
    dashOptions->addItem("One file for all segments");
    dashOptions->addItem("Each segment has its own file");

    QGroupBox *initGroup = new QGroupBox();
    initGroup->setTitle("MPD initialization segment located in:");
    initOptions = new QComboBox();
    initOptions->addItem("SegmentList");
    initOptions->addItem("SegmentBase");
    QVBoxLayout *initLayout = new QVBoxLayout();
    initLayout->addWidget(initOptions);
    initGroup->setLayout(initLayout);
    initGroup->setMaximumHeight(65);

    QGroupBox *urlBox = new QGroupBox();
    urlBox->setTitle("Type URL of files");
    urlLine = new QLineEdit();
    urlLine->setMaximumWidth(195);
    QVBoxLayout *urlLayout = new QVBoxLayout();
    urlLayout->addWidget(urlLine);
    urlBox->setLayout(urlLayout);
    urlBox->setMaximumHeight(50);

    readyButton = new QPushButton("Ready");
    connect(readyButton, SIGNAL(clicked()), this, SLOT(dashFilesSelected()), Qt::QueuedConnection);
    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(dashOptions);
    rightLayout->addWidget(initGroup);
    rightLayout->addWidget(urlBox);
    rightLayout->addWidget(addFilesButton);
    rightLayout->addWidget(removeButton);
    rightGroup = new QGroupBox;
    rightGroup->setMaximumWidth(200);
    rightGroup->setLayout(rightLayout);
    fileLayout = new QHBoxLayout;
    fileLayout->addWidget(fileList);
    fileLayout->addWidget(rightGroup);
    fileGroup = new QGroupBox();
    fileGroup->setLayout(fileLayout);

    readyGroup = new QGroupBox;
    readyGroup->setMaximumHeight(50);
    readyGroup->setMinimumHeight(40);

    QGridLayout *downLayout = new QGridLayout();
    downLayout->addWidget(readyButton, 1, 0);
    downLayout->setColumnStretch(10, 1);
    readyGroup->setLayout(downLayout);

    QVBoxLayout *dashLayout = new QVBoxLayout;
    dashLayout->addWidget(fileGroup);
    dashLayout->addWidget(readyGroup);

    setLayout(dashLayout);
}
////////////////////////////////////////////////////////////////////////////////////////////
DashSection::~DashSection() {
    delete fileGroup;
    delete readyGroup;
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashSection::setDashFileList(QAbstractItemModel *fileModel, const bool &disabled) {
    fileList->setModel(fileModel);
    addFilesButton->setDisabled(disabled);
}
////////////////////////////////////////////////////////////////////////////////////////////
///Slots
////////////////////////////////////////////////////////////////////////////////////////////
void DashSection::dashDirSelected() {
    QString directoryName = QFileDialog::getExistingDirectory(this, tr("Select directory"), "/");
    emit dashDirSig(directoryName);
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashSection::removeButtonClicked() {
    int row = fileList->currentIndex().row();
    emit removeFileSig(row);
}
////////////////////////////////////////////////////////////////////////////////////////////
void DashSection::dashFilesSelected() {
    emit dashFilesSelectedSignal((dashOptions->currentIndex() == 0), urlLine->text(),
                                 (initOptions->currentIndex() == 0));
}




