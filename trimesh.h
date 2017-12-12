#ifndef TRIMESH_H
#define TRIMESH_H

#include <vector>
#include <fstream>
#include <string>
#include <qDebug>
#include <QVector3D>
#include <QVector2D>
#include <QString>
#include <QFile>


struct Vertex{
    QVector3D position;
    QVector3D normal;
    QVector3D texcoord;
};


class TriMesh
{
public:
    TriMesh();
    TriMesh(QString filename);
    const Vertex* Data() const {return vertices_.data(); }
    const int* Index() const {return indices_.data(); }
    int GetVertexNum() const {return vertices_.size(); }
    int GetIndexNum() const {return indices_.size(); }
    void LoadOBJ(QString filename);
private:
    std::vector<Vertex> vertices_;
    std::vector<int> indices_;
    void Clear();


};

#endif // TRIMESH_H
