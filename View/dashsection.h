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
signals:
    void dashDirSig(const QString &dir);
    void dashFilesSelectedSig(const bool& oneFile, const QString &url);
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

