#include "trimesh.h"
#include "utils.h"
TriMesh::TriMesh()
{

}

TriMesh::TriMesh(QString file_name)
{

}

void TriMesh::Clear()
{
    vertices_.clear();
    indices_.clear();
}

void TriMesh::LoadOBJ(QString file_name)
{
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly)){
        exit(-1);
    }

    QTextStream in(&file);
    std::vector<QVector3D> vertices_coords;
    std::vector<QVector3D> vertices_normal;
    std::vector<QVector3D> vertices_texcoords;
    float x, y, z;
    float sum_x=0, sum_y=0, sum_z=0;
    float max_x=-1000, max_y=-1000, max_z=-1000;
    float min_x=1000, min_y=1000, min_z=1000;

    QString line;
    while(!in.atEnd())
    {
        line = in.readLine();
        if(line.isEmpty())
        {
            //line = in.readLine();
            continue;
        }
        if(line[0] == '#')
            qDebug() << line;
        else if(line.left(2) == "v ")
        {
            line.remove(0, 1);  // remove "v "
            QStringList vertex_coords = line.split(' ', QString::SkipEmptyParts);
            x = vertex_coords[0].toFloat();
            y = vertex_coords[1].toFloat();
            z = vertex_coords[2].toFloat();

            vertices_coords.push_back(QVector3D(x, y, z));

            sum_x += x;
            sum_y += y;
            sum_z += z;

            if(x > max_x) max_x=x;
            if(y > max_y) max_y=y;
            if(z > max_z) max_z=z;

            if(x < min_x) min_x = x;
            if(y < min_y) min_y = y;
            if(z < min_z) min_z = z;
        }
        else if(line.left(2) == "vn")
        {
            line.remove(0,2);  // remove "vn "
            QStringList vertex_normal = line.split(' ', QString::SkipEmptyParts);
            x = vertex_normal[0].toFloat();
            y = vertex_normal[1].toFloat();
            z = vertex_normal[2].toFloat();

            vertices_normal.push_back(QVector3D(x,y,z));;
        }
        else if(line.left(2) == "vt")
        {
            line.remove(0,2);
            QStringList vertex_texcoords = line.split(' ', QString::SkipEmptyParts);
            x = vertex_texcoords[0].toFloat();
            y = vertex_texcoords[1].toFloat();

            vertices_texcoords.push_back(QVector2D(x,y));
        }
        else if(line.left(2) == "f ")
        {
            line.remove(0, 1);
            QStringList face_index = line.split(' ', QString::SkipEmptyParts);

            for(int i=0; i<3; i++)
            {
                QString aVert = face_index[i];
                QStringList aVert_index = aVert.split('/');
                int v_index = aVert_index[0].toInt();
                // int t_index = aVert_index[1].toInt();
                int n_index = aVert_index[2].toInt();

                Vertex vert;
                vert.position = vertices_coords[v_index-1];
                vert.normal = vertices_normal[n_index-1];

                vertices_.push_back(vert);
            }
        }

    }

    // 归一
    float x_length = max_x - min_x;
    float y_length = max_y - min_y;
    float z_length = max_z - min_z;
    float scale_f = 1.0 / max3(x_length, y_length, z_length);
    int vert_num = vertices_coords.size();
    QVector3D center_coord = QVector3D(sum_x / vert_num, sum_y / vert_num, sum_z / vert_num);

    for(int i=0; i<vert_num; i++)
    {
        vertices_[i].position = (vertices_[i].position - center_coord) * scale_f;
    }

}
