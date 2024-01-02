#include "../../inc/engine.h"

t_vector v_sub(t_vector v1, t_vector v2)
{
    t_vector v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return (v);
}
