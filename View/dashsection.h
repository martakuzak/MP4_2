#ifndef DASHSECTION_H
#define DASHSECTION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QFileDialog>
#include <QLabel>
#include <QAbstractItemModel>
#include <QDebug>

/*!
 * \brief The DashSection class
 * DashSection contains and displays widgets that build view of dash section of the application.
 */
class DashSection : public QGroupBox {
    Q_OBJECT
private:
    QVBoxLayout *rightLayout;
    QHBoxLayout *fileLayout;
    QPushButton *addFilesButton;
    QPushButton *removeButton;
    QPushButton *readyButton;
    QListView *fileList;
    QComboBox *dashOptions;
    QLineEdit *urlLine;
    QGroupBox *fileGroup;
    QGroupBox *readyGroup;
    QGroupBox *rightGroup;
public:
    /*!
     * \brief DashSection
     * \param model tree model of boxes
     * \param parent
     * Creates dash section. It contains of filenames listview, buttons (selecting directory of files, removing file from list and
     * preparing selected files to dash streaming) and textline of URL address.
     */
    explicit DashSection(QWidget *parent = 0);
    ~DashSection();
    /*!
     * \brief setDashFileList
     * \param fileModel model of selected filenames (full name - with path)
     * \param disabled indicates whether Add files button shall be disabled
     */
    void setDashFileList(QAbstractItemModel *fileModel, const bool &disabled = false);
signals:
    /*!
     * \brief dashDirSig
     * \param dir selected directory
     */
    void dashDirSig(const QString &dir);
    /*!
     * \brief removeFileSig
     * \param row row id of the filename record that shall be removed from the list
     */
    void removeFileSig(const int &row);
    /*!
     * \brief dashFilesSelectedSignal
     * \param oneFile indicates whether all segments of each presentation should be gathered in one file
     * \param url URL address where generated files will be available. It is inserted into MPD file.
     */
    void dashFilesSelectedSignal(const bool& oneFile, const QString &url);
private slots:
    /*!
     * \brief dashDirSelected
     * The method is called when user selects directory of files. It emits dashDirSig()
     * \see dashDirSig();
     */
    void dashDirSelected();
    /*!
     * \brief removeButtonClicked
     * The method is called when user clicks Remove button. It emits removeFileSig()
     * \see removeFileSig();
     */
    void removeButtonClicked();
    /*!
     * \brief dashFilesSelected
     * The method is called when user clicks Ready button. It emits dashFilesSelectedSignal();
     */
    void dashFilesSelected();
};

#endif // DASHSECTION_H

