#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H
#include <QList>
#include <QKeyEvent>
namespace OGE
{
class KeyboardControl
{
public:
    KeyboardControl();
    ~KeyboardControl();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyRelaseEvent(QKeyEvent* event);
protected:
    QList<int> KeyStack;
};
}
#endif // KEYBOARDCONTROL_H
