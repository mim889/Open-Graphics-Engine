#include "keyboardcontrol.h"

KeyboardControl::KeyboardControl()
{
}
KeyboardControl::~KeyboardControl()
{

}

void KeyboardControl::keyRelaseEvent(QKeyEvent* event)
{
    int number = 0;
    for(int i = 0; i < KeyStack.size();i++)
    {
        if(KeyStack[i]==event->key())
            number = i;
    }
    KeyStack.removeAt(number);        //usuwamy klawisz który został naciśnięty z KeyStack
    event->accept();
}
void KeyboardControl::keyPressEvent(QKeyEvent* event)
{
    bool find = false;                    //zmienna potrzeba do sprawdzania czy klawisz jest na liście klawiszy
    for(int i = 0; i < KeyStack.size();i++)
    {
        if(KeyStack[i]==event->key())
            find = true;
    }
    if(!find) KeyStack << event->key(); //jak klawisza nie ma na liście to go tam wrzucamy
    event->accept();
}
