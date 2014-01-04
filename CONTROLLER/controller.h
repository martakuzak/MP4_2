#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "treemodel.h"
#include "dashwrapper.h"

class Controller: public QObject {
    Q_OBJECT
private:
    MainWindow* window;
    TreeModel* model;
    DashWrapper* dashWrap;
private slots:
    void fileSelected(const QString& fileName);
    void boxSelected(QItemSelectionModel* selection);
    void searchBox(const QString& boxType);
    void dashFilesSelected(const QList<QString>& fileList);
public:
    Controller(MainWindow* mw);
};

#endif // CONTROLLER_H
