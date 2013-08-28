#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "model.h"
#include "camera.h"
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
    QSize sizeHint() const;
protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent *event);
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();

private:
        QMatrix4x4 pMatrix;             //macierz projekcji
        float height,width;         //rozmary ekranu
        Model track;        //przykładowy model
        QGLShaderProgram shader;
        Camera camera;
        double dt;
        QTimer *timer;  //timer do obsługi paintGL
        QTime dttimer;  //


protected: Q_SLOT
        void timeout();
};


#endif // MAINWINDOW_H
