#ifndef OPENGRAPHICENGINE_H
#define OPENGRAPHICENGINE_H
#include "model.h"
#include "camera.h"
#include "errorlog.h"
#include <QVector>
namespace OGE
{

class OpenGraphicEngine : public QGLWidget, public QGLFunctions
{
public:
    OpenGraphicEngine(QWidget *parent = 0);
    ~OpenGraphicEngine();
    void AddModel(OGE::Model *model);
    void AddCamera(Camera *camera);
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
        QVector <OGE::Model*> models;
        QVector <OGE::Camera*> cameras;
        QMatrix4x4 pMatrix;             //macierz projekcji
        float height,width;         //rozmary ekranu
        QGLShaderProgram shader;
        double dt;
        QTimer *timer;  //timer do obsługi paintGL
        QTime dttimer;  //
        virtual void intializeOGE();
        virtual void updateOGE(double dt);
protected: Q_SLOT
        void update();
};

}
#endif // OPENGRAPHICENGINE_H
