#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDateTime>
#include "mainwindow.h"
#include "treemodel.h"
#include "dashwrapper.h"

/*!
 * \brief The Controller class
 * The class defines methods that enable to control the application. It gets info about events generated
 * by users by receiving signals and defines response to them.
 */

const QString BOX_NOT_FOUND = "No box found.";
const QString BOX_TOO_SHORT_MSG = "Box type should has at least 4 characters.";
const QString WRITE_FILES_ERROR = "Error while writing files.";
const QString DASH_FILES_SELECTED = "Dash files selected";
const QString NO_FILES_SELECTED = "No files selected";

class Controller: public QObject {
    Q_OBJECT
private:
    MainWindow *window;
    TreeModel *model;
    QStandardItemModel *fileModel;
    DashWrapper *dashWrap;
public:
    /*!
     * \brief Controller
     * \param mw main window of the application
     */
    Controller(MainWindow *mw);
private:
    /*!
     * \brief makeConnection
     * connects MainWindow object signals to this slots
     */
    void makeConnection();
private slots:
    //ANALYZE
    /*!
     * \brief fileSelected
     * \param fileName full name of the selected file (with path)
     * The slot is called when the MainWindow::fileSelected signal is emitted, so when user selects
     * file to analyze. It calls methods on model classes to get box tree model and directs it into MainWindow
     */
    void fileSelected(const QString& fileName);
    /*!
     * \brief boxSelected
     * \param selection selection model of the tree
     * The slot is called when the MainWindow::selectionChanged signal is emitted, so when selection of the
     * box tree has changed. It makes selected box print in the box info table.
     */
    void boxSelected(QItemSelectionModel *selection);
    /*!
     * \brief searchBox
     * \param boxType typed box type
     * The slot is called when the MainWindow::searchBox signal is emitted, so when user clicks Search button.
     * It searches for all the boxes with given type in the tree and selects all of them.
     */
    void searchBox(const QString& boxType);
    //DASH
    /*!
     * \brief dashFilesSelected
     * \param oneFile indicates whether all segments of each presentation should be gathered in one file
     * \param url URL address where generated files will be available. It is inserted into MPD file
     * The slot is called as a response to MainWindow::dashFilesSelectedSignal(), so when user clicks Ready
     * button in the dash section. It uses DashWrapper object to generate files with splitted segments and
     * appropriate MPD file.
     */
    void dashFilesSelected(const bool &oneFile, const QString &url);
    /*!
     * \brief dashDirSelected
     * \param dir selected directory
     * The slot is called as a response to MainWindow::dashDirSelectedSig(), so when user selects directory
     * of files in the dash section. It creates file list model appropriate to main window listview.
     */
    void dashDirSelected(const QString &dir);
    /*!
     * \brief removeFile
     * \param row row id of file that shall be removed
     * The slot is called as a response to MainWindow::removeFileSig(), so when user clicks Remove button
     * in dash section. Controller removes selected row and directs new model to main window.
     */
    void removeFile(const int &row);
};

#endif // CONTROLLER_H
