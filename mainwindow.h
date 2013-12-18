#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QAction>
#include <QMenu>
#include <QTreeView>
#include <QHeaderView>
#include <QMenuBar>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include <QDirModel>
#include <QLineEdit>
#include <QDesktopServices>
#include <QUrl>
#include <qDebug>
#include "treemodel.h"
#include "treeitem.h"
#include "analyzer.h"
#include "dashproxy.h"


class Analyzer;
class TreeModel;
class DashProxy;

/*!
 * \brief The MainWindow class defines a mind window of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    //Actions- File
    QAction *openAct;
    QAction *exitAct;
    QAction * searchBoxAct;
    //Actions - MPEG-DASH
    QAction *dashOneFileAct;
    QAction *dashSeparatedFilesAct;
    //Actions- Help
    QAction * helpAct;
    /*!
     * \brief title
     */
    QString title;
    //Layouts
    QHBoxLayout * boxParseLayout;
    QGridLayout * searchBoxLayout;
    QVBoxLayout * mainLayout;
    QVBoxLayout * boxInfoLayout;
    //Splitters
    QSplitter * vSplitter;
    QSplitter * hSplitter;
    //Group boxes
    QGroupBox * boxParseGroupBox;
    QGroupBox * searchBoxGroupBox;
    QGroupBox * boxInfoGroupBox;
    //search box content
    QLabel * searchLabel;
    QLineEdit * typeBoxType;
    QPushButton * nextSearchButton;
    QProgressBar * boxParsingProgress;
    QProgressDialog * boxParsingProgressDialog;
    //info box content
    QLabel * boxNameLabel;
    QTextEdit * boxInfo;
    QTreeView *treeView;
    /*!
     * \brief model
     */
    TreeModel *model;
    /*!
     * \brief fileMenu
     */
    QMenu *fileMenu;
    QMenu *dashMenu;
    /*!
     * \brief helpMenu
     */
    QMenu *helpMenu;
    /*!
     * \brief analyzer
     */
    Analyzer * analyzer;
    DashProxy * dashProxy;
public:
    //!Constructor
    /*!
     * \param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    //!Destructor
    ~MainWindow();


private slots:
    /*!
     * \brief openFile opens QFileDialog to choose file that is to analyzed.
     * \info After choosing apropiate file, file is analyzed and treemodel is built. Application creates infoBox section
     * (and searchBox section, if it doesn't exist).
     */
    void openFile();
    /*!
     * \brief printSelectedBox prints info about selected Box in boxInfo->
     */
    void printSelectedBox();
    /*!
     * \brief searchBox searches for all boxes with type given in typeBoxType .
     * \info Found boxes are selected and all their predecessors are expanded. Application launches QMessageBox when:
     * - typed boxType hasn't 4 characters
     * - no box was found
     */
    void searchBox();
    /*!
     * \brief launchHelp launches help html site.
     */
    void launchHelp();
    void splitOneFile();


private:
    /*!
     * \brief createActions create actions and adds slots to the widgets
     */
    void createActions();
    /*!
     * \brief createMenu creates menu
     */
    void createMenu();
    /*!
     * \brief setBoxInfoSection creates treeView and boxInfo and adds it to window
     * \param fileName name of the currently analyzed file
     */
    void setBoxInfoSection(const QString& fileName);
    /*!
     * \brief setSearchBoxSection creates search box section.
     * \info search box section enables searching for boxes by typing typename
     */
    void setSearchBoxSection();
};



#endif // MAINWINDOW_H
