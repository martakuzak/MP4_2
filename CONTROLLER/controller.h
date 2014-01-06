#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "treemodel.h"
#include "dashwrapper.h"

class Controller: public QObject {
    Q_OBJECT
private:
    MainWindow *window;
    TreeModel *model;
    QStandardItemModel *fileModel;
    DashWrapper *dashWrap;
private slots:
    void fileSelected(const QString& fileName);
    void boxSelected(QItemSelectionModel *selection);
    void searchBox(const QString& boxType);
    void dashFilesSelected(const bool &oneFile, const QString &url);
    void dashDirSelected(const QString &dir);
    void removeFile(const int &row);
public:
    Controller(MainWindow *mw);
private:
    void makeConnection();
};

#endif // CONTROLLER_H
