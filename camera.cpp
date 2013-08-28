#include "camera.h"
#include "help_func.h"
Camera::Camera(QVector3D cam_position, bool addDefaultKeys):

    alpha(0.0 ),
    beta (0.2),
    distance(1),
    position (cam_position),
    MouseSensitive(0.0075),
    Cam2D(false)
{
    if(addDefaultKeys)
    {
        KeyUp.push_back(Qt::Key_W);
        KeyDown.push_back(Qt::Key_S);
        KeyRight.push_back(Qt::Key_D);
        KeyLeft.push_back(Qt::Key_A);
        KeyPlus.push_back(Qt::Key_Plus);
        KeyMinus.push_back(Qt::Key_Minus);
    }
}
Camera::~Camera()
{

}
void Camera::SetMouseSensitive(double Sensitive)
{
    MouseSensitive = Sensitive;
}
void Camera::AddKeyUp(Qt::Key key)
{
    KeyUp.push_back(key);
}
void Camera::AddKeyDown(Qt::Key key)
{
    KeyDown.push_back(key);
}
void Camera::AddKeyRight(Qt::Key key)
{
    KeyRight.push_back(key);
}
void Camera::AddKeyLeft(Qt::Key key)
{
    KeyLeft.push_back(key);
}
void Camera::AddKeyPlus(Qt::Key key)
{
    KeyPlus.push_back(key);
}
void Camera::AddKeyMinus(Qt::Key key)
{
    KeyMinus.push_back(key);
}
void Camera::DeleteKeyUp(Qt::Key key)
{
    KeyUp.remove(KeyUp.indexOf(key));
}
void Camera::DeleteKeyDown(Qt::Key key)
{
    KeyDown.remove(KeyDown.indexOf(key));
}
void Camera::DeleteKeyRight(Qt::Key key)
{
    KeyRight.remove(KeyRight.indexOf(key));
}
void Camera::DeleteKeyLeft(Qt::Key key)
{
    KeyLeft.remove(KeyLeft.indexOf(key));
}
void Camera::DeleteKeyPlus(Qt::Key key)
{
    KeyPlus.remove(KeyPlus.indexOf(key));
}
void Camera::DeleteKeyMinus(Qt::Key key)
{
    KeyMinus.remove(KeyMinus.indexOf(key));
}
void Camera::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    if (event->buttons() & Qt::LeftButton)
    {
        if(alpha > 360 || alpha < -360)
        {
            alpha = 0;
        }
        alpha -= deltaX*MouseSensitive;
     lastMousePosition = event->pos();
     }
     event->accept();
}
void Camera::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    if (event->orientation() == Qt::Vertical)
    {
        if (delta < 0)
        {
            distance *= 1.1;
        } else if (delta > 0)
        {
            distance *= 0.9;
        }
    }
    event->accept();
}
QMatrix4x4 Camera::CamLookAt()
{
    float moveSpeed = 0.1;
    for(int k = 0; k < KeyStack.size();k++)
    {
        for(int i =0;i<KeyUp.size();i++)
        {
            if(KeyStack[k] == KeyUp[i])
            {
                double dx = moveSpeed*sin(alpha);      //obliczanie wektorów przesunięcia
                double dz = moveSpeed*cos(alpha);
                position.setX(position.x() + dx);           //aktualizacja pozycji
                position.setZ(position.z() + dz);
                break;
            }
        }
        for(int i =0;i<KeyDown.size();i++)
        {
            if(KeyStack[k] == KeyDown[i])
            {
                double dx = -moveSpeed*sin(alpha);      //obliczanie wektorów przesunięcia
                double dz = -moveSpeed*cos(alpha);
                position.setX(position.x() + dx);           //aktualizacja pozycji
                position.setZ(position.z() + dz);
                break;
            }
        }
        for(int i =0;i<KeyDown.size();i++)
        {
            if(KeyStack[k] == KeyLeft[i])
            {
                double dx = moveSpeed*cos(alpha);      //obliczanie wektorów przesunięcia
                double dz = moveSpeed*sin(alpha);
                position.setX(position.x() + dx);           //aktualizacja pozycji
                position.setZ(position.z() + dz);
                break;
            }
        }
        for(int i =0;i<KeyDown.size();i++)
        {
            if(KeyStack[k] == KeyRight[i])
            {
                double dx = -moveSpeed*cos(alpha);      //obliczanie wektorów przesunięcia
                double dz = -moveSpeed*sin(alpha);
                position.setX(position.x() + dx);           //aktualizacja pozycji
                position.setZ(position.z() + dz);
                break;
            }
        }
        for(int i =0;i<KeyDown.size();i++)
        {
            if(KeyStack[k] == KeyPlus[i])
            {
                distance *= 0.9;
                break;
            }
        }
        for(int i =0;i<KeyDown.size();i++)
        {
            if(KeyStack[k] == KeyMinus[i])
            {
                distance *= 1.1;
                break;
            }
        }
    }
    QMatrix4x4 cameraTransformation;
    QMatrix4x4 vMatrix;
    if(Cam2D)
    {
        QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);                       //kamera 2D widok z góry jak w gta 2
        QVector3D cameraViev = QVector3D(sin(alpha)*distance*0.5 + position.x(),beta,cos(alpha)*distance*0.5 + position.z());
        vMatrix.lookAt(position + QVector3D(0,distance+5,0), cameraViev, cameraUpDirection);
    }
    else
    {
        QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);                  //kamera 3D
        QVector3D cameraViev = position;
        vMatrix.lookAt(position - QVector3D(distance*sin(alpha)*distance*0.5,0,distance*cos(alpha)*distance*0.5), cameraViev, cameraUpDirection);
    }
    return vMatrix;
}
void Camera::CamSetyRotate(float yRoate)
{
    alpha = yRoate;
}
void Camera::CamSetPosition(QVector3D pos)
{
    position = pos;
}
