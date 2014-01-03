#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "treemodel.h"

class Controller: public QObject {
    Q_OBJECT
private:
    MainWindow* window;
    TreeModel* model;
private slots:
    void fileSelected(const QString& fileName);
public:
    Controller(MainWindow* mw);
};

#endif // CONTROLLER_H
