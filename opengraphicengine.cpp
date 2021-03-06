#include "opengraphicengine.h"

#include <QDebug>
OGE::OpenGraphicEngine::OpenGraphicEngine(QWidget *parent)
    : QGLWidget(QGLFormat(), parent)
{
    #if ERRORLOG == 1
        #if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
            qInstallMessageHandler(OGE::myMessageOutput);
        #elif (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
            qInstallMsgHandler (OGE::myMessageOutput);
        #endif
    #endif
    timer = new QTimer();
    connect(timer ,SIGNAL(timeout()),this,SLOT(updateEngine()));
    timer->start(5);
    dttimer = QTime::currentTime();

}
OGE::OpenGraphicEngine::~OpenGraphicEngine()
{

}
QSize OGE::OpenGraphicEngine::sizeHint() const
{
    return QSize(800, 600);
}
void OGE::OpenGraphicEngine::mousePressEvent(QMouseEvent *event)
{
    cameras[0]->mousePressEvent(event);
}
void OGE::OpenGraphicEngine::mouseMoveEvent(QMouseEvent *event)
{
    cameras[0]->mouseMoveEvent(event);
}
void OGE::OpenGraphicEngine::wheelEvent(QWheelEvent *event)
{
    cameras[0]->wheelEvent(event);
}
void OGE::OpenGraphicEngine::keyPressEvent(QKeyEvent* event)
{
    cameras[0]->keyPressEvent(event);
}
void OGE::OpenGraphicEngine::keyReleaseEvent(QKeyEvent *event )
{
    cameras[0]->keyRelaseEvent(event);
}
void OGE::OpenGraphicEngine::initializeGL()
{
    glEnable(GL_DEPTH_TEST);        //włączamy testowanie głębokości
    glEnable(GL_CULL_FACE);         //włączamy obcinanie płaszczyzn tylnych
    glClearColor(0.3,0.7,0.8,1.0);       //ustawiamy czyszczenie bufora koloru na biały kolor
    shader.addShaderFromSourceFile(QGLShader::Vertex, ":/shaders/shaders/vertexShader.vsh");       //ładowanie i kompilowanie shaderów
    shader.addShaderFromSourceFile(QGLShader::Fragment, ":/shaders/shaders/fragmentShader.fsh");
    shader.link();
    QGLBuffer * byffer = new QGLBuffer;


    intializeOGE();
}
void OGE::OpenGraphicEngine::updateEngine()
{
    dt = dttimer.elapsed()/(double)1000;
    dttimer = QTime::currentTime();
    updateOGE(dt);
    updateGL();
}
void OGE::OpenGraphicEngine::resizeGL(int width, int height)
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
void OGE::OpenGraphicEngine::paintGL()
{
    QMatrix4x4 mMatrix;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //czyścimy bufor koloru i głębi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    models[0]->Draw(shader,pMatrix,cameras[0]->CamLookAt(),QVector3D(0.0,10.0,0.0));
    glDisable(GL_BLEND);

}
void OGE::OpenGraphicEngine::AddModel(OGE::Model *model)
{
    models.push_back(model);
}
void OGE::OpenGraphicEngine::AddCamera(OGE::Camera *camera)
{
    cameras.push_back(camera);
}
void OGE::OpenGraphicEngine::intializeOGE()
{

}
void OGE::OpenGraphicEngine::updateOGE(double dt)
{

}
