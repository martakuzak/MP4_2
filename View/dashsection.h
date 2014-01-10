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
    void dashDirSig();
    void removeFileSig();
    void dashFilesSig();
public slots:
    void dashDirSelected();
    void removeButtonClicked();
    void dashFilesSelected();
};

#endif // DASHSECTION_H

