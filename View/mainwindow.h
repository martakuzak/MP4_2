#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QHash>
#include <QString>
#include <qDebug>

#include "treemodel.h"
#include "dashsection.h"
#include "analyzesection.h"

class TreeModel;
class DashWrapper;
class AnalyzeSection;

/*!
 *\brief The MainWindow class
 * defines a main window of the application.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

protected:
    //Actions- File
    //when user clicks "open file" in the menu
    QAction *openAct;
    //when user clicks "close" in the menu
    QAction *exitAct;
    //Actions - MPEG-DASH
    //when user clicks "switch to dash section"
    QAction *dashAct;
    //Actions- Help
    //when user clicks "help" in the menu
    QAction *helpAct; 
    //Layout of the whole window
    QVBoxLayout *mainLayout;
    DashSection *dashSection;
    QTabWidget* tabs;
public:
    /*!
     * \brief MainWindow Constructor of MainWindow
     * \param parent
     * Creates window only with menus.
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /*!
     * \brief fileAnalyzed
     * \param model pointer to TreeModel of anylazed MP4 file
     * \param fileName name of the analyzed MP4 file
     * The method creates appropriate AnalyzeSection to display tree of boxes and table of contents.
     */
    void fileAnalyzed(TreeModel *model, const QString &fileName);
    /*!
     * \brief printSelectedBox
     * \param model Model of contents of the selected box.
     * \param item TreeItem object that represents selected box
     * Prints content of the selected box in the table of AnalyzeSection.
     */
    void printSelectedBox(QStandardItemModel *model, TreeItem *item);
    /*!
     * \brief selectBoxesFound
     * \param boxes list of boxes that shall be selected
     * \param fullName full name of the boxes
     * The method is called by Controller after searching for boxes having given type. It selects box records given and exapands tree
     * so that selected records are visible.
     */
    void selectBoxesFound(QModelIndexList& boxes, const QString& fullName);
    /*!
     * \brief showWarningDialog
     * \param mes message to display
     * Shows warning dialog with given message.
     */
    void showWarningDialog(const QString &mes);
    /*!
     * \brief showInfoDialog
     * \param mes message to display
     * Shows info dialog with given message.
     */
    void showInfoDialog(const QString &mes);
    /*!
     * \brief setDashFileList
     * \param fileModel model of filenames list that shall be display in dash listview
     * \param empty indicates wheteher the "open files" button shall be disabled.
     */
    void setDashFileList(QAbstractItemModel *fileModel, const bool disabled = true);
private slots:
    /*!
     * \brief openFileSelected
     * Launches filedialog and sends name and emits fileSelected() signal after selecting file
     * \see fileSelected();
     */
    void openFileSelected();
    /*!
     * \brief selectionChanged
     * \param selection QItemSelectionModel with selected record of the box tree
     * Emits boxSelected() signal
     * \see boxSelected()
     */
    void selectionChanged(QItemSelectionModel *selection);
    /*!
     * \brief searchButtonClicked
     * \param boxType typed box type
     * Called as a response to clicking Search button. It emits searchBox() signal
     * \see searchBox()
     */
    void searchButtonClicked(const QString &boxType);
    /*!
     * \brief switchToDashMenuSelected
     * Called as a response to choosing Switch to dash section option in the menu. It displays analyze section.
     */
    void switchToDashMenuSelected();
    /*!
     * \brief dashFilesSelected
     * \param oneFile indicates whether all segments of each presentation should be gathered in one file
     * \param url URL address where generated files will be available. It is inserted into MPD file.
     * Called after clicking Ready button. It emits dashFilesSelectedSignal() signal
     * \see dashFilesSelectedSignal()
     */
    void dashFilesSelected(const bool &oneFile, const QString &url);
    /*!
     * \brief dashDirSelected
     * \param directoryName selected directory
     * Called after clicking Add files button. It emits dashDirSelectedSig() signal
     * \see dashDirSelectedSig()
     */
    void dashDirSelected(const QString &directoryName);
    /*!
     * \brief removeButtonClicked
     * \param row row id of file that shall be removed
     * Called after clicking Remove button. It emits removeFileSig()
     * \see removeFileSig()
     */
    void removeButtonClicked(const int &row);
    /*!
     * \brief launchHelpSelected
     * Launches help.html file
     */
    void launchHelpSelected();
    /*!
     * \brief tabClosed
     * \param rowId id of the row to remove
     * Removes given tab from the tabs
     */
    void tabClosed(int rowId);
signals:
    /*!
     * \brief fileSelected
     * \param fileName full name (with path) of the selected file
     */
    void fileSelected(const QString& fileName);
    /*!
     * \brief boxSelected
     * \param selection model of selected record in box tree
     */
    void boxSelected(QItemSelectionModel *selection);
    /*!
     * \brief searchBox
     * \param boxType typed box type
     */
    void searchBox(const QString& boxType);
    /*!
     * \brief dashFilesSelectedSignal
     * \param oneFile indicates whether all segments of each presentation should be gathered in one file
     * \param url URL address where generated files will be available. It is inserted into MPD file
     */
    void dashFilesSelectedSignal(const bool& oneFile, const QString &url);
    /*!
     * \brief dashDirSelectedSig
     * \param dir selected directory
     */
    void dashDirSelectedSig(const QString &dir);
    /*!
     * \brief removeFileSig
     * \param row row id of file that shall be removed
     */
    void removeFileSig(const int& row);
private:
    /*!
     * \brief initPointers Sets dashSection and analyzeSection attributes to NULL.
     */
    void initPointers();
    /*!
     * \brief createMenu
     * Creates menu
     */
    void createMenu();
    /*!
     * \brief createActions
     * Creates menu actions (openAct, closeAct, dashAct, helpAct) and connects it to menu items.
     */
    void createActions();
    /*!
     * \brief makeDashConnection
     * connects dashSection signals to this slots
     */
    void makeDashConnection();
    /*!
     * \brief makeAnalyzeConnection
     * connects analyzeSection signals to this slots
     */
    void makeAnalyzeConnection(AnalyzeSection *analyzeSection);
    /*!
     * \brief makeTabsConnection
     * connects tabs signals to slots
     */
    void makeTabsConnection();
    /*!
     * \brief fileAnalyzed
     * \param model pointer to TreeModel of anylazed MP4 file
     * \param fileName name of the analyzed MP4 file
     * The method creates appropriate AnalyzeSection to display tree of boxes and table of contents.
     */
    void fileAnalyzed(TreeModel *model, const QString &fileName, QTabWidget* tbs);
};

///////////////////////////////////////////////////////////////


#endif // MAINWINDOW_H
