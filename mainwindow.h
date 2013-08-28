#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "model.h"
#include <QtOpenGL>
#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QMainWindow>

class MainWindow : public QGLWidget, public QGLFunctions
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
private:
        QMatrix4x4 pMatrix;             //macierz projekcji
        float height,width;
        Model track;
        QGLShaderProgram shader;
};


#endif // MAINWINDOW_H
