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
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QString>
#include <qDebug>

#include "treemodel.h"
#include "dashsection.h"
#include "analyzesection.h"

class Analyzer;
class TreeModel;
class DashWrapper;
class AnalyzeSection;

/*!
 *\brief The MainWindow class defines a mind window of the application
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    //Actions- File
    QAction *openAct;
    QAction *exitAct;
    //Actions - MPEG-DASH
    QAction *dashAct;
    //Actions- Help
    QAction *helpAct;
    QVBoxLayout *mainLayout;
    DashSection *dashSection;
    AnalyzeSection *analyzeSection;
    /*!
     *\brief fileMenu
    */
    QMenu *fileMenu;
    /*!
     *\brief dashMenu
    */
    QMenu *dashMenu;
    /*!
     *\brief helpMenu
    */
    QMenu *helpMenu;
public:
    //!Constructor
    /*!
     *\param parent
    */
    explicit MainWindow(QWidget *parent = 0);
    //!Destructor
    ~MainWindow();
    void fileAnalyzed(TreeModel *mod, const QString &fileName);
    void printSelectedBox(QStandardItemModel *mod, TreeItem *item);
    void boxesFound(QModelIndexList& Items, const QString& textLabel);
    void showWarningDialog(const QString &mes);
    void showInfoDialog(const QString &mes);
    void addFileToDash(QAbstractItemModel *fileModel);
    void dashRowRemoved(QAbstractItemModel *fileModel, const bool empty = false);
    void initializePointers();
private slots:
    /*!
     *\brief openFile opens QFileDialog to choose file that is to analyzed.
     *\info After choosing apropiate file, file is analyzed and treemodel is built. Application creates infoBox section
     *(and searchBox section, if it doesn't exist).
    */
    void openFile();
    /*!
     *\brief launchHelp launches help html site.
    */
    void launchHelp();
    void removeFileFromDash(QAbstractItemModel *fileModel);
    void selectionChanged(QItemSelectionModel *selection);
    void switchToDashMenu();
    //kliknieto przycisk ready
    void dashFilesSelected(const bool &oneFile, const QString &url);
    //kliknieto przycisk Add files
    void dashDirSelected(const QString &directoryName);
    void removedButtonClicked(const int &row);
    void searchButtonClicked(const QString &boxType);
signals:
    void fileSelected(const QString& fileName);
    void boxSelected(QItemSelectionModel *selection);
    void searchBox(const QString& boxType);
    void dashFilesSelectedSignal(const bool& oneFile, const QString &url);
    void dashDirSelectedSig(const QString &dir);
    void removeFileSig(const int& row);
private:
    /*!
     *\brief createActions create actions and adds slots to the widgets
    */
    void createActions();
    /*!
     *\brief createMenu creates menu
    */
    void createMenu();
    void makeDashConnection();
    void makeAnalyzeConnection();
};

///////////////////////////////////////////////////////////////


#endif // MAINWINDOW_H
