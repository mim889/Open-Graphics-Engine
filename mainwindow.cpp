#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow()
{


}

MainWindow::~MainWindow()
{

}
void MainWindow::intializeOGE()
{
   // AddModel(new OGE::Model(":models/models/spider.obj",":models/models/spider.mtl"));
    AddCamera(new OGE::Camera(QVector3D(0.0,0.5,0.0)));
    OGE::Model *model = new OGE::Model;
    model->Load_Assimp("models/CheshireCat/CheshireCat.DAE");
    AddModel(model);
}
void MainWindow::updateOGE(double dt)
{
    //model->SetPosition(model->GetPosition()+QVector3D(dt,0,0));
}
