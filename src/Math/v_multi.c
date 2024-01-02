#include "../../inc/engine.h"

t_vector v_multi(t_vector v1, t_vector v2)
{
    t_vector v;
    v.x = (v1.x * v2.x) - (v1.y * v2.y);
    v.y = 2 * (v1.x * v2.y);
    return (v);
}
