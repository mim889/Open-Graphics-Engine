#include "mainwindow.h"

MainWindow::MainWindow()
{


}

MainWindow::~MainWindow()
{
    delete model;
}
void MainWindow::intializeOGE()
{
    model = new OGE::Model("models/map.obj","models/map.mtl");
    AddModel(model);
    AddCamera(new OGE::Camera(QVector3D(0.0,0.5,0.0)));
}
void MainWindow::updateOGE(double dt)
{
    model->SetPosition(model->GetPosition()+QVector3D(dt,0,0));
}
