#include "dashsection.h"

DashSection::DashSection(QWidget *parent) {

    setActions();
    addFileButton = new QPushButton("Add file");
    addFileButton->addAction(addFileAct);
    connect(addFileButton, SIGNAL(clicked()), this, SLOT(dashDirSelected()));

    removeButton = new QPushButton("Remove");
    removeButton->addAction(removeAct);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));

    fileList = new QListView();
    //fileList->setModel(fileModel);
    fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dashOptions = new QComboBox();
    dashOptions->addItem("One file for all segments");
    dashOptions->addItem("Each segment has its own file");

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
    rightLayout->addWidget(urlBox);
    rightLayout->addWidget(addFileButton);
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

DashSection::~DashSection() {
    delete rightLayout;
    delete fileLayout;
    delete addFileButton;
    delete removeButton;
    delete readyButton;
    delete fileList;
    delete dashOptions;
    delete urlLine;
    delete fileGroup;
    delete readyGroup;
    delete addFileAct;
}

void DashSection::dashDirSelected() {

}

void DashSection::removeButtonClicked() {

}

void DashSection::dashFilesSelected() {

}

void DashSection::setActions() {
    addFileAct = new QAction(tr("&Add files"), this);
    removeAct = new QAction(tr("&Remove file"), this);
}


