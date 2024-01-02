#include "../../inc/engine.h"

/*
new_x = (x * cos(θ)) − (y * sin(θ))
new_y= (x * sin(θ)) + (y * cos(θ))
*/
t_vector v_rot(t_vector v, double angle)
{
    t_vector tmp;

    tmp.x = v.x;
    tmp.y = v.y;

    v.x = (tmp.x * cos(angle * M_PI / 180)) - (tmp.y * sin(angle * M_PI / 180));
    v.y = (tmp.x * sin(angle * M_PI / 180)) - (tmp.y * cos(angle * M_PI / 180));
    return (v);
}
