#include "../../inc/engine.h"

t_vector v_norm(t_vector v)
{
    double len;
    len = sqrt(v.x * v.x + v.y * v.y);
    v.x /= len;
    v.y /= len;
    return (v);
}