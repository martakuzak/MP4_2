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

/*!
 * \brief The AnalyzeSection class represents analyze section of MP4 GUI.
 * Analyze section displays box tree and table of contents of selected box.
 */
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
public:
    /*!
     * \brief AnalyzeSection
     * \param model tree model of boxes
     * \param parent
     * Creates analyze section with box tree, table of selected box contents and search area.
     */
    explicit AnalyzeSection(TreeModel *model, QWidget *parent = 0);
    ~AnalyzeSection();
    /*!
     * \brief printSelectedBox
     * \param model Model of contents of the selected box.
     * \param item TreeItem object that represents selected box
     * Prints content of the selected box in the table.
     */
    void printSelectedBox(QStandardItemModel *model, TreeItem *item);
    /*!
     * \brief selectFoundBoxes
     * \param boxes list of boxes that shall be selected
     * \param fullName full name of the boxes
     * It selects box records given and exapands tree so that selected records are visible.
     */
    void selectFoundBoxes(QModelIndexList& boxes, const QString& fullName);
signals:
    /*!
     * \brief boxSelected
     * \param selection model of selected records in the tree
     * It is emitted after selection of the tree changes
     */
    void boxSelected(QItemSelectionModel *selection);
    /*!
     * \brief searchButtonClicked
     * \param boxType typed box type
     * It is emitted after user clicked Search button
     */
    void searchButtonClicked(const QString& boxType);
private slots:
    /*!
     * \brief searchButtonClicked
     * The slot is connected to clicked signal of Search button.
     */
    void searchButtonClicked();
    /*!
     * \brief selectionChanged
     * The slot is connected to selectionChanged signal of box tree.
     */
    void selectionChanged();
private:
    /*!
     * \brief setBoxInfoSection
     * \param model model of boxes
     * Sets treewidget based on model and table of selected box contents.
     */
    void setBoxInfoSection(TreeModel *model);
    /*!
     * \brief setSearchBoxSection
     * Sets search area of the analyze section. Using search area user can search for boxes with given type.
     */
    void setSearchBoxSection();
};

#endif // ANALYZESECTION_H
