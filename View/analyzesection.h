#ifndef ANALYZESECTION_H
#define ANALYZESECTION_H

#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QTableView>
#include <QTreeView>
#include <QHeaderView>
#include <QAction>
#include <QDebug>

#include "treemodel.h"

class TreeModel;

class AnalyzeSection : public QSplitter {
    Q_OBJECT
private:
    QHBoxLayout *boxParseLayout;
    QGridLayout *searchBoxLayout;
    QVBoxLayout *boxInfoLayout;
    QSplitter *hSplitter;
    //Group boxes
    QGroupBox *boxParseGroupBox;
    QGroupBox *searchBoxGroupBox;
    QGroupBox *boxInfoGroupBox;
    //search box content
    QLabel *searchLabel;
    QLineEdit *typeBoxType;
    QPushButton *nextSearchButton;
    QLabel *boxNameLabel;
    QTableView *tableView;
    QTreeView *treeView;
    QAction *searchBoxAct;

    void setBoxInfoSection(const QString& fileName, TreeModel *model);
    void setSearchBoxSection();
public:
    explicit AnalyzeSection(const QString& fileName, TreeModel *model, QWidget *parent = 0);
    ~AnalyzeSection();
    void printSelectedBox(QStandardItemModel *mod, TreeItem *item);
    void boxesFound(QModelIndexList& Items, const QString& textLabel);
signals:
    void boxSelected(QItemSelectionModel *selection);
    void searchBox(const QString& boxType);
private slots:
    void searchButtonClicked();
    void selectionChanged();
};

#endif // ANALYZESECTION_H
