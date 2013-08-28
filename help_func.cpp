#include "help_func.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
double degrees(float radian )            //funkcja zamieniająca kąt w radnianach na stopnie
{
    return ( 180*radian ) / Pi;
}


double radians(float degrees )       //funkcja zamieniająca kąt w stopniach na radiany
{
    return ( Pi*degrees ) / 180;
}
