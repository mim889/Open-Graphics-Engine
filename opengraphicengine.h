#ifndef OPENGRAPHICENGINE_H
#define OPENGRAPHICENGINE_H
#include "model.h"
#include "camera.h"
#include "errorlog.h"
#include <QVector>
#include <QGLWidget>
QT_BEGIN_NAMESPACE
class QGLSceneNode;
class QWindow;
QT_END_NAMESPACE

namespace OGE
{

class OpenGraphicEngine : public QGLWidget, public QGLFunctions
{
    Q_OBJECT
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

        float *vertexArray;
        float *normalArray;
        float *uvArray;

        int numTriangles;





public: Q_SLOT
        void updateEngine();
};

}
#endif // OPENGRAPHICENGINE_H
