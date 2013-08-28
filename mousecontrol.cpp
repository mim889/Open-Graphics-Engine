#include "mousecontrol.h"

MouseControl::MouseControl()
{
}
void MouseControl::mousePressEvent(QMouseEvent *event)
{
     lastMousePosition = event->pos();
     event->accept();
}
