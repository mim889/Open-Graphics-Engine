#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(QGLFormat(), parent)
{
}

MainWindow::~MainWindow()
{
    
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
}
void MainWindow::paintGL()
{
    QMatrix4x4 mMatrix;                                     //macierz model
    QMatrix4x4 vMatrix;
    double distance = 0.5;
    QMatrix4x4 cameraTransformation;
    QVector3D position(10.0,0.5,0.0);
    double alpha = 0.3;
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);                  //kamera 3D
    QVector3D cameraViev = position;
    vMatrix.lookAt(position-QVector3D(distance*sin(alpha)*distance*0.5,0,distance*cos(alpha)*distance*0.5), cameraViev, cameraUpDirection);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //czyścimy bufor koloru i głębi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    track.Draw(shader,pMatrix,vMatrix,mMatrix,QVector3D(100.0,100.0,100.0));
    glDisable(GL_BLEND);
}
