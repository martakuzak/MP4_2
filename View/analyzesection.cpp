#include "analyzesection.h"

////////////////////////////////////////////////////////////////////////////////////////////
///Public
////////////////////////////////////////////////////////////////////////////////////////////
AnalyzeSection:: AnalyzeSection(TreeModel *model, QWidget *parent) :
    QSplitter(parent) {
    searchBoxAct = new QAction(tr("&Search"), this);
    connect(searchBoxAct, SIGNAL(triggered()), this, SLOT(searchButtonClicked()));
    setSearchBoxSection();
    setBoxInfoSection(model);
}
////////////////////////////////////////////////////////////////////////////////////////////
AnalyzeSection::~AnalyzeSection() {
    delete boxParseGroupBox;
    delete searchBoxGroupBox;
    delete searchBoxAct;
}
////////////////////////////////////////////////////////////////////////////////////////////
void AnalyzeSection::printSelectedBox(QStandardItemModel *model, TreeItem *item) {
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(model);
    tableView->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Expanding);
    if(model->columnCount() > 1) {
        tableView->horizontalHeader()->resizeSection(1, 300);
        tableView->resizeColumnsToContents();
        tableView->horizontalHeader()->setStretchLastSection(true);
    }
    QString text = item->fullName();
    if(text!=NULL) {
        boxNameLabel->setText(text);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
void AnalyzeSection::selectFoundBoxes(QModelIndexList &boxes, const QString &fullName) {
    treeView->clearSelection();
    QModelIndex tmpId;
    while (!boxes.isEmpty()) {
        QModelIndex backId = boxes.back();
        tmpId = backId;
        QModelIndex tmpParent = tmpId.parent();
        while(tmpParent.isValid()) {
            treeView->setExpanded(tmpParent, true);
            tmpParent = tmpParent.parent();
        }
        treeView->selectionModel()->select(backId, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        boxes.pop_back();
    }
    boxNameLabel->setText(fullName);
}
////////////////////////////////////////////////////////////////////////////////////////////
///Slots
////////////////////////////////////////////////////////////////////////////////////////////
void AnalyzeSection::searchButtonClicked() {
    QString boxType = typeBoxType->text();
    emit searchButtonClicked(boxType);
}
////////////////////////////////////////////////////////////////////////////////////////////
void AnalyzeSection::selectionChanged() {
    QItemSelectionModel *selection = treeView->selectionModel();
    emit boxSelected(selection);
}
////////////////////////////////////////////////////////////////////////////////////////////
///Private
////////////////////////////////////////////////////////////////////////////////////////////
void AnalyzeSection::setBoxInfoSection(TreeModel *model) {
    boxParseLayout = new QHBoxLayout();
    boxInfoLayout = new QVBoxLayout();

    boxParseGroupBox = new QGroupBox();
    boxInfoGroupBox = new QGroupBox();
    treeView = new QTreeView(this);
    tableView = new QTableView();
    hSplitter = new QSplitter();
    boxNameLabel = new QLabel();
    boxNameLabel->setMaximumHeight(20);
    boxNameLabel->setFont(QFont("Arial", 13));

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

    addWidget(boxParseGroupBox);
    setOrientation(Qt::Vertical);
}
////////////////////////////////////////////////////////////////////////////////////////////
void AnalyzeSection::setSearchBoxSection() {
    searchBoxLayout = new QGridLayout();
    searchBoxGroupBox = new QGroupBox();
    searchBoxGroupBox->setTitle("Search for box");
    searchLabel = new QLabel("Type box type: ");
    searchLabel->setMaximumSize(200,40);
    typeBoxType = new QLineEdit();
    typeBoxType->setMaximumWidth(50);
    typeBoxType->setMaxLength(4);
    nextSearchButton = new QPushButton("Find");
    nextSearchButton->addAction(searchBoxAct);
    connect(nextSearchButton,
            SIGNAL(clicked()),
            this, SLOT(searchButtonClicked()));

    searchBoxGroupBox->setMaximumHeight(50);
    searchBoxGroupBox->setMinimumHeight(40);
    searchBoxLayout->addWidget(searchLabel, 1, 0);
    searchBoxLayout->addWidget(typeBoxType, 1, 1);
    searchBoxLayout->addWidget(nextSearchButton, 1, 2);
    searchBoxLayout->setColumnStretch(10, 1);
    searchBoxGroupBox->setLayout(searchBoxLayout);

    addWidget(searchBoxGroupBox);
}
////////////////////////////////////////////////////////////////////////////////////////////
