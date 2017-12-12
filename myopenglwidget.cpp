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

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
{

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
    if(!shader_program_->addShaderFromSourceFile(QOpenGLShader::Vertex, v_shader_file_))
    {
        std::cerr << "unable to compile vertex shader: ";
        std::cerr << v_shader_file_.toStdString() << std::endl;
    }
    if(!shader_program_->addShaderFromSourceFile(QOpenGLShader::Fragment, f_shader_file_))
    {
        std::cerr << "unable to compile fragment shader: ";
        std::cerr << f_shader_file_.toStdString() << std::endl;
    }
    if(!shader_program_->link())
        std::cerr << "unable to link shader.\n";

    shader_program_->bind();
    this->model_mat_loc_ = shader_program_->uniformLocation("model");
    this->view_mat_loc_ = shader_program_->uniformLocation("view");
    this->projection_mat_loc_ = shader_program_->uniformLocation("projection");
    this->light_pos_loc_ = shader_program_->uniformLocation("light_pos");
    this->camera_pos_loc_ = shader_program_->uniformLocation("view_pos");

}

void MyOpenGLWidget::paintGL()
{

}

void MyOpenGLWidget::SetupVertexAttribs()
{
    this->VAO.create();
    QOpenGLVertexArrayObject::Binder VAOBinder(&this->VAO);
    this->VBO.create();
    this->EBO.create();

    VBO.bind();
    VBO.allocate(this->mesh_.Data(), this->mesh_.GetVertexNum() * sizeof(Vertex));
    EBO.bind();
    EBO.allocate(this->mesh_.Index(), this->mesh_.GetIndexNum() * sizeof(int));

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    // position
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(0));
    // normal
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    // texcoord
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texcoord)));


}
