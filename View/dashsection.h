#ifndef DASHSECTION_H
#define DASHSECTION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QListView>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QDebug>

class DashSection : public QGroupBox {
    Q_OBJECT
private:
    QVBoxLayout *rightLayout;
    QHBoxLayout *fileLayout;
    QPushButton *addFileButton;
    QPushButton *removeButton;
    QPushButton *readyButton;
    QListView *fileList;
    QComboBox *dashOptions;
    QLineEdit *urlLine;
    QGroupBox *fileGroup;
    QGroupBox *readyGroup;
    QGroupBox *rightGroup;
    //QLabel
    //actions
    QAction *addFileAct;
    QAction *removeAct;
public:
    explicit DashSection(QWidget *parent = 0);
    ~DashSection();
    void removeFileFromDash(QAbstractItemModel *fileModel, const bool &empty = false);
    void addFileToDash(QAbstractItemModel *fileModel);
signals:
    void dashDirSig(const QString &dir);
    void dashFilesSelectedSignal(const bool& oneFile, const QString &url);
    void removeFileSig(const int &row);
    void dashFilesSig();
private slots:
    void dashDirSelected();
    void removeButtonClicked();
    void dashFilesSelected();
private:
    void setActions();
};

#endif // DASHSECTION_H

