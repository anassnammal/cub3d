#include "../../inc/engine.h"

double v_dot(t_vector v1, t_vector v2)
{
    t_vector tmp1;
    t_vector tmp2;

    tmp1 = v_norm(v1);
    tmp2 = v_norm(v2);
    return ((tmp1.x * tmp2.x) + (tmp1.y * tmp2.y));
}