#include "mainwindow.h"
#include <QApplication>
#include "trimesh.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TriMesh testmesh;
    testmesh.LoadOBJ("F:/bunny.obj");

    return a.exec();
}
