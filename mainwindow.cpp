#include "mainwindow.h"

MainWindow::MainWindow()
{


}

MainWindow::~MainWindow()
{
    
}
void MainWindow::intializeOGE()
{
    OGE::Model *model = new OGE::Model("models/map.obj","models/map.mtl");
    AddModel(model);
    AddCamera(new OGE::Camera(QVector3D(0.0,0.5,0.0)));
}
void MainWindow::updateOGE(double dt)
{

}
