#ifndef CAMERA_H
#define CAMERA_H
#include "keyboardcontrol.h"
#include "mousecontrol.h"
#include <QtOpenGL>
#include <QVector3D>
#include <QMatrix4x4>
#include <QWidget>
#include <QEvent>

class Camera :public KeyboardControl, public MouseControl
{
public:
    Camera(QVector3D cam_position = QVector3D(0.0f,0.0f,0.0f), bool addDefaultKeys = true);
    ~Camera();
    QMatrix4x4 CamLookAt();
    void CamSetPosition(QVector3D pos);
    void CamSetyRotate(float yRoate);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void SetMouseSensitive(double Sensitive);

    void AddKeyUp(Qt::Key key);
    void AddKeyDown(Qt::Key key);
    void AddKeyRight(Qt::Key key);
    void AddKeyLeft(Qt::Key key);
    void AddKeyPlus(Qt::Key key);
    void AddKeyMinus(Qt::Key key);
    void DeleteKeyUp(Qt::Key key);
    void DeleteKeyDown(Qt::Key key);
    void DeleteKeyRight(Qt::Key key);
    void DeleteKeyLeft(Qt::Key key);
    void DeleteKeyPlus(Qt::Key key);
    void DeleteKeyMinus(Qt::Key key);


    double alpha;
    bool Cam2D;
private:
    QVector3D position;
    double beta;
    double distance;
    double MouseSensitive;
    QPoint lastMousePosition;
    QVector<Qt::Key> KeyUp,KeyDown,KeyRight,KeyLeft,KeyPlus,KeyMinus;    //klawisze do obsługi kamery

protected:


};


#endif // CAMERA_H
