#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "model.h"
#include "camera.h"
#include "opengraphicengine.h"
#include <QtOpenGL>
#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QMainWindow>



class MainWindow: public OGE::OpenGraphicEngine
{
public:
    MainWindow();
    ~MainWindow();
protected:
    void intializeOGE();
    void updateOGE(double dt);
private:
    //OGE::Model *model;

};


#endif // MAINWINDOW_H
