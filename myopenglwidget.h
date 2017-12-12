#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QPoint>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QVector3D>
#include <QVector2D>
#include <iostream>

#include "trimesh.h"
#include "qcamera.h"

class MyOpenGLWidget:public QOpenGLWidget, protected QOpenGLFunctions
{
        Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = 0);
    ~MyOpenGLWidget();
    void InitMeshFromFile(QString filename);
    void CleanUp();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void resizeGL(int w, int h);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent *event);
    void initializeGL();
    void paintGL();
private:
    void SetupVertexAttribs();

public:
    QString v_shader_file_;
    QString f_shader_file_;
    QCamera camera_;

private:

    QVector3D object_color_;
    QVector3D light_color_;
    QVector3D light_pos_;

    TriMesh mesh_;
    QOpenGLShaderProgram* shader_program_;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLBuffer EBO;
    GLuint model_mat_loc_;
    GLuint view_mat_loc_;
    GLuint projection_mat_loc_;
    GLuint light_pos_loc_;
    GLuint camera_pos_loc_;

    QMatrix4x4 model_;
    QMatrix4x4 view_;
    QMatrix4x4 projection_;

    QPoint mouse_last_pos_;
    int screen_width_;
    int screen_height_;


};

#endif // MYOPENGLWIDGET_H
