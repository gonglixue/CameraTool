#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):QOpenGLWidget(parent),
    shader_program_(0),
    VBO(QOpenGLBuffer::VertexBuffer),
    EBO(QOpenGLBuffer::IndexBuffer)
{
    v_shader_file_ = QDir::currentPath() + "/default.vert";
    f_shader_file_ = QDir::currentPath() + "/defualt.frag";
    light_pos_ = QVector3D(0, 0, 2);

    camera_ = QCamera(QVector3D(0, 0, 5));
    model_.setToIdentity();

    qDebug() << "shader path:" << v_shader_file_;
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    CleanUp();
}

QSize MyOpenGLWidget::minimumSizeHint() const
{
    return QSize(400, 400);
}
QSize MyOpenGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    projection_.setToIdentity();
    projection_.perspective(camera_.Zoom, GLfloat(w)/h, 0.01f, 100.0f);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{

}
void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{

}

void MyOpenGLWidget::CleanUp()
{
    makeCurrent();
    this->VBO.destroy();
    this->EBO.destroy();
    delete this->shader_program_;
    doneCurrent();
}

void MyOpenGLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MyOpenGLWidget::CleanUp);
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    shader_program_ = new QOpenGLShaderProgram;

}
