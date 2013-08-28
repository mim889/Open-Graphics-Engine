#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H
#include <QMouseEvent>
#include <QPoint>
class MouseControl
{
public:
    MouseControl();
    virtual void mousePressEvent(QMouseEvent *event);
protected:
    QPoint lastMousePosition;
};

#endif // MOUSECONTROL_H
