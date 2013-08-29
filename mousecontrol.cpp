#include "mousecontrol.h"

OGE::MouseControl::MouseControl()
{
}
void OGE::MouseControl::mousePressEvent(QMouseEvent *event)
{
     lastMousePosition = event->pos();
     event->accept();
}
void OGE::MouseControl::mouseMoveEvent(QMouseEvent *event)
{

}
void OGE::MouseControl::wheelEvent(QWheelEvent *event)
{

}
