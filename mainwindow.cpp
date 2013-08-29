#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(QGLFormat(), parent),camera(QVector3D(0.0,0.5,0.0))
{
    timer = new QTimer();
    timer->start(5);
    connect(timer ,SIGNAL(timeout()),this,SLOT(timeout()));
    dttimer = QTime::currentTime();
}

MainWindow::~MainWindow()
{
    
}
QSize MainWindow::sizeHint() const
{
    return QSize(1080, 1890);
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    camera.mousePressEvent(event);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    camera.mouseMoveEvent(event);
}
void MainWindow::wheelEvent(QWheelEvent *event)
{
    camera.wheelEvent(event);
}
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    camera.keyPressEvent(event);
}
void MainWindow::keyReleaseEvent(QKeyEvent *event )
{
    camera.keyRelaseEvent(event);
}
void MainWindow::initializeGL()
{
    glEnable(GL_DEPTH_TEST);        //włączamy testowanie głębokości
    glEnable(GL_CULL_FACE);         //włączamy obcinanie płaszczyzn tylnych
    glClearColor(0.3,0.7,0.8,1.0);       //ustawiamy czyszczenie bufora koloru na biały kolor

    track.Load_OBJ("models/map.obj","models/map.mtl");
    shader.addShaderFromSourceFile(QGLShader::Vertex, "vertexShader.vsh");       //ładowanie i kompilowanie shaderów
    shader.addShaderFromSourceFile(QGLShader::Fragment, "fragmentShader.fsh");
    shader.link();
}
void MainWindow::timeout()
{
    updateGL();
    dt = dttimer.elapsed()/(double)1000;
    dttimer = QTime::currentTime();
}
void MainWindow::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }
    this->height = height;
    this->width = width;
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.1, 1000);     //ustawianie macierzy projekcji
    glViewport(0, 0, width, height);
    updateGL();
}
void MainWindow::paintGL()
{
    QMatrix4x4 mMatrix;                                     //macierz model

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //czyścimy bufor koloru i głębi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    track.Draw(shader,pMatrix,camera.CamLookAt(),mMatrix,QVector3D(100.0,100.0,100.0));
    glDisable(GL_BLEND);
}
